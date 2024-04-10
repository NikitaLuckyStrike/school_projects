#include "s21_decimal.h"

void s21_null(s21_decimal *dst) {
  for (int i = 0; i < 4; i++) dst->bits[i] = 0;
}
