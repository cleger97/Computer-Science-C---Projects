// Fruit cpp file
// Alex Leger
// Section 05
// email: cleger1@gmail.com
// Date: 4/27/2017
// Project 4: The Garden
#include "Fruit.h"
#include <cstdlib>
using namespace std;


Fruit::Fruit() {
    srand(10);

    // Generate random color!
    int rColor = rand() % 7;
    switch (rColor) {
        case 0: {m_color = "Red"; break;}
        case 1: {m_color = "Blue"; break;}
        case 2: {m_color = "Green"; break;}
        case 3: {m_color = "Indigo"; break;}
        case 4: {m_color = "Violet"; break;}
        case 5: {m_color = "Teal"; break;}
        case 6: {m_color = "Orange"; break;}
        default: {m_color = "Error in color"; break;}
    }

}

string Fruit::GetColor() {
    return m_color;
}