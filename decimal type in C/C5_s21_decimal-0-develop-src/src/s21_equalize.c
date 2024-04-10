#include "s21_decimal.h"

int s21_equalize(int *exp_1, int *exp_2, s21_decimal *value_1,
                 s21_decimal *value_2, int *f) {
  int result = 0;
  int flag = 0;
  for (; *exp_1 > *exp_2 && !s21_is_end(*value_1); (*exp_1)--)
    s21_cut_10(value_1);
  s21_decimal temp = {0};
  s21_copy(&temp, *value_2);
  for (; *exp_2 < *exp_1 && !s21_offset(1, &temp) && !s21_sum(1, &temp);
       (*exp_2)++)
    s21_copy(value_2, temp);
  for (; *exp_1 > *exp_2; (*exp_1)--) {
    result = s21_cut_10(value_1);
    if (result && *exp_1 - 1 > *exp_2) flag = 1;
    if (result) *f = 1;
  }
  return result == 5 ? (result + flag) : result;
}
