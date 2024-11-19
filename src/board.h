#pragma once
typedef struct {
    size_t **board;
    size_t length; 
    size_t height;
    int generation;
    int population;
} Board;

void draw_board(Board board);
// initialize ncurses and create a new Board
Board init_board(size_t board_length, size_t board_height);

// Returns the number of alive neighbors surrounding a specified cell on the board.
// A neighbor is defined as any cell that is within a distance of less than 2 spaces 
// from the given cell (including diagonals). 
// Example:
// @ @ @ @ @
// @ ^ ^ ^ @ 
// @ ^ * ^ @ 
// @ ^ ^ ^ @
// @ @ @ @ @
int count_neighbors(Board* board, int x, int y);

// Update the cells on a given board, using the conway's game 
// of life rules
void update_board(Board* board);
