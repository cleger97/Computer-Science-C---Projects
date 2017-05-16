// Vegetable cpp file
// Alex Leger
// Section 05
// email: cleger1@gmail.com
// Date: 4/27/2017
// Project 4: The Garden

#include "Vegetable.h"
#include <time.h>
using namespace std;

// Vegetable constructor
Vegetable::Vegetable() {
    m_color = "Green";
}

// Vegetable fancy constructor
Vegetable::Vegetable(string color) {
    m_color = color;
}

// Vegetable death sequence
void Vegetable::die() {
    Plant::SetIsAlive(false);
}

// Vegetable harvest function
// Prints out and then dies
void Vegetable::harvest() {
    cout << "The vegetable has been harvested." << endl;
    Vegetable::die();
}

// Vegetable tick function
// Either harvests or grows if not diseased
void Vegetable::tick() {
    // Beginning of the tick
    // Vegetable is "undiseased";
    Plant::SetIsDiseased(false);
    // 20% chance to disease
    int a = rand() % 5 + 1;
    if (a == 5) {
        Plant::SetIsDiseased(true);
    }

    // Checks to see if diseased
    bool isDiseased = GetIsDiseased();
    int size = GetSize();

    if (Plant::GetIsAlive()) {
        // Harvests first
        if (size == 5) {
            harvest();
        } else {
            // If didn't harvest then apply growth tick if not diseased
            if (!isDiseased) {
                Plant::SetSize(++size);
            }
        }
    }    
    // End of the tick.
}

ostream& Vegetable::operator<<(ostream& os) {
    string pType;
    switch (Plant::GetSize()) {
        case 0: 
        case 1:
        case 2:
        case 3: {pType = "Seedling"; break;}
        case 4: {pType = "Medium-sized"; break;}
        case 5: {pType = "Fully Mature"; break;}
        default: {pType = "Error in ptype"; break;}
    }
    // Fancy if statements
    string isHarvestable = (Plant::GetSize() == 5) ? "Is Harvestable" : "Not Harvestable";
    string isAlive = (Plant::GetIsAlive()) ? "Is Alive" : "Harvested";
    string isDiseased = (Plant::GetIsDiseased()) ? "Is Diseased" : "Not Diseased";

    string add = "";
    if (Plant::GetIsAlive() == false) {
        add = "Vegetable: Harvested";
    } else {
        add = "Vegetable (" + pType + " : " + isAlive + " : " + isHarvestable + " : " + isDiseased + ")";
    }

    os << add << endl;
    return os;
}