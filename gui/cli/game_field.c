#include "game_field.h"
#include <ncurses.h>
#include "../../defines.h"
#include "display.h"
#include "graphic_chars.h"

void draw_block_in_field(int i, int j, field_type_t block) {
    int y = DISPLAY_UP + i, x = DISPLAY_LEFT + j;
    if (block == FIELD_BLOCK1)
        draw_block(x, y, CH_BLOCK1);
    else if (block == FIELD_BLOCK2)
        draw_block(x, y, CH_BLOCK2);
    else if (block == FIELD_BLOCK3)
        draw_block(x, y, CH_BLOCK3);
    else if (block == FIELD_BLOCK4)
        draw_block(x, y, CH_BLOCK4);
    else if (block == FIELD_MISSING_BLOCK)
        draw_block(x, y, CH_MISSING_BLOCK);
    else if (block ==FIELD_EMPTY)
        draw_block(x, y, CH_EMPTY, CH_EMPTY);
}

void draw_start_game_field(field_type_t **field) {
    for (int i = 0; i < GAME_FIELD_ROWS; i++) 
        for (int j = 0; j < GAME_FIELD_COLS; j++) 
            draw_block_in_field(i, j, field[i][j]);
}
