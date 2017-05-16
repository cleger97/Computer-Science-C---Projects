// Flower cpp file
// Alex Leger
// Section 05
// email: cleger1@gmail.com
// Date: 4/27/2017
// Project 4: The Garden
#include "Flower.h" 
#include <time.h>
using namespace std;

// Flower constructor
Flower::Flower() {
    m_numPetals = 5;
    m_color = "Red";
    m_isFlowering = false;
}

// Fancy flower constructor
Flower::Flower(int numPetals, string color) {
    m_numPetals = numPetals;
    m_color = color;
    m_isFlowering = false;
}

// Flower death sequence
void Flower::die() {
    Plant::SetIsAlive(false);
    m_numPetals = 0;
}

// Flower tick method
// Flowers, drops petals or increases size if not diseased
void Flower::tick() {
    // Beginning of the tick
    // Plant is "undiseased";
    Plant::SetIsDiseased(false);
    // 20% chance to disease
    int a = rand() % 5 + 1;
    if (a == 5) {
        Plant::SetIsDiseased(true);
    }

    // Life continues.
    int size = Plant::GetSize();

    
    if (Plant::GetIsAlive()) {
        // If the plant has flowered already then it dies next tick
        if (m_numPetals == 0) {
            cout << "The flower has died." << endl;
            Flower::die();
        return;
        }
        if (m_isFlowering) {
            // If the plant is flowering then it drops its petals
            m_numPetals = 0;
            cout << "The flower drops it's petals." << endl;
            m_isFlowering = false;
        } else {
            // The plant grows.
            if (size == 3) {
                m_isFlowering = true;
            } else if (Plant::GetIsDiseased() == false) {
                Plant::SetSize(++size);
            } 
        // If the plant is diseased then nothing happens.
        }
    }
    

    // End of the tick.
}

ostream& Flower::operator<<(ostream& os) {
    string pType;
    switch (Plant::GetSize()) {
        case 0: 
        case 1: {pType = "Seedling"; break;}
        case 2: {pType = "Medium-sized"; break;}
        case 3: {pType = "Fully Mature"; break;}
        default: {pType = "Error in ptype"; break;}
    }

    // Fancy if statements
    string isAlive = (Plant::GetIsAlive()) ? "Is Alive" : "Dead";
    string isDiseased = (Plant::GetIsDiseased()) ? "Is Diseased" : "Not Diseased";
    string flowering = (m_isFlowering) ? "Is Flowering" : "Not Flowering";

    string add = "";
    if (Plant::GetIsAlive() == false) {
        add = "Flower : Dead";
    } else {
        add = "Flower (" + pType +  ": " + isAlive + " : " + flowering + " : " + isDiseased + ")";
    }

    
    os << add << endl;
    return os;

}