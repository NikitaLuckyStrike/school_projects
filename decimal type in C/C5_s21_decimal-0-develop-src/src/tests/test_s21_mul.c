#include "main.h"

START_TEST(mul_1) {
  s21_decimal x = {{-1, -1, -1, 123}}, y = {{-1, -1, -1, 0}},
              z = {{1234567891, 0, 0, 0}};
  int res = s21_mul(x, y, &z);
  ck_assert_int_eq(res, 4);
}
END_TEST

START_TEST(mul_2) {
  s21_decimal x = {{-1, -1, -1, 0}}, y = {{-1, -1, -1, 123}},
              z = {{1234567891, 0, 0, 0}};
  int res = s21_mul(x, y, &z);
  ck_assert_int_eq(res, 4);
}
END_TEST

START_TEST(mul_3) {
  s21_decimal x = {{-1, -1, -1, 0}}, y = {{-1, -1, -1, 0}}, *z = NULL;
  int res = s21_mul(x, y, z);
  ck_assert_int_eq(res, 4);
  ck_assert_ptr_null(z);
}
END_TEST

START_TEST(mul_4) {
  s21_decimal x = {{5, 0, 0, 65536 * 28}}, y = {{0, 0, 0, 65536 + INT_MIN}},
              z = {{1234567891, 0, 0, 0}}, r = {{0, 0, 0, 0}};
  int res = s21_mul(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(mul_5) {
  s21_decimal x = {{0, 0, 0, 65536 * 28}}, y = {{-1, -1, -1, 65536 + INT_MIN}},
              z = {{1234567891, 0, 0, 0}}, r = {{0, 0, 0, 0}};
  int res = s21_mul(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(mul_6) {
  s21_decimal x = {{5, 0, 0, 65536 * 28}}, y = {{1, 0, 0, 65536 + INT_MIN}},
              z = {{1234567891, 0, 0, 0}},
              r = {{0, 0, 0, 65536 * 28 + INT_MIN}};
  int res = s21_mul(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(mul_7) {
  s21_decimal x = {{501, 0, 0, 65536 * 28}}, y = {{1, 0, 0, 65536 * 3}},
              z = {{1234567891, 0, 0, 0}}, r = {{1, 0, 0, 65536 * 28}};
  int res = s21_mul(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(mul_8) {
  s21_decimal x = {{15, 0, 0, 65536 * 28 + INT_MIN}}, y = {{1, 0, 0, 65536}},
              z = {{1234567891, 0, 0, 0}},
              r = {{2, 0, 0, 65536 * 28 + INT_MIN}};
  int res = s21_mul(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(mul_9) {
  s21_decimal x = {{3245, 2345, 235, 65536 * 12 + INT_MIN}},
              y = {{1, 123, -4, 65536 * 20}}, z = {{1234567891, 0, 0, 0}},
              r = {
                  {-1517501793, -1387362546, 1861861821, 65536 * 10 + INT_MIN}};
  int res = s21_mul(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(mul_10) {
  s21_decimal x = {{-23, -234, -56, 65536 * 3 + INT_MIN}},
              y = {{1, 123, -4, 65536 * 26}}, z = {{1234567891, 0, 0, 0}},
              r = {{-712395190, 1996166673, -892143674, INT_MIN}};
  int res = s21_mul(x, y, &z);
  // print_d(x);
  // print_d(y);
  // print_d(z);
  ck_assert_int_eq(res, 0);
  // for (int i = 0; i < 4; i++) printf("%d\n", z.bits[i]);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(mul_11) {
  s21_decimal x = {{-23, -234, -56, 65536 * 3 + INT_MIN}},
              y = {{1, 123, -4, 65536 * 25}}, z = {{1234567891, 0, 0, 0}};
  int res = s21_mul(x, y, &z);
  ck_assert_int_eq(res, 2);
}

START_TEST(mul_12) {
  s21_decimal x = {{-23, -234, -56, 65536 * 3 + INT_MIN}},
              y = {{1, 123, -4, 65536 * 25 + INT_MIN}},
              z = {{1234567891, 0, 0, 0}};
  int res = s21_mul(x, y, &z);
  ck_assert_int_eq(res, 1);
}

START_TEST(mul_13) {
  s21_decimal x = {{57235, 0, 0, 65536}},
              y = {{1748078329, 1038941595, 750409, 65536}},
              z = {{1234567891, 0, 0, 0}},
              r = {{-1717986918, -1717986919, 429496729, 0}};
  int res = s21_mul(x, y, &z);
  // print_d(x);
  // print_d(y);
  // print_d(z);
  ck_assert_int_eq(res, 0);
  // for (int i = 0; i < 4; i++) printf("%d\n", z.bits[i]);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

Suite *test_mul(void) {
  Suite *s = suite_create("\033[5m\033[1;31m\033[47m-=S21_MUL=-\033[0m");
  TCase *tc = tcase_create("mul_tc");

  tcase_add_test(tc, mul_1);
  tcase_add_test(tc, mul_2);
  tcase_add_test(tc, mul_3);
  tcase_add_test(tc, mul_4);
  tcase_add_test(tc, mul_5);
  tcase_add_test(tc, mul_6);
  tcase_add_test(tc, mul_7);
  tcase_add_test(tc, mul_8);
  tcase_add_test(tc, mul_9);
  tcase_add_test(tc, mul_10);
  tcase_add_test(tc, mul_11);
  tcase_add_test(tc, mul_12);
  tcase_add_test(tc, mul_13);

  suite_add_tcase(s, tc);
  return s;
}
