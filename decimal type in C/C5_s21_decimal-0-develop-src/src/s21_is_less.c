#include "s21_decimal.h"

int s21_is_less(s21_decimal x, s21_decimal y) {
  int result = 0;
  int ex = s21_get_exp(x), ey = s21_get_exp(y);

  if (s21_correct(x) || s21_correct(y)) {
    result = 0;
    // fprintf(stderr, "one or both decimal isn`t correct\n");
  } else if (!s21_is_zero(x) && !s21_is_zero(y)) {
    result = 0;
  } else if (s21_get_sign(x) != s21_get_sign(y)) {
    if (s21_get_sign(x) == -1)
      result = 1;
    else
      result = 0;
  } else if (ex == ey) {
    for (int i = 95; i >= 0; i--) {
      if ((x.bits[i / 32] & 1 << (i % 32)) !=
          (y.bits[i / 32] & 1 << (i % 32))) {
        if ((x.bits[i / 32] & 1 << (i % 32) && s21_get_sign(x) == -1) ||
            (y.bits[i / 32] & 1 << (i % 32) && s21_get_sign(x) == 1))
          result = 1;
        i = 0;
      }
    }
  } else {
    if (ex < ey) {
      if (!(s21_offset(ey - ex, &x)) && !(s21_sum(ey - ex, &x))) {
        s21_set_exp(ey, &x);
        result = s21_is_less(x, y);
      } else {
        if (s21_get_sign(x) == -1) result = 1;
      }
    } else {
      if (!(s21_offset(ex - ey, &y)) && !(s21_sum(ex - ey, &y))) {
        s21_set_exp(ex, &y);
        result = s21_is_less(x, y);
      } else {
        if (s21_get_sign(y) == 1) result = 1;
      }
    }
  }
  return result;
}
