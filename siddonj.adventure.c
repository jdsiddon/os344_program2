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

struct Room {
  char name[100];
  char type[100];
  char filePath[100];
  int connCount;
  struct Room *connections[6];
};


struct Room* allocate() {
  struct Room *rooms = (struct Room*) malloc (7 * sizeof(struct Room));
  return rooms;
}




void initializeRooms(struct Room* rooms) {
  char *possibleRooms[] = { "dungeon", "plover", "twisty", "Zork", "Pizza", "Crowther", "XYZZY", "bathroom", "ZELD", "bedroom" };

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

    roomExists = 0;

    // Make sure room name doesn't exist.
    do {
      roomExists = 0;
      roomIndex = rand() % 10;                                // Generate random number between 0 and 9.
      strcpy(rooms[numRooms].name, possibleRooms[roomIndex]);        // Look up room name and write it to the new room.

      for(i = 0; i < numRooms; i++) {
        if(!strcmp(rooms[numRooms].name, rooms[i].name)) {           // Check if room name has already been assigned.
          roomExists = 1;
          break;                      // There already is a room with that name.
        }
      }

    } while(roomExists);

    // Room has a unique name.

    rooms[numRooms].connCount = 0;      // Intilize number of connections.

    // Set rooms file path.
    strcpy(rooms[numRooms].filePath, "");
    strcat(rooms[numRooms].filePath, "./");
    strcat(rooms[numRooms].filePath, tempDirectory);
    strcat(rooms[numRooms].filePath, "/");
    strcat(rooms[numRooms].filePath, rooms[numRooms].name);

    // Open file
    FILE *roomFile = fopen(rooms[numRooms].filePath, "w");

    // Write room name.
    fputs("ROOM NAME: ", roomFile);
    fputs(rooms[numRooms].name, roomFile);
    fputs("\n", roomFile);

    fclose(roomFile);

    numRooms++;
  }
};

void assignRoomTypes(struct Room* rooms) {
  char *possibleRoomTypes[] = { "START_ROOM", "MID_ROOM", "END_ROOM" };
  int i = 0;
  int j = 0;
  int roomIndex = 0;

  for(i = 0; i < NUM_ROOMS; i++) {
    FILE *roomFile = fopen(rooms[i].filePath, "w");          // Open room for writing.

    // Assign Room Type
    // Make sure room name doesn't exist.
    int roomType = 0;
    do {
      roomType = 0;
      roomIndex = rand() % 3;                                // Generate random number between 0 and 9.
      strcpy(rooms[i].type, possibleRoomTypes[roomIndex]);        // Look up room name and write it to the new room.

      if(!strcmp(rooms[i].type, possibleRoomTypes[0]) || !strcmp(rooms[i].type, possibleRoomTypes[2])) {    // If roomtype is start or end, make sure no others have that type.
        for(j = 0; j < NUM_ROOMS; j++) {
          if(!strcmp(rooms[i].type, rooms[j].type)) {           // Check if room name has already been assigned.
            roomType = 1;
            break;                                      // There already is a room with that name.
          }
        }
      }

    } while(roomType);

    // Set room type.
    fputs("ROOM TYPE: ", roomFile);
    fputs(rooms[i].type, roomFile);
    fputs("\n", roomFile);

    fclose(roomFile);
  }
};


void connectRooms(struct Room* rooms) {
  int i = 0;
  int j = 0;
  int randNum;
  int roomAlreadyConnected = 0;
  struct Room *sourceRoom;              // Starting room.
  struct Room *destRoom;                // Destination to connect to.

  for(i = 0; i < NUM_ROOMS; i++) {
    sourceRoom = &rooms[i];

    while(sourceRoom->connCount < MIN_CONNECTIONS) {          // Add connections to rooms when their connections are less than minimum.
      randNum = rand() % NUM_ROOMS;                           // Get random room index.
      destRoom = &rooms[randNum];                             // Assign destination room to pointer.
      roomAlreadyConnected = 0;                               // Variable to determine if the rooms are already connected.

      if(!strcmp(destRoom->name, sourceRoom->name)) {         // Room is looking at itself, return to top of to get different destination.
        continue;

      } else if(destRoom->connCount < MAX_CONNECTIONS) {      // Make sure destination room has less than maximum number of connect
        for(j = 0; j < sourceRoom->connCount; j++) {          // Make sure rooms aren't already connected, loop through each existing connection.
          if(!strcmp(destRoom->name, sourceRoom->connections[j]->name)) {         // If the connection already exists, toggle a connection indicator.
            roomAlreadyConnected = 1;
            break;                                            // Break out of for loop.
          }
        }

        if(roomAlreadyConnected > 0) {                        // Connectino already exists, return to top of while loop to fine new room to connect.
          continue;
        }

        // Connection is new, so connect rooms.
        // Link the structs together.
        destRoom->connections[destRoom->connCount] = sourceRoom;            // Link connectee back to root.
        sourceRoom->connections[sourceRoom->connCount] = destRoom;          // Link root to connectee.

        // Incrementing connection counts so we can use that number when writing to each file.
        destRoom->connCount++;                                              // Increment connection count for connectee.
        sourceRoom->connCount++;                                            // Increment connection count for rootRoom room.

        // Update destination room file with source room name.
        FILE *connectedRoom = fopen(destRoom->filePath, "a+");              // Open destination room and append to the end of file.
        fprintf(connectedRoom, "CONNECTION %d: %s\n", destRoom->connCount, sourceRoom->name);
        fclose(connectedRoom);

        // Update source room file with destination room name.
        FILE *rootRoom = fopen(sourceRoom->filePath, "a+");                 // Open the source room and append to the end of file.
        fprintf(rootRoom, "CONNECTION %d: %s\n", sourceRoom->connCount, destRoom->name);
        fclose(rootRoom);
      }
    }
  }
};

// Look up room type.


  // for(i = 0; i < NUM_ROOMS; i++) {

  //   FILE *room = fopen(filePath, "r+a");


  //   int connectionCount = 0;


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
  // return rooms; // Return array of rooms.


void deleteRooms(struct Room *rooms) {

};


int main() {
  srand(time(NULL));       // Create random seed.

  // get starting room. initializeRooms
  struct Room *rooms = NULL;
  rooms = allocate();

  initializeRooms(rooms);

  connectRooms(rooms);

  deleteRooms(rooms);

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
