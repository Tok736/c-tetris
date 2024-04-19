#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncurses.h>

void draw_display();
void draw_box(int left, int right, int up, int down);
void draw_block(int x, int y, int left_ch, int right_ch);
void cool_symbols();

void draw_menu_display();
void draw_game_display();

void print_str_centered(int x, int y, char *str);
void init_ncurses();

#endif  // DISPLAY_H