// Tree cpp file
// Alex Leger
// Section 05
// email: cleger1@gmail.com
// Date: 4/27/2017
// Project 4: The Garden

#include "Tree.h"
#include <time.h>

using namespace std;

// Tree constructor
Tree::Tree() {
    // do nothing
}

// Tree destructor
// Destroys fruit
Tree::~Tree() {
    Tree::ClearFruit();
}

// Tree death sequence
void Tree::die() {
    Plant::SetIsAlive(false);
}

// Tree fruit destroyer method
void Tree::ClearFruit() {
    // Clearing the fruit    
    // Via iterator
    vector<Fruit*>::iterator fruit;
    for(fruit = m_fruit.begin(); fruit != m_fruit.end(); ++fruit) {
        delete (*fruit);
    }
    m_fruit.clear();
    return;
}

// Tree tick method
// Adds size and adds a fruit every month if older than 36 months
// Dies at 120 months
void Tree::tick() {
    // Beginning of the tick
    // Tree is "undiseased";
    Plant::SetIsDiseased(false);
    // 20% chance to disease
    int a = rand() % 5 + 1;
    if (a == 5) {
        Plant::SetIsDiseased(true);
    }

    // Checks to see if diseased
    int size = GetSize();

    if (Plant::GetIsAlive()) {
        if (Plant::GetIsDiseased() == false) {
            // If older than 36 months add a fruit to the tree
            if (Plant::GetSize() / 12 >= 3) {
                Fruit* f = new Fruit;
                m_fruit.push_back(f);
            }
            Plant::SetSize(++size);
        }

        if (Plant::GetSize() > 120) {
            // Tree dies. RIP
            cout << "The tree withers away." << endl;
            Tree::die();
        }
    }
    

    
}

ostream& Tree::operator<<(ostream& os) {
    int treeStatus = Plant::GetSize() / 12;
    string pType;
    if (treeStatus < 3) {
        switch (treeStatus) {
        case 0: { pType = "Seedling"; break;}
        case 1: { pType = "Sapling"; break;}
        case 2: { pType = "Pole"; break;}
        default: {pType = "Error in ptype"; break;}
        }
    } else {
        pType = "Mature";
    }
    // Fancy if statements
    string isAlive = (Plant::GetIsAlive()) ? "Is Alive" : "Dead";
    string isDiseased = (Plant::GetIsDiseased()) ? "Is Diseased" : "Not Diseased";
    string isFruiting = (treeStatus > 3) ? "Fruiting" : "Not Fruiting";

    string add = "";
    if (Plant::GetIsAlive() == false) {
        // If the tree is dead then we don't display any stats
        add = "Tree : Withering (dead)";
    } else {
        add = "Tree (" + pType + " : " + isAlive + " : " + isFruiting + " : " + isDiseased + ")";
    }
    
    os << add << endl;
    return os;
}

