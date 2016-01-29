#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_ROOMS 7
#define MAX_CONNECTIONS 6
#define MIN_CONNECTIONS 3

// Define possible room names.
// Define possible room types.
// START_ROOM, MID_ROOM, END_ROOM

// This function concatenates two cstrings. WARNING MEMORY MUST BE DEALLOCATED BY CALLER!!!
// void concat(char *destination, char *buffer) {
//   strcat(destination, buffer);
// }



void initializeRooms() {
  char *possibleRooms[] = { "dungeon", "plover", "twisty", "Zork", "Pizza", "Crowther", "XYZZY", "bathroom", "ZELD", "bedroom" };
  char tempDirectory[200] = "siddonj.rooms.";
  int PID = getpid();
  char buffer[100];

  // Create temp directory name
  snprintf(buffer, 100, "%d", PID);         // Convert PID to string.
  strcat(tempDirectory, buffer);            // Combine PID with temporary directory name.
  printf("%s", tempDirectory);

  // Create temporary directory
  mkdir(tempDirectory);


// While loop until we get 7 rooms made.

// -Assign Room Name
// Generate random number between 0 and 9.

// Look up room name
// Check if room name has already been assigned.

// If it has generate another random value and try again.

// Else
// -Assign Room Type
// Generate random number between 0 and 2.

// Look up room type.
// If START_ROOM has been assigned generate new number.
// If END_ROOM has been assigned generate new number.

// Create 7 different room files and store them in the temporary directory. FIle name is Room Name
// ROOM NAME: [Randomly assigned]
// CONNECTION 1:
// CONNECTION 2:
// CONNECTION 3:
// ROOM TYPE: START_ROOM

// Room created increment total created counter.

// We now have 7 rooms, let's assign connections between them.

// For each room file.
// Check and see how many connections the room has, if 6 get another room.
// Generate a number between 3 and 6, thats the number of connections we will have.
// For each connection

// Generate a number between 0 and 6, thats the name of the room it will connect to.
// Find the file the room name it will connnect to in the temp directory.

// Total the number of connections in connecting room.

// If less than 6 - Make connection between rooms.
// Write connection in current room.
// Write connection in connecting room.

// Else, find new room to connect to.


// Continue loop.


// Return the starting room.

// END FUNC.
};


int main() {
  // get starting room. initializeRooms
  initializeRooms();


  // While player is not in end room.

  // Read current room file.
  // Allocate space to hold possible connections in array.
  // Prompt player with room movement options.
  // CURRENT LOCATION: [Current room]
  // POSSIBLE CONNECTIONS: [room1], [room2].
  // WHERE TO? >

  // If user enters name of room in array
  //  set current room to that room name.
  //  Increment steps taken counter.
  //  Write room name in temporary path file.

  // Else write error to user then reprompt.
  // HUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN.


  // Once in end room.
  // Print out steps taken counter.
  // Print out contents of temporary path file.




};
