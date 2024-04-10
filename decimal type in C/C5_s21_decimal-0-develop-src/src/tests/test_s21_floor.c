#include "main.h"

START_TEST(floor_1) {
  s21_decimal x = {{12345, 0, 0, 65536}}, z = {{1291, 0, 0, 0}},
              r = {{1234, 0, 0, 0}};
  int res = s21_floor(x, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(floor_2) {
  s21_decimal x = {{123449, 0, 0, 65536 * 2}}, z = {{1291, 0, 0, 0}},
              r = {{1234, 0, 0, 0}};
  int res = s21_floor(x, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(floor_3) {
  s21_decimal x = {{12345, 0, 0, 65536 + INT_MIN}}, z = {{1291, 0, 0, 0}},
              r = {{1235, 0, 0, INT_MIN}};
  int res = s21_floor(x, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(floor_4) {
  s21_decimal x = {{123449, 0, 0, 65536 * 2 + INT_MIN}}, z = {{1291, 0, 0, 0}},
              r = {{1235, 0, 0, INT_MIN}};
  int res = s21_floor(x, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(floor_5) {
  s21_decimal x = {{12345, 0, 0, 123}}, z = {{1291, 0, 0, 0}};
  int res = s21_floor(x, &z);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(floor_6) {
  s21_decimal x = {0}, *z = NULL;
  int res = s21_floor(x, z);
  ck_assert_int_eq(res, 1);
  ck_assert_ptr_null(z);
}
END_TEST

START_TEST(floor_7) {
  s21_decimal x = {{123449, 0, 0, 65536 * 2 + INT_MIN}}, z = {{1291, 0, 0, 0}},
              r = {{1235, 0, 0, INT_MIN}};
  int res = s21_floor(x, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(floor_8) {
  s21_decimal x = {{33, 0, 0, 65536}}, z = {{1291, 0, 0, 0}},
              r = {{3, 0, 0, 0}};
  for (int k = 0; k < 14; k++) {
    int res = s21_floor(x, &z);
    ck_assert_int_eq(res, 0);
    for (int i = 0; i < 4; i++) {
      ck_assert_int_eq(z.bits[i], r.bits[i]);
    }
    x.bits[0] += 1;
    if (x.bits[0] == 40) r.bits[0] += 1;
  }
}
END_TEST

START_TEST(floor_9) {
  s21_decimal x = {{331, 0, 0, 65536 * 2}}, z = {{1291, 0, 0, 0}},
              r = {{3, 0, 0, 0}};
  for (int k = 0; k < 14; k++) {
    int res = s21_floor(x, &z);
    ck_assert_int_eq(res, 0);
    for (int i = 0; i < 4; i++) {
      ck_assert_int_eq(z.bits[i], r.bits[i]);
    }
    x.bits[0] += 10;
    if (x.bits[0] == 401) r.bits[0] += 1;
  }
}
END_TEST

START_TEST(floor_10) {
  s21_decimal x = {{33, 0, 0, 65536 + INT_MIN}}, z = {{1291, 0, 0, 0}},
              r = {{4, 0, 0, INT_MIN}};
  for (int k = 0; k < 14; k++) {
    int res = s21_floor(x, &z);
    ck_assert_int_eq(res, 0);
    for (int i = 0; i < 4; i++) {
      ck_assert_int_eq(z.bits[i], r.bits[i]);
    }
    x.bits[0] += 1;
    if (x.bits[0] == 41) r.bits[0] += 1;
  }
}
END_TEST

START_TEST(floor_11) {
  s21_decimal x = {{331, 0, 0, 65536 * 2 + INT_MIN}}, z = {{1291, 0, 0, 0}},
              r = {{4, 0, 0, INT_MIN}};
  for (int k = 0; k < 14; k++) {
    int res = s21_floor(x, &z);
    ck_assert_int_eq(res, 0);
    for (int i = 0; i < 4; i++) {
      ck_assert_int_eq(z.bits[i], r.bits[i]);
    }
    x.bits[0] += 10;
    if (x.bits[0] == 401) r.bits[0] += 1;
  }
}
END_TEST

START_TEST(floor_12) {
  s21_decimal x = {{-1, -1, -1, 65536 + INT_MIN}}, z = {{1291, 0, 0, 0}},
              r = {{-1717986918, -1717986919, 429496729, INT_MIN}};
  int res = s21_floor(x, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

Suite *test_floor(void) {
  Suite *s = suite_create("\033[5m\033[1;31m\033[47m-=S21_FLOOR=-\033[0m");
  TCase *tc = tcase_create("floor_tc");

  tcase_add_test(tc, floor_1);
  tcase_add_test(tc, floor_2);
  tcase_add_test(tc, floor_3);
  tcase_add_test(tc, floor_4);
  tcase_add_test(tc, floor_5);
  tcase_add_test(tc, floor_6);
  tcase_add_test(tc, floor_7);
  tcase_add_test(tc, floor_8);
  tcase_add_test(tc, floor_9);
  tcase_add_test(tc, floor_10);
  tcase_add_test(tc, floor_11);
  tcase_add_test(tc, floor_12);

  suite_add_tcase(s, tc);
  return s;
}
