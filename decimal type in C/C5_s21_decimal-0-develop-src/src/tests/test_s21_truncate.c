#include "main.h"

START_TEST(truncate_1) {
  s21_decimal *y = NULL, x = {{0, 0, 0, 0}};
  int res = 0;
  res = s21_truncate(x, y);
  // print_decimal(y);
  ck_assert_ptr_null(y);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(truncate_2) {
  s21_decimal x = {{1201234, 0, 0, 65536 * 29}}, y = {{0, 0, 0, 0}};
  int res = 0;
  res = s21_truncate(x, &y);
  // print_decimal(y);
  ck_assert_int_eq(y.bits[0], 0);
  ck_assert_int_eq(res, 1);
}
END_TEST
START_TEST(truncate_3) {
  s21_decimal x = {{1201234, 0, 0, 65536 * 3}}, y = {{0, 0, 0, 0}};
  int res = 0;
  res = s21_truncate(x, &y);
  // print_decimal(y);
  ck_assert_int_eq(y.bits[0], 1201);
  ck_assert_int_eq(res, 0);
}
END_TEST

Suite *test_truncate(void) {
  Suite *s = suite_create("\033[5m\033[1;31m\033[47m-=S21_TRUNCATE=-\033[0m");
  TCase *tc = tcase_create("truncate_tc");

  tcase_add_test(tc, truncate_1);
  tcase_add_test(tc, truncate_2);
  tcase_add_test(tc, truncate_3);

  suite_add_tcase(s, tc);
  return s;
}
