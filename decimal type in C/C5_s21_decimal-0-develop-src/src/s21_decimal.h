#ifndef _SRC_DECIMAL_H_
#define _SRC_DECIMAL_H_

#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 79228162514264337593543950335.L
#define S21_EPS 1e-28

typedef struct {
  int bits[4];
} s21_decimal;

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

void s21_null(s21_decimal *dst);
int s21_is_big(float x);
int s21_is_zero(s21_decimal x);
void s21_set_exp(int e, s21_decimal *dst);
void s21_set_sign(s21_decimal *dst);
int s21_correct(s21_decimal x);
int s21_get_exp(s21_decimal x);
int s21_get_sign(s21_decimal x);
int s21_offset(int e, s21_decimal *dst);           // in float ->decimal.c
int s21_sum(int e, s21_decimal *dst);              // in float -> decimal.c
void s21_copy(s21_decimal *dst, s21_decimal src);  // in float ->decimal.c
int s21_is_end(s21_decimal x);
int s21_cut_10(s21_decimal *x);
int s21_cut_10s(s21_decimal *x, int start);
int s21_dir_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_equalize(int *, int *, s21_decimal *, s21_decimal *, int *);
void s21_dir_sub(s21_decimal, s21_decimal, s21_decimal *);

// for bdcm
typedef struct {
  int bits[8];
} s21_bdcm;

int s21_from_d_to_bd(s21_bdcm *dst, s21_decimal src);
void s21_eq(int e, s21_bdcm *x);
void s21_slip(int e, s21_bdcm *dst);
void s21_s(s21_bdcm *dst, s21_bdcm temp);
void s21_c(s21_bdcm *dst, s21_bdcm src);
int s21_less(s21_bdcm v_1, s21_bdcm v_2);
int s21_pavno(s21_bdcm v_1, s21_bdcm v_2);
int s21_lp(s21_bdcm v_1, s21_bdcm v_2);
void s21_min(s21_bdcm value_1, s21_bdcm value_2, s21_bdcm *result);
int s21_cut_2(s21_bdcm *x);
void s21_dir_mod(s21_bdcm *val_1, s21_bdcm *val_2);
int s21_zero(s21_bdcm x);
int s21_bit(s21_bdcm *x);
void s21_dir_div(s21_bdcm *val_1, s21_bdcm *val_2, s21_bdcm *r, int *);
void s21_n(s21_bdcm *x);
int s21_10(s21_bdcm *x);
int s21_end(s21_bdcm x);
int s21_bit(s21_bdcm *x);
int s21_over(s21_bdcm *x);
#endif  // _SRC_DECIMAL_H_
