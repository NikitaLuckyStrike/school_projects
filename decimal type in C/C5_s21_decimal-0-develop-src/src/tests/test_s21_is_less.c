#include "main.h"

START_TEST(is_less_1) {
  s21_decimal x = {{120, 0, 0, 0}}, y = {{120000000, 0, 0, 0}};
  int res = 0;
  for (int i = 0; i < 7; i++) {
    y.bits[3] += 65536;
    res = s21_is_less(x, y);
    if (i < 5)
      ck_assert_int_eq(res, 1);
    else
      ck_assert_int_eq(res, 0);
  }
}
END_TEST

START_TEST(is_less_2) {
  s21_decimal x = {{120, 0, 0, 0}}, y = {{120000000, 0, 0, INT_MIN}};
  int res = 0;
  for (int i = 0; i < 12; i++) {
    y.bits[3] += 65536;
    res = s21_is_less(x, y);
    ck_assert_int_eq(res, 0);
  }
}
END_TEST

START_TEST(is_less_3) {
  s21_decimal x = {{120, 0, 0, INT_MIN}}, y = {{120000000, 0, 0, 0}};
  int res = 0;
  for (int i = 0; i < 12; i++) {
    y.bits[3] += 65536;
    res = s21_is_less(x, y);
    ck_assert_int_eq(res, 1);
  }
}
END_TEST

START_TEST(is_less_4) {
  s21_decimal x = {{120, 0, 0, INT_MIN}}, y = {{120000000, 0, 0, INT_MIN}};
  int res = 0;
  for (int i = 0; i < 12; i++) {
    y.bits[3] += 65536;
    res = s21_is_less(x, y);
    if (i < 6)
      ck_assert_int_eq(res, 0);
    else
      ck_assert_int_eq(res, 1);
  }
}
END_TEST

START_TEST(is_less_5) {
  s21_decimal x = {{120, 0, 0, 23}}, y = {{120000000, 0, 0, 0}};
  int res = s21_is_less(x, y);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_less_6) {
  s21_decimal x = {{120, 0, 0, 0}}, y = {{12, 0, 0, 1}};
  int res = s21_is_less(x, y);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_less_7) {
  s21_decimal x = {{0, 0, 0, 0}}, y = {{0, 0, 0, 65536 * 6 + INT_MIN}};
  int res = s21_is_less(x, y);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_less_8) {
  s21_decimal x = {{12345, 2345, 2345, 65536 * 10 + INT_MIN}},
              y = {{12345, 0, 0, 65536 * 27 + INT_MIN}};
  int res = s21_is_less(x, y);
  ck_assert_int_eq(res, 1);
}
END_TEST

Suite *test_is_less(void) {
  Suite *s = suite_create("\033[5m\033[1;31m\033[47m-=S21_IS_LESS=-\033[0m");
  TCase *tc = tcase_create("is_less_tc");

  tcase_add_test(tc, is_less_1);
  tcase_add_test(tc, is_less_2);
  tcase_add_test(tc, is_less_3);
  tcase_add_test(tc, is_less_4);
  tcase_add_test(tc, is_less_5);
  tcase_add_test(tc, is_less_6);
  tcase_add_test(tc, is_less_7);
  tcase_add_test(tc, is_less_8);

  suite_add_tcase(s, tc);
  return s;
}
