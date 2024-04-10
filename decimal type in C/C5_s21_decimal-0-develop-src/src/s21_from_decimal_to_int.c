#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int result = 0;
  if (dst == NULL || s21_truncate(src, &src) || src.bits[1] || src.bits[2] ||
      ((src.bits[0] & 1 << 31) && !(src.bits[3] & 1 << 31))) {
    result = 1;
  } else {
    *dst = 0;
    for (int i = 0, temp = 1; i < 32; temp *= 2, i++) {
      if (src.bits[0] & 1 << i) *dst += temp;
    }
    if (src.bits[3] & 1 << 31) *dst *= -1;
  }
  return result;
}
