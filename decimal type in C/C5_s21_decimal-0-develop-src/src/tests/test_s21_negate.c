#include "main.h"

START_TEST(negate_1) {
  s21_decimal x = {{120, 123, 1, 0}}, *z = NULL;
  int res = s21_negate(x, z);
  ck_assert_ptr_null(z);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(negate_2) {
  s21_decimal x = {{120, 123, 1, 65536 * 29}}, z = {0};
  int res = s21_negate(x, &z);
  ck_assert_int_eq(res, 1);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], 0);
  }
}
END_TEST

START_TEST(negate_3) {
  s21_decimal x = {{120, 123, 1, 0}}, y = {{120, 123, 1, INT_MIN}}, z = {0};
  int res = s21_negate(x, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(y.bits[i], z.bits[i]);
  }
}
END_TEST

START_TEST(negate_4) {
  s21_decimal x = {{120, 123, 1, INT_MIN}}, y = {{120, 123, 1, 0}}, z = {0};
  int res = s21_negate(x, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(y.bits[i], z.bits[i]);
  }
}
END_TEST

START_TEST(negate_5) {
  s21_decimal x = {{120, 123, 1, 0}}, z = {0};
  int res = s21_negate(x, &z);
  ck_assert_int_eq(res, 0);
  res = s21_negate(z, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(x.bits[i], z.bits[i]);
  }
}
END_TEST

START_TEST(negate_6) {
  s21_decimal x = {{1234, 1234, 1234, INT_MIN}}, z = {0};
  int res = s21_negate(x, &z);
  ck_assert_int_eq(res, 0);
  res = s21_negate(z, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(x.bits[i], z.bits[i]);
  }
}
END_TEST

Suite *test_negate(void) {
  Suite *s = suite_create("\033[5m\033[1;31m\033[47m-=S21_NEGATE=-\033[0m");
  TCase *tc = tcase_create("negate_tc");

  tcase_add_test(tc, negate_1);
  tcase_add_test(tc, negate_2);
  tcase_add_test(tc, negate_3);
  tcase_add_test(tc, negate_4);
  tcase_add_test(tc, negate_5);
  tcase_add_test(tc, negate_6);

  suite_add_tcase(s, tc);
  return s;
}
