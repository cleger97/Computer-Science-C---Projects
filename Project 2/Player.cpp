//Player File
// Author: Alex Leger
// Date: 3/9/2017
// Section: 01
// Email: cleger1@umbc.edu
// Description: The card file.

#include <stdio.h>
#include <iostream>
#include <vector>
#include "Player.h"

using namespace std;

// Default constructor
Player::Player() {
    // Do nothing. Unused constructor.
}

// Create a player with a name, an empty hand, and a deck. Did not lose yet so set lost to false.
Player::Player(string name) {
    m_name = name;
    // Not sure what to do about deck yet
    SetLost(false);
}

// Preview Card
Card Player::PreviewCard(int index){
    Card toReturn = m_hand.at(index);
    return toReturn;
}

// Returns the card being played.
Card Player::PlayCard(int index) {
    Card toReturn = m_hand.at(index);
    m_hand.erase(m_hand.begin() + index);
    return toReturn;
}

// Lose a card and return it
Card Player::LoseCard(int index) {
    Card toReturn = m_hand.at(index);
    m_hand.erase(m_hand.begin() + index);
    return toReturn;
}

// Returns if player lost
bool Player::HasLost() {
    return m_lost;
}

// Returns if the player has cards
bool Player::HasCards() {
    return (m_hand.size() == 0) ? false : true;
}

// Returns if the player is assigned an extra turn
bool Player::HasExtraTurn() {
    return m_extraTurn;
}

// Adds a card to hand - returns integer value of result
int Player::AddToHand(Card card) {
    int cardValue = card.GetType();
    switch (cardValue) {
        case 0: {
            // It's an exploding kitten!!
            m_hand.push_back(card);
            return 0;
            // If I get a compiler error it's probably *right* here.
            break;
        }
        default: {
            // It's literally anything else.
            m_hand.push_back(card);
            return 1;
            // Or here.
            break;
        }
    }
}

// Get the player name
string Player::GetName() {
    return m_name;
}

// Print out hand
void Player::DisplayHand() {
    // Iterator for loop for vector cards
    int iterator = 0;
    for (vector<Card>::iterator pCard = m_hand.begin(); pCard != m_hand.end(); ++pCard) {
        cout << iterator << ": " << (*pCard).ToString() << endl;
        iterator++;
    }
    return;
}

// Defuse Menu
void Player::DisplayDefuses() {
    // Iterator for loop for vector cards
    int iterator = 0;
    for (vector<Card>::iterator pCard = m_hand.begin(); pCard != m_hand.end(); ++pCard) {
        if ((*pCard).GetType() == 1) {cout << iterator << ": " << (*pCard).ToString() << endl;}
        iterator++;
    }
    return;
}


int Player::GetNumberOfCards() {
    return m_hand.size();
}

// Returns the bomb.
Card Player::ReturnBomb() {
    // Delete index of bomb
    Card bombCard;
    int index = 0;
    int counter = 0;
    for (vector<Card>::iterator pCard = m_hand.begin(); pCard != m_hand.end(); ++pCard) {
        counter++;
        if ((*pCard).GetType() == 0) {
            bombCard = (*pCard);
            index = counter;
        }
    }
    // Return bomb
    m_hand.erase(m_hand.begin() + index);
    return bombCard;
}

// Set lost status
void Player::SetLost(bool value) {
    m_lost = value;
}

// Set extra turn status
void Player::SetExtraTurn(bool value) {
    m_extraTurn = value;
}

// Checks deck to see if a card exists
int Player::Contains(int type) {
    int location = 0;
    for (vector<Card>::iterator it = m_hand.begin(); it != m_hand.end(); ++it) {
        if ((*it).GetType() == type) return location;
        location++;
    }
    return -1;
}

// Set phase of turn
void Player::SetPhase(int type) {
    m_phase = type;
    if (type > 3 or type < 0) {
        cout << "Invalid phase!" << endl;
    }
}

int Player::GetPhase() {
    return m_phase;
}