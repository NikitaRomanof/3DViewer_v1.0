#include "s21_matrix.h"

matrix_t s21_create_matrix(int rows, int columns) {
  matrix_t A = {0};

  A.rows = rows;
  A.columns = columns;

  A.matrix = (float **)calloc(rows, sizeof(float *));

  for (int i = 0; i < rows; i++) {
    A.matrix[i] = (float *)calloc(columns, sizeof(float));
  }

  s21_fill_matrix(&A, 0);

  return A;
}

void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    free(A->matrix[i]);
  }

  free(A->matrix);

  A->columns = 0;
  A->rows = 0;
  A->matrix = NULL;
}

matrix_t s21_mult_number(matrix_t *A, float number) {
  matrix_t resultMatrix = s21_create_matrix(A->rows, A->columns);

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      resultMatrix.matrix[i][j] = A->matrix[i][j] * number;
    }
  }

  return resultMatrix;
}

matrix_t s21_mult_matrix(matrix_t *A, matrix_t *B) {
  matrix_t resultMatrix = s21_create_matrix(A->rows, B->columns);

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      for (int k = 0; k < B->rows; k++) {
        resultMatrix.matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }

  return resultMatrix;
}

void s21_fill_matrix(matrix_t *A, float value) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] = value;
    }
  }
}

void s21_addArrayToMatrix(matrix_t *A, const float *array, int arrayLength) {
  for (int i = 0, count = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns && count < arrayLength; j++) {
      A->matrix[i][j] = array[count];
      count++;
    }
  }
}
