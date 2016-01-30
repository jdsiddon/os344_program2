#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

#define NUM_ROOMS 7
#define MAX_CONNECTIONS 6
#define MIN_CONNECTIONS 3

// Struct to hold room data.
struct Room {
  char name[100];
  char type[100];
  char filePath[100];
  int connCount;
  struct Room *connections[6];
};

// This function gets called to allocate enough space to hold the number rooms that will be used to play.
struct Room* allocate() {
  struct Room *rooms = (struct Room*) malloc (NUM_ROOMS * sizeof(struct Room));
  return rooms;
}

typedef struct Room Room;


// This function gets called to initialize each room with a unique room name and create each room's text file with their room name.
void initializeRooms(struct Room* rooms, char *tempDirectory) {
  char *possibleRooms[] = { "dungeon", "plover", "twisty", "Zork", "Pizza", "Crowther", "XYZZY", "bathroom", "ZELD", "bedroom" };
  int numRooms = 0;       // Number of rooms in game created.
  int roomIndex = 0;
  int i;
  int roomExists = 0;
  int startAssigned = 0;
  int endAssigned = 0;
  int assignedRoomType = 0;

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
  int startSet = 0;
  int endSet = 0;

  struct Room *currentRoom;
  struct Room *otherRoom;

  for(i = 0; i < NUM_ROOMS; i++) {
    currentRoom = &rooms[i];

    // Assign Room Type
    // Make sure room name doesn't exist.
    int roomType = 0;
    do {
      roomIndex = rand() % 3;                                                   // Generate random number between 0 and 2.
      // printf("\n%d\n", roomIndex);
      if((roomIndex == 0 && !startSet) || (roomIndex == 2 && !endSet)) {                                    // If the selected room type was start or end.
        if(roomIndex == 0)
          startSet = 1;
        if(roomIndex == 1)
          endSet = 1;

      }
      // As long as roomType is set to 1, we will keep assigning room type until a valid type is assigned.
      strcpy(currentRoom->type, possibleRoomTypes[roomIndex]);                  // Look up room name and write it to the new room.

    } while(!startSet && !endSet);                              // Keep looping while room is of dupe start/end type
                                                                              // and start and end aren't set.

    // Save room type to room file.
    FILE *roomFile = fopen(currentRoom->filePath, "a+");                        // Open room for writing.
    fprintf(roomFile, "ROOM TYPE: %s\n", currentRoom->type);                    // Write type to file.
    fclose(roomFile);                                                           // Close file.
  }
};

// This function connects each room in rooms to one another. It makes sure that
// The two rooms are linked together. e.g., Room A connects to Room B and Room B connects to Room A.
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



void deleteRooms(struct Room *rooms) {
  free(rooms);
  rooms = 0;
};


Room* setStartRoom(struct Room* rooms, char *tempDirectory) {
  int i = 0;
  struct Room *currRoom;
  char pathFileLocation[100];

  for(i = 0; i < NUM_ROOMS; i++) {
    currRoom = &rooms[i];

    if(!strcmp(currRoom->type, "START_ROOM")) {
      break;
    }
  }

  strcpy(pathFileLocation, "./");
  strcat(pathFileLocation, tempDirectory);
  strcat(pathFileLocation, "/path");              // Set file to record users path.
  printf(pathFileLocation);
  FILE *pathFile = fopen(pathFileLocation, "a+");
  fputs(currRoom->name, pathFile);
  fclose(pathFile);

  return currRoom;
};

void printRoomOptions(struct Room *room) {
  char buffer[100];
  char *lineElements;
  int elem = 0;
  int lines = 0;
  int lineCount = 0;
  int c;
  FILE *roomFile = fopen(room->filePath, "r");                // Open file for reading.

  // Determine number of lines in file so we know where to start and stop reading from it.
  do {
    c = fgetc(roomFile);                                      // Get a character from file.
    if(c == '\n')                                             // If that character = a new line then we know we have a line.
      lines++;                                                // Increments line counter.
  } while(c != EOF);

  fseek(roomFile, 0, SEEK_SET);                               // Reset read position to beginning of file.

  while(fgets(buffer, 100, roomFile) != NULL) {               // Read through each line in the file.
    lineCount++;
    lineElements = strtok(buffer, ":");                       // Divide line up by ":" symbol.
    elem = 1;                                                 // elem 1 is left-side of : elem 2 is right-side.

    while(lineElements != NULL) {                             // Loop through the two elements.
      if(elem == 2) {                                         // Only print out the 2nd element in each line (data).
        if (lineCount == 1) {
          printf("CURRENT LOCATION:%s", lineElements);
          printf("POSSIBLE CONNECTIONS:");
        } else if(lineCount >= 2 && lines > lineCount) {      // Only print out from 2nd to end-1 lines.
          lineElements[strcspn(lineElements, "\n")] = 0;      // Pull out newline, strcspn grabs the string chunk that is not in "\n"
          printf(",%s", lineElements);
        }
      }

      elem++;
      lineElements = strtok(NULL, ":");                       // Get next element.
    }

  }
  fclose(roomFile);
};

Room* getUserChoice(struct Room* room, char *pathFileLocation) {
  int i = 0;
  int roomValid = 0;
  struct Room *newRoom;
  char buffer[100];
  char path[100];


  do {
    printf("\nWHERE TO?>");
    fgets(buffer, 100, stdin);
    buffer[strcspn(buffer, "\n")] = 0;                        // Pull out newline character from user entered string so string match can work.

    // Loop through each connection room has.
    for(i = 0; i < room->connCount; i++) {
      if(!strcmp(room->connections[i]->name, buffer)) {       // If the user-entered string matches a connection, go to that room.
        newRoom = room->connections[i];                      // Set new room.
        // Write new room
        // printf(pathFileLocation);
        // FILE *pathFile = fopen(pathFileLocation, "a+");
        // fprintf(pathFile, "%s", newRoom->name);
        // fputs("t", pathFile);
        // fclose(pathFile);
        strcpy(path, "./");
        strcat(path, pathFileLocation);
        strcat(path, "/path");              // Set file to record users path.
        FILE *pathFile = fopen(path, "a+");
        fputs(newRoom->name, pathFile);
        fclose(pathFile);
        // printf("%s\n", path);
        roomValid = 1;
      }
    }
  } while(!roomValid);


  return newRoom;
};


int main() {
  char buffer[100];
  int PID = getpid();
  char tempDirectory[200] = "siddonj.rooms.";

  srand(time(NULL));       // Create random seed.

  // get starting room. initializeRooms
  struct Room *rooms = allocate();

  // Create temp directory name
  snprintf(buffer, 100, "%d", PID);         // Convert PID to string.
  strcat(tempDirectory, buffer);            // Combine PID with temporary directory name.

  // Create temporary directory
  mkdir(tempDirectory, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH );     // make directory, read/write/search permissions for owner and group.


  // Set up the rooms to play.
  initializeRooms(rooms, tempDirectory);
  connectRooms(rooms);
  assignRoomTypes(rooms);

  // Play the game!
  struct Room *currentRoom = setStartRoom(rooms, tempDirectory);
  printf("Starting room: %s\n", currentRoom->name);
  printf("Type: %s\n", currentRoom->type);


  // Prompt user with move options from currentRoom
  printRoomOptions(currentRoom);

  // Get user choice
  currentRoom = getUserChoice(currentRoom, tempDirectory);

  // Validate string

  // Set room to user selection

  // Write room in user path file.


  // Once at end


  // COngradulate user

  // Print contents fo path file to screen.



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
