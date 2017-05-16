// File: proj1.cpp
// Project: 1
// Name: Alex Leger
// Date: 2/16/17
// Section: 05 (Lab)/01 (Lecture)
// Email: cleger1@umbc.edu
// Description: Manhunt! A simulator designed to allow people to search an area for a person.
// Built in array usage and management of input to allow people to do certain things.

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Global constants
// Length and Width of the maze
const int LENGTH = 10;
const int WIDTH = 10;

//--------
// Function: getInput(output, min, max)
// Precondition: A string to output and a min/max value to calibrate input.
// Postcondition: Returns an integer between the boundaries.
//--------
int getInput(string output, int min, int max);

//--------
// Function: playGame(maze, coordinates, target) 
// Precondition: A maze that has been initalized and coordinates of the target and the player.
// Postcondition: none.
//--------
void playGame(char maze[LENGTH][WIDTH], int playerCoordinates[2], int targetCoordinates[2]);

//--------
// Function: generateMaze(maze, coordinates, target)
// Precondition: A maze that has been initialized and coordinates of the target and the player.
// Postcondition: A maze that is now loaded with the player, the target and unmarked spaces
// which will be used as the game continues.
//--------
void generateMaze(char maze[LENGTH][WIDTH], int playerCoordinates[2], int targetCoordinates[2]);

//--------
// Function: checkBounds(target)
// Precondition: An array with two numbers.
// Postcondition: Returns true if the numbers (coordinates) are in bounds or false otherwise.
//--------
bool checkBounds(int targetCoordinates[2]);

//--------
// Function: searchSpot(maze, targetCoordinates, spaceCoordinates) 
// Precondition: The player is in a spot adjacent to the piece and the spot searched exists in the array.
// Postcondition: Returns either true (found target) or false (did not find target.) Will move investigator
// to the new spot if false.
//--------
bool searchSpot(char maze[LENGTH][WIDTH], int targetCoordinates[2], int spaceCoordinates[2]);

//--------
// Function: move(maze, playerCoordinates, newCoordinates)
// Precondition: An initalized maze, and the playerCoordinates must already be in bounds.
// Postcondition: Returns either true (if the spot is able to be moved to) and will move the player, or
// returns false if the spot is not within boundaries.
//--------
bool move(char maze[LENGTH][WIDTH], int playerCoordinates[2], int newCoordinates[2]);

//--------
// Function: printMaze(char[][] maze)
// Precondition: A maze that has been initialized.
// Postcondition: A printout of the maze.
//--------
void printMaze(char maze[LENGTH][WIDTH]);

//--------
// Function: dispvictory(maze, targetCoordinates)
// Precondition: Victory has been confirmed.
// Postcondition: Displays the maze and the found target.
//--------
void dispvictory(char maze[LENGTH][WIDTH], int targetCoordinates[2]);

//--------
// Function: giveHint(playerCoordinates, targetCoordinates)
// Precondition: No victory has occured (targets are on different spaces.)
// Postcondition: A (small) hint about the location of the target.
//--------
void giveHint(int playerCoordinates[2], int targetCoordinates[2]);

int main() {
  
  cout << "Welcome to the Manhunt simulation!" << endl;
  cout << "Your objective is to find a person in an area." << endl;
  
  const int startOptions = 3;
  cout << endl << "What would you like to do?" << endl;
  cout << "1. Load a game from file" << endl;
  cout << "2. Start a new game" << endl;
  cout << "3. Exit" << endl;
  int input = 0;
  
  do {
    cout << "Enter a number, between 1 and " << startOptions << ": " << endl;
    cin >> input;
  } while (input < 1 or input > startOptions);

  char maze[10][10];
  int playerCoordinates[2] = {0,0};
  int targetCoordinates[2] = {0,0};
  switch (input) {
  case 1: {
    // Load file
    const char fName[10] = "proj1.txt";
    ifstream istream;
    istream.open(fName);
    
    // These may need to be switched.
    istream >> playerCoordinates[1];
    istream >> playerCoordinates[0];
    istream >> targetCoordinates[1];
    istream >> targetCoordinates[0];
    
    istream.close();

    playGame(maze, playerCoordinates, targetCoordinates);
    
    break;
  }
  case 2: {
    // Start a new game
    cout << "New game setting selected." << endl;
    cout << "Initalizing data..." << endl << endl;

    // These may need to be switched, depending on the output of the game.
    playerCoordinates[1] = getInput("Enter the starting x of the player.", 0, WIDTH - 1);
    playerCoordinates[0] = getInput("Enter the starting y of the player.", 0, LENGTH - 1);
    
    targetCoordinates[1] = getInput("Enter the starting x of the target.", 0, WIDTH - 1);
    targetCoordinates[0] = getInput("Enter the starting y of the target.", 0, LENGTH - 1);
    
    playGame(maze, playerCoordinates, targetCoordinates); 

    break;
  }
  case 3: {
    // Exit
    cout << "Well that was quick." << endl;
    cout << "Shutting down program..." << endl;
    return 0;
  }
  default: {
    // Something broke.
    cout << "Something didn't work here." << endl;
    cout << "You inputted: " << input << endl;
    return 0;
  }
  }

  return 0;
}

// getInput
// Forcibly returns an integer value from the user within boundaries.
int getInput(string output, int min, int max) {
  int input = min - 1;
  int cycles = 0;
  do {
    if (cycles > 0) {
      cout << "Make sure your value is between " << min << " and " << max << "." << endl;
    }
    cout << output;
    cin >> input;
    cycles++;
  } while (input < min or input > max);
  return input;

}

// playGame
// The main function that runs while the game is running.
void playGame(char maze[LENGTH][WIDTH], int playerCoordinates[2], int targetCoordinates[2]) {
  cout << "Initalizing simulation..." << endl;
  generateMaze(maze, playerCoordinates, targetCoordinates);

  // Handler for the legendary "I put in the same coordinates for both" effect.
  bool didStartTogether = (targetCoordinates[0] == playerCoordinates[0]) and (targetCoordinates[1] == playerCoordinates[1]);
  if (didStartTogether) {
    cout << "The investigator started in the same spot as the target. As such, the manhunt never begins..." << endl;
    return;
  }

  int input = 0;


  do {

    printMaze(maze);

    cout << "You may either make a move, view map, or exit." << endl;
    cout << "Select your option." << endl;
    cout << "1. Move North" << endl;
    cout << "2. Move South" << endl;
    cout << "3. Move West" << endl;
    cout << "4. Move East" << endl;
    cout << "5. View Map" << endl;
    cout << "6. Exit" << endl;
    
    const int numOptions = 6;
    do {
      cout << "Enter a value between 1 and " << numOptions << ": " << endl;
      cin >> input;
    } while (input < 1 or input > numOptions);

    bool victory = false;

    switch (input) {
    case 1: {
      // Move North
      int newCoordinates[2] = {playerCoordinates[0] - 1, playerCoordinates[1]};
      bool inBounds = checkBounds(newCoordinates);
      if (inBounds) {
	      victory = searchSpot(maze, targetCoordinates, newCoordinates);
	      if (victory) {
	        cout << "Target found!" << endl;
            dispvictory(maze, targetCoordinates);
	        return;
	      } else {
	        if (move(maze, playerCoordinates, newCoordinates)) {
                giveHint(playerCoordinates, targetCoordinates);
          }  
	      }
      } else {
        cout << "Not in bounds" << endl;
      }
      break;
    }
    case 2: {
      // Move South
      int newCoordinates[2] = {playerCoordinates[0] + 1, playerCoordinates[1]};
      bool inBounds = checkBounds(newCoordinates);
      if (inBounds) {
        victory = searchSpot(maze, targetCoordinates, newCoordinates);
        if (victory) {
          cout << "Target found!" << endl;
          dispvictory(maze, targetCoordinates);
          return;
        } else {
          if (move(maze, playerCoordinates, newCoordinates)) {
            giveHint(playerCoordinates, targetCoordinates);
          } 
        }
      } else {
        cout << "Not in bounds" << endl;
      }
      break;
    } 
    case 3: {
      // Move West
      int newCoordinates[2] = {playerCoordinates[0], playerCoordinates[1] - 1};
      bool inBounds = checkBounds(newCoordinates);
      if (inBounds) {
        victory = searchSpot(maze, targetCoordinates, newCoordinates);
        if (victory) {
          cout << "Target found!" << endl;
          dispvictory(maze, targetCoordinates);
          return;
        } else {
          if (move(maze, playerCoordinates, newCoordinates)) {
            giveHint(playerCoordinates, targetCoordinates);
          } 
        }
      } else {
        cout << "Not in bounds" << endl;
      }
      break;
    }
    case 4: {
      // Move East
      int newCoordinates[2] = {playerCoordinates[0], playerCoordinates[1] + 1};
      bool inBounds = checkBounds(newCoordinates);
      if (inBounds) {
        victory = searchSpot(maze, targetCoordinates, newCoordinates);
        if (victory) {
          cout << "Target found!" << endl;
          dispvictory(maze, targetCoordinates);
          return;
        } else {
          if (move(maze, playerCoordinates, newCoordinates)) {
            giveHint(playerCoordinates, targetCoordinates);
          } 
        }
      } else {
        cout << "Not in bounds" << endl;
      }
      break;
    }
    case 5: {
      // View Map
      cout << endl;
      cout << "Map" << endl;
      cout << endl;
      printMaze(maze);
      break;
    }
    case 6: {
      // Exit
      break;
    }
    } // End Switch


  } while (input != 6);

  return;

}

// generateMaze
// The initial function to build the maze.
void generateMaze(char maze[LENGTH][WIDTH], int playerCoordinates[2], int targetCoordinates[2]) {
  for (int l = 0; l < LENGTH; l++) {
    for (int w = 0; w < WIDTH; w++) {
      if (w == playerCoordinates[1] and l == playerCoordinates[0]) {
        maze[l][w] = 'I';
      } else if (w == targetCoordinates[1] and l == targetCoordinates[0]) {
        maze[l][w] = '_';
      } else {
        maze[l][w] = '_';
      }
    }
  }
  return;
}

// checkBounds
// Returns true if in bounds or false otherwise
bool checkBounds(int newCoordinates[2]) {
  bool inBounds = (newCoordinates[0] >= 0 and newCoordinates[0] < LENGTH and newCoordinates[1] >= 0 and newCoordinates[1] < WIDTH);
  return inBounds;
}

// move
// Returns true (and moves the player) or false if the point is out of bounds.
bool move(char maze[LENGTH][WIDTH], int playerCoordinates[2], int newCoordinates[2]) {
  // True if new coordinates are in bounds, false otherwise
  bool inBounds = checkBounds(newCoordinates);
  // If the movement is in bounds then move and return true, or return false otherwise
  if (inBounds) {
    maze[playerCoordinates[0]][playerCoordinates[1]] = '*';
    maze[newCoordinates[0]][newCoordinates[1]] = 'I';
    playerCoordinates[0] = newCoordinates[0];
    playerCoordinates[1] = newCoordinates[1];
    return true;
  } else {
    return false;
  }
}

// searchSpot 
// Searches a space. Return true if target or false otherwise.
bool searchSpot(char maze[LENGTH][WIDTH], int targetCoordinates[2], int spaceCoordinates[2]) {
  //char current = maze[spaceCoordinates[0]][spaceCoordinates[1]];
  if (targetCoordinates[0] == spaceCoordinates[0] and targetCoordinates[1] == spaceCoordinates[1]) {
    return true;
  } else {
    return false;
  }
}

// printMaze
// Print out the maze.
void printMaze(char maze[LENGTH][WIDTH]) {
  for (int l = 0; l < LENGTH; l++) {
    for (int w = 0; w < WIDTH; w++) {
      cout << maze[l][w] << " ";
    }
    cout << endl;
  } 
}

// dispvictory
// Displays victory stuff.
void dispvictory(char maze[LENGTH][WIDTH], int targetCoordinates[2]) {
  maze[targetCoordinates[0]][targetCoordinates[1]] = 'T';
  printMaze(maze);
  cout << "Thank you for using the Manhunt simulation!" << endl;
}

void giveHint(int playerCoordinates[2], int targetCoordinates[2]) {
    // The design said check east-west first then north-south.
    if (targetCoordinates[1] != playerCoordinates[1]) {
        bool isLeft = (targetCoordinates[1] - playerCoordinates[1]) < 0;
        if (isLeft) {
            cout << "You may want to move west." << endl;
        } else {
            cout << "You may want to move east." << endl;
        }
    } else if (targetCoordinates[0] != playerCoordinates[0]) {
        bool isNorth = (targetCoordinates[0] - playerCoordinates[0]) < 0;
        if (isNorth) {
            cout << "You may want to move north." << endl;
        } else {
            cout << "You may want to move south." << endl;
        }
    } else {
        cout << "This statement should never be printed.";
    }


}