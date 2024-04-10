#include "main.h"

START_TEST(is_less_or_equal_1) {
  s21_decimal x = {{120, 0, 0, 0}}, y = {{120000000, 0, 0, 0}};
  int res = 0;
  for (int i = 0; i < 9; i++) {
    y.bits[3] += 65536;
    res = s21_is_less_or_equal(x, y);
    if (i < 6)
      ck_assert_int_eq(res, 1);
    else
      ck_assert_int_eq(res, 0);
  }
}
END_TEST

START_TEST(is_less_or_equal_2) {
  s21_decimal x = {{120, 0, 0, 0}}, y = {{120000000, 0, 0, INT_MIN}};
  int res = 0;
  for (int i = 0; i < 12; i++) {
    y.bits[3] += 65536;
    res = s21_is_less_or_equal(x, y);
    ck_assert_int_eq(res, 0);
  }
}
END_TEST

START_TEST(is_less_or_equal_3) {
  s21_decimal x = {{120, 0, 0, INT_MIN}}, y = {{120000000, 0, 0, 0}};
  int res = 0;
  for (int i = 0; i < 12; i++) {
    y.bits[3] += 65536;
    res = s21_is_less_or_equal(x, y);
    ck_assert_int_eq(res, 1);
  }
}
END_TEST

START_TEST(is_less_or_equal_4) {
  s21_decimal x = {{120, 0, 0, INT_MIN}}, y = {{120000000, 0, 0, INT_MIN}};
  int res = 0;
  for (int i = 0; i < 12; i++) {
    y.bits[3] += 65536;
    res = s21_is_less_or_equal(x, y);
    if (i < 5)
      ck_assert_int_eq(res, 0);
    else
      ck_assert_int_eq(res, 1);
  }
}
END_TEST

Suite *test_is_less_or_equal(void) {
  Suite *s =
      suite_create("\033[5m\033[1;31m\033[47m-=S21_IS_LESS_OR_EQUAL=-\033[0m");
  TCase *tc = tcase_create("is_less_or_equal_tc");

  tcase_add_test(tc, is_less_or_equal_1);
  tcase_add_test(tc, is_less_or_equal_2);
  tcase_add_test(tc, is_less_or_equal_3);
  tcase_add_test(tc, is_less_or_equal_4);

  suite_add_tcase(s, tc);
  return s;
}
