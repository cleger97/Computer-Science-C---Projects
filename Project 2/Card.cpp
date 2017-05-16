// Card File
// Author: Alex Leger
// Date: 3/9/2017
// Section: 01
// Email: cleger1@umbc.edu
// Description: The card file.

#include "Card.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>

using namespace std;

// Default constructor.
Card::Card() {
    // Do nothing. Unused constructor.
}

// Initalize the card.
Card::Card(int value, string desc) {
    m_type = value;
    if (m_type > 9 or m_type < 0) {
        cout << "Invalid Card Type!" << endl;
    }
    m_desc = desc;

}

// Return the type of card.
int Card::GetType() {
    return m_type;
}

// Convert the card name and number to a string.
string Card::ToString() {
    string retVal = "";
    string sTypeApp = "";
    switch (m_type) {
        case 0: {
            sTypeApp = "Exploding Kitten: ";
            break;
        }
        case 1: {
            sTypeApp = "Defuse: ";
            break;
        }
        case 2: {
            sTypeApp = "Attack: ";
            break;
        }
        case 3: {
            sTypeApp = "Skip: ";
            break;
        }
        case 4: {
            sTypeApp = "See the Future: ";
            break;
        }
        case 5: {
            sTypeApp = "Shuffle Cards: ";
        }
    }

    retVal = sTypeApp + m_desc;
    return retVal;
}

bool Card::Equals(Card comparator) {
    return (m_type == comparator.GetType()) ? true : false;
}

