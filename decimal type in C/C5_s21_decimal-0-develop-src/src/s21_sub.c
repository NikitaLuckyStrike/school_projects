#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res = 0;
  if (result == NULL || s21_correct(value_1) || s21_correct(value_2)) {
    res = 4;
  } else {
    s21_null(result);
    int exp_1 = s21_get_exp(value_1), exp_2 = s21_get_exp(value_2), rest = 0;
    int sign_1 = s21_get_sign(value_1), sign_2 = s21_get_sign(value_2);
    if (!s21_is_zero(value_1) || !s21_is_zero(value_2)) {
      if (s21_is_zero(value_2)) {
        s21_copy(result, value_2);
        s21_negate(*result, result);
      } else if (s21_is_zero(value_1)) {
        s21_copy(result, value_1);
      }
    } else if (sign_1 == -1 * sign_2) {
      s21_negate(value_2, &value_2);
      res = s21_add(value_1, value_2, result);
    } else {
      if (s21_is_greater_or_equal(value_1, value_2)) {
        if (sign_1 == -1) {
          s21_negate(value_2, &value_2);
          s21_negate(value_1, &value_1);
          res = s21_sub(value_2, value_1, result);
        } else {
          if (exp_1 > exp_2) {
            s21_offset(exp_1 - exp_2, &value_2);
            s21_sum(exp_1 - exp_2, &value_2);
            exp_2 = exp_1;
          } else if (exp_1 < exp_2) {
            int f = 0;
            rest = s21_equalize(&exp_2, &exp_1, &value_2, &value_1, &f);
          }
          s21_dir_sub(value_1, value_2, result);
          if (rest > 5 || (rest == 5 && (s21_is_end(*result) % 2))) {
            s21_decimal t = {{1, 0, 0, 0}};
            s21_dir_sub(*result, t, result);
          }
          s21_set_exp(exp_1, result);
        }
      } else {
        if (sign_1 == 1) {
          res = s21_sub(value_2, value_1, result);
          s21_negate(*result, result);
        } else {
          s21_negate(value_2, &value_2);
          s21_negate(value_1, &value_1);
          res = s21_sub(value_1, value_2, result);
          s21_negate(*result, result);
        }
      }
    }
  }
  return res;
}

void s21_dir_sub(s21_decimal value_1, s21_decimal value_2,
                 s21_decimal *result) {
  int depot = 0, mask = 1, sum = 0;
  for (int i = 95; i >= 0; i--) {
    if (value_1.bits[i / 32] & mask << (i % 32)) sum += 1;
    if (value_2.bits[i / 32] & mask << (i % 32)) sum -= 1;

    if (sum == 1) {
      if (!(result->bits[i / 32] & mask << (i % 32)))
        result->bits[i / 32] += mask << (i % 32);
      sum -= 1;
    } else if (sum == -1) {
      result->bits[depot / 32] -= mask << (depot % 32);
      for (int k = depot - 1; k >= i; k--) {
        result->bits[k / 32] += mask << (k % 32);
      }
      sum += 1;
    } else if (result->bits[i / 32] & mask << (i % 32)) {
      result->bits[i / 32] -= mask << (i % 32);
    }
    if (result->bits[i / 32] & mask << (i % 32)) depot = i;
  }
}
