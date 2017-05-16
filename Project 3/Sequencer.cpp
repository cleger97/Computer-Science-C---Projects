// File: Sequencer.cpp
// Name: Alex Leger
// Date: 3/30/2017
// Section: 05
// Email: cleger1@umbc.edu
// Desc: Sequencer source file

#include "Sequencer.h"

using namespace std;

// Sequencer initialization
Sequencer::Sequencer(string fileName) {
    m_fileName = fileName;
    cout << "*********************" << endl;
    cout << "*********************" << endl;
    cout << "DNA Sequencer Program" << endl;

    readFile();

    mainMenu();
}

// Sequencer destructor
Sequencer::~Sequencer() {
    
}

// Read in a file
void Sequencer::readFile() {
    ifstream inData(m_fileName.c_str());
    char next;

    cout << "Inserting nucleotides..." << endl;
    while (inData.get(next)) {
        if (next != 'G' and next != 'A' and next != 'T' and next != 'C') continue;
        // Debug!
        // cout << "Inserting nucleotide " << next << "..." << endl;

        m_dna.InsertEnd(next);
    }

    inData.close();
}

// Display main menu
void Sequencer::mainMenu() {
    int totalOptions = 5;
    int input = -1;

    do {
        cout << "*********************" << endl;
        cout << "Menu choice options: " << endl;
        cout << "1. Display Sequencer (Leading Strand)" << endl;
        cout << "2. Display Sequencer (Base Pairs)" << endl;
        cout << "3. Inventory Basic Amino Acids" << endl;
        cout << "4. Sequence entire DNA Strand" << endl;
        cout << "5. Exit DNA Sequencer" << endl;
        // menu choices here

        do {
            cout << "Select an option: ";
            cin >> input;
        } while (input < 1 or input > totalOptions);

        cout << "*********************" << endl;
        switch (input) {
            case 1: {
                m_dna.Display(1);
                break;
            }
            case 2: {
                m_dna.Display(2);
                break;
            }
            case 3: {
                cout << "Displaying basic amino acids: " << endl;
                m_dna.NumAmino("Tryptophan", "TGG");
                m_dna.NumAmino("Phenylalanine", "TTT");
                break;
            }
            case 4: {
                m_dna.Sequence();
                break;
            }
            case 5: break;
            default: break;
        }
        
    } while (input != 5);

    cout << "Exiting sequencer." << endl;
    return;
}