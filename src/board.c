#include <stdio.h>
#include <stdlib.h>
#include <ncursesw/curses.h>
#include <unistd.h>
#include "board.h"
#define SLEEP_TIME 200000
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
    {
        board.board[j] = (size_t *) malloc(board.length * sizeof(size_t));
        for (size_t i = 0; i < board.length; i++)
            board.board[j][i] = rand() % 8;
    }
        
    return board;
}

void draw_board(Board board) 
{
    clear();
    for (size_t j = 0; j < board.height; j++) 
    {
        for (size_t i = 0; i < board.length; i++) 
            addch((board.board[j][i]) ? '#' : ' ');
        addch('\n'); 
    }
    refresh();
    usleep(SLEEP_TIME);
}

int count_neighbors(Board* board, int x, int y) 
{
    int neighbors_count = 0;
    if (x >= board->length || x < 0 || y >= board->height || y < 0 )
        return -1;

    for (int j = max(y - 1, 0); j <= min(y + 1, board->height - 1); j++)
        for (int i = max(x - 1, 0); i <= min(x + 1, board->length - 1); i++)
            if (!(j == y && i == x))
                neighbors_count += board->board[j][i];

    return neighbors_count;
}

void update_board(Board* board) 
{
    for (int y = 0; y < board->height; y++)
        for (int x = 0; x < board->length; x++)
        {
            int neighbors_count = count_neighbors(board, x, y);

            if (neighbors_count == -1)
                    continue;
            //Any live cell with fewer than two live neighbours dies, as if by underpopulation.
            if (neighbors_count < 2)
                board->board[y][x] = 0;
            // Any live cell with more than three live neighbours dies, as if by overpopulation.
            if (neighbors_count > 3)
                board->board[y][x] = 0;
            // Any dead cell with exactly three live neighbours becomes a live cell,
            // as if by reproduction.
            if (board->board[y][x] == 0 && neighbors_count == 3)
                board->board[y][x] = 1;
        }
}
