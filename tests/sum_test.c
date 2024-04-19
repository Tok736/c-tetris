#include <check.h>
#include <stdlib.h>

#include "../brick_game/tetris/level_data.h"
#include "../brick_game/tetris/field_types.h"
#include "../defines.h"

START_TEST(init_level_data_test) {
    level_data data;
    init_level_data(&data);

    ck_assert_int_eq(data.level_num, 0);
    ck_assert_int_eq(data.score, 0);

    for (int i = 0; i < GAME_FIELD_ROWS; i++) {
        for (int j = 0; j < GAME_FIELD_COLS; j++) {
            ck_assert_int_eq(data.field1[i][j], FIELD_EMPTY);
            ck_assert_int_eq(data.current_field[i][j], FIELD_EMPTY);
            ck_assert_int_eq(data.field2[i][j], FIELD_MISSING_BLOCK);
            ck_assert_int_eq(data.prev_field[i][j], FIELD_MISSING_BLOCK);
        }
    }
}
END_TEST

START_TEST(flip_field_test) {
    level_data data;
    init_level_data(&data);

    ck_assert_int_eq(data.level_num, 0);
    ck_assert_int_eq(data.score, 0);

    field_type_t types[] = {FIELD_EMPTY, FIELD_BLOCK1, FIELD_BLOCK2, FIELD_BLOCK3, FIELD_BLOCK4, FIELD_MISSING_BLOCK};
    int types_amount = sizeof(types) / sizeof(field_type_t);

    for (int i = 0; i < GAME_FIELD_ROWS; i++) {
        for (int j = 0; j < GAME_FIELD_COLS; j++) {
            data.current_field[i][j] = types[rand() % types_amount];
            data.prev_field[i][j] = types[rand() % types_amount];
        }
    }

    for (int i = 0; i < GAME_FIELD_ROWS; i++) {
        for (int j = 0; j < GAME_FIELD_COLS; j++) {
            ck_assert_int_eq(data.field1[i][j], data.current_field[i][j]);
            ck_assert_int_eq(data.field2[i][j], data.prev_field[i][j]);
        }
    }

    flip_field(&data);

    for (int i = 0; i < GAME_FIELD_ROWS; i++) {
        for (int j = 0; j < GAME_FIELD_COLS; j++) {
            ck_assert_int_eq(data.field2[i][j], data.current_field[i][j]);
            ck_assert_int_eq(data.field1[i][j], data.prev_field[i][j]);
        }
    }
}
END_TEST

Suite *matrix_init_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Level data tests");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, init_level_data_test);
    tcase_add_test(tc_core, flip_field_test);
    

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = matrix_init_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? 0 : 1;
}