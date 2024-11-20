#include <stdio.h>
#include <stdlib.h>
#include <ncursesw/curses.h>
#include <unistd.h>
#include <time.h>
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

void cast_curses()
{
    initscr();
    cbreak();
    noecho();
    srand(time(NULL));
    start_color();

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
}


Board init_board(size_t board_length, size_t board_height) 
{

    Board board;
    
    board.length = board_length;
    board.height = board_height;
    board.generation = 0;
    board.population = 0;

    board.board = (size_t **) malloc(board.height * sizeof(size_t));
    for (size_t j = 0; j < board.height; j++)
    {
        board.board[j] = (size_t *) malloc(board.length * sizeof(size_t));
        for (size_t i = 0; i < board.length; i++)
            board.board[j][i] = rand() % 2; 
    }
        
    return board;
}

void draw_board(Board board) 
{
    clear();
    attron(COLOR_PAIR(1));
    for (size_t j = 0; j < board.height; j++) 
    {
        for (size_t i = 0; i < board.length; i++) 
            addch((board.board[j][i]) ? '#' : ' ');
        addch('\n'); 
    }
    attroff(COLOR_PAIR(1));
    printw("\ngeneration: %d\n", board.generation);
    printw("population: %d\n", board.population);
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
    // First, the function create a new 2d array, 
    // based on how the board should be update
    board->population = 0;
    int new_board[board->height][board->length];
    for (int y = 0; y < board->height; y++)
        for (int x = 0; x < board->length; x++)
        {
            int neighbors_count = count_neighbors(board, x, y);

            if (neighbors_count == -1)
                    continue;

            // RULES: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
            
            //Any live cell with fewer than two live neighbours dies, as if by underpopulation.
            if (neighbors_count < 2)
                new_board[y][x] = 0;
            // Any live cell with more than three live neighbours dies, as if by overpopulation.
            if (neighbors_count > 3)
                new_board[y][x] = 0;
            // Any dead cell with exactly three live neighbours becomes a live cell,
            // as if by reproduction.
            if (board->board[y][x] == 0 && neighbors_count == 3)
                new_board[y][x] = 1;
        }

    // Actually update the board
    for (int y = 0; y < board->height; y++)
        for (int x = 0; x < board->length; x++)
        {
            board->board[y][x] = new_board[y][x];
            if (board->board[y][x])
                board->population++;
        }

    board->generation++;
}
