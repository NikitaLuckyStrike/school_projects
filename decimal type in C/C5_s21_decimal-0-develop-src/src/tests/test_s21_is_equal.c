#include "main.h"

START_TEST(is_equal_1) {
  s21_decimal x = {{1234, 123, 1234, INT_MIN}},
              y = {{1234, 123, 1234, INT_MIN}};
  int result = s21_is_equal(x, y);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(is_equal_2) {
  s21_decimal x = {{0, 0, 0, 0}}, y = {{0, 0, 0, INT_MIN}};
  int result = s21_is_equal(x, y);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(is_equal_3) {
  s21_decimal x = {{0, 3, 0, 0}}, y = {{0, 3, 0, INT_MIN}};
  int result = s21_is_equal(x, y);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(is_equal_4) {
  s21_decimal x = {{0, 0, 0, 123}}, y = {{0, 0, 0, 123}};
  int result = s21_is_equal(x, y);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(is_equal_5) {
  s21_decimal x = {{456, 267, 23467, 393216}}, y = {{456, 267, 23467, 393216}};
  int result = s21_is_equal(x, y);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(is_equal_6) {
  s21_decimal x = {{456, 267, 23467, 393216}},
              y = {{456, 267, 23467, 393216 + INT_MIN}};
  int result = s21_is_equal(x, y);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(is_equal_7) {
  s21_decimal x = {{12, 34, 56, 0}}, y = {{12, 33, 56, 0}};
  int result = s21_is_equal(x, y);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(is_equal_8) {
  s21_decimal x = {{456, 267, 23467, 0}}, y = {{456, 267, 23467, 0}};
  int result = 0;
  for (int i = 0; i < 34; i++) {
    x.bits[3] += 65536;
    y.bits[3] += 65536;
    result = s21_is_equal(x, y);
    if (i < 28)
      ck_assert_int_eq(result, 1);
    else
      ck_assert_int_eq(result, 0);
  }
}
END_TEST

START_TEST(is_equal_9) {
  s21_decimal x = {{7, 0, 0, 0}}, y = {{7, 0, 0, 0}};
  int result = 0;
  for (int i = 0; i < 28; i++) {
    x.bits[3] += 65536;
    s21_offset(1, &x);
    s21_sum(1, &x);
    result = s21_is_equal(x, y);
    ck_assert_int_eq(result, 1);
  }
}
END_TEST

START_TEST(is_equal_10) {
  s21_decimal x = {{35, 0, 0, INT_MIN}}, y = {{35, 0, 0, INT_MIN}};
  int result = 0;
  for (int i = 0; i < 26; i++) {
    y.bits[3] += 65536;
    s21_offset(1, &y);
    s21_sum(1, &y);
    result = s21_is_equal(x, y);
    ck_assert_int_eq(result, 1);
  }
}
END_TEST

START_TEST(is_equal_11) {
  s21_decimal x = {{0, 0, 0, INT_MIN}}, y = {{0, 0, 0, 0}};
  int result = 0;
  for (int i = 0; i < 30; i++) {
    y.bits[3] += 65536;
    s21_offset(1, &y);
    s21_sum(1, &y);
    result = s21_is_equal(x, y);
    if (i < 28)
      ck_assert_int_eq(result, 1);
    else
      ck_assert_int_eq(result, 0);
  }
}
END_TEST

START_TEST(is_equal_12) {
  s21_decimal x = {{0, 0, 0, 0}}, y = {{0, 0, 0, 0}};
  int result = 0;
  for (int i = 0; i < 30; i++) {
    y.bits[3] += 65536;
    s21_offset(1, &y);
    s21_sum(1, &y);
    result = s21_is_equal(x, y);
    // print_decimal(x);
    // print_decimal(y);
    // printf("%d\n", result);
    if (i < 28)
      ck_assert_int_eq(result, 1);
    else
      ck_assert_int_eq(result, 0);
  }
}
END_TEST

Suite *test_is_equal(void) {
  Suite *s = suite_create("\033[5m\033[1;31m\033[47m-=S21_IS_EQUAL=-\033[0m");
  TCase *tc = tcase_create("is_equal_tc");

  tcase_add_test(tc, is_equal_1);
  tcase_add_test(tc, is_equal_2);
  tcase_add_test(tc, is_equal_3);
  tcase_add_test(tc, is_equal_4);
  tcase_add_test(tc, is_equal_5);
  tcase_add_test(tc, is_equal_6);
  tcase_add_test(tc, is_equal_7);
  tcase_add_test(tc, is_equal_8);
  tcase_add_test(tc, is_equal_9);
  tcase_add_test(tc, is_equal_10);
  tcase_add_test(tc, is_equal_11);
  tcase_add_test(tc, is_equal_12);

  suite_add_tcase(s, tc);
  return s;
}
