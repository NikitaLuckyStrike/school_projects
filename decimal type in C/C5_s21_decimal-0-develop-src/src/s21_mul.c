#include "s21_decimal.h"

void s21_dir_mul(s21_bdcm val_1, s21_bdcm val_2, s21_bdcm *r, int *);

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res = 0;
  if (result) s21_null(result);

  if (!result || s21_correct(value_1) || s21_correct(value_2)) {
    res = 4;
  } else if (!s21_is_zero(value_1) || !s21_is_zero(value_2)) {
    s21_null(result);
  } else {
    int sign_1 = s21_get_sign(value_1), sign_2 = s21_get_sign(value_2);
    int exp_1 = s21_get_exp(value_1), exp_2 = s21_get_exp(value_2);
    int total = exp_1 + exp_2;
    s21_bdcm val_1 = {0}, val_2 = {0}, r = {0};
    s21_from_d_to_bd(&val_1, value_1);
    s21_from_d_to_bd(&val_2, value_2);

    int count1 = 0, count2 = 0;
    for (int i = 0; i < 96; i++) {
      if (val_1.bits[i / 32] & 1 << (i % 32)) count1++;
      if (val_2.bits[i / 32] & 1 << (i % 32)) count2++;
    }
    if (count1 >= count2)
      s21_dir_mul(val_1, val_2, &r, &total);
    else
      s21_dir_mul(val_2, val_1, &r, &total);
    if (s21_bit(&r) < 96) {
      for (int k = 0; k < 3; k++) result->bits[k] = r.bits[k];
      s21_set_exp(total, result);
      if (sign_1 != sign_2) s21_negate(*result, result);
    } else {
      (sign_1 == sign_2) ? (res = 1) : (res = 2);
    }
  }
  return res;
}

void s21_dir_mul(s21_bdcm val_1, s21_bdcm val_2, s21_bdcm *r, int *exp) {
  int step = 0;
  for (int i = 0; i <= s21_bit(&val_2); i++, step++) {
    if (val_2.bits[i / 32] & 1 << (i % 32)) {
      if (step) {
        s21_slip(step, &val_1);
        step = 0;
      }
      s21_s(r, val_1);
    }
  }
  int rest = 0, flag = 0;
  for (; *exp > 28 || (s21_bit(r) > 95 && *exp > 0); (*exp)--) {
    rest = s21_10(r);
    if (!flag && *exp - 1 > 28 && rest) flag = 1;
  }
  if (s21_over(r) && *exp > 0 &&
      (rest > 5 || (rest == 5 && (flag || s21_end(*r) % 2)))) {
    if (!flag && rest) flag = 1;
    rest = s21_10(r);
    (*exp)--;
  }
  if (rest > 5 || (rest == 5 && (flag || s21_end(*r) % 2))) {
    s21_bdcm temp = {{1, 0}};
    s21_s(r, temp);
  }
}
