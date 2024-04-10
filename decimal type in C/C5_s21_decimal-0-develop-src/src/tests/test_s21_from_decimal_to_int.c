#include "main.h"

START_TEST(from_decimal_to_int_1) {
  s21_decimal x = {{0}};
  int *y = NULL, res = s21_from_decimal_to_int(x, y);
  ck_assert_int_eq(res, 1);
  ck_assert_ptr_null(y);
}
END_TEST

START_TEST(from_decimal_to_int_2) {
  s21_decimal x = {{0, 0, 0, 134}};
  int y = 0, res = s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(from_decimal_to_int_3) {
  s21_decimal x = {{0, 0, 123, 0}};
  int y = 0, res = s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(from_decimal_to_int_4) {
  s21_decimal x = {{0, 1, 0, INT_MIN}};
  int y = 0, res = s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(from_decimal_to_int_5) {
  s21_decimal x = {{INT_MIN, 0, 0, 0}};
  int y = 0, res = s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(from_decimal_to_int_6) {
  s21_decimal x = {{INT_MIN, 0, 0, INT_MIN}};
  int y = 0, st = INT_MIN;
  int res = s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(y, st);
}
END_TEST

START_TEST(from_decimal_to_int_7) {
  s21_decimal x = {{0, 1, 0, 65536}};
  int y = 0, st = 429496729;
  int res = s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(y, st);
}
END_TEST

START_TEST(from_decimal_to_int_8) {
  s21_decimal x = {{0, 0, 234, 65536 * 15}};
  int y = 0, st = 4316538;
  int res = s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(y, st);
}
END_TEST

START_TEST(from_decimal_to_int_9) {
  s21_decimal x = {{0, 500000, 0, 65536 * 6 + INT_MIN}};
  int y = 0, st = INT_MIN;
  int res = s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(y, st);
}
END_TEST

START_TEST(from_decimal_to_int_10) {
  s21_decimal x = {{0, 0, 0, 65536}};
  int y = 0, st = 0;
  for (; st * 2 + 3 > st;) {
    st = st * 2 + 3;
    x.bits[0] = st;
    int res = s21_from_decimal_to_int(x, &y);
    ck_assert_int_eq(res, 0);
    ck_assert_int_eq(y, st / 10);
  }
}
END_TEST

START_TEST(from_decimal_to_int_11) {
  s21_decimal x = {{0, 0, 0, 65536 + INT_MIN}};
  int y = 0, st = 0;
  for (; st * 2 - 1 < st;) {
    st = st * 2 - 1;
    x.bits[0] = st * -1;
    int res = s21_from_decimal_to_int(x, &y);
    ck_assert_int_eq(res, 0);
    ck_assert_int_eq(y, st / 10);
  }
}
END_TEST

Suite *test_from_decimal_to_int(void) {
  Suite *s =
      suite_create("\033[5m\033[1;31m\033[47m-=S21_DECIMAL->INT=-\033[0m");
  TCase *tc = tcase_create("from_decimal_to_int_tc");

  tcase_add_test(tc, from_decimal_to_int_1);
  tcase_add_test(tc, from_decimal_to_int_2);
  tcase_add_test(tc, from_decimal_to_int_3);
  tcase_add_test(tc, from_decimal_to_int_4);
  tcase_add_test(tc, from_decimal_to_int_5);
  tcase_add_test(tc, from_decimal_to_int_6);
  tcase_add_test(tc, from_decimal_to_int_7);
  tcase_add_test(tc, from_decimal_to_int_8);
  tcase_add_test(tc, from_decimal_to_int_9);
  tcase_add_test(tc, from_decimal_to_int_10);
  tcase_add_test(tc, from_decimal_to_int_11);

  suite_add_tcase(s, tc);
  return s;
}
