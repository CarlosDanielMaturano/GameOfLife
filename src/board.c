#include <stdio.h>
#include <ncursesw/curses.h>
#include <unistd.h>
#define BOARD_LENGTH 60
#define BOARD_HEIGHT 20
#define SLEEP_TIME 14000
#define EMPTY '*'

char board[BOARD_HEIGHT][BOARD_LENGTH];

void init_board() 
{
    initscr();
    cbreak();
    noecho();
    for (size_t j = 0; j < BOARD_HEIGHT; j++) 
        for (size_t i = 0; i < BOARD_LENGTH; i++) 
            board[j][i] = EMPTY;
}

void draw_board() 
{
    clear();
    for (size_t j = 0; j < BOARD_HEIGHT; j++) 
    {
        for (size_t i = 0; i < BOARD_LENGTH; i++) 
            addch(board[j][i]);
        addch('\n'); 
    }
    refresh();
    usleep(SLEEP_TIME);
}

void say_hello() 
{
    printf("Hello, World\n");
};
