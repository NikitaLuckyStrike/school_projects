#include "s21_decimal.h"

void s21_set_exp(int e, s21_decimal *dst) {
  int mask = 1;
  for (int i = 0; i < 8; i++) {
    if (e & mask << i) {
      if (!(dst->bits[3] & mask << (16 + i))) dst->bits[3] += mask << (16 + i);
    } else {
      if (dst->bits[3] & mask << (16 + i)) dst->bits[3] -= (mask << (16 + i));
    }
  }
}
