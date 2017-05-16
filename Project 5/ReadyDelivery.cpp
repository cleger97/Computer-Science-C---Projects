// ReadyDelivery.cpp
// Alex Leger
// CMSC 202 Project 5
// cleger1@umbc.edu
// Section 05

#include "ReadyDelivery.h"
#include <sstream>
#include <istream>
#include <string>

using namespace std;

// ReadyDelivery constructors

ReadyDelivery::ReadyDelivery() {
    // This should probably do nothing.
    cout << "Invalid call of ReadyDelivery" << endl;
}

// Load the three vectors with the items
// Set names and call individual functions
ReadyDelivery::ReadyDelivery(string truckFile, string deliveryFile, string itemFile) {
    m_truckFile = truckFile;
    m_deliveryFile = deliveryFile;
    m_itemFile = itemFile;

    
    LoadItem();
    cout << "Initalization of items complete." << endl;
    LoadDelivery();
    cout << "Initalization of deliveries complete." << endl;
    LoadTruck();
    cout << "Initalization of trucks complete." << endl;

    
}

// Load the truck.
void ReadyDelivery::LoadTruck() {
    // Initalize truck file.
    fstream inData (m_truckFile.c_str(), std::fstream::in);
    string inLine = "";
    while (getline(inData, inLine)) {
        istringstream parsedInput(inLine);
        string name = "";
        string temp1 = ""; // Maximum capacity of the truck.
        int capacity = 0;

        parsedInput >> name;
        parsedInput >> temp1;

        capacity = atoi(temp1.c_str());
        Truck<Item, MAX_CAPACITY> truck (name, capacity);
        m_truck.push_back(truck);

    }

    inData.close();
}

// Load the deliveries.
void ReadyDelivery::LoadDelivery() {
    // Initalize delivery list.
    fstream inData (m_deliveryFile.c_str(), std::fstream::in);
    string inLine = "";
    while (getline(inData, inLine)) {
        istringstream parsedInput(inLine);
        string name;
        string temp1; // # of items
        string temp2; // RT time
        int itemCount;
        int rtTime;

        parsedInput >> name;
        parsedInput >> temp1;
        parsedInput >> temp2;

        itemCount = atoi(temp1.c_str());
        rtTime = atoi(temp2.c_str());

        Delivery del (name, itemCount, rtTime);
        m_delivery.push_back(del);
    }

    inData.close();
}

// Load the items.
void ReadyDelivery::LoadItem() {
    // Initalize item list.
    // Create a file stream to read the items.
    fstream inData (m_itemFile.c_str(), std::fstream::in);
    string inLine = "";
    while (getline(inData, inLine)) {
        istringstream parsedInput(inLine);
        string name;
        string temp1; // Weight
        float weight;

        parsedInput >> name;
        parsedInput >> temp1;
        weight = atof(temp1.c_str());
        Item i (name, weight);
        m_item.push_back(i);
    }

    inData.close();
}

// Return the truck.
vector< Truck<Item, MAX_CAPACITY> > & ReadyDelivery::GetTruck() {
    return m_truck;
}

vector<Delivery> ReadyDelivery::GetDelivery() {
    return m_delivery;
}

vector<Item> ReadyDelivery::GetItem() {
    return m_item;
}