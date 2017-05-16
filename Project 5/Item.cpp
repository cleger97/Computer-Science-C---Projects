// Item.cpp
// Alex Leger
// CMSC 202 Project 5
// cleger1@umbc.edu
// Section 05

#include "Item.h"

using namespace std;

// Item constructors

Item::Item() {
    m_name = "Generic Item";
    m_weight = 1.0;
}

Item::Item(string iName, float iWeight) {
    m_name = iName;
    m_weight = iWeight;
}

// Name Getter

string Item::GetName() const{
    return m_name;
}

float Item::GetWeight() const{
    return m_weight;
}
