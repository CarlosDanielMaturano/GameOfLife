#include <stdio.h>
#include "board.h"
#include <ncurses/curses.h>
#define BOARD_LENGTH 100
#define BOARD_HEIGHT 30

int main() 
{
    cast_curses();
    Board board = init_board(BOARD_LENGTH, BOARD_HEIGHT);
    int ch;
    for (;;) 
    {
        draw_board(board);
        update_board(&board);
        ch = getch();
        if (ch == ERR)
            ;
        
        if (ch == 'r')
            reset_board_population(&board);
    }
}
