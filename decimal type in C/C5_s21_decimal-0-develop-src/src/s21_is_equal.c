#include "s21_decimal.h"

int s21_is_equal(s21_decimal x, s21_decimal y) {
  int result = 1;
  int ex = s21_get_exp(x), ey = s21_get_exp(y);
  if (s21_correct(x) || s21_correct(y)) {
    result = 0;
    // fprintf(stderr, "one or both decimal isn`t correct\n");
  } else if (!s21_is_zero(x) && !s21_is_zero(y)) {
    result = 1;
  } else if (ex == ey) {
    int mask = 1;
    for (int i = 0; i < 128 && result; i++) {
      if (i != 127) {
        if ((x.bits[i / 32] & mask << i % 32) !=
            (y.bits[i / 32] & mask << i % 32)) {
          result = 0;
        }
      } else {
        if (s21_get_sign(x) != s21_get_sign(y)) {
          result = 0;
        }
      }
    }
  } else {
    result = 0;
    if (ex < ey) {
      if (!(s21_offset(ey - ex, &x)) && !(s21_sum(ey - ex, &x))) {
        s21_set_exp(ey, &x);
        result = s21_is_equal(x, y);
      }
    } else {
      if (!(s21_offset(ex - ey, &y)) && !(s21_sum(ex - ey, &y))) {
        s21_set_exp(ex, &y);
        result = s21_is_equal(x, y);
      }
    }
  }
  return result;
}
