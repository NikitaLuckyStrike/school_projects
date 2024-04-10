#include "s21_decimal.h"

int s21_is_big(float x) {
  int result = 0, temp = *((int *)(&x)), mask = 1, sum = -127;
  mask <<= 23;
  for (int i = 0, e = 1; i < 8; i++, e *= 2) {
    if (temp & mask) sum += e;
    mask <<= 1;
  }
  if (sum >= 96) result = 1;
  return result;
}
