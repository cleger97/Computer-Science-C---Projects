// Game File
// Author: Alex Leger
// Date: 3/9/2017
// Section: 01
// Email: cleger1@umbc.edu
// Description: The game file.

#include "Game.h" 
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>

using namespace std;

// The actual game itself
// How the game will be started (and run in.)
Game::Game() {
    // Intialize stuff
    cout << "Welcome to the Exploding Kittens game!" << endl;
    cout << "Meow!" << endl << endl << endl;

    cout << "How many players are playing?" << endl;
    ostringstream oss;

    int numPlayers;
    do {
        cout << "Enter a value between 2 and 4: ";
        string temp;
        getline (cin, temp);
        numPlayers = atoi(temp.c_str());
    } while (numPlayers < 2 or numPlayers > 4);

    SetNumPlayers(numPlayers);

    // Set generic names for players
    for (int i = 0; i < numPlayers; i++) {
        string name = "Player ";
        oss << name << (i+1);
        name = oss.str();

        // Reset oss
        oss.str("");
        oss.clear();

        // Create class
        Player p(name);
        m_players[i] = p;
    }

    m_cardCount = LoadDeck(DECK_NAME);

    // Initalize player order
    m_currPlayerID = 0;
    m_nextPlayerID = 1;

    m_currPlayer = &m_players[m_currPlayerID];
    m_nextPlayer = &m_players[m_nextPlayerID];

    // They're in the play phase!
    (*m_currPlayer).SetPhase(0);

    
    // Run the game
    PlayGame();

}


// Sets the number of players in the game
// Inputs into the game itself
void Game::SetNumPlayers(int numPlayers) {
    if (numPlayers > 1) {
        m_numPlayers = numPlayers;
    } else {
        m_numPlayers = 2;
        cout << "Invalid choice; defaulting to 2 players.";
    }
    
}

// Shuffles the deck
void Game::Shuffle() {
    srand(RAND_SEED);

    vector<Card> shuffledVector (1);
    // Creates a for loop using an iterator loop and pointers on a vector
    // Will add the new values to random locations in the new vector.
    for (vector<Card>::iterator i = m_deck.begin(); i != m_deck.end(); ++i) {
        // With a minimum of zero this should always insert into something.
        if (shuffledVector.size() == 0) {
            shuffledVector.push_back((*i));
        } else {
            shuffledVector.insert(shuffledVector.begin() + (rand() % shuffledVector.size()), (*i));
        }
    }
    m_deck = shuffledVector;

    m_deck.pop_back();
}

// Peek at the next [peek num] cards
void Game::Peek() {
    for (unsigned int i = 0; i < PEEK_NUM; i++) {
        Card nextCard = m_deck.at(m_deck.size() - i - 1);
        cout << nextCard.ToString() << endl;
    }
    
}

// Draw the next card.
Card Game::DrawCard() {
    Card nextCard = m_deck.back();
    
    m_deck.pop_back();
    m_cardCount--;
    return nextCard;
}

// Steal a card.
Card Game::StealCard() {
    cout << "Select a player to steal a card from." << endl;
    for (int i = 0; i < m_numPlayers; i++) {
        if (i == m_currPlayerID) continue;
        if (m_players[i].HasLost() == true) continue;
        cout << i << ": " << m_players[i].GetName() << endl;
    }
    int select = -1;
    do {
        cout << "Select a player: ";
        cin >> select;
    } while (select < 0 or select > m_numPlayers - 1 or m_players[select].HasLost() == true);

    Player *m_selectedPlayer = &m_players[select];
    cout << "Select a card from this player: " << endl;

    int cardNum = m_selectedPlayer->GetNumberOfCards();
    for (int i = 0; i < cardNum; i++) {
        cout << i << ": Card " << i << endl;
    }

    select = -1;
    do {
        cout << "Select a card: " << endl;
        cin >> select;
    } while (select < 0 or select > cardNum - 1);

    Card retVal = m_selectedPlayer->LoseCard(select);
    return retVal;
}

// Do something with the card
// Will only call defuse if there is a bomb card
// Otherwise handles rest.
int Game::HandleCard(int cardNum) {
    switch (cardNum) {
        case 0: {
            // Bomb Card
            break;
        }
        case 1: {
            // Defuse Card
            break;  
        }
        case 2: {
            // Attack Card
            cout << "You've deployed an attack card!" << endl;
            (*m_currPlayer).SetPhase(3);
            (*m_nextPlayer).SetExtraTurn(true);
            return 1;
            break;
        }
        case 3: {
            // Skip Card
            cout << "You've deployed a skip card!" << endl;
            (*m_currPlayer).SetPhase(3);
            return 1;
            break;
        }
        case 4: {
            // See the Future (3 card reveal)
            cout << "You've seen into the future!" << endl;
            Peek();
            break;
        }
        case 5: {
            // Shuffle Deck Card
            cout << "You've decided to change the deck a bit!" << endl;
            Shuffle();
            break;
        }
        case 6: {
            // Catermelons
            cout << "You've tried to play some Catermelons!" << endl;
            int locPair = (*m_currPlayer).Contains(6);
            if (locPair != -1) {
                cout << "You've played a pair!" << endl;
                Card dispense = (*m_currPlayer).LoseCard(locPair);
                Discard(dispense);
                (*m_currPlayer).AddToHand(StealCard());
            } else {
                cout << "You don't have a pair of catermelons!" << endl;
                Card c(6, "Catermelon");
                (*m_currPlayer).AddToHand(c);
            }
            break;
        }
        case 7: {
            // Hairy Potato Cat
            cout << "You've tried to play some Hairy Potato Cats!" << endl;
            int locPair = (*m_currPlayer).Contains(7);
            if (locPair != -1) {
                cout << "You've played a pair!" << endl;
                Card dispense = (*m_currPlayer).LoseCard(locPair);
                Discard(dispense);
                (*m_currPlayer).AddToHand(StealCard());
            } else {
                cout << "You don't have a pair of hairy potato cats!" << endl;
                Card c(7, "Hairy Potato Cat");
                (*m_currPlayer).AddToHand(c);
            }
            break;
        }
        case 8: {
            // Zombie Kitten
            cout << "You've tried to play some Zombie Kittens!" << endl;
            int locPair = (*m_currPlayer).Contains(8);
            if (locPair != -1) {
                cout << "You've played a pair!" << endl;
                Card dispense = (*m_currPlayer).LoseCard(locPair);
                Discard(dispense);
                (*m_currPlayer).AddToHand(StealCard());
            } else {
                cout << "You don't have a pair of Zombie Kittens!" << endl;
                Card c(8, "Zombie Kitten");
                (*m_currPlayer).AddToHand(c);
            }
            break;
        }
        case 9: {
            // Taco Cat
            cout << "You've tried to play some Tacocats!" << endl;
            int locPair = (*m_currPlayer).Contains(9);
            if (locPair != -1) {
                cout << "You've played a pair!" << endl;
                Card dispense = (*m_currPlayer).LoseCard(locPair);
                Discard(dispense);
                (*m_currPlayer).AddToHand(StealCard());
            } else {
                cout << "You don't have a pair of Tacocats!" << endl;
                Card c(9, "Tacocat");
                (*m_currPlayer).AddToHand(c);
            }
            break;
        }
        default: {
            cout << "Error: Invalid Cat Card" << endl;
            break;
        }
    }
    return 0;
}

Card Game::GetCardFromPlayer() {
    // Prompt using hand count
    (*m_currPlayer).DisplayHand();
    int numCards = (*m_currPlayer).GetNumberOfCards();
    int value = -1;
    do {
        cout << "Select a card value: " << endl;
        string temp;
        getline(cin, temp);
        value = atoi(temp.c_str());
    } while (value < 0 or value > numCards - 1);

    return (*m_currPlayer).PlayCard(value);
    // Return the card
}

Card Game::GetDefuseFromPlayer() {
    // Prompt using hand count
    (*m_currPlayer).DisplayDefuses();
    int numCards = (*m_currPlayer).GetNumberOfCards();
    int value = -1;
    do {
        cout << "Select a card value: " << endl;
        string temp;
        getline(cin, temp);
        value = atoi(temp.c_str());
    } while (value < 0 or value > numCards - 1 or (*m_currPlayer).PreviewCard(value).GetType() != 1);

    return (*m_currPlayer).PlayCard(value);
    // Return the card
}

// Play the game.
void Game::PlayGame() {
    cout << "And the game begins. (Finished pre-game initalization.)" << endl;
    // Random glitch fix - first card not appearing
    //m_deck.pop_back();

    cout << "Dealing cards..." << endl;
    for (int i = 0; i < INIT_CARDS * m_numPlayers; i++) {
        Card draw = DrawCard();
        //cout << "Dealt card to player " << (i % m_numPlayers) + 1 << "." << endl;
        m_players[i % m_numPlayers].AddToHand(draw);
    }

    m_cardCount += AddBombCards(BOMB_NAME);

    // Random glitch fix - first card not appearing
    //m_deck.pop_back();

    cout << "Now, the fun begins! (Cards dealt and shuffled!)" << endl;
    bool hasWinner = false;

    do {
        int phase;
        do {
            phase = (*m_currPlayer).GetPhase();
            //cout << "Phase: " << phase << endl;
            cout << endl << "It is " << (*m_currPlayer).GetName() << "'s turn." << endl << endl;
            int choice = 0;
            // Get input for menu.
            if (phase == 0) {
                do {
                    cout << endl;
                    cout << "Pick an option." << endl;
                    cout << "1. View Cards" << endl;
                    cout << "2. Play a card" << endl;
                    cout << "3. Draw a card" << endl;
                    string temp;
                    cout << "Your Choice: ";
                    getline(cin, temp);
                    choice = atoi(temp.c_str());
                    cout << endl;
                } while (choice < 1 or choice > 3);
            }

            if (choice == 1) {
                cout << "Displaying hand." << endl;
                (*m_currPlayer).DisplayHand();
                phase = -1;
            } 
            if (choice == 2) {
                phase = 0;
            }
            if (choice == 3) {
                phase = 1;
            }

            switch (phase) {
            case 0: {
                // Play Card Phase
                cout << "Play a card." << endl;
                Card pCard = GetCardFromPlayer();
                int pType = pCard.GetType();
                int handler = 0;
                if (pType == 1) {
                    cout << "You can't play a defuse card here!" << endl;
                } else {
                    handler = HandleCard(pType); 
                }

                break;
            }
            case 1: {
                // Draw card phase
                cout << "Drawing a card." << endl;
                Card dCard = DrawCard();
                (*m_currPlayer).AddToHand(dCard);
                //cout << "Card Type: " << dCard.GetType() << endl;
                phase = (dCard.GetType() == 0) ? 2 : 3;
                (*m_currPlayer).SetPhase(phase);
                break;
            }
            case 2: {
                // Handle the bomb!
                if ((*m_currPlayer).Contains(1) != -1) {
                    cout << "You have drawn an exploding kitten but have a defuse! Play one!" << endl;
                    // Defuse Menu
                    Card toPlay = GetDefuseFromPlayer();
                    Discard (toPlay);
                    Card returnedBomb = (*m_currPlayer).ReturnBomb();
                    m_deck.insert(m_deck.begin() + (rand() % m_deck.size()), returnedBomb);
                    
                } else {
                    // Standard.
                    cout << "You have drawn an exploding kitten and have no defuses! You lose!" << endl;
                    (*m_currPlayer).SetLost(true);
                }
                phase = 3;
                break;
            }
            case 3: {
                // Not sure if this should ever run.
                break;
            }
            default: {
                cout << "" << endl;
                break;
            }
            } // end switch
        } while (phase != 3);

        cout << endl << "Turn end" << endl;
        cout << m_cardCount << " cards remaining." << endl;
        UpdatePlayer(hasWinner);
    } while (hasWinner == false);
    
    cout << "Winner has been found!" << endl;
    cout << (*m_currPlayer).GetName() << " wins!" << endl;

}

// Load the deck (with non-exploding kitten cards.)
int Game::LoadDeck(string fileName) {
    fstream inData (fileName.c_str(), std::fstream::in);
    string inLine = "";
    int totalCards = 0;
    while (getline(inData, inLine)) {
        // Convert inline to cstring -> convert into an integer.
        int value = atoi(inLine.c_str());
        // Get the description line.
        getline(inData, inLine);
        // Create a new card using the value and description.
        Card c (value, inLine);
        
        // Now add it to the deck.
        m_deck.push_back(c);
        totalCards++;
    }
    inData.close();
    Shuffle();
    return totalCards;
}

// Add bombs. I mean exploding kittens.
// It's quite literally as simple as the load deck with a different file.
int Game::AddBombCards(string fileName) {
    int extraCards = LoadDeck(fileName);
    Shuffle();
    return extraCards;
}

// Checks a set of cards to see if there exists a card of a specific numerical type.
int Game::Contains(int type) {
    int location = 0;
    for (vector<Card>::iterator it = m_played.begin(); it != m_played.end(); ++it) {
        if ((*it).GetType() == type) return location;
        location++;
    }
    return -1;
}

// Update player, sets winner if someone won.
void Game::UpdatePlayer(bool &winner) {
    // If they have an extra turn then we just remove that and force them to play again.
    if (m_currPlayer->HasExtraTurn()) {
        m_currPlayer->SetExtraTurn(false);
        cout << "You're not quite done yet!" << endl;
        return;
    }
    // The old "next player" is already set and verified; now we just update current player.
    m_currPlayerID = m_nextPlayerID;

    // Now we set a new, valid next player. They have to have not lost.
    do {
        m_nextPlayerID++;
        if (m_nextPlayerID > m_numPlayers - 1) {
            m_nextPlayerID = 0;
        }
        m_nextPlayer = &m_players[m_nextPlayerID];

    } while ((*m_nextPlayer).HasLost());
    
    m_currPlayer = &m_players[m_currPlayerID];
    
    // If the only valid next player is the current player than the current player wins.
    if ((*m_nextPlayer).GetName() == (*m_currPlayer).GetName()) {
        winner = true;
        return;
    }

    // Otherwise we start draw phase.
    (*m_currPlayer).SetPhase(0);

    m_played.clear();
    return;
}

// The simple way to get rid of cards, by adding them to the discard pile.
void Game::Discard(Card c) {
    m_discard.push_back(c);
    m_played.push_back(c);
}