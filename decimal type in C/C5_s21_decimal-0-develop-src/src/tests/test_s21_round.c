#include "main.h"

START_TEST(round_1) {
  s21_decimal x = {{12345, 0, 0, 65536}}, z = {{1291, 0, 0, 0}},
              r = {{1234, 0, 0, 0}};
  int res = s21_round(x, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(round_2) {
  s21_decimal x = {{123449, 0, 0, 65536 * 2}}, z = {{1291, 0, 0, 0}},
              r = {{1234, 0, 0, 0}};
  int res = s21_round(x, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(round_3) {
  s21_decimal x = {{12345, 0, 0, 65536 + INT_MIN}}, z = {{1291, 0, 0, 0}},
              r = {{1234, 0, 0, INT_MIN}};
  int res = s21_round(x, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(round_4) {
  s21_decimal x = {{123449, 0, 0, 65536 * 2 + INT_MIN}}, z = {{1291, 0, 0, 0}},
              r = {{1234, 0, 0, INT_MIN}};
  int res = s21_round(x, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(round_5) {
  s21_decimal x = {{12345, 0, 0, 123}}, z = {{1291, 0, 0, 0}};
  int res = s21_round(x, &z);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(round_6) {
  s21_decimal x = {0}, *z = NULL;
  int res = s21_round(x, z);
  ck_assert_int_eq(res, 1);
  ck_assert_ptr_null(z);
}
END_TEST

START_TEST(round_7) {
  s21_decimal x = {{123449, 0, 0, 65536 * 2 + INT_MIN}}, z = {{1291, 0, 0, 0}},
              r = {{1234, 0, 0, INT_MIN}};
  int res = s21_round(x, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(round_8) {
  s21_decimal x = {{33, 0, 0, 65536}}, z = {{1291, 0, 0, 0}},
              r = {{3, 0, 0, 0}};
  for (int k = 0; k < 14; k++) {
    int res = s21_round(x, &z);
    ck_assert_int_eq(res, 0);
    for (int i = 0; i < 4; i++) {
      ck_assert_int_eq(z.bits[i], r.bits[i]);
    }
    x.bits[0] += 1;
    if (x.bits[0] == 35 || x.bits[0] == 46) r.bits[0] += 1;
  }
}
END_TEST

START_TEST(round_9) {
  s21_decimal x = {{331, 0, 0, 65536 * 2}}, z = {{1291, 0, 0, 0}},
              r = {{3, 0, 0, 0}};
  for (int k = 0; k < 14; k++) {
    int res = s21_round(x, &z);
    ck_assert_int_eq(res, 0);
    for (int i = 0; i < 4; i++) {
      ck_assert_int_eq(z.bits[i], r.bits[i]);
    }
    x.bits[0] += 10;
    if (x.bits[0] == 351 || x.bits[0] == 451) r.bits[0] += 1;
  }
}
END_TEST

START_TEST(round_10) {
  s21_decimal x = {{33, 0, 0, 65536 + INT_MIN}}, z = {{1291, 0, 0, 0}},
              r = {{3, 0, 0, INT_MIN}};
  for (int k = 0; k < 14; k++) {
    int res = s21_round(x, &z);
    ck_assert_int_eq(res, 0);
    for (int i = 0; i < 4; i++) {
      ck_assert_int_eq(z.bits[i], r.bits[i]);
    }
    x.bits[0] += 1;
    if (x.bits[0] == 35 || x.bits[0] == 46) r.bits[0] += 1;
  }
}
END_TEST

START_TEST(round_11) {
  s21_decimal x = {{331, 0, 0, 65536 * 2 + INT_MIN}}, z = {{1291, 0, 0, 0}},
              r = {{3, 0, 0, INT_MIN}};
  for (int k = 0; k < 14; k++) {
    int res = s21_round(x, &z);
    ck_assert_int_eq(res, 0);
    for (int i = 0; i < 4; i++) {
      ck_assert_int_eq(z.bits[i], r.bits[i]);
    }
    x.bits[0] += 10;
    if (x.bits[0] == 351 || x.bits[0] == 451) r.bits[0] += 1;
  }
}
END_TEST

Suite *test_round(void) {
  Suite *s = suite_create("\033[5m\033[1;31m\033[47m-=S21_ROUND=-\033[0m");
  TCase *tc = tcase_create("round_tc");

  tcase_add_test(tc, round_1);
  tcase_add_test(tc, round_2);
  tcase_add_test(tc, round_3);
  tcase_add_test(tc, round_4);
  tcase_add_test(tc, round_5);
  tcase_add_test(tc, round_6);
  tcase_add_test(tc, round_7);
  tcase_add_test(tc, round_8);
  tcase_add_test(tc, round_9);
  tcase_add_test(tc, round_10);
  tcase_add_test(tc, round_11);

  suite_add_tcase(s, tc);
  return s;
}
