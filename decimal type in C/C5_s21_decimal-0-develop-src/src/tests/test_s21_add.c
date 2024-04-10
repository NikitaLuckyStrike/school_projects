#include "main.h"

START_TEST(add_1) {
  s21_decimal x = {{-1, -1, -1, 0}}, y = {{10, 0, 0, 65536 * 2 + INT_MIN}},
              *z = NULL;
  int res = s21_add(x, y, z);
  ck_assert_int_eq(res, 4);
  ck_assert_ptr_null(z);
}
END_TEST

START_TEST(add_2) {
  s21_decimal x = {{12, 0, 0, 12}}, y = {{12, 0, 0, 0}},
              z = {{1234567891, 0, 0, 0}};
  int res = s21_add(x, y, &z);
  ck_assert_int_eq(res, 4);
}
END_TEST

START_TEST(add_3) {
  s21_decimal x = {{12, 0, 0, 0}}, y = {{12, 0, 0, 324}},
              z = {{1234567891, 0, 0, 0}};
  int res = s21_add(x, y, &z);
  ck_assert_int_eq(res, 4);
}
END_TEST

START_TEST(add_4) {
  s21_decimal x = {{12, 0, 0, 0}}, y = {{12, 0, 0, 0}},
              z = {{1234567891, 0, 0, 0}}, r = {{24, 0, 0, 0}};
  int res = s21_add(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(add_5) {
  s21_decimal x = {{-1, -1, -1, 0}}, y = {{4, 0, 0, 65536}},
              z = {{1234567891, 0, 0, 0}}, r = {{-1, -1, -1, 0}};
  int res = s21_add(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(add_6) {
  s21_decimal x = {{-4, -1, -1, 0}}, y = {{2500, 0, 0, 65536 * 3}},
              z = {{1234567891, 0, 0, 0}}, r = {{-2, -1, -1, 0}};
  int res = s21_add(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(add_7) {
  s21_decimal x = {{-4, -1, -1, 0}}, y = {{2501, 0, 0, 65536 * 3}},
              z = {{1234567891, 0, 0, 0}}, r = {{-1, -1, -1, 0}};
  int res = s21_add(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(add_8) {
  s21_decimal x = {{-3, -1, -1, 0}}, y = {{1500, 0, 0, 65536 * 3}},
              z = {{1234567891, 0, 0, 0}}, r = {{-2, -1, -1, 0}};
  int res = s21_add(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(add_9) {
  s21_decimal x = {{-3, -1, -1, 0}}, y = {{1501, 0, 0, 65536 * 3}},
              z = {{1234567891, 0, 0, 0}}, r = {{-1, -1, -1, 0}};
  int res = s21_add(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(add_10) {
  s21_decimal x = {{-1234, -1, -1, 0}}, y = {{0, 0, 0, INT_MIN}},
              z = {{1234567891, 0, 0, 0}}, r = {{-1234, -1, -1, 0}};
  int res = s21_add(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(add_11) {
  s21_decimal x = {{-134, -1, -1, 0}}, y = {{0, 0, 0, 65536}},
              z = {{1234567891, 0, 0, 0}}, r = {{-134, -1, -1, 0}};
  int res = s21_add(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(add_12) {
  s21_decimal x = {{0, 0, 0, INT_MIN}}, y = {{130, 0, 0, 65536}},
              z = {{1234567891, 0, 0, 0}}, r = {{130, 0, 0, 65536}};
  int res = s21_add(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(add_13) {
  s21_decimal x = {{0, 0, 0, 0}}, y = {{133, 0, 0, 65536 + INT_MIN}},
              z = {{1234567891, 0, 0, 0}}, r = {{133, 0, 0, 65536 + INT_MIN}};
  int res = s21_add(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(add_14) {
  s21_decimal x = {{-11, -1, -1, 65536}},
              y = {{1966705, 0, 0, 65536 * 2 + INT_MIN}},
              z = {{1234567891, 0, 0, 0}}, r = {{-196682, -1, -1, 65536}};
  int res = s21_add(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(add_15) {
  s21_decimal x = {{2673431, 0, 0, 65536}},
              y = {{134567892, 0, 0, 65536 * 2 + INT_MIN}},
              z = {{1234567891, 0, 0, 0}},
              r = {{107833582, 0, 0, 65536 * 2 + INT_MIN}};
  int res = s21_add(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(add_16) {
  s21_decimal x = {{-11, -1, -1, 65536 + INT_MIN}},
              y = {{1044565, 0, 0, 65536 * 2}}, z = {{1234567891, 0, 0, 0}},
              r = {{-104468, -1, -1, 65536 + INT_MIN}};
  int res = s21_add(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(add_17) {
  s21_decimal x = {{45367, 0, 0, 65536 + INT_MIN}},
              y = {{34565426, 0, 0, 65536 * 2}}, z = {{1234567891, 0, 0, 0}},
              r = {{34111756, 0, 0, 65536 * 2}};
  int res = s21_add(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(add_18) {
  s21_decimal x = {{-11, -1, -1, 65536}}, y = {{100001, 0, 0, 65536 * 5}},
              z = {{1234567891, 0, 0, 0}}, r = {{-1, -1, -1, 65536}};
  int res = s21_add(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(add_19) {
  s21_decimal x = {{-11, -1, -1, 65536}}, y = {{200001, 0, 0, 65536 * 5}},
              z = {{1234567891, 0, 0, 0}},
              r = {{-1717986917, -1717986919, 429496729, 0}};
  int res = s21_add(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(add_20) {
  s21_decimal x = {{-11, -1, -1, 65536}}, y = {{200000, 0, 0, 65536 * 5}},
              z = {{1234567891, 0, 0, 0}},
              r = {{-1717986918, -1717986919, 429496729, 0}};
  int res = s21_add(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(add_21) {
  s21_decimal x = {{-11, -1, -1, 65536}}, y = {{300000, 0, 0, 65536 * 5}},
              z = {{1234567891, 0, 0, 0}},
              r = {{-1717986916, -1717986919, 429496729, 0}};
  int res = s21_add(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(add_22) {
  s21_decimal x = {{-11, -1, -1, 65536}}, y = {{400000, 0, 0, 65536 * 5}},
              z = {{1234567891, 0, 0, 0}},
              r = {{-1717986916, -1717986919, 429496729, 0}};
  int res = s21_add(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(add_23) {
  s21_decimal x = {{-11, -1, -1, 65536}}, y = {{300001, 0, 0, 65536 * 5}},
              z = {{1234567891, 0, 0, 0}},
              r = {{-1717986916, -1717986919, 429496729, 0}};
  int res = s21_add(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(add_24) {
  s21_decimal x = {{-11, -1, -1, 65536}}, y = {{400001, 0, 0, 65536 * 5}},
              z = {{1234567891, 0, 0, 0}},
              r = {{-1717986915, -1717986919, 429496729, 0}};
  int res = s21_add(x, y, &z);
  ck_assert_int_eq(res, 0);
  // print_d(x);
  // print_d(y);
  // print_d(z);
  // for (int i = 0; i< 4; i++) printf("%d\n", z.bits[i]);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(add_25) {
  s21_decimal x = {{-11, -1, -1, 65536}}, y = {{105, 0, 0, 65536 * 2}},
              z = {{1234567891, 0, 0, 0}},
              r = {{-1717986918, -1717986919, 429496729, 0}};
  int res = s21_add(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(add_26) {
  s21_decimal x = {{-11, -1, -1, 65536}}, y = {{104, 0, 0, 65536 * 2}},
              z = {{1234567891, 0, 0, 0}}, r = {{-1, -1, -1, 65536}};
  int res = s21_add(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(add_27) {
  s21_decimal x = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal y = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal r = {0};
  ;
  ck_assert_int_eq(2, s21_add(x, y, &r));
}
END_TEST

START_TEST(add_28) {
  s21_decimal x = {{UINT_MAX, UINT_MAX, UINT_MAX, 65536 * 5}};
  s21_decimal y = {{UINT_MAX, UINT_MAX, UINT_MAX, 65536 * 3}};
  s21_decimal r = {0};
  ck_assert_int_eq(0, s21_add(x, y, &r));
}
END_TEST

START_TEST(add_29) {
  s21_decimal x = {{-1, -1, -1, INT_MIN}},
              y = {{50, 0, 0, 65536 * 2 + INT_MIN}},
              z = {{1234567891, 0, 0, 0}};
  int res = s21_add(x, y, &z);
  ck_assert_int_eq(res, 2);
}
END_TEST

Suite *test_add(void) {
  Suite *s = suite_create("\033[5m\033[1;31m\033[47m-=S21_ADD=-\033[0m");
  TCase *tc = tcase_create("add_tc");

  tcase_add_test(tc, add_1);
  tcase_add_test(tc, add_2);
  tcase_add_test(tc, add_3);
  tcase_add_test(tc, add_4);
  tcase_add_test(tc, add_5);
  tcase_add_test(tc, add_6);
  tcase_add_test(tc, add_7);
  tcase_add_test(tc, add_8);
  tcase_add_test(tc, add_9);
  tcase_add_test(tc, add_10);
  tcase_add_test(tc, add_11);
  tcase_add_test(tc, add_12);
  tcase_add_test(tc, add_13);
  tcase_add_test(tc, add_14);
  tcase_add_test(tc, add_15);
  tcase_add_test(tc, add_16);
  tcase_add_test(tc, add_17);
  tcase_add_test(tc, add_18);
  tcase_add_test(tc, add_19);
  tcase_add_test(tc, add_20);
  tcase_add_test(tc, add_21);
  tcase_add_test(tc, add_22);
  tcase_add_test(tc, add_23);
  tcase_add_test(tc, add_24);
  tcase_add_test(tc, add_25);
  tcase_add_test(tc, add_26);
  tcase_add_test(tc, add_27);
  tcase_add_test(tc, add_28);
  tcase_add_test(tc, add_29);

  suite_add_tcase(s, tc);
  return s;
}
