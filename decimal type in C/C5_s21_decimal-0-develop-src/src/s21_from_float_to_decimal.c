#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int result = 0;
  if (dst == NULL) {
    result = 1;
  } else {
    s21_null(dst);
    if (fabs(src) > 0 && fabs(src) < S21_EPS) {
      s21_null(dst);
      result = 1;
    } else if (src == 0) {
      s21_null(dst);
    } else if (s21_is_big(src)) {
      result = 1;
    } else {
      double temp = 1, cp = fabs(src);
      int e = 0;
      if (cp >= 10000000) {
        for (; cp > 10000000; e--) cp /= 10;
        if ((fmod(cp, temp) - fmod(cp, temp / 10)) / (temp / 10) >= 5)
          cp += temp;
        cp -= fmod(cp, temp);
      } else {
        for (; cp < 1000000 && e < 28; e++) cp *= 10;
        int i = 0;
        for (; temp * 10 < cp; i++) temp *= 10;
        for (; i > 0; i--) temp /= 10;
        if ((fmod(cp, temp) - fmod(cp, temp / 10)) / (temp / 10) >= 5)
          cp += +temp;
        cp -= fmod(cp, temp);
      }
      for (; fmod(cp, 10) == 0 && e > 0; e--) cp /= 10;
      s21_from_int_to_decimal(cp, dst);
      if (e > 0 && e < 29) {
        s21_set_exp(e, dst);
      } else if (e < 0) {
        s21_offset(-e, dst);
        s21_sum(-e, dst);
      }
      if (src < 0) s21_set_sign(dst);
      // print_decimal(*dst);
    }
  }
  return result;
}

int s21_offset(int e, s21_decimal *dst) {
  int mask = 1, total = 95, start = 95, result = 0, i = 0;
  for (; !(dst->bits[start / 32] & mask << start % 32) && start > 0;) start--;
  if (start + e <= total) {
    for (i = total; i >= 0; i--) {
      if (dst->bits[i / 32] & mask << i % 32) {
        if (dst->bits[(i + e) / 32] & mask << (i + e) % 32) {
        } else {
          dst->bits[(i + e) / 32] += (mask << (i + e) % 32);
        }
      } else if (dst->bits[(i + e) / 32] & mask << (i + e) % 32) {
        dst->bits[(i + e) / 32] -= (mask << (i + e) % 32);
      }
    }
    for (int k = 0; k < e; k++) {
      dst->bits[k / 32] -= (dst->bits[k / 32] & mask << k % 32);
    }
  } else {
    result = 1;
  }
  return result;
}

void s21_copy(s21_decimal *dst, s21_decimal src) {
  for (int i = 0; i < 4; i++) {
    dst->bits[i] = src.bits[i];
  }
}

int s21_sum(int e, s21_decimal *dst) {
  int mask = 1, result = 0, depot = 0;
  s21_decimal temp = {0};

  for (; e > 0 && !result; e--) {
    depot = 0;
    s21_copy(&temp, *dst);
    result = s21_offset(2, &temp);
    for (int i = 0; i < 96 && !result; i++) {
      if (dst->bits[i / 32] & (mask << (i % 32))) depot++;
      if (temp.bits[i / 32] & (mask << (i % 32))) depot++;
      if (depot == 1) {
        if (!(dst->bits[i / 32] & (mask << (i % 32)))) {
          dst->bits[i / 32] += (mask << (i % 32));
        }
        depot = 0;
      } else if (depot == 2) {
        if (dst->bits[i / 32] & (mask << (i % 32))) {
          dst->bits[i / 32] -= (mask << (i % 32));
        }
        depot = 1;
      } else if (depot == 3) {
        depot = 1;
      }
    }
    if (depot) result = 1;
  }
  return result;
}
