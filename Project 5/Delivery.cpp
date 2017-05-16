// Delivery.cpp
// Alex Leger
// CMSC 202 Project 5
// cleger1@umbc.edu
// Section 05


#include "Delivery.h"

using namespace std;

// Delivery constructor

Delivery::Delivery() {
    m_name = "Generic Name";
    m_numItem = 1;
    m_rtMinute = 1;
}

Delivery::Delivery(string name, int numItem, int rtMinute) {
    m_name = name;
    m_numItem = numItem;
    m_rtMinute = rtMinute;
}

// Getters 

string Delivery::GetName() const{
    return m_name;
}

int Delivery::GetNumItem() const{
    return m_numItem;
}

int Delivery::GetRTMinute() const{
    return m_rtMinute;
}