#include "s21_decimal.h"

int s21_is_greater_or_equal(s21_decimal x, s21_decimal y) {
  int result = 0;
  if (s21_is_greater(x, y) || s21_is_equal(x, y)) result = 1;
  return result;
}
