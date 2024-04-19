#ifndef LEVEL_DATA_H
#define LEVEL_DATA_H

#include "../../defines.h"
#include "field_types.h"

typedef struct level_data {
    int level_num;
    int score;

    field_type_t field1[GAME_FIELD_ROWS][GAME_FIELD_COLS];
    field_type_t field2[GAME_FIELD_ROWS][GAME_FIELD_COLS];

    field_type_t *field1_pointers[GAME_FIELD_ROWS];
    field_type_t *field2_pointers[GAME_FIELD_ROWS];

    field_type_t **current_field;
    field_type_t **prev_field;

} level_data;

void init_level_data(level_data *data);
void flip_field(level_data *data);

#endif  // LEVEL_DATA_H
                  