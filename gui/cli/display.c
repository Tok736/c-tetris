#include <ncurses.h>
#include <string.h>
#include <locale.h>

#include "display.h"
#include "graphic_chars.h"
#include "../../defines.h"

void draw_box(int left, int right, int up, int down) {
    for (int i = up + 1; i < down; i++) 
        mvhline(i, left + 1, CH_EMPTY, right - left - 1);

    mvhline(up, left + 1, ACS_HLINE, right - left - 1);
    mvhline(down, left + 1, ACS_HLINE, right - left - 1);
    
    mvvline(up + 1, left, ACS_VLINE, down - up - 1);
    mvvline(up + 1, right, ACS_VLINE, down - up - 1);

    mvaddch(up, left, ACS_ULCORNER);
    mvaddch(down, left, ACS_LLCORNER);
    mvaddch(up, right, ACS_URCORNER);
    mvaddch(down, right, ACS_LRCORNER);    
}

void draw_block(int x, int y, int left_ch, int right_ch) {
    mvaddch(y, x, left_ch);
    mvaddch(y, x + 1, right_ch);
}

void draw_display() {
    for (int i = 0; i < DISPLAY_WIDTH + 9; i++) 
        draw_block(i, DISPLAY_HEIGHT + 5, CH_BLOCK2);
    for (int i = 0; i < 5 + DISPLAY_HEIGHT; i++) {
        draw_block(0, i, CH_BLOCK2);
        draw_block(DISPLAY_WIDTH + 8, i, CH_BLOCK2);
    }
    for (int k = 0; k < 3; k++) {
        draw_block(k * 4 + 2, 0, CH_BLOCK2);
        draw_block(DISPLAY_WIDTH - k * 4 + 6, 0, CH_BLOCK2);
    }
    mvprintw(0, DISPLAY_CENTER_X - 5, "T E T R I S");
}

void clean_display() {
    for (int i = DISPLAY_LEFT; i <= DISPLAY_RIGHT; i++)
        mvvline(DISPLAY_UP, i, CH_EMPTY, DISPLAY_DOWN - DISPLAY_UP + 1);
}

void draw_game_display() {
    clean_display();
    // draw_box(4, 5 + DISPLAY_WIDTH, 2, 3 + DISPLAY_HEIGHT);
    mvvline(DISPLAY_UP, VERTICAL_LINE_X, ACS_VLINE, DISPLAY_HEIGHT);
    mvaddch(DISPLAY_UP - 1, VERTICAL_LINE_X, ACS_BSSS);
    mvaddch(DISPLAY_DOWN + 1, VERTICAL_LINE_X, ACS_SSBS);
}

void draw_menu_display() {
    clean_display();
    draw_box(4, 5 + DISPLAY_WIDTH, 2, 3 + DISPLAY_HEIGHT);
}

void print_str_centered(int x, int y, char *str) {
    mvprintw(y, x - (strlen(str) - 1) / 2, "%s", str);
}

void init_ncurses() {
    setlocale(LC_ALL, "");
    set_escdelay(0);
    initscr();
    noecho();
    cbreak();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
} 

void cool_symbols() {
    int start = 60;
    mvaddch(0, start++, ACS_CKBOARD);
    mvaddch(0, start++, ACS_CKBOARD);
    mvaddch(0, start++, (char)0x2588);
    mvaddch(0, start++, (char)0x2588);
    mvaddch(0, start++, ACS_CKBOARD | A_REVERSE);
    mvaddch(0, start++, ACS_CKBOARD | A_REVERSE);
    mvaddch(0, start++, ACS_BSSS | A_REVERSE);
    mvaddch(0, start++, ACS_SSBS | A_REVERSE);

    // mvaddch(0, start++, 'B' | A_REVERSE);
    // mvaddch(0, start++, A_REVERSE);
    

    // mvaddch(0, start++, ACS_BBSS);
    // mvaddch(0, start++, ACS_BSBS);
    // mvaddch(0, start++, ACS_BULLET);
    // mvaddch(0, start++, ACS_DARROW);
    // mvaddch(0, start++, ACS_DEGREE);
    // mvaddch(0, start++, ACS_DIAMOND);
    // mvaddch(0, start++, ACS_LEQUAL);
    // mvaddch(0, start++, ACS_GEQUAL);
    // mvaddch(0, start++, ACS_LANTERN);
    // mvaddch(0, start++, ACS_LARROW);
    // mvaddch(0, start++, ACS_NEQUAL);
    // mvaddch(0, start++, ACS_PI);
    // mvaddch(0, start++, ACS_PLMINUS);
    // mvaddch(0, start++, ACS_PLUS);
    // mvaddch(0, start++, ACS_LTEE);
    // mvaddch(0, start++, ACS_RTEE);
    // mvaddch(0, start++, ACS_S1);
    // mvaddch(0, start++, ACS_S3);
    // mvaddch(0, start++, ACS_S7);
    // mvaddch(0, start++, ACS_S9);
    // mvaddch(0, start++, ACS_STERLING);

    // mvaddch(0, start++, ACS_BSSS);
    // mvaddch(0, start++, ACS_SSBS);
}
