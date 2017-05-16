// Tqueue.h
// Alex Leger
// CMSC 202 Project 5
// cleger1@umbc.edu
// Section 05

#ifndef TQUEUE_H
#define TQUEUE_H

#include <iostream>
#include <cstdlib>
using namespace std;

template <class T, int N>
class Tqueue {
public:
  //Name: Tqueue - Default Constructor
  //Precondition: None (Must be templated)
  //Postcondition: Creates a queue using dynamic array
  Tqueue(); //Default Constructor
  //Name: Copy Constructor - Not used but required for project 5
  //Precondition: Existing Tqueue
  //Postcondition: Copies an existing Tqueue
  Tqueue( const Tqueue<T,N> &x ); //Copy Constructor
  //Name: Destructor
  //Precondition: Existing Tqueue
  //Postcondition: Destructs existing Tqueue
  ~Tqueue(); //Destructor
  //Name: enqueue
  //Precondition: Existing Tqueue
  //Postcondition: Adds item to back of queue
  void enqueue(T data); //Adds item to queue (to back)
  //Name: dequeue
  //Precondition: Existing Tqueue
  //Postcondition: Removes item from front of queue
  void dequeue(T &); //Removes item from queue (from front)
  //Name: queueFront
  //Precondition: Existing Tqueue
  //Postcondition: Retrieve front (does not remove it)
  void queueFront(T &);    // Retrieve front (does not remove it)
  //Name: isEmpty
  //Precondition: Existing Tqueue
  //Postcondition: Returns 1 if queue is empty else 0
  int isEmpty(); //Returns 1 if queue is empty else 0
  //Name: isFull
  //Precondition: Existing Tqueue
  //Postcondition: Returns 1 if queue is full else 0
  int isFull(); //Returns 1 if queue is full else 0
  //Name: Overloaded assignment operator - Not used but required for project 5
  //Precondition: Existing Tqueue
  //Postcondition: Sets one Tqueue to same as a second Tqueue using =
  Tqueue<T,N>& operator=( const Tqueue<T,N>& y); //Overloaded assignment operator for queue
private:
  T* m_data; //Data of the queue (Must be dynamically allocated array)
  int m_front; //Front of the queue
  int m_back; //Back of the queue
};

//**** Add class definition below ****
  // Constructor for tqueue
  template <class T, int N>
  Tqueue<T,N>::Tqueue() {
    m_data = new T[N]();
    m_front = 0;
    m_back = 0;
  }

  // Copy constructor for tqueue
  template <class T, int N>
  Tqueue<T,N>::Tqueue(const Tqueue<T,N> &x) {
      if (this == &x) return;

      m_data = new T[N]();
      //cout << "Allocating Copy data" << endl;

      *m_data = *x.m_data;
      m_front = x.m_front;
      m_back = x.m_back;
  }

  // Destructor for tqueue
  template <class T, int N>
  Tqueue<T,N>::~Tqueue() {
    delete [] m_data;
  }

  // Enqueue operator
  template <class T, int N>
  void Tqueue<T,N>::enqueue(T data) {
    // Add one to back -> add data to new back spot
    m_data[m_back] = data;
    m_back++;
  }

  // Dequeue operator
  template <class T, int N>
  void Tqueue<T,N>::dequeue(T& data) {
    T retData = m_data[m_front];

    if (m_back != 0) {
      // Shift everything up one position
      for (int i = 0; i < m_back - 1; i++) {
        m_data[i] = m_data[i+1];
      }
      
      // Since the back is now nonexistant we can shift the back spot up one
      m_back--;
    }
    

    data = retData;
    return;
  }

  // Gets front value
  template <class T, int N> 
  void Tqueue<T,N>::queueFront(T& obj) {
    obj = m_data[m_front];
  }

  // IsEmpty check
  template <class T, int N>
  int Tqueue<T,N>::isEmpty() {
    return (m_back == 0) ? 1 : 0;
  }

  // IsFull check
  template <class T, int N>
  int Tqueue<T,N>::isFull() {
    return (m_front == 0 and m_back == N - 1) ? 1 : 0;
  }
  
  // Overloaded equal sign operator
  template <class T, int N>
  Tqueue<T,N>& Tqueue<T,N>::operator=( const Tqueue<T,N>& y) {
    if (this != &y) {
      Tqueue<T,N> temp (y);
      // wipe out old data (correctly.)

      delete [] m_data;
      
      // add new data
      m_data = new T[N]();
      m_front = y.m_front;
      m_back = y.m_back;
      *m_data = *y.m_data;
    }
    

    return (*this);
  }
#endif
