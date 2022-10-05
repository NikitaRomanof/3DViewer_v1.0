#include "affineTransformations.h"

void moveObject(float **loadArray, int n, float move, int cordinate,
                float **loadArray2) {
  float x = 0;
  float y = 0;
  float z = 0;
  if (cordinate == 1) {
    x = move;
  } else if (cordinate == 2) {
    y = move;
  } else if (cordinate == 3) {
    z = move;
  }
  float moveArray[] = {1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z, 0, 0, 0, 1};

  matrix_t moveMatrix = s21_create_matrix(4, 4);
  s21_addArrayToMatrix(&moveMatrix, moveArray,
                       sizeof(moveArray) / sizeof(float));

  float poundArray[4];
  for (int i = 0; i < n; i++) {
    poundArray[0] = loadArray[i][0];
    poundArray[1] = loadArray[i][1];
    poundArray[2] = loadArray[i][2];
    poundArray[3] = 1.0;
    matrix_t poundMatrix = s21_create_matrix(4, 1);
    s21_addArrayToMatrix(&poundMatrix, poundArray,
                         sizeof(poundArray) / sizeof(float));
    matrix_t resultMatrix = s21_mult_matrix(&moveMatrix, &poundMatrix);
    loadArray2[i][0] = resultMatrix.matrix[0][0];
    loadArray2[i][1] = resultMatrix.matrix[1][0];
    loadArray2[i][2] = resultMatrix.matrix[2][0];
    s21_remove_matrix(&resultMatrix);
    s21_remove_matrix(&poundMatrix);
  }

  s21_remove_matrix(&moveMatrix);
}

void turnObject(float **loadArray, int n, int degrees, int cordinate,
                float **loadArray2) {
  float radians = degrees * PI / 180;
  float turnArray[16];
  if (cordinate == 1) {
    turnArray[0] = 1;
    turnArray[1] = 0;
    turnArray[2] = 0;
    turnArray[3] = 0;
    turnArray[4] = 0;
    turnArray[5] = cos(radians);
    turnArray[6] = sin(radians);
    turnArray[7] = 0;
    turnArray[8] = 0;
    turnArray[9] = -sin(radians);
    turnArray[10] = cos(radians);
    turnArray[11] = 0;
    turnArray[12] = 0;
    turnArray[13] = 0;
    turnArray[14] = 0;
    turnArray[15] = 1;
  } else if (cordinate == 2) {
    turnArray[0] = cos(radians);
    turnArray[1] = 0;
    turnArray[2] = -sin(radians);
    turnArray[3] = 0;
    turnArray[4] = 0;
    turnArray[5] = 1;
    turnArray[6] = 0;
    turnArray[7] = 0;
    turnArray[8] = sin(radians);
    turnArray[9] = 0;
    turnArray[10] = cos(radians);
    turnArray[11] = 0;
    turnArray[12] = 0;
    turnArray[13] = 0;
    turnArray[14] = 0;
    turnArray[15] = 1;
  } else if (cordinate == 3) {
    turnArray[0] = cos(radians);
    turnArray[1] = sin(radians);
    turnArray[2] = 0;
    turnArray[3] = 0;
    turnArray[4] = -sin(radians);
    turnArray[5] = cos(radians);
    turnArray[6] = 0;
    turnArray[7] = 0;
    turnArray[8] = 0;
    turnArray[9] = 0;
    turnArray[10] = 1;
    turnArray[11] = 0;
    turnArray[12] = 0;
    turnArray[13] = 0;
    turnArray[14] = 0;
    turnArray[15] = 1;
  }

  matrix_t turnMatrix = s21_create_matrix(4, 4);
  s21_addArrayToMatrix(&turnMatrix, turnArray,
                       sizeof(turnArray) / sizeof(float));
  float poundArray[4];
  for (int i = 0; i < n; i++) {
    poundArray[0] = loadArray[i][0];
    poundArray[1] = loadArray[i][1];
    poundArray[2] = loadArray[i][2];
    poundArray[3] = 1.0;
    matrix_t poundMatrix = s21_create_matrix(4, 1);
    s21_addArrayToMatrix(&poundMatrix, poundArray,
                         sizeof(poundArray) / sizeof(float));
    matrix_t resultMatrix = s21_mult_matrix(&turnMatrix, &poundMatrix);
    loadArray2[i][0] = resultMatrix.matrix[0][0];
    loadArray2[i][1] = resultMatrix.matrix[1][0];
    loadArray2[i][2] = resultMatrix.matrix[2][0];
    s21_remove_matrix(&resultMatrix);
    s21_remove_matrix(&poundMatrix);
  }

  s21_remove_matrix(&turnMatrix);
}

void scaleObject(float **loadArray, int n, float scale, float **loadArray2) {
  float poundArray[4];
  for (int i = 0; i < n; i++) {
    poundArray[0] = loadArray[i][0];
    poundArray[1] = loadArray[i][1];
    poundArray[2] = loadArray[i][2];
    poundArray[3] = 1.0;
    matrix_t poundMatrix = s21_create_matrix(4, 1);
    s21_addArrayToMatrix(&poundMatrix, poundArray,
                         sizeof(poundArray) / sizeof(float));
    matrix_t resultMatrix = s21_mult_number(&poundMatrix, scale);
    loadArray2[i][0] = resultMatrix.matrix[0][0];
    loadArray2[i][1] = resultMatrix.matrix[1][0];
    loadArray2[i][2] = resultMatrix.matrix[2][0];
    s21_remove_matrix(&resultMatrix);
    s21_remove_matrix(&poundMatrix);
  }
}
