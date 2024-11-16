#pragma once
void draw_board();
// init the ncurses things
void init_board();

// Returns the number of alive neighbors surrounding a specified cell on the board.
// A neighbor is defined as any cell that is within a distance of less than 2 spaces 
// from the given cell (including diagonals). 
// Example:
// @ @ @ @ @
// @ ^ ^ ^ @ 
// @ ^ * ^ @ 
// @ ^ ^ ^ @
// @ @ @ @ @
int count_neighbors(size_t x, size_t y);
