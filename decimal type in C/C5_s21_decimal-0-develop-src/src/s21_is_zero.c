#include "s21_decimal.h"

int s21_is_zero(s21_decimal x) {
  int result = 0, mask = 1;

  for (int i = 0; i < 96 && !result; i++) {
    if (x.bits[i / 32] & mask << (i % 32)) result = 1;
  }

  return result;
}
