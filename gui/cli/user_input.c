#include <ncurses.h>

#include "user_input.h"
#include "../../signals.h"
#include "../../defines.h"

signal_t get_game_user_signal() {
    signal_t signal = NO_SIGNAL;
    int ch = getch();

    if ('a' <= ch && ch <= 'z')
        ch -= 32;

    if (ch == KEY_ENTER || ch == ' ' || ch == '\n')
        signal = SIGNAL_DROP_DOWN;
    else if (ch == 'A' || ch == KEY_LEFT)
        signal = SIGNAL_MOVE_LEFT;
    else if (ch == 'D' || ch == KEY_RIGHT)
        signal = SIGNAL_MOVE_LEFT;
    else if (ch == 'Q' || ch == KEY_UP)
        signal = SIGNAL_ROTATE_LEFT;
    else if (ch == 'E' || ch == KEY_DOWN)
        signal = SIGNAL_ROTATE_RIGHT;
    else if (ch == KEY_ESCAPE)
        signal = SIGNAL_PAUSE_MENU;

    return signal;
}
