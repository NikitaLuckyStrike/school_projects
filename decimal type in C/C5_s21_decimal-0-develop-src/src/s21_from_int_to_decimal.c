#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int result = 0;
  if (dst == NULL) {
    result = 1;
  } else {
    s21_null(dst);
    if (src >= 0) {
      dst->bits[0] = src;
    } else {
      dst->bits[3] += 1 << 31;
      dst->bits[0] = -src;
    }
  }
  return result;
}
