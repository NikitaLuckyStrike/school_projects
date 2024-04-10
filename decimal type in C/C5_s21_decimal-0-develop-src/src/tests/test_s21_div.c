#include "main.h"

START_TEST(div_1) {
  s21_decimal x = {{20, 0, 0, 12 + INT_MIN}}, y = {{30, 0, 0, 65536}},
              z = {{1234567891, 0, 0, 0}};
  int res = s21_div(x, y, &z);
  ck_assert_int_eq(res, 4);
}
END_TEST

START_TEST(div_2) {
  s21_decimal x = {{20, 0, 0, 65536 + INT_MIN}}, y = {{30, 0, 0, 12 + 65536}},
              z = {{1234567891, 0, 0, 0}};
  int res = s21_div(x, y, &z);
  ck_assert_int_eq(res, 4);
}
END_TEST

START_TEST(div_3) {
  s21_decimal x = {{20, 0, 0, 65536 + INT_MIN}}, y = {{0, 0, 0, 65536}},
              *z = NULL;
  int res = s21_div(x, y, z);
  ck_assert_int_eq(res, 4);
  ck_assert_ptr_null(z);
}
END_TEST

START_TEST(div_4) {
  s21_decimal x = {{20, 0, 0, 65536 + INT_MIN}}, y = {{0, 0, 0, 65536}},
              z = {{23434, 2345, 234, 0}};
  int res = s21_div(x, y, &z);
  ck_assert_int_eq(res, 3);
}
END_TEST

START_TEST(div_5) {
  s21_decimal x = {{20, 0, 0, 65536 + INT_MIN}}, y = {{0, 0, 0, 0 + INT_MIN}},
              z = {{1234567891, 0, 0, 0}};
  int res = s21_div(x, y, &z);
  ck_assert_int_eq(res, 3);
}
END_TEST

START_TEST(div_6) {
  s21_decimal x = {{0, 0, 0, 65536 + INT_MIN}}, y = {{30, 0, 0, 65536}},
              z = {{1234567891, 0, 0, 0}}, r = {{0, 0, 0, 0}};
  int res = s21_div(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(div_7) {
  s21_decimal x = {{0, 0, 0, 0}}, y = {{30, 0, 0, 65536}},
              z = {{1234567891, 0, 0, 0}}, r = {{0, 0, 0, 0}};
  int res = s21_div(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(div_8) {
  s21_decimal x = {{-1, -1, -1, 0}}, y = {{2, 0, 0, 65536}},
              z = {{1234567891, 0, 0, 0}};
  int res = s21_div(x, y, &z);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(div_9) {
  s21_decimal x = {{-1, -1, -1, INT_MIN}}, y = {{3, 0, 0, 65536}},
              z = {{1234567891, 0, 0, 0}};
  int res = s21_div(x, y, &z);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(div_10) {
  s21_decimal x = {{20, 0, 0, 65536 + INT_MIN}}, y = {{30, 0, 0, 65536}},
              z = {{1234567891, 0, 0, 0}},
              r = {{178956971, 695075222, 361400724, 65536 * 28 + INT_MIN}};
  int res = s21_div(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(div_11) {
  s21_decimal x = {{1, 0, 0, 65536 * 2 + INT_MIN}},
              y = {{30, 0, 0, 65536 * 3 + INT_MIN}},
              z = {{1234567891, 0, 0, 0}},
              r = {{89478485, 347537611, 180700362, 65536 * 28}};
  int res = s21_div(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(div_12) {
  s21_decimal x = {{-1, -1, -1, INT_MIN}}, y = {{21, 0, 0, 65536 * 28}},
              z = {{-11, 0, 0, 0}};
  int res = s21_div(x, y, &z);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(div_13) {
  s21_decimal x = {{50, 0, 0, 65536 * 28 + INT_MIN}}, y = {{100, 0, 0, 0}},
              z = {{1234567891, 0, 0, 0}},
              r = {{0, 0, 0, 65536 * 28 + INT_MIN}};
  int res = s21_div(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(div_14) {
  s21_decimal x = {{51, 0, 0, 65536 * 28 + INT_MIN}},
              y = {{100, 0, 0, INT_MIN}}, z = {{1234567891, 0, 0, 0}},
              r = {{1, 0, 0, 65536 * 28}};
  int res = s21_div(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(div_15) {
  s21_decimal x = {{3, 0, 0, 65536 * 28 + INT_MIN}}, y = {{4, 0, 0, INT_MIN}},
              z = {{1234567891, 0, 0, 0}}, r = {{1, 0, 0, 65536 * 28}};
  int res = s21_div(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(div_16) {
  s21_decimal x = {{345456, 346346, 345634, 65536 * 15 + INT_MIN}},
              y = {{2345, 673, 235, 0}}, z = {{1234567891, 0, 0, 0}},
              r = {{2038515368, 3424433, 0, 65536 * 28 + INT_MIN}};
  int res = s21_div(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(div_17) {
  s21_decimal x = {{-456, 3456346, -34575634, 65536 * 28}},
              y = {{2345, 673, 22535, 65536 * 28}}, z = {{1234567891, 0, 0, 0}},
              r = {{565847572, 1321064804, 1024878166, 65536 * 23}};
  int res = s21_div(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(div_18) {
  s21_decimal x = {{-456, 3456346, -34575634, 65536 * 28}},
              y = {{2345, 673, 22535, 65536 * 14}}, z = {{1234567891, 0, 0, 0}},
              r = {{-1393614065, 106850910, 1, 65536 * 28}};
  int res = s21_div(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(div_19) {
  s21_decimal x = {{-456, 345634346, -34575634, 65536 * 28}},
              y = {{2345, 673, 22345535, 65536 * 14}},
              z = {{1234567891, 0, 0, 0}},
              r = {{-1402237799, 4439140, 0, 65536 * 28}};
  int res = s21_div(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(div_20) {
  s21_decimal x = {{-456, 345634346, -34575634, 65536 * 28}},
              y = {{2345, 673, 22345535, 65536 * 3 + INT_MIN}},
              z = {{1234567891, 0, 0, 0}},
              r = {{190660, 0, 0, 65536 * 28 + INT_MIN}};
  int res = s21_div(x, y, &z);
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

START_TEST(div_21) {
  s21_decimal x = {{315, 0, 0, 65536 * 28}}, y = {{10, 0, 0, INT_MIN}},
              z = {{1234567891, 0, 0, 0}},
              r = {{32, 0, 0, 65536 * 28 + INT_MIN}};
  int res = s21_div(x, y, &z);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], r.bits[i]);
  }
}
END_TEST

START_TEST(div_22) {
  float num1 = 83.519;
  float num2 = 21.373;
  float res_origin = num1 / num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_float_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  float res_int = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(div_23) {
  int num1 = -32768;
  int num2 = 2;
  int res_origin = -16384;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(div_24) {
  s21_decimal dec1 = {{100, 0, 0, 0}};
  s21_decimal dec2 = {{99999, 0, 0, 0}};

  float res_s21 = 0;
  float res = 100.0 / 99999.0;

  s21_decimal res1;
  s21_div(dec1, dec2, &res1);
  s21_from_decimal_to_float(res1, &res_s21);
  ck_assert_float_eq_tol(res_s21, res, 6);
}
END_TEST

START_TEST(div_25) {
  s21_decimal dec1;
  s21_decimal dec2;
  int tmp1 = 100;
  float tmp2 = 999.99;
  float res_s21 = 0.0;
  float res = 0.100001;
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_float_to_decimal(tmp2, &dec2);
  s21_decimal res1;
  s21_div(dec1, dec2, &res1);
  s21_from_decimal_to_float(res1, &res_s21);
  ck_assert_float_eq_tol(res_s21, res, 6);
}
END_TEST

START_TEST(div_26) {
  s21_decimal dec1;
  s21_decimal dec2;
  int tmp1 = -100;
  int tmp2 = -99999;
  float res_s21 = 0;
  float res = 0.00100001;
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_int_to_decimal(tmp2, &dec2);
  s21_decimal res1;
  s21_div(dec1, dec2, &res1);
  s21_from_decimal_to_float(res1, &res_s21);
  ck_assert_float_eq_tol(res_s21, res, 6);
}
END_TEST

START_TEST(div_27) {
  float num1 = -100.5;
  float num2 = -99999.5;
  s21_decimal dec1 = {0};  // -100.5
  s21_decimal dec2 = {0};
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  float res_s21 = 0;
  float res = 0.001005005;
  s21_decimal res1 = {0};
  s21_div(dec1, dec2, &res1);
  s21_from_decimal_to_float(res1, &res_s21);
  ck_assert_float_eq_tol(res_s21, res, 6);
}
END_TEST

START_TEST(div_28) {
  s21_decimal dec1 = {{10.0e3, 0, 0, 0}};
  s21_decimal dec2 = {{2.00e2, 0, 0, 0}};

  int res_s21 = 0;
  int res = 50;

  s21_decimal res1;
  s21_div(dec1, dec2, &res1);
  s21_from_decimal_to_int(res1, &res_s21);
  ck_assert_float_eq_tol(res_s21, res, 6);
}
END_TEST

START_TEST(div_29) {
  s21_decimal dec1 = {{1110, 0, 0, 0}};
  s21_decimal dec2 = {{0, 0, 0, 0}};

  s21_decimal res1;
  int res = s21_div(dec1, dec2, &res1);
  ck_assert_int_eq(res, 3);
}
END_TEST

START_TEST(div_30) {
  s21_decimal x = {{5, 0, 0, 0x801C0000}};
  s21_decimal y = {{1, 0, 0, 0x1C0000}};
  s21_decimal res;
  int res_code = s21_div(x, y, &res);

  ck_assert_int_eq(res_code, 0);
  ck_assert_int_eq(res.bits[0], 5);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], (int)0x80000000);
}
END_TEST

START_TEST(div_31) {
  s21_decimal x = {
      {0xFA0F974, 0x559A6EFD, 0x129, 0xA0000}};  //  548485135456.4542134644
  s21_decimal y = {{8, 0, 0, 0x30000}};          //  0.008
  s21_decimal res;
  int res_code = s21_div(x, y, &res);  //  68560641932056.77668305

  ck_assert_int_eq(res_code, 0);
  ck_assert_int_eq(res.bits[0], (int)0x538937D1);
  ck_assert_int_eq(res.bits[1], (int)0xAB010ABC);
  ck_assert_int_eq(res.bits[2], (int)0x173);
  ck_assert_int_eq(res.bits[3], (int)0x80000);
}
END_TEST

START_TEST(div_32) {
  s21_decimal x = {{8, 0, 0, 0x50000}};  //  0.00008
  s21_decimal y = {{0x33333333, 0x33333333, 0x33333333,
                    0x10000}};  //  1584563250285286751870879006.7
  s21_decimal res;
  int res_code = s21_div(x, y, &res);  //  0

  ck_assert_int_eq(res_code, 0);
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 65536 * 28);
}
END_TEST

START_TEST(div_33) {
  s21_decimal x = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                    0xA0000}};  //  7922816251426433759.3543950335
  s21_decimal y = {{0x33333333, 0x33333333, 0x33333333,
                    0x50000}};  //  158456325028528675187087.90067
  s21_decimal res;
  int res_code = s21_div(x, y, &res);  //  0.00005

  ck_assert_int_eq(res_code, 0);
  ck_assert_int_eq(res.bits[0], 5);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], (int)0x50000);
}
END_TEST

START_TEST(div_34) {
  s21_decimal x = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                    0x800A0000}};  //  -7922816251426433759.3543950335
  s21_decimal y = {{0x33333333, 0x33333333, 0x33333333,
                    0x50000}};  //  158456325028528675187087.90067
  s21_decimal res;
  int res_code = s21_div(x, y, &res);  //  -0.00005

  ck_assert_int_eq(res_code, 0);
  ck_assert_int_eq(res.bits[0], 5);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], (int)0x80050000);
}
END_TEST

START_TEST(div_35) {
  s21_decimal x = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                    0}};           //  79228162514264337593543950335
  s21_decimal y = {{1, 0, 0, 0}};  //  5
  s21_decimal res;
  int res_code = s21_div(x, y, &res);  //  79228162514264337593543950335 - max

  ck_assert_int_eq(res_code, 0);
  ck_assert_int_eq(res.bits[0], (int)0xFFFFFFFF);
  ck_assert_int_eq(res.bits[1], (int)0xFFFFFFFF);
  ck_assert_int_eq(res.bits[2], (int)0xFFFFFFFF);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(div_36) {
  s21_decimal x = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                    0x80000000}};  //  -79228162514264337593543950335
  s21_decimal y = {{1, 0, 0, 0}};  //  1
  s21_decimal res;
  int res_code = s21_div(x, y, &res);  //  -79228162514264337593543950335 - min

  ck_assert_int_eq(res_code, 0);
  ck_assert_int_eq(res.bits[0], (int)0xFFFFFFFF);
  ck_assert_int_eq(res.bits[1], (int)0xFFFFFFFF);
  ck_assert_int_eq(res.bits[2], (int)0xFFFFFFFF);
  ck_assert_int_eq(res.bits[3], (int)0x80000000);
}
END_TEST

START_TEST(div_37) {
  s21_decimal x = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
                    0}};  //  79228162514264337593543950334
  s21_decimal y = {{1, 0, 0, 0x10000}};
  s21_decimal res;
  int res_code = s21_div(x, y, &res);  //  (max-1)*10

  ck_assert_int_eq(res_code, 1);
}
END_TEST

START_TEST(div_38) {
  s21_decimal x = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
                    0x80000000}};  //  -79228162514264337593543950334
  s21_decimal y = {{1, 0, 0, 0x10000}};
  s21_decimal res;
  int res_code = s21_div(x, y, &res);  //  -(max-1)*10

  ck_assert_int_eq(res_code, 2);
}
END_TEST

START_TEST(div_39) {
  s21_decimal x = {{9345975, 0, 0, 0x10000}};
  s21_decimal y = {{0, 0, 0, 0}};
  s21_decimal res_dec;
  int res_code = s21_div(x, y, &res_dec);
  ck_assert_int_eq(res_code, 3);
}
END_TEST

START_TEST(div_40) {
  s21_decimal x = {{9345975, 0, 0, 0x10000}};
  s21_decimal y = {{0, 0, 0, 0x80000000}};
  s21_decimal res_dec;
  int res_code = s21_div(x, y, &res_dec);
  ck_assert_int_eq(res_code, 3);
}
END_TEST

START_TEST(div_41) {
  s21_decimal x = {{1880543360, 1288162084, 3269716480, 65536 * 11}},
              y = {{57612902, 0, 0, 65536 * 10}}, z = {{1234567891, 0, 0, 0}},
              r = {{364196164, -261661480, 567531987, 65536 * 8}};
  int res = s21_div(x, y, &z);
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

Suite *test_div(void) {
  Suite *s = suite_create("\033[5m\033[1;31m\033[47m-=S21_DIV=-\033[0m");
  TCase *tc = tcase_create("div_tc");

  tcase_add_test(tc, div_1);
  tcase_add_test(tc, div_2);
  tcase_add_test(tc, div_3);
  tcase_add_test(tc, div_4);
  tcase_add_test(tc, div_5);
  tcase_add_test(tc, div_6);
  tcase_add_test(tc, div_7);
  tcase_add_test(tc, div_8);
  tcase_add_test(tc, div_9);
  tcase_add_test(tc, div_10);
  tcase_add_test(tc, div_11);
  tcase_add_test(tc, div_12);
  tcase_add_test(tc, div_13);
  tcase_add_test(tc, div_14);
  tcase_add_test(tc, div_15);
  tcase_add_test(tc, div_16);
  tcase_add_test(tc, div_17);
  tcase_add_test(tc, div_18);
  tcase_add_test(tc, div_19);
  tcase_add_test(tc, div_20);
  tcase_add_test(tc, div_21);
  tcase_add_test(tc, div_22);
  tcase_add_test(tc, div_23);
  tcase_add_test(tc, div_24);
  tcase_add_test(tc, div_25);
  tcase_add_test(tc, div_26);
  tcase_add_test(tc, div_27);
  tcase_add_test(tc, div_28);
  tcase_add_test(tc, div_29);
  tcase_add_test(tc, div_30);
  tcase_add_test(tc, div_31);
  tcase_add_test(tc, div_32);
  tcase_add_test(tc, div_33);
  tcase_add_test(tc, div_34);
  tcase_add_test(tc, div_35);
  tcase_add_test(tc, div_36);
  tcase_add_test(tc, div_37);
  tcase_add_test(tc, div_38);
  tcase_add_test(tc, div_39);
  tcase_add_test(tc, div_40);
  tcase_add_test(tc, div_41);

  suite_add_tcase(s, tc);
  return s;
}
