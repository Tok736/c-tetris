#ifndef SIGNALS_H
#define SIGNALS_H

typedef enum signal_t {
    NO_SIGNAL,

    // Menu signals
    SIGNAL_MAIN_MENU,
    SIGNAL_LEVELS_MENU,
    SIGNAL_LEADERBOARDS_MENU,
    SIGNAL_GAMEOVER_MENU,
    SIGNAL_EXIT_MENU,
    SIGNAL_ACCEPT_RESET_MENU,
    SIGNAL_PAUSE_MENU,
    
    // Action signals
    SIGNAL_EXIT_GAME,
    SIGNAL_START_PLAY,
    SIGNAL_RESET_LEADERBOARDS,

    // Game control signals
    SIGNAL_MOVE_LEFT,
    SIGNAL_MOVE_RIGHT,
    SIGNAL_ROTATE_LEFT,
    SIGNAL_ROTATE_RIGHT,
    SIGNAL_DROP_DOWN,
    
    // Game events signals
    SIGNAL_SPAWN_NEW_FIGURE,
    SIGNAL_MOVING,
    SIGNAL_COLLIDE,
    SIGNAL_GAMEOVER,
} signal_t;

#endif  // SIGNALS_H