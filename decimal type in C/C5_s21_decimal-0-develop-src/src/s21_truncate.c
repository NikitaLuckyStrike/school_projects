#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int res = 0;

  if (result == NULL || s21_correct(value)) {
    res = 1;
  } else {
    int e = s21_get_exp(value);
    s21_copy(result, value);
    for (; e > 0; e--) {
      s21_cut_10(result);
    }
  }
  return res;
}
