#include "s21_decimal.h"

void s21_set_sign(s21_decimal *dst) {
  if (!(dst->bits[3] & 1 << 31)) dst->bits[3] += (1 << 31);
}
