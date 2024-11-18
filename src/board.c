#include <stdio.h>
#include <ncursesw/curses.h>
#include <unistd.h>
#define BOARD_LENGTH 60
#define BOARD_HEIGHT 20
#define SLEEP_TIME 14000
#define EMPTY 0

size_t board[BOARD_HEIGHT][BOARD_LENGTH];

static inline int max(int a, int b) 
{
    return (a > b) ? a : b;
}

static inline int min(int a, int b) 
{
    return (a < b) ? a : b;
}

void init_board() 
{
    initscr();
    cbreak();
    noecho();
    for (size_t j = 0; j < BOARD_HEIGHT; j++) 
        for (size_t i = 0; i < BOARD_LENGTH; i++) 
            board[j][i] = EMPTY;

    board[0][0] = 1;
    board[0][1] = 1;
    board[0][2] = 1;
    board[1][0] = 1;
    board[1][2] = 1;
    board[2][0] = 1;
    board[2][1] = 1;
    board[2][2] = 1;

    board[1][1] = 1;
}

void draw_board() 
{
    clear();
    for (size_t j = 0; j < BOARD_HEIGHT; j++) 
    {
        for (size_t i = 0; i < BOARD_LENGTH; i++) 
            addch((board[j][i]) ? '#' : '*');
        addch('\n'); 
    }
    refresh();
    usleep(SLEEP_TIME);
}


int count_neighbors(int **board, size_t board_length, size_t board_height, size_t x, size_t y) 
{
    int neighbors_count = 0;
    if (x > board_length || x < 0 || y > board_height || y < 0 )
        return -1;

    for (int j = max(y - 1, 0); j <= min(y + 1, board_height); j++)
        for (int i = max(x - 1, 0); i <= min(x + 1, board_length); i++)
            if (!(j == y && i == x))
                neighbors_count += board[j][i];

    return neighbors_count;
}
