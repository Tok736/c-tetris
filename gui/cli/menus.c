#include "display.h"
#include "../../defines.h"
#include "menu.h"
#include "../../signals.h"

signal_t handle_main_menu() {
    draw_menu_display();
    menu_item main_menu[4], back_item;
    int item_amount = 4;
    int w = 23;
    int h = 3;
    int dy = 3;
    int x = DISPLAY_CENTER_X - w / 2;
    int y = DISPLAY_CENTER_Y - (int)(dy * (item_amount / 2.0)) + 1;
    init_menu_item(&main_menu[0], "Play", x, y, h, w, false, SIGNAL_START_PLAY);
    init_menu_item(&main_menu[1], "Levels", x, y + dy, h, w, false, SIGNAL_LEVELS_MENU);
    init_menu_item(&main_menu[2], "Leaderboards", x, y + dy * 2, h, w, false, SIGNAL_LEADERBOARDS_MENU);
    init_menu_item(&main_menu[3], "Exit", x, y + dy * 3, h, w, false, SIGNAL_EXIT_MENU);

    init_menu_item(&back_item, "", 0, 0, 0, 0, false, SIGNAL_EXIT_MENU);

    return handle_menu(main_menu, item_amount, &back_item);
}

signal_t handle_exit_menu() {
    draw_menu_display();
    menu_item main_menu[2], back_item;
    int item_amount = 2;
    int w = 21;
    int h = 3;
    int dy = 3;
    int x = DISPLAY_CENTER_X - w / 2;
    int y = DISPLAY_CENTER_Y - (int)(dy * ((item_amount) / 2.0)) + 1;
    print_str_centered(DISPLAY_CENTER_X, y - dy, "Do you want to exit?");

    init_menu_item(&main_menu[0], "Yes!", x, y, h, w, false, SIGNAL_EXIT_GAME);
    init_menu_item(&main_menu[1], "No, I don't", x, y + dy, h, w, false, SIGNAL_MAIN_MENU);

    init_menu_item(&back_item, "", 0, 0, 0, 0, false, SIGNAL_MAIN_MENU);

    return handle_menu(main_menu, item_amount, &back_item);
}

signal_t handle_levels_menu(int *level_num) {
    draw_menu_display();
    menu_item main_menu[10], back_item;
    int item_amount = 10;
    int w = 13;
    int h = 3;
    int dy = 3;
    int x_left = DISPLAY_CENTER_X - w / 2 - w + 6;
    int x_right = DISPLAY_CENTER_X - w / 2 + 7;
    int y = DISPLAY_CENTER_Y - (int)(dy * ((item_amount) / 4.0)) + 1;

    init_menu_item(&main_menu[0], "1evel 0", x_left, y, h, w, false, -0);
    init_menu_item(&main_menu[1], "level 1", x_left, y + dy, h, w, false, -1);
    init_menu_item(&main_menu[2], "level 2", x_left, y + dy * 2, h, w, false, -2);
    init_menu_item(&main_menu[3], "level 3", x_left, y + dy * 3, h, w, false, -3);
    init_menu_item(&main_menu[4], "level 4", x_left, y + dy * 4, h, w, false, -4);

    init_menu_item(&main_menu[5], "1evel 5", x_right, y, h, w, false, -5);
    init_menu_item(&main_menu[6], "level 6", x_right, y + dy, h, w, false, -6);
    init_menu_item(&main_menu[7], "level 7", x_right, y + dy * 2, h, w, false, -7);
    init_menu_item(&main_menu[8], "level 8", x_right, y + dy * 3, h, w, false, -8);
    init_menu_item(&main_menu[9], "level 9", x_right, y + dy * 4, h, w, false, -9);

    init_menu_item(&back_item, "", 0, 0, 0, 0, false, SIGNAL_MAIN_MENU);

    int result = handle_menu(main_menu, item_amount, &back_item);
    
    if (result != SIGNAL_MAIN_MENU) {
        *level_num = -result;
        result = SIGNAL_START_PLAY;
    }

    return result;
}

signal_t handle_gameover_menu() {
    draw_menu_display();
    menu_item main_menu[2], back_item;
    int item_amount = 2;
    int w = 21;
    int h = 3;
    int dy = 3;
    int x = DISPLAY_CENTER_X - w / 2;
    int y = DISPLAY_CENTER_Y - (int)(dy * ((item_amount) / 2.0)) + 1;
    print_str_centered(DISPLAY_CENTER_X, y - dy, "You lost. Want to try again?");

    init_menu_item(&main_menu[0], "Restart", x, y, h, w, false, SIGNAL_START_PLAY);
    init_menu_item(&main_menu[1], "Main menu", x, y + dy, h, w, false, SIGNAL_MAIN_MENU);

    init_menu_item(&back_item, "", 0, 0, 0, 0, false, SIGNAL_MAIN_MENU);

    return handle_menu(main_menu, item_amount, &back_item);
}

signal_t handle_leaderboards_menu() {
    draw_menu_display();
    menu_item main_menu[2], back_item;
    int item_amount = 2;
    int w = 13;
    int h = 3;
    int dy = 3;
    int x_left = DISPLAY_CENTER_X - w / 2 - w + 6;
    int x_right = DISPLAY_CENTER_X - w / 2 + 7;
    int y = DISPLAY_DOWN - dy;

    init_menu_item(&main_menu[0], "Reset", x_left, y, h, w, false, SIGNAL_ACCEPT_RESET_MENU);
    init_menu_item(&main_menu[1], "Back", x_right, y, h, w, false, SIGNAL_MAIN_MENU);

    init_menu_item(&back_item, "", 0, 0, 0, 0, false, SIGNAL_MAIN_MENU);

    return handle_menu(main_menu, item_amount, &back_item);
}

signal_t handle_accept_reset_menu() {
    draw_menu_display();
    menu_item main_menu[2], back_item;
    int item_amount = 2;
    int w = 21;
    int h = 3;
    int dy = 3;
    int x = DISPLAY_CENTER_X - w / 2;
    int y = DISPLAY_CENTER_Y - (int)(dy * ((item_amount) / 2.0)) + 1;
    print_str_centered(DISPLAY_CENTER_X, y - dy - 2, "Do you want to reset");
    print_str_centered(DISPLAY_CENTER_X, y - dy, "all the leaderboards?");

    init_menu_item(&main_menu[0], "Yes", x, y, h, w, false, SIGNAL_RESET_LEADERBOARDS);
    init_menu_item(&main_menu[1], "No", x, y + dy, h, w, false, SIGNAL_LEADERBOARDS_MENU);

    init_menu_item(&back_item, "", 0, 0, 0, 0, false, SIGNAL_LEADERBOARDS_MENU);

    return handle_menu(main_menu, item_amount, &back_item);
}

signal_t handle_pause_menu() {
    draw_menu_display();
    menu_item main_menu[2], back_item;
    int item_amount = 2;
    int w = 21;
    int h = 3;
    int dy = 3;
    int x = DISPLAY_CENTER_X - w / 2;
    int y = DISPLAY_CENTER_Y - (int)(dy * ((item_amount) / 2.0)) + 1;
    print_str_centered(DISPLAY_CENTER_X, y - dy, "Game is paused");

    init_menu_item(&main_menu[0], "Continue", x, y, h, w, false, SIGNAL_START_PLAY);
    init_menu_item(&main_menu[1], "Main menu", x, y + dy, h, w, false, SIGNAL_MAIN_MENU);

    init_menu_item(&back_item, "", 0, 0, 0, 0, false, SIGNAL_START_PLAY);

    return handle_menu(main_menu, item_amount, &back_item);
}