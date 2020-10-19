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


int main () {
    Player * user;
    int ch;
    screenSetUp();

    mapSetUp();

    user = playerSetUp();

    while((ch = getch()) != 'q') {
        handleInput(ch, user);
    }

    getch();
    endwin();

    return 0;
}

int screenSetUp() {
    initscr();
    noecho();
    srand(time(NULL));
    refresh();

    return 1;
}

Room ** mapSetUp() {

    Room ** rooms;
    rooms = malloc(sizeof(Room)*6);

    //first room
    // mvprintw(13, 13, "---------");
    // mvprintw(14, 13, "|.......|");
    // mvprintw(15, 13, "|.......|");
    // mvprintw(16, 13, "|.......|");
    // mvprintw(17, 13, "|.......|");
    // mvprintw(18, 13, "---------");

    rooms[0] = createRoom(13, 13, 6, 8);
    drawRoom(rooms[0]);

    //second room
    // mvprintw(2, 40, "---------");
    // mvprintw(3, 40, "|.......|");
    // mvprintw(4, 40, "|.......|");
    // mvprintw(5, 40, "|.......|");
    // mvprintw(6, 40, "|.......|");
    // mvprintw(7, 40, "---------");

    rooms[1] = createRoom(40, 2, 6, 8);
    drawRoom(rooms[1]);

    //third room
    // mvprintw(10, 40, "-------------");
    // mvprintw(11, 40, "|...........|");
    // mvprintw(12, 40, "|...........|");
    // mvprintw(13, 40, "|...........|");
    // mvprintw(14, 40, "|...........|");
    // mvprintw(15, 40, "|...........|");
    // mvprintw(16, 40, "-------------");

    rooms[2] = createRoom(40, 10, 6, 12);
    drawRoom(rooms[2]);

    connectDoors(rooms[0]->doors[3], rooms[2]->doors[1]);

    return rooms;
}

Room * createRoom(int x, int y, int height, int width){

    Room * newRoom;
    newRoom = malloc(sizeof(Room));

    newRoom->position.x = x;
    newRoom->position.y = y;
    newRoom->width = width;
    newRoom->height = height;



    newRoom->doors = malloc(sizeof(Position) * 4);

    //top door
    newRoom->doors[0] = malloc(sizeof(Position));
    newRoom->doors[0]->x = rand() % (width - 2) + newRoom->position.x + 1;
    newRoom->doors[0]->y = newRoom->position.y;

    //left door
    newRoom->doors[1] = malloc(sizeof(Position));
    newRoom->doors[1]->y = rand() % (height - 2) + newRoom->position.y + 1;
    newRoom->doors[1]->x = newRoom->position.x;

    //bottom door
    newRoom->doors[2] = malloc(sizeof(Position));
    newRoom->doors[2]->x = rand() % (width - 2) + newRoom->position.x + 1;
    newRoom->doors[2]->y = newRoom->position.y + newRoom->height - 1;

    //right door
    newRoom->doors[3] = malloc(sizeof(Position));
    newRoom->doors[3]->y = rand() % (height - 2) + newRoom->position.y + 1;
    newRoom->doors[3]->x = newRoom->position.x + width - 1;

    return newRoom;
}

int drawRoom(Room * room) {

    int x;
    int y;

    //draw top and bottom
    for(x = room->position.x; x < room->position.x+ room->width; x++) {
        mvprintw(room->position.y, x, "-");
        mvprintw(room->position.y + room->height - 1, x, "-"); 
    }

    //draw floors and side walls
    for(y = room->position.y + 1; y < room->position.y + room->height - 1; y++) {
        mvprintw(y, room->position.x, "|");
        mvprintw(y, room->position.x + room->width - 1, "|");
        for(x = room->position.x + 1; x < room->position.x + room->width - 1; x++) {
            mvprintw(y, x, ".");
        }
    }

    //draw doors
    mvprintw(room->doors[0]->y, room->doors[0]->x, "+");
    mvprintw(room->doors[1]->y, room->doors[1]->x, "+");
    mvprintw(room->doors[2]->y, room->doors[2]->x, "+");
    mvprintw(room->doors[3]->y, room->doors[3]->x, "+");
    return 1;
}

int connectDoors(Position * doorOne, Position * doorTwo) {
    
    Position temp;

    temp.x = doorOne->x;
    temp.y = doorOne->y;

    while (1)
    {
        //step left
        if ((abs((temp.x - 1) - doorTwo->x) < abs(temp.x - doorTwo->x)) && (mvinch(temp.y, temp.x - 1) == ' ')) {
            mvprintw(temp.y, temp.x - 1, "#");
            temp.x = temp.x-1;
        //step left
        } else if ((abs((temp.x + 1) - doorTwo->x) < abs(temp.x - doorTwo->x)) && (mvinch(temp.y, temp.x + 1) == ' ')) {
            mvprintw(temp.y, temp.x + 1, "#");
            temp.x = temp.x + 1;
        //step down
        } else if ((abs((temp.y + 1) - doorTwo->y) < abs(temp.y - doorTwo->y)) && (mvinch(temp.y + 1, temp.x) == ' ')) {
            mvprintw(temp.y + 1, temp.x, "#");
            temp.y = temp.y + 1;
        //step up
        } else if ((abs((temp.y - 1) - doorTwo->y) < abs(temp.y - doorTwo->y)) && (mvinch(temp.y - 1, temp.x) == ' ')) {
            mvprintw(temp.y - 1, temp.x, "#");
            temp.y = temp.y - 1;
        } else {
            return 0;
        }

        getch();
    }
    
    return 1;
}

Player * playerSetUp() {
    Player * newPlayer;
    newPlayer = malloc(sizeof(Player));

    newPlayer->position.x = 14;
    newPlayer->position.y = 14;
    newPlayer->health = 20;

    mvprintw(newPlayer->position.y, newPlayer->position.x, "@");
    move(newPlayer->position.y,newPlayer->position.x);

    return newPlayer;
}

int handleInput (int input, Player * user) {
    int newY;
    int newX;
    switch(input) {
        //move up
        case 'w':
        case 'W':
            newY = user->position.y - 1;
            newX = user->position.x;

            break;
        //move down
        case 's':
        case 'S':
            newY = user->position.y + 1;
            newX = user->position.x;
            break;
        //move left
        case 'a':
        case 'A':
            newY = user->position.y;
            newX = user->position.x - 1;
            break;
        //move right
        case 'd':
        case 'D':
            newY = user->position.y;
            newX = user->position.x + 1;
            break;
        default:
            break;
    }

    checkPosition(newY, newX, user);
}

//checks what is at next position
int checkPosition(int newY, int newX, Player * user) {

    int space;
    switch (mvinch(newY, newX)) {
        case '.':
        case '#':
        case '+':
            playerMove(newY, newX, user);
            break;
        default:
            move(user->position.y, user->position.x);
            break;
    }
}
int playerMove(int y, int x, Player * user) {
    mvprintw(user->position.y, user->position.x, ".");

    user->position.x = x;
    user->position.y = y;

    mvprintw(user->position.y, user->position.x, "@");
    move(user->position.y,user->position.x);


}
