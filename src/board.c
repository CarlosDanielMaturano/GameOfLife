#include <stdio.h>
#include <stdlib.h>
#include <ncursesw/curses.h>
#include <unistd.h>
#include "board.h"
#define SLEEP_TIME 14000
#define EMPTY 0

Board board;

static inline int max(int a, int b) 
{
    return (a > b) ? a : b;
}

static inline int min(int a, int b) 
{
    return (a < b) ? a : b;
}

Board init_board(size_t board_length, size_t board_height) 
{
    initscr();
    cbreak();
    noecho();

    Board board;
    
    board.length = board_length;
    board.height = board_height;

    board.board = (size_t **) malloc(board.height * sizeof(size_t));
    for (size_t j = 0; j < board.height; j++)
        board.board[j] = (size_t *) malloc(board.length * sizeof(size_t));

    board.board[0][0] = 1;
    board.board[0][1] = 1;
    board.board[0][2] = 1;
    board.board[1][0] = 1;
    board.board[1][2] = 1;
    board.board[2][0] = 1;
    board.board[2][1] = 1;
    board.board[2][2] = 1;
    board.board[1][1] = 1;

    return board;
}

void draw_board(Board board) 
{
    clear();
    for (size_t j = 0; j < board.height; j++) 
    {
        for (size_t i = 0; i < board.length; i++) 
            addch((board.board[j][i]) ? '#' : '*');
        addch('\n'); 
    }
    refresh();
    usleep(SLEEP_TIME);
}

int count_neighbors(Board board, size_t x, size_t y) 
{
    int neighbors_count = 0;
    if (x > board.length || x < 0 || y > board.height || y < 0 )
        return -1;

    for (int j = max(y - 1, 0); j <= min(y + 1, board.height); j++)
        for (int i = max(x - 1, 0); i <= min(x + 1, board.length); i++)
            if (!(j == y && i == x))
                neighbors_count += board.board[j][i];

    return neighbors_count;
}
