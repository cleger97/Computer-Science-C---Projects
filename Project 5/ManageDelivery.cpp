// ManageDelivery.cpp
// Alex Leger
// CMSC 202 Project 5
// cleger1@umbc.edu
// Section 05

#include "ManageDelivery.h"

using namespace std;

// ManageDelivery class

// Constructor
ManageDelivery::ManageDelivery(vector<Truck<Item,MAX_CAPACITY> > truck, vector<Delivery> delivery, vector<Item> item) {
    
    
    for (unsigned int i = 0; i < delivery.size(); i++) {
        m_delivery.push_back(delivery.at(i));
    }

    cout << "Delivery loaded." << endl;
    cout << "Total deliveries: " << m_delivery.size() << endl;
    
    m_item = item;
    cout << "Item loaded." << endl;
    
    m_truck = truck;
    cout << "Truck loaded." << endl;
    

    ManageDelivery::StartDelivery();
}

// This function gets called multiple times.
// It will continue to get called until every delivery is finished.
// Then when it finishes, the program is done.
void ManageDelivery::StartDelivery() {
    // So this is the management for the deliveries
    // Must *cycle* through trucks in order to figure out which one to use

    // Load all the deliveries.

    if (m_delivery.size() == 0) {
        // If it is we're done.
        // Do done stuff.
        cout << endl << "Deliveries all finished." << endl;
        ManageDelivery::DisplayItemLeft();
        return;
    }

    for (unsigned int i = 0; i < m_truck.size(); i++) {
        // Initalize the current truck.
        Truck<Item, MAX_CAPACITY> currentTruck = m_truck.at(i);
        cout << endl << "Current truck: " << currentTruck.GetName() << endl;
        currentTruck.SetTime(currentTruck.GetTime() + 10);
        // # of items currently loaded via deliveries.
        int itemCount = 0;

        // If the current delivery list isn't empty then we add new deliveries to trucks.
        if (m_delivery.size() > 0) {
            
            while (m_delivery.size() > 0) {
                Delivery currentDelivery = m_delivery.at(0);
                // Check to see if the truck can hold this delivery.
                // If it cannot then we need to immediately exit the for loop so that no delivery is skipped.
                if ((itemCount + currentDelivery.GetNumItem() > currentTruck.GetCapacity())) break;

                // Add the # of items to the total item count of this truck.
                itemCount += currentDelivery.GetNumItem();

                // Now we need to add the delivery to the truck.
                currentTruck.AddDelivery(currentDelivery);

                // And add the items to the truck.
                for (int i = 0; i < currentDelivery.GetNumItem(); i++) {
                    Item currentItem = m_item.at(0);
                    Item i (currentItem);
                    currentTruck.AddItem(i);
                    // Output the item added.
                    cout << currentTruck.GetName() << " loaded with " << i.GetName() << "." << endl;
                    m_item.erase(m_item.begin());
                }

                // Remove this delivery from the list.
                m_delivery.erase(m_delivery.begin());
            }   

            m_truck.at(i) = currentTruck;
        } 
    }


    cout << endl << "Deliveries removed from list. Starting runs" << endl;

    // Start delivery.
    for (unsigned int i = 0; i < m_truck.size(); i++) {
        ManageDelivery::DeliverItem(i);
    }

    cout << endl << "Remaining delivery count: " << m_delivery.size() << endl;

    // Delivery should be finished. Now, we start the cycle anew.
    ManageDelivery::StartDelivery();
}

// The integer should refer to the truck that is sent.
void ManageDelivery::DeliverItem(int j) {
    cout << "Truck " << m_truck.at(j).GetName() << " has began delivering." << endl;
    m_truck.at(j).CompleteDelivery();
    cout << "Truck " << m_truck.at(j).GetName() << " has finished this cycle." << endl;
    // That's literally it.
}

void ManageDelivery::DisplayItemLeft() {
    cout << "Remaining items:" << endl;
    if (m_item.size() == 0) {
        cout << "No items left." << endl;
    }
    for (unsigned int i = 0; i < m_item.size(); i++) {
        cout << (i + 1) << ": " << m_item.at(i).GetName() << endl;
    }
}