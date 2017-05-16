/*
 *Title: Exploding Kittens Card Game
 *Date: 2/22/2017
 *Author: Nick Lawrence and Jeremy Dixon
 *Edited by Alex Leger (added new functions and variables.)
 *Description: This is the game class for the exploding kittens game
*/

#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>

// Game Constants

// Number of cards a See into the Future card can show
const unsigned int PEEK_NUM = 3;
// The number of intial cards
const int INIT_CARDS = 4;
// Name of the main deck file
const string DECK_NAME = "deck.txt";
// Name of the main bomb deck file
const string BOMB_NAME = "bomb.txt";
// Seed for the pseudo random number generator
const int RAND_SEED = 10;


class Game {
public:
	// Name - Constructor
	// Desc - Runs the game
	// Preconditions - a valid constant that holds the name of the deck file and bomb file
	// Postconditions - Runs the game
	Game();
	void SetNumPlayers(int numPlayers);
private:
	// Name - Shuffle()
	// Desc - Shuffles the cards that are currently in the deck
	// Preconditions - A deck with at least 1 card
	// Postconditions - A deck with the elements shuffled in a different order
	void Shuffle();

	// Name - Peek()
	// Desc - The Action for the See into the future card
	// Preconditions - A deck with at least 1 card
	// Postconditions - Will print the next [insert const num] card(s) in the deck
	void Peek();

	// Name - DrawCard()
	// Desc - Get the card on the top of the deck and give it to a player
	// Preconditions - At least 1 card in the deck
	// Postconditions - Returns and deletes the top card on the deck
	Card DrawCard();

	// Name - StealCard()
	// Desc - Interface for stealing cards.
	// Preconditions - Another player needs to not have lost yet.
	// Postcondition - A stolen card.
	Card StealCard();

	// Name - HandleCard()
	// Desc - Handles the last card placed by the currentPlayer
	// Preconditions - An integer number representing the currentPlayer,
	//                 a card placed on the discard pile
	// Postconditions - Handles the card according to their descriptions
	int HandleCard(int cardNum);

	// Name - GetCardFromPlayer()
	// Desc - Acquires a card from a player.
	// Preconditions - An integer representing which player is currently playing.
	// Postconditions - The card in which the player played.
	Card GetCardFromPlayer();

	// Name - GetCardFromPlayer()
	// Desc - Acquires a defuse from a player.
	// Preconditions - An integer representing which player is currently playing.
	// Postconditions - The defuse in which the player played.
	Card GetDefuseFromPlayer();

	// Name - PlayGame()
	// Desc - Runs the game
	// Preconditions - A loaded deck, all players having cards
	// Postconditions - Determine winner and print to console
	void PlayGame();

	// Name - LoadDeck()
	// Desc - Loads the cards in from a text file
	// Preconditions - A valid filepath
	// Postcondition - m_deck contains cards
	int LoadDeck(string fileName);

	// Name - AddBombCards()
	// Desc - Loads the bomb cards in from a text file,
	//        this must be separate due to the nature of the game
	// Preconditions - A valid filepath, the file must contain 1 less bomb
	//                 than the number of players
	// Postconditions - Adds the bomb cards to m_deck
	int AddBombCards(string fileName);

	// Name - Contains(int type)
	// Desc - Checks a deck for a card of the same type. Returns the index if one exists
	//        or false otherwise.
	// Preconditions - A valid comparator card.
	// Postconditions - Returns the index if the card exists or -1 otherwise.
	int Contains(int type);

	// Name - UpdatePlayer() 
	// Desc - Updates the current player.
	// Preconditions - None.
	// Postconditions - Updates the current player. Sets winner to true if there is no one left.
	void UpdatePlayer(bool &winner);

	// Name - Discard(Card c) 
	// Desc - Discards a card.
	// Preconditions - none.
	// Postconditions - adds a card to discard.
	void Discard(Card c);

	int m_cardCount; // Card count!

	int m_numPlayers;
	Player m_players[4];
	vector<Card> m_deck; //Vector holding available cards
	vector<Card> m_discard; //Vector holding cards already used

	vector<Card> m_played; // Vector holding all cards played this round
	int m_currPlayerID; // Current player (id)
	Player* m_currPlayer; // Current player
	int m_nextPlayerID; // Next player (id)
	Player* m_nextPlayer; // Next player
};

#endif /* GAME_H */
