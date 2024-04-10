#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int result = 0;
  if (dst == NULL || s21_correct(src)) {
    result = 1;
  } else {
    int e = 0, sign = 1, mask = 1, temp = 1;
    double value = 0, st = 1;
    for (int i = 0; i < 32; i++) {
      if (i >= 16 && i < 24) {
        if (src.bits[3] & mask << i) e += temp;
        temp *= 2;
      } else if (i == 31) {
        if (src.bits[3] & mask << i) sign = -1;
      }
    }
    for (int k = 0; k < 96; k++) {
      if (src.bits[k / 32] & mask << k % 32) value += st;
      st *= 2;
    }
    value *= sign;
    for (; e > 0; e--) value /= 10;
    *dst = (float)value;
  }
  return result;
}
