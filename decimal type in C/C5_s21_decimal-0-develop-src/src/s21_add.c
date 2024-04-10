#include "s21_decimal.h"

int for_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
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
      } else if (s21_is_zero(value_1)) {
        s21_copy(result, value_1);
      }
    } else if (sign_1 == sign_2) {
      int flag = 0;
      if (exp_1 > exp_2) {
        rest = s21_equalize(&exp_1, &exp_2, &value_1, &value_2, &flag);
      } else if (exp_1 < exp_2) {
        rest = s21_equalize(&exp_2, &exp_1, &value_2, &value_1, &flag);
      }
      if ((exp_1 == exp_2)) {
        int depot = s21_dir_add(value_1, value_2, result);
        s21_set_exp(exp_1, result);
        if (sign_1 == -1) s21_set_sign(result);
        if (depot == 1 && exp_1 == 0) {
          sign_1 == -1 ? (res = 2) : (res = 1);
        } else if (depot == 1) {
          rest = s21_cut_10s(result, depot);
          if (rest > 5 || (rest == 5 && (s21_is_end(*result) % 2 || flag))) {
            s21_decimal t = {{1, 0, 0, 0}};
            s21_dir_add(*result, t, result);
          }
        } else if (rest > 5 || (rest == 5 && (s21_is_end(*result) % 2))) {
          s21_decimal t = {{1, 0, 0, 0}};
          depot = s21_dir_add(*result, t, result);
          if (depot == 1 && exp_1 == 0) {
            sign_1 == -1 ? (res = 2) : (res = 1);
          } else if (depot == 1) {
            rest = s21_cut_10s(result, depot);
            if (rest > 5 || (rest == 5 && (s21_is_end(*result) % 2 || flag))) {
              s21_decimal t = {{1, 0, 0, 0}};
              s21_dir_add(*result, t, result);
            }
          }
        }
      }
    } else {
      res = for_sub(value_1, value_2, result);
    }
  }
  return res;
}

int s21_dir_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int depot = 0, mask = 1;
  for (int i = 0; i < 96; i++) {
    if (value_1.bits[i / 32] & (mask << (i % 32))) depot++;
    if (value_2.bits[i / 32] & (mask << (i % 32))) depot++;
    if (depot % 2 == 1) {
      if (!(result->bits[i / 32] & mask << (i % 32)))
        result->bits[i / 32] += mask << (i % 32);
      depot == 1 ? (depot = 0) : (depot = 1);
    } else if (depot == 2) {
      if ((result->bits[i / 32] & mask << (i % 32)))
        result->bits[i / 32] -= mask << i % 32;
      depot = 1;
    }
  }
  return depot;
}

int for_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sign_1 = s21_get_sign(value_1), res = 0;

  if (sign_1 == 1) {
    s21_negate(value_2, &value_2);
    if (s21_is_less(value_2, value_1)) {
      res = s21_sub(value_1, value_2, result);
    } else {
      res = s21_sub(value_2, value_1, result);
      s21_negate(*result, result);
    }
  } else {
    s21_negate(value_1, &value_1);
    if (s21_is_greater_or_equal(value_2, value_1)) {
      res = s21_sub(value_2, value_1, result);
    } else {
      res = s21_sub(value_1, value_2, result);
      s21_negate(*result, result);
    }
  }
  return res;
}
