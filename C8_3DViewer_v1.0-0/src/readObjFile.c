#include "readObjFile.h"

void readFile(char* path, float** vertexArray, int length, int width) {
  FILE* file = fopen(path, "r");
  char str[256];
  char* token;
  surfaceArray surfaces;
  surfaces.lenght = 0;
  surfaces.width = width;
  surfaces.data = calloc(sizeof(surfaceData), length);
  pointArray points;
  points.data = calloc(sizeof(pointData), length);
  points.lenght = 0;
  while (!feof(file)) {
    if (fgets(str, 256, file)) {
      token = strtok(str, " ");
      if (token != NULL) {
        if (strcmp(token, "v") ==
            0) {  //  проверка что строка содержит список вершин
          fillPointArray(token, &points);
        } else if (strcmp(token, "f") ==
                   0) {  //  проверка что строка содержит список поверхностей
          fillSurfaceDataArray(token, &surfaces);
        }
      }
    }
  }
  fclose(file);
  int count = 0;
  for (int i = 0; i < surfaces.lenght; i++) {
    for (int j = 0; j < surfaces.width; j++) {
      vertexArray[count][0] = points.data[surfaces.data[i].f[j] - 1].x;
      vertexArray[count][1] = points.data[surfaces.data[i].f[j] - 1].y;
      vertexArray[count][2] = points.data[surfaces.data[i].f[j] - 1].z;
      count++;
    }
  }
  free(surfaces.data);
  free(points.data);
}

int getStringsQantity(char* path, int* lenght, int* width) {
  *width -= 1;
  int error = 0;
  FILE* file = fopen(path, "r");
  if (file != NULL) {
    char str[256];
    char* token;
    while (!feof(file)) {
      if (fgets(str, 256, file)) {
        token = strtok(str, " ");
        if (token != NULL && strcmp(token, "f") == 0) {
          if (*lenght == 0) {
            for (int i = 0; token != 0; i++) {
              *width += 1;
              token = strtok(NULL, " ");
            }
          }
          *lenght += 1;
        }
      }
    }
    fclose(file);
    *lenght *= *width;
  } else {
    error = 1;
  }
  return error;
}

void fillPointArray(char* token, pointArray* points) {
  token = strtok(NULL, " ");
  if (token != NULL) {
      points->data[points->lenght].x = strtof(token, NULL);
  } else {
      points->data[points->lenght].x = 0.0f;
  }
  token = strtok(NULL, " ");
  if (token != NULL) {
      points->data[points->lenght].y = strtof(token, NULL);
  } else {
      points->data[points->lenght].y = 0.0f;
  }
  token = strtok(NULL, " ");
  if (token != NULL) {
      points->data[points->lenght].z = strtof(token, NULL);
  } else {
      points->data[points->lenght].z = 0.0f;
  }
  points->lenght += 1;
}

void fillSurfaceDataArray(char* token, surfaceArray* surfaces) {
  token = strtok(NULL, " ");
  for (int i = 0; token != 0; i++) {
    surfaces->data[surfaces->lenght].f[i] = atol(token);
    token = strtok(NULL, " ");
  }
  surfaces->lenght += 1;
}
