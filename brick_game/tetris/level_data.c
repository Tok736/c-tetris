#include "level_data.h"
#include "field_types.h"

void init_level_data(level_data *data) {
    data->level_num = 0;
    for (int i = 0; i < GAME_FIELD_ROWS; i++) 
        for (int j = 0; j < GAME_FIELD_COLS; j++) {
            data->field1[i][j] = FIELD_EMPTY;
            data->field2[i][j] = FIELD_MISSING_BLOCK;
        }
    for (int i = 0; i < GAME_FIELD_ROWS; i++) {
        data->field1_pointers[i] = &(data->field1[i][0]);
        data->field2_pointers[i] = &(data->field2[i][0]);
    }
    data->current_field = data->field1_pointers;
    data->prev_field = data->field2_pointers;
    data->score = 0;
}

void flip_field(level_data *data) {
    field_type_t **temp = data->current_field;
    data->current_field = data->prev_field;
    data->prev_field = temp;
}

