#include "nethack.h"

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