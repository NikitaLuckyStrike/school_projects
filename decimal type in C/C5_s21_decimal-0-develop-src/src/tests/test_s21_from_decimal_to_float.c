#include "main.h"

START_TEST(from_decimal_to_float_1) {
  float y = 123.456, yre = 0;
  s21_decimal x = {0};
  s21_from_float_to_decimal(y, &x);
  int result = s21_from_decimal_to_float(x, &yre);
  // printf("%.40f\n%.40f\n", yre, y);
  ck_assert_float_eq_tol(yre, y, 1e-7);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_decimal_to_float_2) {
  float y = 0.00000000000000000000000073736361612636, yre = 0;
  s21_decimal x = {0};
  s21_from_float_to_decimal(y, &x);
  int result = s21_from_decimal_to_float(x, &yre);
  // printf("%.40f\n%.40f\n", yre, y);
  ck_assert_float_eq_tol(yre, y, S21_EPS);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_decimal_to_float_3) {
  float y = -12345678.2345e-8, yre = 0;
  s21_decimal x = {0};
  s21_from_float_to_decimal(y, &x);
  int result = s21_from_decimal_to_float(x, &yre);
  // printf("%.40f\n%.40f\n", yre, y);
  ck_assert_float_eq_tol(yre, y, 1e+9);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_decimal_to_float_4) {
  float y = 12345678.2345e+8, yre = 0;
  s21_decimal x = {0};
  s21_from_float_to_decimal(y, &x);
  int result = s21_from_decimal_to_float(x, &yre);
  // printf("%.40lf\n%.40f\n", (double)yre, y);
  ck_assert_float_eq_tol(yre, y, 1e+9);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_decimal_to_float_5) {
  float y = FLT_MIN, yre = 0;
  s21_decimal x = {0};
  for (; y < 1;) {
    int res = s21_from_float_to_decimal(y, &x);
    int result = s21_from_decimal_to_float(x, &yre);
    // printf("%.40f\n%.40f\n", yre, y);
    if (y < S21_EPS) {
      ck_assert_float_eq(yre, 0);
      ck_assert_int_eq(res, 1);
      y *= 2;
    } else {
      long double m = 1;
      for (; m > y; m /= 10)
        ;
      for (int i = 0; i < 6 && m / 10 > S21_EPS; i++) m /= 10;
      // printf("%.40f\n%.40f\n%.40Lf <-m\n", yre, y, m);
      ck_assert_float_eq_tol(yre, y, m);
      ck_assert_int_eq(result, 0);
      y += FLT_EPSILON * 2 + 0.00123;
    }
  }
}
END_TEST

START_TEST(from_decimal_to_float_6) {
  float y = -FLT_MIN, yre = 0;
  s21_decimal x = {0};
  for (; y > -1;) {
    int res = s21_from_float_to_decimal(y, &x);
    int result = s21_from_decimal_to_float(x, &yre);
    // printf("%.40f\n%.40f\n", yre, y);
    if (y > -S21_EPS) {
      ck_assert_float_eq(yre, 0);
      ck_assert_int_eq(res, 1);
      y *= 2;
    } else {
      long double m = 1;
      for (; m > -y; m /= 10)
        ;
      for (int i = 0; i < 6 && m / 10 > S21_EPS; i++) m /= 10;
      // printf("%.40f\n%.40f\n%.40Lf <-m\n", yre, y, m);
      ck_assert_float_eq_tol(yre, y, m);
      ck_assert_int_eq(result, 0);
      y -= FLT_EPSILON * 2 + 0.00123;
    }
  }
}
END_TEST

START_TEST(from_decimal_to_float_7) {
  float y = 123, yre = 0;
  s21_decimal x = {0};
  for (; y <= MAX;) {
    int res = s21_from_float_to_decimal(y, &x);
    int result = s21_from_decimal_to_float(x, &yre);
    // printf("%.40f\n%.40f\n", yre, y);
    if (y == MAX) {
      ck_assert_float_eq(yre, 0);
      ck_assert_int_eq(res, 1);
      y *= 2;
    } else {
      long double m = 1;
      for (; m * 10 < y; m *= 10)
        ;
      for (int i = 0; i < 6; i++) m /= 10;
      // printf("%.40f\n%.40f\n%.40Lf <-m\n", yre, y, m);
      ck_assert_float_eq_tol(yre, y, m);
      ck_assert_int_eq(result, 0);
      y *= 3;
      if (y > MAX) y = MAX;
    }
  }
}
END_TEST

START_TEST(from_decimal_to_float_8) {
  float y = -23.345345, yre = 0;
  s21_decimal x = {0};
  for (; y >= -MAX;) {
    int res = s21_from_float_to_decimal(y, &x);
    int result = s21_from_decimal_to_float(x, &yre);
    // printf("%.40f\n%.40f\n", yre, y);
    if (y == -MAX) {
      ck_assert_float_eq(yre, 0);
      ck_assert_int_eq(res, 1);
      y *= 2;
    } else {
      long double m = 1;
      for (; m * 10 < -y; m *= 10)
        ;
      for (int i = 0; i < 6; i++) m /= 10;
      // printf("%.40f\n%.40f\n%.LE <-m\n", yre, y, m);
      ck_assert_float_eq_tol(yre, y, m);
      ck_assert_int_eq(result, 0);
      y *= 2;
      if (y < -MAX) y = -MAX;
    }
  }
}
END_TEST

START_TEST(from_decimal_to_float_9) {
  float y = 1234, *yre = NULL;
  s21_decimal x = {0};
  s21_from_float_to_decimal(y, &x);
  int result = s21_from_decimal_to_float(x, yre);
  // printf("%.40f\n%.40f\n", yre, y);
  ck_assert_ptr_eq(yre, NULL);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(from_decimal_to_float_10) {
  float y = 1234, yre = 0;
  s21_decimal x = {{1234, 0, 0, 124}};
  int result = s21_from_decimal_to_float(x, &yre);
  // printf("%.41f\n%.40f\n", yre, y);
  ck_assert_float_eq(yre, 0);
  ck_assert_float_eq(y, 1234);
  ck_assert_int_eq(result, 1);
}
END_TEST
Suite *test_from_decimal_to_float(void) {
  Suite *s =
      suite_create("\033[5m\033[1;31m\033[47m-=S21_DECIMAL->FLOAT=-\033[0m");
  TCase *tc = tcase_create("from_decimal_to_float_tc");

  tcase_add_test(tc, from_decimal_to_float_1);
  tcase_add_test(tc, from_decimal_to_float_2);
  tcase_add_test(tc, from_decimal_to_float_3);
  tcase_add_test(tc, from_decimal_to_float_4);
  tcase_add_test(tc, from_decimal_to_float_5);
  tcase_add_test(tc, from_decimal_to_float_6);
  tcase_add_test(tc, from_decimal_to_float_7);
  tcase_add_test(tc, from_decimal_to_float_8);
  tcase_add_test(tc, from_decimal_to_float_9);
  tcase_add_test(tc, from_decimal_to_float_10);

  suite_add_tcase(s, tc);
  return s;
}
