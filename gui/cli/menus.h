#ifndef GRAPHIC_CHARS_H
#define GRAPHIC_CHARS_H

#include "../../signals.h"

signal_t handle_main_menu();
signal_t handle_exit_menu();
signal_t handle_levels_menu(int *level_num);
signal_t handle_gameover_menu();
signal_t handle_leaderboards_menu();
signal_t handle_accept_reset_menu();
signal_t handle_pause_menu();

#endif  // GRAPHIC_CHARS_H