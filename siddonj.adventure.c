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
  char *possibleRoomTypes[] = { "START_ROOM", "MID_ROOM", "END_ROOM" };
  char *createdRooms[7];

  char tempDirectory[200] = "siddonj.rooms.";
  char filePath[200] = "";
  int PID = getpid();
  char buffer[100];

  int numRooms = 0;       // Number of rooms in game created.
  int roomIndex = 0;

  int i;
  int roomExists = 0;


  int startAssigned = 0;
  int endAssigned = 0;
  int assignedRoomType = 0;

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

      // Write room name.
      fputs("ROOM NAME: ", roomFile);
      fputs(roomName, roomFile);
      fputs("\n", roomFile);

      // -Assign Room Type
      // Generate random number between 0 and 2.
      // TODO: Clean up this awful loop!
      int assignedRoomType = 0;
      char *roomType = "";
      int roomTypeIndex = 0;
      int loopDone = 0;

      do {
        roomTypeIndex = rand() % 3;

        if(roomTypeIndex == 0) {
          if(startAssigned == 0) {// If START_ROOM has been assigned generate new number.
            startAssigned = 1;
            roomType = possibleRoomTypes[roomTypeIndex];
            loopDone = 1;
            break;
          }

        } else if(roomTypeIndex == 1) {
          roomType = possibleRoomTypes[roomTypeIndex];
          loopDone = 1;
          break;

        } else if(roomTypeIndex == 2) { // If END_ROOM has been assigned generate new number.
          if(endAssigned == 0) {
            endAssigned = 1;
            roomType = possibleRoomTypes[roomTypeIndex];
            loopDone = 1;
            break;
          }
        }

      } while(loopDone == 0);

      printf("%s", roomType);

      fputs("ROOM TYPE: ", roomFile);
      fputs(roomType, roomFile);
      fputs("\n", roomFile);

      fclose(roomFile);
      numRooms++;

    }
  }
// Look up room type.


// Create 7 different room files and store them in the temporary directory. FIle name is Room Name
// ROOM NAME: [Randomly assigned]
// CONNECTION 1:
// CONNECTION 2:
// CONNECTION 3:
// ROOM TYPE: START_ROOM

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
