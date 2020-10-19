#ifndef NETHACK_H
#define NETHCAK_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

typedef struct Position {
    int x;
    int y;
    // TILE_TYPE tile;
} Position;

typedef struct Room {
    Position position;
    int height;
    int width;

    Position ** doors;
    //Monster ** monsters;
    //Item ** items;
} Room;

typedef struct Player {
    Position position;
    int health;
    // Room * room;
} Player;

int screenSetUp();
Room ** mapSetUp();
int checkPosition(int newY, int newX, Player * user);
int handleInput(int input, Player * user);
int playerMove(int y, int x, Player * user);
Player * playerSetUp();

//ROOM FUNCTIONS
Room * createRoom(int x, int y, int height, int width);
int drawRoom(Room * room);
int connectDoors(Position * doorOne, Position * doorTwo);

#endif