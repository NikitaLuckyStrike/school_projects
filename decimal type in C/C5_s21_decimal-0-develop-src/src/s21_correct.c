#include "s21_decimal.h"

int s21_correct(s21_decimal x) {
  int result = 0, mask = 1;
  for (int i = 0; i < 32 && !result; i++) {
    if ((i >= 0 && i < 16) || (i >= 24 && i < 31)) {
      if (x.bits[3] & mask << i) result = 1;
    }
  }
  int m = s21_get_exp(x);
  if (!(m >= 0 && m <= 28)) result = 1;

  return result;
}
