// Driver file
// Alex Leger

#include "Garden.h"
#include "driver.h"

using namespace std;

// Menu
// Prints out menu options
void menu() {
    cout << "Select an option." << endl;
    cout << "1. Plant Single Item" << endl;
    cout << "2. Plant many of Same Item" << endl;
    cout << "3. Plant a full Garden" << endl;
    cout << "4. Exit" << endl;
    return;
}

// manageMenu - takes in input as to what user wants to do 
void manageMenu(Garden& garden) {
    int input = -1;
    while (input != 4) {
        menu();
        while (input < 1 or input > 4) {
            cout << "Your choice: ";
            cin >> input;
        }
        cout << "**********************" << endl;
        
        switch (input) {
            case 1: {
                // Single garden
                singleGarden(garden);
                return; // Program ends after this
            }
            case 2: {
                // Single garden with different quantity
                int inputB = -1;
                while (inputB < 0) {
                    cout << "How many plants? ";
                    cin >> inputB;
                }
                singleGarden(garden, inputB);
                return; // Program ends after this
            }
            case 3: {
                manyGarden(garden);
                return; // Program ends after this
            }
            case 4: {
                // Exit
                return; // Program ends after this
            }
        }
    }
}

// Single garden - calls addPlant and simulateTime with a user given plant type
void singleGarden(Garden& garden, int quantity) {
    // Get the plant type.
    plantMenu();
    int input = -1;
    while (input < 1) {
        cout << "Your choice: ";
        cin >> input;
    }
    garden.addPlant(input, quantity);

    simulateTime(garden);

}

// Many garden - calls addPlant and simulateTime for all plant types
void manyGarden(Garden& garden) {
    // Plant Flower
    int input = -1;
    cout << "How many flowers would you like to plant?" << endl;
    while (input < 0) {
        cout << "Your choice: ";
        cin >> input;
    }
    garden.addPlant(1, input);

    // Plant Vegetable
    input = -1;
    cout << "How many vegetables would you like to plant?" << endl;
    while (input < 0) {
        cout << "Your choice: ";
        cin >> input;
    }
    garden.addPlant(2, input);

    // Plant trees
    input = -1;
    cout << "How many trees would you like to plant?" << endl;
    while (input < 0) {
        cout << "Your choice: ";
        cin >> input;
    }
    garden.addPlant(3, input);

    simulateTime(garden);
}

// Displays types of plants
void plantMenu() {
    cout << "Select an option." << endl;
    cout << "1. Flower" << endl;
    cout << "2. Vegetable" << endl;
    cout << "3. Tree" << endl;
    return;
}

// simulateTime - calls tick(num) for garden
void simulateTime(Garden& garden) {
    int numOfMonths = -1;
    cout << "How many months would you like to simulate?" << endl;
    while (numOfMonths < 1) {
        cout << "Enter a value (greater than 0): ";
        cin >> numOfMonths;
    }

    garden.tick(numOfMonths);

}

// main 
int main() {
    Garden plantGarden;
    cout << "Welcome to the garden!" << endl;
    cout << "**********************" << endl;
    manageMenu(plantGarden);
    cout << "Exiting the garden." << endl;
    return 0;
}