/*There are a number of optional functions in Truck.h. 
This is because you may want to implement the management of the trucks in a variety of ways. 
Trucks are kind of complex so it is up to you as to how you want to implement them. 
If you don't use a function, just stub it out and include a quick comment.
*/

// Truck.h
// Alex Leger
// CMSC 202 Project 5
// cleger1@umbc.edu
// Section 05

#ifndef TRUCK_H
#define TRUCK_H

#include "Item.h"
#include "Tqueue.h"
#include "Delivery.h"

#include <vector>
using namespace std;

template <class T, int N>
class Truck {
 public:
  //Name: Truck(string, int) Overloaded constructor.
  //Precondition: Requires truck file has been loaded
  //Postcondition: Builds a new templated truck
  Truck(string inName, int capacity);

  //Name: Destructor
  //Precondition: Requires truck file has been loaded
  //Postcondition: Destroys everything in truck

  // Not necessary (no dynamic memory used.)
  //~Truck();

  //Name: GetItems (optional)
  //Precondition: Requires that the truck's item queue has been populated
  //Postcondition: Templated accessor for this truck's cargo
  Tqueue<T,N> GetItems() const;

  //Name: GetItemAt (optional)
  //Precondition: Requires that the truck's item queue has been populated
  //Postcondition: Templated accessor for this truck's cargo at a specific location

  // This function seemed to have very confusing implementation, so it wasn't worth using.
  //const T& GetItemAt(int index) const;

  //Name: AddItem (optional)
  //Precondition: Requires that the trucks have been loaded
  //Postcondition: Adds item into this truck
  void AddItem(T inputObject);

  //Name: DeliverItemFromTruck (optional)
  //Precondition: Requires that the trucks have been loaded
  //Postcondition: Delivers item from this truck to customer
  void DeliverItemFromTruck();  

  //Name: AddDelivery (optional)
  //Precondition: Requires that all deliveries have been input and trucks
  //Postcondition: Used to add deliveries for specific trucks
  void AddDelivery(Delivery&);

  //Name: CompleteDelivery (optional)
  //Precondition: Requires that deliveries have been assigned to this truck
  //Postcondition: Removes current deliveries from this truck
  void CompleteDelivery();

  //Name: GetDeliveryAt (optional)
  //Precondition: Requires that this truck has at least 1 delivery assigned to it
  //Postcondition: Used to return a specific delivery
  Delivery& GetDeliveryAt(int index);

  //Name: GetDelivery (optional)
  //Precondition: Requires deliveries have been asssigned to this truck
  //Postcondition: Used to return the entire vector of deliveries
  vector<Delivery> GetDelivery() const;
 
  //Name: GetTime (optional)
  //Precondition: None
  //Postcondition: Used to return current time for a specific truck
  int GetTime(); 

  //Name: SetTime (optional)
  //Precondition: None
  //Postcondition: Used to set time for a specific truck
  void SetTime(int time);

  //Name: GetCapacity (optional)
  //Precondition: Requires that the trucks have been loaded
  //Postcondition: Used to access the capacity of a truck
  int GetCapacity() const;

  //Name: GetName (optional)
  //Precondition: Requires that the trucks have been loaded
  //Postcondition: Used to access the name of a truck
  string GetName() const;

private:
  string m_name;
  int m_capacity;
  int m_time;
  vector<Delivery> m_curDelivery;
  Tqueue<T,N> m_item;	
};
//Implement the class definition below

template <class T, int N>
Truck<T,N>::Truck(string inName, int capacity) {
    m_name = inName;
    m_capacity = capacity;
    m_time = 0;

}

// Truck destructor
// Delete the Tqueue
//Truck<T,N>::~Truck() {

//}

// Getter for the items
// (Note for whoever grades: GetItem isn't correct, as there's multiple items, so the header now says GetItems())
template <class T, int N> 
Tqueue<T,N> Truck<T,N>::GetItems() const{
    return m_item;
}

// Add an item to the truck.
template <class T, int N>
void Truck<T,N>::AddItem(T item) {
    m_item.enqueue(item);
}

// Deliver a singular item.
template <class T, int N>
void Truck<T,N>::DeliverItemFromTruck() {
    // Dequeue the current item.
    T currentItem;
    m_item.dequeue(currentItem);
    // Output the item (not required).
}


// Add a delivery to the truck
template <class T, int N>
void Truck<T,N>::AddDelivery(Delivery& delivery) {
    m_curDelivery.push_back(delivery);
    cout << "Added delivery " << m_curDelivery.size() << "." << endl;
}

// Complete the current delivery
template <class T, int N>
void Truck<T,N>::CompleteDelivery() {
    if (m_curDelivery.size() == 0) {
      cout << "No deliveries." << endl;
      return;
    }

    while (m_curDelivery.size() > 0) {

      Delivery currentDelivery = m_curDelivery.at(0);

      Truck::SetTime(Truck::GetTime() + currentDelivery.GetRTMinute());

      // Deliver items.
      for (int i = 0; i < currentDelivery.GetNumItem(); i++) {
          DeliverItemFromTruck();
      }
      cout << endl << "Delivery complete!" << endl;
      cout << "Delivery time: " << Truck::GetTime() << endl;
      cout << "Delivery for: " << currentDelivery.GetName() << endl;
      cout << "Delivered: " << currentDelivery.GetNumItem() << " items." << endl;

      m_curDelivery.erase(m_curDelivery.begin() + 0);
    }
    
    return;
}

// Getter for a delivery at a certain location
template <class T, int N>
Delivery& Truck<T,N>::GetDeliveryAt(int index) {
    return m_curDelivery.at(index);
}

// Get the current delivery time for this truck
// This should return the total time at the beginning and 0 at the end
template <class T, int N>
int Truck<T,N>::GetTime() {
    return m_time;
}

// Set the current delivery time for this truck
// This can be changed by a certain time depending on the current delivery 
template <class T, int N>
void Truck<T,N>::SetTime(int time) {
    m_time = time;
}

// Get capacity of the truck
template <class T, int N>
int Truck<T,N>::GetCapacity() const{
    return m_capacity;
}

// Get truck name
template <class T, int N>
string Truck<T,N>::GetName() const{
    return m_name;
}

#endif
