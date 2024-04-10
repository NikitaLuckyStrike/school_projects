#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res = 0;
  if (result) s21_null(result);

  if (!result || s21_correct(value_1) || s21_correct(value_2)) {
    res = 4;
  } else if (!s21_is_zero(value_2)) {
    res = 3;
  } else if (!s21_is_zero(value_1)) {
    s21_null(result);
  } else {
    int sign_1 = s21_get_sign(value_1), sign_2 = s21_get_sign(value_2);
    int exp_1 = s21_get_exp(value_1), exp_2 = s21_get_exp(value_2);
    s21_bdcm val_1 = {0}, val_2 = {0}, r = {0};
    s21_from_d_to_bd(&val_1, value_1);
    s21_from_d_to_bd(&val_2, value_2);

    if (exp_1 >= exp_2) {
      exp_1 -= exp_2;
      exp_2 = 0;
    } else if (exp_2 > exp_1) {
      s21_eq(exp_2 - exp_1, &val_1);
      exp_1 = 0;
      exp_2 -= exp_1;
    }
    s21_dir_div(&val_1, &val_2, &r, &exp_1);
    if (s21_bit(&r) < 96) {
      for (int i = 0; i < 3; i++) result->bits[i] = r.bits[i];
      s21_set_exp(exp_1, result);
      if (sign_1 != sign_2) s21_negate(*result, result);
    } else {
      (sign_1 == sign_2) ? (res = 1) : (res = 2);
    }
  }
  return res;
}

void s21_dir_div(s21_bdcm *val_1, s21_bdcm *val_2, s21_bdcm *r, int *exp) {
  s21_bdcm temp = {0}, temp_r = {0};
  int flag = 0;
  for (int br = 0; *exp <= 29 && !br;) {
    for (int i = s21_bit(val_1); i >= 0; i--) {
      s21_slip(1, &temp);
      if (val_1->bits[i / 32] & 1 << (i % 32)) temp.bits[0] += 1;
      if (s21_lp(*val_2, temp)) {
        s21_min(temp, *val_2, &temp);
        temp_r.bits[0] += 1;
      }
      if (i) s21_slip(1, &temp_r);
    }

    s21_s(r, temp_r);
    s21_n(&temp_r);
    if (!s21_zero(temp) || s21_bit(r) > 212) {
      br = 1;
    } else {
      if (*exp == 29 && s21_zero(temp)) flag = 1;
      if (*exp != 29) {
        s21_c(val_1, temp);
        s21_eq(1, val_1);
        s21_eq(1, r);
        s21_n(&temp);
        (*exp)++;
      } else {
        br = 1;
      }
    }
  }
  int rest = 0;
  for (; *exp > 28 || (s21_bit(r) > 95 && *exp > 0);) {
    rest = s21_10(r);
    (*exp)--;
  }
  if (s21_over(r) && *exp > 0 &&
      (rest > 5 || (rest == 5 && (flag || s21_end(*r) % 2)))) {
    if (!flag && rest) flag = 1;
    rest = s21_10(r);
    (*exp)--;
  }
  if (rest > 5 || (rest == 5 && (flag || s21_end(*r) % 2))) {
    s21_bdcm a = {{1, 0}};
    s21_s(r, a);
  }
}
int s21_over(s21_bdcm *x) {
  int res = 1;
  for (int i = 95; i >= 0 && res; i--) {
    if (!(x->bits[i / 32] & 1 << (i % 32))) res = 0;
  }
  return res;
}
void s21_n(s21_bdcm *x) {
  for (int i = 0; i < 8; i++) {
    x->bits[i] = 0;
  }
}

int s21_10(s21_bdcm *x) {
  int result = -1;
  if (x) {
    int temp = 0, mask = 10;
    s21_bdcm y = {0};
    for (int i = 213; i >= 0; i--) {
      temp <<= 1;
      if (x->bits[i / 32] & 1 << i % 32) temp += 1;
      s21_slip(1, &y);
      if (temp >= mask) {
        temp -= mask;
        y.bits[0] += 1;
      }
    }
    s21_c(x, y);
    result = temp;
  }
  return result;
}
int s21_bit(s21_bdcm *x) {
  int res = 0;
  for (int i = 223; i >= 0 && !res; i--) {
    if (x->bits[i / 32] & 1 << (i % 32)) res = i;
  }
  return res;
}
int s21_end(s21_bdcm x) {
  int result = 0;
  for (int i = 0; i < 214; i++) {
    if (x.bits[i / 32] & 1 << (i % 32)) {
      if (i == 0)
        result += 1;
      else if (i % 4 == 1)
        result += 2;
      else if (i % 4 == 2)
        result += 4;
      else if (i % 4 == 3)
        result += 8;
      else if (i % 4 == 0)
        result += 6;
    }
  }
  return result % 10;
}
