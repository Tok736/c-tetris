#include <string.h>
#include <curses.h>
#include <ncurses.h>

#include "menu.h"
#include "graphic_chars.h"
#include "display.h"
#include "../../signals.h"
#include "../../defines.h"

void init_menu_item(menu_item *item, char *text, int x, int y, int h, int w, bool is_active, signal_t signal) {
    strncpy(item->text, text, MAX_TEXT_SIZE - 1);
    item->text[MAX_TEXT_SIZE - 1] = '\0';
    item->posx = x;
    item->posy = y;
    item->height = h;
    item->width = w;
    item->is_active = is_active;
    item->signal = signal;
}

void draw_menu_item(menu_item *item, bool is_hover) {
    int left = item->posx,
        right = item->posx + item->width - 1,
        up = item->posy,
        down = item->posy + item->height - 1,
        centerx = (left + right) / 2,
        centery = (up + down) / 2,
        text_left = centerx - (strlen(item->text) + 1) / 2,
        text_right = centerx + (strlen(item->text) + 2) / 2;

    draw_box(left, right, up, down);

    print_str_centered(centerx, centery, item->text);

    if (is_hover) {
        mvaddch(centery, text_left - 1, CH_MENU_LEFT_ARROW);
        mvaddch(centery, text_right + 1, CH_MENU_RIGHT_ARROW);
    }
}

signal_t handle_menu(menu_item *items, int item_amount, menu_item *back_item) {
    int hover_pos = 0;
    signal_t signal = NO_SIGNAL;
    while (signal == NO_SIGNAL) {  
        for (int i = 0; i < item_amount; i++)
            draw_menu_item(&items[i], hover_pos == i);

        int ch = getch();

        if ('a' <= ch && ch <= 'z')
            ch -= 32;
        
        if (ch == KEY_UP || ch == KEY_LEFT || ch == 'W' || ch == 'A')
            hover_pos = (hover_pos - 1 + item_amount) % item_amount;
        else if (ch == KEY_DOWN || ch == KEY_RIGHT || ch == 'S' || ch == 'D')
            hover_pos = (hover_pos + 1) % item_amount;
        else if (ch == KEY_ENTER || ch == ' ' || ch == '\n')
            signal = items[hover_pos].signal;
        else if (ch == KEY_ESCAPE)
            signal = back_item->signal;
    }
    return signal;
}
