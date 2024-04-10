#include "main.h"

START_TEST(from_float_to_decimal_1) {
  s21_decimal x = {0};
  float y = 1. / 0.;
  int v[4] = {0, 0, 0, 0};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(x.bits[i], v[i]);
  }
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(from_float_to_decimal_2) {
  s21_decimal *x = NULL;
  float y = 12;
  int result = s21_from_float_to_decimal(y, x);
  ck_assert_ptr_eq(x, NULL);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(from_float_to_decimal_3) {
  s21_decimal x = {0};
  float y = -.00000000003450044652;
  int v[4] = {3450045, 0, 0, 65536 * 17 + INT_MIN};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(x.bits[i], v[i]);
  }
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_4) {
  s21_decimal x = {0};
  float y = -.1234000112345652;
  int v[4] = {1234, 0, 0, 2147745792};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(x.bits[i], v[i]);
  }
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_5) {
  s21_decimal x = {0};
  float y = .000000000345000043;
  int v[4] = {3450001, 0, 0, 1048576};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(x.bits[i], v[i]);
  }
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_6) {
  s21_decimal x = {0};
  float y = 1123.234e-23;
  int v[4] = {1123234, 0, 0, 1703936};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(x.bits[i], v[i]);
  }
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_7) {
  s21_decimal x = {0};
  float y = 1123.234e+23;
  int v[4] = {3760193536, 3071107411, 6089063, 0};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(x.bits[i], v[i]);
  }
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_8) {
  s21_decimal x = {0};
  float y = 1.23456789e-22;
  int v[4] = {1234568, 0, 0, 1835008};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(x.bits[i], v[i]);
  }
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_9) {
  s21_decimal x = {0};
  float y = 1.23456789e-23;
  int v[4] = {123457, 0, 0, 1835008};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(x.bits[i], v[i]);
  }
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_10) {
  s21_decimal x = {0};
  float y = 1.23456789e-24;
  int v[4] = {12346, 0, 0, 1835008};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(x.bits[i], v[i]);
  }
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_11) {
  s21_decimal x = {0};
  float y = 1.23456789e-25;
  int v[4] = {1235, 0, 0, 1835008};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(x.bits[i], v[i]);
  }
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_12) {
  s21_decimal x = {0};
  float y = 1.23456789e-26;
  int v[4] = {123, 0, 0, 1835008};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(x.bits[i], v[i]);
  }
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_13) {
  s21_decimal x = {0};
  float y = 1.23456789e-27;
  int v[4] = {12, 0, 0, 1835008};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(x.bits[i], v[i]);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_14) {
  s21_decimal x = {0};
  float y = 1.23456789e-28;
  int v[4] = {1, 0, 0, 1835008};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(x.bits[i], v[i]);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_15) {
  s21_decimal x = {0};
  float y = 1.23456789e-29;
  int v[4] = {0, 0, 0, 0};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(x.bits[i], v[i]);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(from_float_to_decimal_16) {
  s21_decimal x = {0};
  float y = 10000003e-28;
  int v[4] = {1, 0, 0, 1376256};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(x.bits[i], v[i]);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_17) {
  s21_decimal x = {0};
  float y = 10000007e-28;
  int v[4] = {1000001, 0, 0, 1769472};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(x.bits[i], v[i]);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_18) {
  s21_decimal x = {0};
  float y = 1.023e-27;
  int v[4] = {1, 0, 0, 1769472};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(x.bits[i], v[i]);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_19) {
  s21_decimal x = {0};
  float y = 1.073e-27;
  int v[4] = {11, 0, 0, 1835008};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(x.bits[i], v[i]);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_20) {
  s21_decimal x = {0};
  float y = 345.234e-20;
  int v[4] = {345234, 0, 0, 1507328};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(x.bits[i], v[i]);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_21) {
  s21_decimal x = {0};
  float y = 1.073e-17;
  int v[4] = {1073, 0, 0, 1310720};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(x.bits[i], v[i]);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_22) {
  s21_decimal x = {0};
  float y = 1.234567e-14;
  int v[4] = {1234567, 0, 0, 1310720};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(x.bits[i], v[i]);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_23) {
  s21_decimal x = {0};
  float y = -1.234567e-11;
  int v[4] = {1234567, 0, 0, 2148597760};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(x.bits[i], v[i]);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_24) {
  s21_decimal x = {0};
  float y = 1.2345678e-9;
  int v[4] = {1234568, 0, 0, 983040};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(x.bits[i], v[i]);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_25) {
  s21_decimal x = {0};
  float y = 4.3456712e-5;
  int v[4] = {4345671, 0, 0, 720896};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(x.bits[i], v[i]);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_26) {
  s21_decimal x = {0};
  float y = 7.13456576e-2;
  int v[4] = {7134566, 0, 0, 524288};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(x.bits[i], v[i]);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_27) {
  s21_decimal x = {0};
  float y = 0.0;
  int v[4] = {0, 0, 0, 0};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(x.bits[i], v[i]);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_28) {
  s21_decimal x = {0};
  float y = .73234523452345;
  int v[4] = {7323452, 0, 0, 458752};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(x.bits[i], v[i]);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_29) {
  s21_decimal x = {0};
  float y = -23.1234;
  int v[4] = {231234, 0, 0, 2147745792};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(x.bits[i], v[i]);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_30) {
  s21_decimal x = {0};
  float y = 534.00002;
  int v[4] = {534, 0, 0, 0};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(x.bits[i], v[i]);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_31) {
  s21_decimal x = {0};
  float y = -34562.006;
  int v[4] = {3456201, 0, 0, 2147614720};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(x.bits[i], v[i]);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_32) {
  s21_decimal x = {0};
  float y = 760000.0;
  int v[4] = {760000, 0, 0, 0};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(x.bits[i], v[i]);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_33) {
  s21_decimal x = {0};
  float y = -832456342345.34673;
  int v[4] = {3527711872, 193, 0, 2147483648};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(x.bits[i], v[i]);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_34) {
  s21_decimal x = {{1234351, 1234567, 12356542, 1234121}};
  float y = 9732131234575756436473.323123474;
  int v[4] = {3340992512, 2490559861, 527, 0};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(x.bits[i], v[i]);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_35) {
  s21_decimal x = {{0, 0, 0, 35698723}};
  float y = -4300200000000000000000000.00123;
  int v[4] = {765460480, 1327600626, 233114, 2147483648};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(x.bits[i], v[i]);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_36) {
  s21_decimal x = {0};
  float y = 0.0000003123454523452345;
  int v[4] = {3123455, 0, 0, 851968};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(x.bits[i], v[i]);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_37) {
  s21_decimal x = {0};
  float y = 0.0000006123454523452345;
  int v[4] = {6123454, 0, 0, 851968};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(x.bits[i], v[i]);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_38) {
  s21_decimal x = {0};
  float y = -1234567891234567891234567898.f;
  int v[4] = {83886080, 1649500280, 66926065, 2147483648};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(x.bits[i], v[i]);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_39) {
  s21_decimal x = {0};
  float y = 79e+27;
  int v[4] = {2550136832, 1364693707, 4282598581, 0};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(x.bits[i], v[i]);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_40) {
  s21_decimal x = {0};
  float y = 81e+27;
  int v[4] = {0, 0, 0, 0};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(x.bits[i], v[i]);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(from_float_to_decimal_41) {
  s21_decimal x = {0};
  float y = -79228162514264337593543950335.f;
  int v[4] = {0, 0, 0, 0};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(x.bits[i], v[i]);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(from_float_to_decimal_42) {
  s21_decimal x = {0};
  float y = 7922816.0e+22F;
  int v[4] = {536870912, 3012735514, 4294967159, 0};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(x.bits[i], v[i]);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_43) {
  s21_decimal x = {0};
  float y = -7922816.0e+22F;
  int v[4] = {536870912, 3012735514, 4294967159, 2147483648};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(x.bits[i], v[i]);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_44) {
  s21_decimal x = {0};
  float y = 7922816.1e+22F;
  int v[4] = {0, 0, 0, 0};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(x.bits[i], v[i]);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(from_float_to_decimal_45) {
  s21_decimal x = {0};
  float y = 0.3;
  int v[4] = {3, 0, 0, 65536};
  int result = s21_from_float_to_decimal(y, &x);
  // printf("%d\n%u\n%u\n%u\n%u\n", result, x.bits[0], x.bits[1], x.bits[2],
  //       x.bits[3]);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(x.bits[i], v[i]);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_46) {
  s21_decimal x = {0};
  float y = 987654.35;
  int v[4] = {9876544, 0, 0, 65536};
  int result = s21_from_float_to_decimal(y, &x);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(x.bits[i], v[i]);
  }
  ck_assert_int_eq(result, 0);
}
END_TEST
Suite *test_from_float_to_decimal(void) {
  Suite *s =
      suite_create("\033[5m\033[1;31m\033[47m-=S21_FLOAT->DECIMAL=-\033[0m");
  TCase *tc = tcase_create("from_float_to_decimal_tc");

  tcase_add_test(tc, from_float_to_decimal_1);
  tcase_add_test(tc, from_float_to_decimal_2);
  tcase_add_test(tc, from_float_to_decimal_3);
  tcase_add_test(tc, from_float_to_decimal_4);
  tcase_add_test(tc, from_float_to_decimal_5);
  tcase_add_test(tc, from_float_to_decimal_6);
  tcase_add_test(tc, from_float_to_decimal_7);
  tcase_add_test(tc, from_float_to_decimal_8);
  tcase_add_test(tc, from_float_to_decimal_9);
  tcase_add_test(tc, from_float_to_decimal_10);
  tcase_add_test(tc, from_float_to_decimal_11);
  tcase_add_test(tc, from_float_to_decimal_12);
  tcase_add_test(tc, from_float_to_decimal_13);
  tcase_add_test(tc, from_float_to_decimal_14);
  tcase_add_test(tc, from_float_to_decimal_15);
  tcase_add_test(tc, from_float_to_decimal_16);
  tcase_add_test(tc, from_float_to_decimal_17);
  tcase_add_test(tc, from_float_to_decimal_18);
  tcase_add_test(tc, from_float_to_decimal_19);
  tcase_add_test(tc, from_float_to_decimal_20);
  tcase_add_test(tc, from_float_to_decimal_21);
  tcase_add_test(tc, from_float_to_decimal_22);
  tcase_add_test(tc, from_float_to_decimal_23);
  tcase_add_test(tc, from_float_to_decimal_24);
  tcase_add_test(tc, from_float_to_decimal_25);
  tcase_add_test(tc, from_float_to_decimal_26);
  tcase_add_test(tc, from_float_to_decimal_27);
  tcase_add_test(tc, from_float_to_decimal_28);
  tcase_add_test(tc, from_float_to_decimal_29);
  tcase_add_test(tc, from_float_to_decimal_30);
  tcase_add_test(tc, from_float_to_decimal_31);
  tcase_add_test(tc, from_float_to_decimal_32);
  tcase_add_test(tc, from_float_to_decimal_33);
  tcase_add_test(tc, from_float_to_decimal_34);
  tcase_add_test(tc, from_float_to_decimal_35);
  tcase_add_test(tc, from_float_to_decimal_36);
  tcase_add_test(tc, from_float_to_decimal_37);
  tcase_add_test(tc, from_float_to_decimal_38);
  tcase_add_test(tc, from_float_to_decimal_39);
  tcase_add_test(tc, from_float_to_decimal_40);
  tcase_add_test(tc, from_float_to_decimal_41);
  tcase_add_test(tc, from_float_to_decimal_42);
  tcase_add_test(tc, from_float_to_decimal_43);
  tcase_add_test(tc, from_float_to_decimal_44);
  tcase_add_test(tc, from_float_to_decimal_45);
  tcase_add_test(tc, from_float_to_decimal_46);

  suite_add_tcase(s, tc);
  return s;
}
