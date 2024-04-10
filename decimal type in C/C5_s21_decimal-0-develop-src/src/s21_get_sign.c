#include "s21_decimal.h"

int s21_get_sign(s21_decimal x) { return (x.bits[3] & (1 << 31)) ? -1 : 1; }
