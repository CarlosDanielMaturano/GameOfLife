#include <stdio.h>
#include "board.h"
#define BOARD_LENGTH 60
#define BOARD_HEIGHT 20

int main() 
{
    Board board = init_board(BOARD_LENGTH, BOARD_HEIGHT);
    for (;;) 
    {
        draw_board(board);
        update_board(&board);
    }
}
