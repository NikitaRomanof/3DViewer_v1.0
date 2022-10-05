#ifndef S21_MATRIX
#define S21_MATRIX
#define SUCCESS 1
#define FAILURE 0
#define EPSILON 1e-7

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct matrix_struct {
  float **matrix;
  int rows;
  int columns;
} matrix_t;

matrix_t s21_create_matrix(int rows, int columns);
void s21_remove_matrix(matrix_t *A);

matrix_t s21_mult_number(matrix_t *A, float number);
matrix_t s21_mult_matrix(matrix_t *A, matrix_t *B);

void s21_fill_matrix(matrix_t *A, float value);
void s21_addArrayToMatrix(matrix_t *A, const float *array, int arrayLength);

#endif
