#include "s21_decimal.h"

int s21_is_end(s21_decimal x) {
  int result = 0;

  for (int i = 0; i < 96; i++) {
    if (x.bits[i / 32] & 1 << (i % 32)) {
      if (i == 0)
        result += 1;
      else if (i % 4 == 1)
        result += 2;
      else if (i % 4 == 2)
        result += 4;
      else if (i % 4 == 3)
        result += 8;
      else if (i % 4 == 0)
        result += 6;
    }
  }
  return result % 10;
}
