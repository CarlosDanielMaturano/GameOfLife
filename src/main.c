#include <stdio.h>
#include "board.h"

int main() 
{
    init_board();
    for (;;) 
    {
        draw_board();
    }
}
