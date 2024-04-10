#include "main.h"

START_TEST(is_greater_1) {
  s21_decimal x = {{120, 0, 0, 0}}, y = {{120000000, 0, 0, 0}};
  int res = 0;
  for (int i = 0; i < 9; i++) {
    y.bits[3] += 65536;
    res = s21_is_greater(x, y);
    if (i < 6)
      ck_assert_int_eq(res, 0);
    else
      ck_assert_int_eq(res, 1);
  }
}
END_TEST

START_TEST(is_greater_2) {
  s21_decimal x = {{120, 0, 0, 0}}, y = {{120000000, 0, 0, INT_MIN}};
  int res = 0;
  for (int i = 0; i < 12; i++) {
    y.bits[3] += 65536;
    res = s21_is_greater(x, y);
    ck_assert_int_eq(res, 1);
  }
}
END_TEST

START_TEST(is_greater_3) {
  s21_decimal x = {{120, 0, 0, INT_MIN}}, y = {{120000000, 0, 0, 0}};
  int res = 0;
  for (int i = 0; i < 12; i++) {
    y.bits[3] += 65536;
    res = s21_is_greater(x, y);
    ck_assert_int_eq(res, 0);
  }
}
END_TEST

START_TEST(is_greater_4) {
  s21_decimal x = {{120, 0, 0, INT_MIN}}, y = {{120000000, 0, 0, INT_MIN}};
  int res = 0;
  for (int i = 0; i < 12; i++) {
    y.bits[3] += 65536;
    res = s21_is_greater(x, y);
    if (i < 5)
      ck_assert_int_eq(res, 1);
    else
      ck_assert_int_eq(res, 0);
  }
}
END_TEST

START_TEST(is_greater_5) {
  s21_decimal x = {{120, 0, 0, 23}}, y = {{120000000, 0, 0, 0}};
  int res = s21_is_greater(x, y);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_greater_6) {
  s21_decimal x = {{120, 0, 0, 0}}, y = {{12, 0, 0, 1}};
  int res = s21_is_greater(x, y);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_greater_7) {
  s21_decimal x = {{0, 0, 0, 0}}, y = {{0, 0, 0, 65536 * 6 + INT_MIN}};
  int res = s21_is_greater(x, y);
  ck_assert_int_eq(res, 0);
}
END_TEST

Suite *test_is_greater(void) {
  Suite *s = suite_create("\033[5m\033[1;31m\033[47m-=S21_IS_GREATER=-\033[0m");
  TCase *tc = tcase_create("is_greater_tc");

  tcase_add_test(tc, is_greater_1);
  tcase_add_test(tc, is_greater_2);
  tcase_add_test(tc, is_greater_3);
  tcase_add_test(tc, is_greater_4);
  tcase_add_test(tc, is_greater_5);
  tcase_add_test(tc, is_greater_6);
  tcase_add_test(tc, is_greater_7);

  suite_add_tcase(s, tc);
  return s;
}
