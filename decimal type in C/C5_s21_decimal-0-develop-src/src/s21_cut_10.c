#include "s21_decimal.h"

int s21_cut_10(s21_decimal *x) {
  int result = -1;
  if (x && !s21_correct(*x)) {
    int temp = 0, mask = 10;
    s21_decimal y = {0};
    for (int i = 95; i >= 0; i--) {
      temp <<= 1;
      if (x->bits[i / 32] & 1 << i % 32) temp += 1;
      s21_offset(1, &y);
      if (temp >= mask) {
        temp -= mask;
        y.bits[0] += 1;
      }
    }
    s21_set_exp(s21_get_exp(*x) - 1, &y);
    if (s21_get_sign(*x) == -1) s21_set_sign(&y);
    s21_copy(x, y);
    result = temp;
  }
  return result;
}
