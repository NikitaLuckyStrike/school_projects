#include "s21_decimal.h"

int s21_get_exp(s21_decimal x) {
  int result = 0, mask = 1 << 16, e = 1;

  for (int i = 0; i < 8; i++, e *= 2) {
    if (x.bits[3] & mask << i) result += e;
  }
  return result;
}
