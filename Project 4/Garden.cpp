// Garden cpp file
// Alex Leger
// Section 05
// email: cleger1@gmail.com
// Date: 4/27/2017
// Project 4: The Garden

#include "Garden.h"

// Garden constructor
// Defaults the month to 1
Garden::Garden() {
    // Garden constructor
    m_month = 1;
}

// Garden destructor
// Removes plants from vector then clears it
Garden::~Garden() {
    // Garden destructor
    vector<Plant*>::iterator plant;
    for(plant = m_garden.begin(); plant != m_garden.end(); ++plant) {
        delete (*plant);
    }
    m_garden.clear();
    return;
}

// Garden addPlant method
// Adds plant depending on type and quantity
void Garden::addPlant(int type, int quantity) {
    m_gardenSize += quantity;

    switch(type) {
        case 1: {
            for (int i = 0; i < quantity; i++) {
                Plant* p = new Flower;
                m_garden.push_back(p);
            }
            break;
        }
        case 2: {
            for (int i = 0; i < quantity; i++) {
                Plant* p = new Vegetable;
                m_garden.push_back(p);
            }
            break;
        }
        case 3: {
            for (int i = 0; i < quantity; i++) {
                Plant* p = new Tree;
                m_garden.push_back(p);
            }
            break;

        }

    }
}

// Garden tick multi method
// Calls tick() multiple times
void Garden::tick(int num) { 
    for (int i = 0; i < num; i++) {
        Garden::tick();
    }
}

// Garden tick method
// Adds one tick to every plant then couts their status
void Garden::tick() {
    cout << "It is month " << m_month << "." << endl;
    // iterate through the plants and use accordingly.
    vector<Plant*>::iterator plant;
    int i = 0;
    for(plant = m_garden.begin(); plant != m_garden.end(); plant++) {
        
        (*plant)->tick();
        Plant* p = (*plant);
        cout << ++i << ": ";
        (*p) << cout;
    }
    m_month++;
}

// m_gardenSize getter
int Garden::getSize() {
    return m_gardenSize;
}

// m_month getter
int Garden::getMonths() {
    return m_month - 1;
}