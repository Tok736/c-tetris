#include <curses.h>
#include <ncurses.h>
#include <linux/limits.h>

#include "signals.h"
#include "gui/cli/display.h"
#include "gui/cli/menus.h"
#include "gui/cli/user_input.h"
#include "gui/cli/game_field.h"

#include "brick_game/tetris/level_data.h"

int get_absolute_path(int argc, char **argv, char *path);
void run();
signal_t run_game(level_data *data);

int main() {
    // char path[PATH_MAX];
    // get_absolute_path(argc, argv, path);
    run();

    return 0;
}

// int get_absolute_path(int argc, char **argv, char *path) {
//     char *res = realpath(argv[0], path);
//     return (res && argc == 1)
// }

void run() {
    init_ncurses();

    draw_display();
    cool_symbols();

    level_data data;
    init_level_data(&data);
                                                 
    signal_t signal = SIGNAL_MAIN_MENU;
    while (true) {
        if (signal == SIGNAL_START_PLAY)
            signal = run_game(&data);
        else if (signal == SIGNAL_MAIN_MENU) 
            signal = handle_main_menu();
        else if (signal == SIGNAL_EXIT_MENU)
            signal = handle_exit_menu();
        else if (signal == SIGNAL_GAMEOVER_MENU)
            signal = handle_gameover_menu();
        else if (signal == SIGNAL_LEVELS_MENU)
            signal = handle_levels_menu(&data.level_num);
        else if (signal == SIGNAL_LEADERBOARDS_MENU)
            signal = handle_leaderboards_menu();
        else if (signal == SIGNAL_ACCEPT_RESET_MENU)
            signal = handle_accept_reset_menu();
        else if (signal == SIGNAL_PAUSE_MENU)
            signal = handle_pause_menu();
        else if (signal == SIGNAL_EXIT_GAME)
            break;
        else
            break;
    }
    
    endwin();
}

signal_t run_game(level_data *data) {
    draw_game_display();
    signal_t signal = NO_SIGNAL;

    draw_start_game_field(data->current_field);

    while (signal == NO_SIGNAL) {
        signal = get_game_user_signal();

        
        if (signal != SIGNAL_PAUSE_MENU)
            signal = NO_SIGNAL;
    }

    return signal;
}