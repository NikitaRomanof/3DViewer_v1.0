#ifndef READ_OBJ_FILE
#define READ_OBJ_FILE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct surfaceData {
  long int f[20];
} surfaceData;

typedef struct surfaceArray {
  surfaceData* data;
  int lenght;
  int width;
} surfaceArray;

typedef struct pointData {
  float x;
  float y;
  float z;
} pointData;

typedef struct pointArray {
  pointData* data;
  int lenght;
} pointArray;

int getStringsQantity(char* path, int* lenght, int* width);
void readFile(char* path, float** vertexArray, int length, int width);
void fillPointArray(char* token, pointArray* points);
void fillSurfaceDataArray(char* token, surfaceArray* surfaces);


#endif
