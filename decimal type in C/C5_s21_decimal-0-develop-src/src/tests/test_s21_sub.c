#include "main.h"

START_TEST(sub_0) {
  s21_decimal x = {{-1, -1, -1, 0}}, y = {{10, 0, 0, 65536 * 2 + INT_MIN}},
              *z = NULL;
  int res = s21_sub(x, y, z);
  ck_assert_int_eq(res, 4);
  ck_assert_ptr_null(z);
}
END_TEST

START_TEST(sub_1) {
  s21_decimal x = {{0}}, y = {{0}}, z = {{1234567891, 0, 0, 0}},
              r = {{1234574, 0, 0, 65536 + INT_MIN}};
  s21_from_float_to_decimal(-123456.8, &x);
  s21_from_float_to_decimal(0.6, &y);
  int res = s21_sub(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(sub_2) {
  s21_decimal x = {{-1, -1, -1, 65536}}, y = {{10, 0, 0, 65536 * 2 + INT_MIN}},
              z = {0};
  int res = s21_sub(x, y, &z);
  s21_cut_10(&x);
  x.bits[0] += 1;
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], x.bits[i]);
  }
}
END_TEST

START_TEST(sub_3) {
  s21_decimal x = {{-1, -1, -1, 65536}}, y = {{50, 0, 0, 65536 * 2 + INT_MIN}},
              z = {0};
  int res = s21_sub(x, y, &z);
  s21_cut_10(&x);
  x.bits[0] += 1;
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], x.bits[i]);
  }
}
END_TEST

START_TEST(sub_4) {
  s21_decimal x = {{-1, -1, -1, 65536}}, y = {{10, 0, 0, 65536 + INT_MIN}},
              z = {0};
  int res = s21_sub(x, y, &z);
  s21_cut_10(&x);
  x.bits[0] += 1;
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], x.bits[i]);
  }
}
END_TEST

START_TEST(sub_5) {
  s21_decimal x = {{-1, -1, -1, 65536}}, y = {{20, 0, 0, 65536 + INT_MIN}},
              z = {0};
  int res = s21_sub(x, y, &z);
  s21_cut_10(&x);
  x.bits[0] += 3;
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], x.bits[i]);
  }
}
END_TEST

START_TEST(sub_6) {
  s21_decimal x = {{-1, -1, -1, 0}}, y = {{100, 0, 0, 65536 * 2 + INT_MIN}},
              z = {0};
  int res = s21_sub(x, y, &z);
  ck_assert_int_eq(res, 1);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], 0);
  }
}
END_TEST

START_TEST(sub_7) {
  s21_decimal x = {{-1, -1, -1, 0}}, y = {{49, 0, 0, 65536 * 2 + INT_MIN}},
              z = {0};
  int res = s21_sub(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], x.bits[i]);
  }
}
END_TEST

START_TEST(sub_8) {
  s21_decimal x = {{22345, 2345, 23451, 0}}, y = {{0, 0, 0, 0}}, z = {0};
  int res = s21_sub(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], x.bits[i]);
  }
}
END_TEST

START_TEST(sub_9) {
  s21_decimal x = {{0, 0, 0, INT_MIN}},
              y = {{239, 235, 457, 65536 * 2 + INT_MIN}}, z = {0};
  int res = s21_sub(x, y, &z);
  s21_negate(y, &y);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], y.bits[i]);
  }
}
END_TEST

START_TEST(sub_10) {
  s21_decimal x = {{234, 0, 0, 65536 * 2 + INT_MIN}}, y = {{160, 0, 0, 65536}},
              z = {0}, r = {{1834, 0, 0, 65536 * 2 + INT_MIN}};
  int res = s21_sub(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(sub_11) {
  s21_decimal x = {{-2, -1, -1, 0}}, y = {{50, 0, 0, 65536 * 2 + INT_MIN}},
              z = {0}, r = {{-2, -1, -1, 0}};
  int res = s21_sub(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(sub_12) {
  s21_decimal x = {{-2, -1, -1, 0}}, y = {{500001, 0, 0, 65536 * 6 + INT_MIN}},
              z = {0}, r = {{-1, -1, -1, 0}};
  int res = s21_sub(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(sub_13) {
  s21_decimal x = {{100, 0, 0, 0}}, y = {{99999, 0, 0, 0}}, z = {0},
              r = {{99899, 0, 0, INT_MIN}};
  int res = s21_sub(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(sub_14) {
  s21_decimal x = {{100, 0, 0, INT_MIN}}, y = {{99999, 0, 0, INT_MIN}}, z = {0},
              r = {{99899, 0, 0, 0}};
  int res = s21_sub(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(sub_15) {
  s21_decimal x = {{12345, 0, 0, 0}}, y = {{1234567, 0, 0, 65536 * 2}}, z = {0},
              r = {{67, 0, 0, 65536 * 2 + INT_MIN}};
  int res = s21_sub(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(sub_16) {
  s21_decimal x = {{-2, -1, -1, 0}}, y = {{500001, 0, 0, 65536 * 6 + INT_MIN}},
              z = {0}, r = {{-1, -1, -1, 0}};
  int res = s21_sub(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(sub_17) {
  s21_decimal x = {{-2, -1, -1, 0}}, y = {{500001, 0, 0, 65536 * 6 + INT_MIN}},
              z = {0}, r = {{-1, -1, -1, 0}};
  int res = s21_sub(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(sub_18) {
  s21_decimal x = {{12340, 0, 0, 65536}}, y = {{1400, 0, 0, 65536 * 2}},
              z = {0}, r = {{12200, 0, 0, 65536}};
  int res = s21_sub(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(sub_19) {
  s21_decimal x = {{-1, -1, -1, 0}}, y = {{5, 0, 0, 65536}}, z = {0},
              r = {{-2, -1, -1, 0}};
  int res = s21_sub(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(sub_20) {
  s21_decimal x = {{-1, -1, -1, INT_MIN}}, y = {{15, 0, 0, 65536 + INT_MIN}},
              z = {0}, r = {{-2, -1, -1, INT_MIN}};
  int res = s21_sub(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(sub_21) {
  s21_decimal x = {{-1, -1, -1, INT_MIN}}, y = {{16, 0, 0, 65536 + INT_MIN}},
              z = {0}, r = {{-3, -1, -1, INT_MIN}};
  int res = s21_sub(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(sub_22) {
  s21_decimal x = {{-1, -1, -1, INT_MIN}},
              y = {{1501, 0, 0, 65536 * 3 + INT_MIN}}, z = {0},
              r = {{-3, -1, -1, INT_MIN}};
  int res = s21_sub(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(sub_23) {
  s21_decimal x = {{123, 0, 0, 0}}, y = {{120, 0, 0, 0}}, z = {0},
              r = {{3, 0, 0, 0}};
  int res = s21_sub(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(sub_24) {
  s21_decimal x = {{-1, -1, -1, INT_MIN}}, y = {{-1, -1, -1, INT_MIN}}, z = {0},
              r = {{0, 0, 0, 0}};
  int res = s21_sub(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(sub_25) {
  s21_decimal x = {{123, 0, 0, 0}}, y = {{126, 0, 0, 0}}, z = {0},
              r = {{3, 0, 0, INT_MIN}};
  int res = s21_sub(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(sub_26) {
  s21_decimal x = {{1234, 0, 0, INT_MIN}}, y = {{1230, 0, 0, INT_MIN}}, z = {0},
              r = {{4, 0, 0, INT_MIN}};
  int res = s21_sub(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(sub_27) {
  s21_decimal x = {{1234, 0, 0, INT_MIN}}, y = {{1239, 0, 0, INT_MIN}}, z = {0},
              r = {{5, 0, 0, 0}};
  int res = s21_sub(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(sub_28) {
  s21_decimal x = {{-3, -1, -1, INT_MIN}}, y = {{2500, 0, 0, 65536 * 3}},
              z = {0};
  int res = s21_sub(x, y, &z);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(sub_29) {
  s21_decimal x = {{-3, -1, -1, 0}}, y = {{2500, 0, 0, 65536 * 3 + INT_MIN}},
              z = {0};
  int res = s21_sub(x, y, &z);
  ck_assert_int_eq(res, 1);
}
END_TEST

Suite *test_sub(void) {
  Suite *s = suite_create("\033[5m\033[1;31m\033[47m-=S21_SUB=-\033[0m");
  TCase *tc = tcase_create("sub_tc");

  tcase_add_test(tc, sub_0);
  tcase_add_test(tc, sub_1);
  tcase_add_test(tc, sub_2);
  tcase_add_test(tc, sub_3);
  tcase_add_test(tc, sub_4);
  tcase_add_test(tc, sub_5);
  tcase_add_test(tc, sub_6);
  tcase_add_test(tc, sub_7);
  tcase_add_test(tc, sub_8);
  tcase_add_test(tc, sub_9);
  tcase_add_test(tc, sub_10);
  tcase_add_test(tc, sub_11);
  tcase_add_test(tc, sub_12);
  tcase_add_test(tc, sub_13);
  tcase_add_test(tc, sub_14);
  tcase_add_test(tc, sub_15);
  tcase_add_test(tc, sub_16);
  tcase_add_test(tc, sub_17);
  tcase_add_test(tc, sub_18);
  tcase_add_test(tc, sub_19);
  tcase_add_test(tc, sub_20);
  tcase_add_test(tc, sub_21);
  tcase_add_test(tc, sub_22);
  tcase_add_test(tc, sub_23);
  tcase_add_test(tc, sub_24);
  tcase_add_test(tc, sub_25);
  tcase_add_test(tc, sub_26);
  tcase_add_test(tc, sub_27);
  tcase_add_test(tc, sub_28);
  tcase_add_test(tc, sub_29);
  /*tcase_add_test(tc, sub_30);
  tcase_add_test(tc, sub_31);
  tcase_add_test(tc, sub_32);
  tcase_add_test(tc, sub_33);
  tcase_add_test(tc, sub_34);
  tcase_add_test(tc, sub_35);
  tcase_add_test(tc, sub_36);
  tcase_add_test(tc, sub_37);
  tcase_add_test(tc, sub_38);
  tcase_add_test(tc, sub_39);
*/

  suite_add_tcase(s, tc);
  return s;
}
