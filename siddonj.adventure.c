#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_ROOMS 7
#define MAX_CONNECTIONS 6
#define MIN_CONNECTIONS 3

// Define possible room names.
// Define possible room types.
// START_ROOM, MID_ROOM, END_ROOM


void initializeRooms() {
  char *possibleRooms[] = { "dungeon", "plover", "twisty", "Zork", "Pizza", "Crowther", "XYZZY", "bathroom", "ZELD", "bedroom" };
  char *createdRooms[7];

  char tempDirectory[200] = "siddonj.rooms.";
  char filePath[200] = "";
  int PID = getpid();
  char buffer[100];

  int numRooms = 0;       // Number of rooms in game created.
  int roomIndex = 0;

  int i;
  int roomExists = 0;

  // Create temp directory name
  snprintf(buffer, 100, "%d", PID);         // Convert PID to string.
  strcat(tempDirectory, buffer);            // Combine PID with temporary directory name.
  printf("%s", tempDirectory);

  // Create temporary directory
  mkdir(tempDirectory);


// While loop until we get 7 rooms made.
  while(numRooms < NUM_ROOMS) {
    strcpy(filePath, "");               // Clear file path.
    strcat(filePath, "./");               // Apend current directory to beginning.
    strcat(filePath, tempDirectory);      // Add path to temporary folder.
    strcat(filePath, "/");                // Add trailing slash.


    roomExists = 0;
// -Assign Room Name
    // Generate random number between 0 and 9.
    roomIndex = rand() % 10;
    // printf("Room Index: %d", roomIndex);

    // Look up room name and store address to name in created room array.
    char *roomName = possibleRooms[roomIndex];

    // Make sure room doesn't exist.
    for(i = 0; i < numRooms; i++) {
      if(!strcmp(roomName, createdRooms[i])) {
        //printf("roomName: %s, createdRooms: %s\n", roomName, createdRooms[i]);
        roomExists = 1;
        break;
      }
    }

    // Check if room name has already been assigned.
    if(roomExists) {   // If it has generate another random value and try again.
      continue;

    } else {          // Room doesn't exist.
      createdRooms[numRooms] = possibleRooms[roomIndex];        // Add room name to 'selected room name array'.

      // Open file
      strcat(filePath, createdRooms[numRooms]);            // Combine PID with temporary directory name.
      printf("%s\n", filePath);
      FILE *roomFile = fopen(filePath, "w");
      fclose(roomFile);
// Else
// -Assign Room Type
// Generate random number between 0 and 2.
  // while()
      // int roomType = rand() % 3;

      // if(roomType == 1) {
      //   startAssigned = 1;
      //   continue;
      // } else if(roomType == 3) {
      //   endAssigned = 1;
      //   continue;
      // }


      numRooms++;
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
    }
  }


  for(i = 0; i < NUM_ROOMS; i++) {
    printf("Room: %s\n", createdRooms[i]);

  }

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
  srand(time(NULL));       // Create random seed.

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
