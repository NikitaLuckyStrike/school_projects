#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int res = 0;

  if (result == NULL || s21_correct(value)) {
    res = 1;
  } else {
    s21_copy(result, value);
    if (result->bits[3] & 1 << 31) {
      result->bits[3] -= (1 << 31);
    } else {
      result->bits[3] += (1 << 31);
    }
  }
  return res;
}
