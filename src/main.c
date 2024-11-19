#include <stdio.h>
#include "board.h"
#define BOARD_LENGTH 100
#define BOARD_HEIGHT 30

int main() 
{
    Board board = init_board(BOARD_LENGTH, BOARD_HEIGHT);
    for (;;) 
    {
        draw_board(board);
        update_board(&board);
    }
}
