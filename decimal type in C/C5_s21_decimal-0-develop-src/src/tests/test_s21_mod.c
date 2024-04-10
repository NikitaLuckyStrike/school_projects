#include "main.h"

START_TEST(mod_1) {
  s21_decimal x = {{-2, -1, -1, 65536}}, y = {{-4, -1, -1, 65536}},
              z = {{1234567891, 0, 0, 0}}, r = {{2, 0, 0, 65536}};
  int res = s21_mod(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(mod_2) {
  s21_decimal x = {{-2, -1, -1, 65536 * 2}}, y = {{-1, -1, -1, 65536}},
              z = {{1234567891, 0, 0, 0}}, r = {{-2, -1, -1, 65536 * 2}};
  int res = s21_mod(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(mod_3) {
  s21_decimal x = {{13, 0, 0, 123}}, y = {{2, 0, 0, 0}},
              z = {{1, 0, 0, 65536 * 28}};
  int res = s21_mod(x, y, &z);
  ck_assert_int_eq(res, 4);
}
END_TEST

START_TEST(mod_4) {
  s21_decimal x = {{13, 0, 0, 0}}, y = {{2, 0, 0, 345}},
              z = {{1234567891, 0, 0, 0}};
  int res = s21_mod(x, y, &z);
  ck_assert_int_eq(res, 4);
}
END_TEST

START_TEST(mod_5) {
  s21_decimal x = {{13, 0, 0, 123}}, y = {{2, 0, 0, 0}}, *z = NULL;
  int res = s21_mod(x, y, z);
  ck_assert_int_eq(res, 4);
  ck_assert_ptr_null(z);
}
END_TEST

START_TEST(mod_6) {
  s21_decimal x = {{0, 0, 0, 0 + INT_MIN}}, y = {{-1, -1, -1, 65536}},
              z = {{1234567891, 0, 0, 0}}, r = {{0, 0, 0, 0}};
  int res = s21_mod(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(mod_7) {
  s21_decimal x = {{-1, -1, -1, 65536 * 10}}, y = {{0, 0, 0, 65536 * 2}},
              z = {{1234567891, 0, 0, 0}};
  int res = s21_mod(x, y, &z);
  ck_assert_int_eq(res, 3);
}
END_TEST

START_TEST(mod_8) {
  s21_decimal x = {{-1, -1, -1, 65536 * 2}}, y = {{-1, -1, -1, 65536 * 5}},
              z = {{1234567891, 0, 0, 0}}, r = {{0, 0, 0, 65536 * 5}};
  int res = s21_mod(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(mod_9) {
  s21_decimal x = {{-3, -1, -1, 65536 * 10}}, y = {{-1, 0, 0, 65536 * 5}},
              z = {{1234567891, 0, 0, 0}}, r = {{-18915, 18912, 0, 65536 * 10}};
  int res = s21_mod(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(mod_10) {
  s21_decimal x = {{1879048192, -1291644761, -500259693, 0}},
              y = {{1, 0, 0, 65536 * 4}}, z = {{1234567891, 0, 0, 0}},
              r = {{0, 0, 0, 65536 * 4}};
  int res = s21_mod(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(mod_11) {
  s21_decimal x = {{12347123, 0, 0, 65536 * 2 + INT_MIN}},
              y = {{23451, 0, 0, 65536 * 4}}, z = {{1234567891, 0, 0, 0}},
              r = {{17150, 0, 0, 65536 * 4 + INT_MIN}};
  int res = s21_mod(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(mod_12) {
  s21_decimal x = {{12347123, 2345, 2345, 65536 * 15 + INT_MIN}},
              y = {{23451, -1, -1, 65536 * 27}}, z = {{1291, 0, 0, 0}},
              r = {{1642171631, -2023641165, -603462460, 65536 * 27 + INT_MIN}};
  int res = s21_mod(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(mod_13) {
  s21_decimal x = {{12347123, 2345, 2345, 65536 * 15 + INT_MIN}},
              y = {{23451, -1, -1, 65536 * 27 + INT_MIN}},
              z = {{1291, 0, 0, 0}},
              r = {{1642171631, -2023641165, -603462460, 65536 * 27 + INT_MIN}};
  int res = s21_mod(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(mod_14) {
  s21_decimal x = {{1234987123, 0, 0, 65536 * 5 + INT_MIN}},
              y = {{23451, 1, 0, 65536 * 7 + INT_MIN}}, z = {{1291, 0, 0, 0}},
              r = {{-1055995912, 0, 0, 65536 * 7 + INT_MIN}};
  int res = s21_mod(x, y, &z);
  ck_assert_int_eq(res, 0);
  // print_d(x);
  // print_d(y);
  // print_d(z);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

Suite *test_mod(void) {
  Suite *s = suite_create("\033[5m\033[1;31m\033[47m-=S21_MOD=-\033[0m");
  TCase *tc = tcase_create("mod_tc");

  tcase_add_test(tc, mod_1);
  tcase_add_test(tc, mod_2);
  tcase_add_test(tc, mod_3);
  tcase_add_test(tc, mod_4);
  tcase_add_test(tc, mod_5);
  tcase_add_test(tc, mod_6);
  tcase_add_test(tc, mod_7);
  tcase_add_test(tc, mod_8);
  tcase_add_test(tc, mod_9);
  tcase_add_test(tc, mod_10);
  tcase_add_test(tc, mod_11);
  tcase_add_test(tc, mod_12);
  tcase_add_test(tc, mod_13);
  tcase_add_test(tc, mod_14);

  suite_add_tcase(s, tc);
  return s;
}
