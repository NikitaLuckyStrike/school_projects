#include "s21_decimal.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res = 0;
  int sign_1 = s21_get_sign(value_1), sign_2 = s21_get_sign(value_2);
  int exp_1 = s21_get_exp(value_1), exp_2 = s21_get_exp(value_2);
  if (sign_2 == -1) s21_negate(value_2, &value_2);
  if (sign_1 == -1) s21_negate(value_1, &value_1);
  if (result) s21_null(result);

  if (!result || s21_correct(value_1) || s21_correct(value_2)) {
    res = 4;
  } else if (s21_is_greater(value_2, value_1) && s21_is_zero(value_1)) {
    s21_copy(result, value_1);
    if (sign_1 == -1) s21_negate(*result, result);
  } else if (!s21_is_zero(value_2)) {
    res = 3;
  } else if (s21_is_equal(value_1, value_2) || !s21_is_zero(value_1)) {
    s21_null(result);
  } else {
    s21_bdcm val_1 = {0}, val_2 = {0};
    s21_from_d_to_bd(&val_1, value_1);
    s21_from_d_to_bd(&val_2, value_2);
    if (exp_1 > exp_2) {
      s21_eq(exp_1 - exp_2, &val_2);
      exp_2 = exp_1;
    } else if (exp_2 > exp_1) {
      s21_eq(exp_2 - exp_1, &val_1);
      exp_1 = exp_2;
    }
    s21_dir_mod(&val_1, &val_2);

    for (int i = 0; i < 3; i++) result->bits[i] = val_1.bits[i];
    s21_set_exp(exp_1, result);
    if (sign_1 == -1) s21_negate(*result, result);
  }

  return res;
}

void s21_dir_mod(s21_bdcm *val_1, s21_bdcm *val_2) {
  int step = 0;
  s21_bdcm temp = {0};
  s21_c(&temp, *val_2);
  s21_slip(1, &temp);
  for (; s21_less(temp, *val_1); step++) {
    s21_c(val_2, temp);
    s21_slip(1, &temp);
  }
  for (; s21_lp(*val_2, *val_1) || step > 0;) {
    if (s21_lp(*val_2, *val_1)) {
      s21_min(*val_1, *val_2, val_1);
    } else if (step > 0) {
      s21_cut_2(val_2);
      step--;
    }
  }
}

int s21_from_d_to_bd(s21_bdcm *dst, s21_decimal src) {
  int result = 0;
  if (!dst) {
    // result = 1;
  } else {
    for (int i = 0; i < 8; i++) {
      if (i < 3)
        dst->bits[i] = src.bits[i];
      else
        dst->bits[i] = 0;
    }
  }
  return result;
}

void s21_eq(int e, s21_bdcm *x) {
  s21_bdcm temp = {0};
  s21_slip(e, x);
  for (int i = 0; i < e; i++) {
    s21_c(&temp, *x);
    s21_slip(2, x);
    s21_s(x, temp);
  }
}

void s21_s(s21_bdcm *dst, s21_bdcm temp) {
  int depot = 0;
  for (int i = 0; i < 213; i++) {
    if (dst->bits[i / 32] & (1 << (i % 32))) depot++;
    if (temp.bits[i / 32] & (1 << (i % 32))) depot++;
    if (depot == 1) {
      if (!(dst->bits[i / 32] & (1 << (i % 32))))
        dst->bits[i / 32] += 1 << (i % 32);
      depot = 0;
    } else if (depot == 2) {
      if (dst->bits[i / 32] & 1 << (i % 32))
        dst->bits[i / 32] -= (1 << (i % 32));
      depot = 1;
    } else if (depot == 3) {
      depot = 1;
    }
  }
}

void s21_slip(int e, s21_bdcm *dst) {
  int start = 213;
  for (; !(dst->bits[start / 32] & 1 << (start % 32)) && start > 0;) start--;

  for (int i = start; i >= 0; i--) {
    int k = i + e;
    if (dst->bits[i / 32] & 1 << (i % 32)) {
      if (!(dst->bits[k / 32] & 1 << (k % 32)))
        dst->bits[k / 32] += (1 << (k % 32));
    } else {
      if ((dst->bits[k / 32] & 1 << (k % 32)))
        dst->bits[k / 32] -= (1 << (k % 32));
    }
  }
  for (int m = 0; m < e; m++) {
    dst->bits[m / 32] -= (dst->bits[m / 32] & 1 << m % 32);
  }
}

void s21_c(s21_bdcm *dst, s21_bdcm src) {
  for (int i = 0; i < 8; i++) {
    dst->bits[i] = src.bits[i];
  }
}

int s21_less(s21_bdcm v_1, s21_bdcm v_2) {
  int result = 0;

  for (int i = 213; i >= 0 && !result; i--) {
    int sum = 0;
    if (v_1.bits[i / 32] & 1 << (i % 32)) sum += 1;
    if (v_2.bits[i / 32] & 1 << (i % 32)) sum -= 1;
    if (sum == 1) i = 0;
    if (sum == -1) result = 1;
  }
  return result;
}

int s21_pavno(s21_bdcm v_1, s21_bdcm v_2) {
  int result = 1;

  for (int i = 213; i >= 0 && result; i--) {
    int sum = 0;
    if (v_1.bits[i / 32] & 1 << (i % 32)) sum += 1;
    if (v_2.bits[i / 32] & 1 << (i % 32)) sum -= 1;
    if (sum != 0) result = 0;
  }
  return result;
}

int s21_lp(s21_bdcm v_1, s21_bdcm v_2) {
  int result = 0;
  if (s21_less(v_1, v_2) || s21_pavno(v_1, v_2)) result = 1;
  return result;
}

int s21_cut_2(s21_bdcm *x) {
  int result = -1;
  if (x) {
    int temp = 0, mask = 2;
    s21_bdcm y = {0};
    for (int i = 213; i >= 0; i--) {
      temp <<= 1;
      if (x->bits[i / 32] & 1 << i % 32) temp += 1;
      s21_slip(1, &y);
      if (temp >= mask) {
        temp -= mask;
        y.bits[0] += 1;
      }
    }
    s21_c(x, y);
    result = temp;
  }
  return result;
}
void s21_min(s21_bdcm value_1, s21_bdcm value_2, s21_bdcm *result) {
  int depot = 0, mask = 1, sum = 0;
  for (int i = 213; i >= 0; i--) {
    if (value_1.bits[i / 32] & mask << (i % 32)) sum += 1;
    if (value_2.bits[i / 32] & mask << (i % 32)) sum -= 1;

    if (sum == 1) {
      if (!(result->bits[i / 32] & mask << (i % 32)))
        result->bits[i / 32] += mask << (i % 32);
      sum -= 1;
    } else if (sum == -1) {
      result->bits[depot / 32] -= mask << (depot % 32);
      for (int k = depot - 1; k >= i; k--) {
        result->bits[k / 32] += mask << (k % 32);
      }
      sum += 1;
    } else if (result->bits[i / 32] & mask << (i % 32)) {
      result->bits[i / 32] -= mask << (i % 32);
    }
    if (result->bits[i / 32] & mask << (i % 32)) depot = i;
  }
}
int s21_zero(s21_bdcm x) {
  int res = 0;

  for (int i = 0; i < 214 && !res; i++) {
    if (x.bits[i / 32] & 1 << (i % 32)) res = 1;
  }
  return res;
}
