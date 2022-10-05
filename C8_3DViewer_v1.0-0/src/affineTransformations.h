#ifndef AFFINE_TRANSFORMATION 
#define AFFINE_TRANSFORMATION 

#include "s21_matrix.h"
#include <math.h>

#define PI 3.141592653589793238462643
void moveObject(float **loadArray, int n, float move, int cordinate, float **loadArray2);
void turnObject(float **loadArray, int n, int degrees, int cordinates, float **loadArray2);
void scaleObject(float **loadArray, int n, float scale, float **loadArray2);

#endif
