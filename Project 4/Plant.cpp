// Plant cpp file
// Alex Leger
// Section 05
// email: cleger1@gmail.com
// Date: 4/27/2017
// Project 4: The Garden

#include "Plant.h"


using namespace std;

// Plant Constructor and Destructor go here
// Since they're never called, then we don't need to access them
// Or define them, to be exact.

Plant::Plant() {
    srand(time(NULL));
    m_size = 0;
    m_isAlive = true;
    m_isDiseased = false;
    
}

Plant::~Plant() {

}

// m_isDiseased getter
bool Plant::GetIsDiseased() {
    return m_isDiseased;
}

// m_isAlive getter
bool Plant::GetIsAlive() {
    return m_isAlive;
}

// m_size getter
int Plant::GetSize() {
    return m_size;
}

// m_size setter
void Plant::SetSize(int size) {
    m_size = size;
}

// m_isAlive setter
void Plant::SetIsAlive(bool isAlive) {
    m_isAlive = isAlive;
}

// m_isDiseased setter
void Plant::SetIsDiseased(bool isDiseased){
    m_isDiseased = isDiseased;
}

