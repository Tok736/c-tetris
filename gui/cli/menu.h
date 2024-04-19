#ifndef MENU_H
#define MENU_H

#define MAX_TEXT_SIZE 256

#include <stdbool.h>

#include "../../signals.h"

typedef struct menu_item {
    char text[MAX_TEXT_SIZE];
    int height, width, posx, posy;
    bool is_active;
    signal_t signal;
} menu_item;

void init_menu_item(menu_item *item, char *text, int x, int y, int h, int w, bool is_active, signal_t signal);
signal_t handle_menu(menu_item *items, int item_amount, menu_item *back_item);

#endif  // MENU_H