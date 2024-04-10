#include "main.h"

START_TEST(from_int_to_decimal_1) {
  s21_decimal *x = NULL;
  int y = 1234;
  int result = s21_from_int_to_decimal(y, x);
  ck_assert_ptr_null(x);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(from_int_to_decimal_2) {
  s21_decimal x = {0};
  int y = 1;
  for (; y * 2 + 1 > y;) {
    y = y * 2 + 1;
    int result = s21_from_int_to_decimal(y, &x);
    ck_assert_int_eq(result, 0);
    ck_assert_int_eq(x.bits[0], y);
  }
}
END_TEST

START_TEST(from_int_to_decimal_3) {
  s21_decimal x = {0};
  int y = 0;
  for (; y * 2 - 1 < y;) {
    y = y * 2 - 1;
    int result = s21_from_int_to_decimal(y, &x);
    ck_assert_int_eq(result, 0);
    ck_assert_int_eq(x.bits[0] * -1, y);
  }
}
END_TEST

Suite *test_from_int_to_decimal(void) {
  Suite *s =
      suite_create("\033[5m\033[1;31m\033[47m-=S21_INT->DECIMAL=-\033[0m");
  TCase *tc = tcase_create("from_int_to_decimal_tc");

  tcase_add_test(tc, from_int_to_decimal_1);
  tcase_add_test(tc, from_int_to_decimal_2);
  tcase_add_test(tc, from_int_to_decimal_3);

  suite_add_tcase(s, tc);
  return s;
}
