#include <check.h>

#include "affineTransformations.h"
#include "readObjFile.h"

START_TEST(test1_readObj) {
  char *path = "test.obj";
  int length = 0;
  int width = 0;

  getStringsQantity(path, &length, &width);

  ck_assert_int_eq(length, 9);
  ck_assert_int_eq(width, 3);

  float **array = (float **)malloc(length * sizeof(float *));

  for (int i = 0; i < length; i++) {
    array[i] = (float *)malloc(3 * sizeof(float));
  }

  readFile(path, array, length, width);

  for (int i = 0; i < length; i++) {
    free(array[i]);
  }

  free(array);
}
END_TEST

START_TEST(test2_readObj) {
  char *path = "test123.obj";
  int length = 0;
  int width = 0;

  int error = getStringsQantity(path, &length, &width);

  ck_assert_int_eq(error, 1);
}
END_TEST

Suite *readObj_suite(void) {
  Suite *s;
  TCase *tc_readObj;
  s = suite_create("readObj");
  tc_readObj = tcase_create("readObj");
  tcase_add_test(tc_readObj, test1_readObj);
  tcase_add_test(tc_readObj, test2_readObj);

  suite_add_tcase(s, tc_readObj);
  return s;
}

START_TEST(test1_affineTransformations) {
  int length = 1;
  float move = 1.0;

  float **loadArray = (float **)malloc(length * sizeof(float *));
  float **loadArray2 = (float **)malloc(length * sizeof(float *));

  for (int i = 0; i < length; i++) {
    loadArray[i] = (float *)malloc(3 * sizeof(float));
    loadArray2[i] = (float *)malloc(3 * sizeof(float));
  }

  loadArray[0][0] = 4.0;
  loadArray[0][1] = 5.0;
  loadArray[0][2] = 6.0;

  moveObject(loadArray, length, move, 1, loadArray2);

  ck_assert_float_eq(loadArray2[0][0], 5);

  for (int i = 0; i < length; i++) {
    free(loadArray[i]);
    free(loadArray2[i]);
  }

  free(loadArray);
  free(loadArray2);
}
END_TEST

START_TEST(test2_affineTransformations) {
  int length = 1;
  float move = 1.0;

  float **loadArray = (float **)malloc(length * sizeof(float *));
  float **loadArray2 = (float **)malloc(length * sizeof(float *));

  for (int i = 0; i < length; i++) {
    loadArray[i] = (float *)malloc(3 * sizeof(float));
    loadArray2[i] = (float *)malloc(3 * sizeof(float));
  }

  loadArray[0][0] = 4.0;
  loadArray[0][1] = 5.0;
  loadArray[0][2] = 6.0;

  moveObject(loadArray, length, move, 2, loadArray2);

  ck_assert_float_eq(loadArray2[0][1], 6);

  for (int i = 0; i < length; i++) {
    free(loadArray[i]);
    free(loadArray2[i]);
  }

  free(loadArray);
  free(loadArray2);
}
END_TEST

START_TEST(test3_affineTransformations) {
  int length = 1;
  float move = 1.0;

  float **loadArray = (float **)malloc(length * sizeof(float *));
  float **loadArray2 = (float **)malloc(length * sizeof(float *));

  for (int i = 0; i < length; i++) {
    loadArray[i] = (float *)malloc(3 * sizeof(float));
    loadArray2[i] = (float *)malloc(3 * sizeof(float));
  }

  loadArray[0][0] = 4.0;
  loadArray[0][1] = 5.0;
  loadArray[0][2] = 6.0;

  moveObject(loadArray, length, move, 3, loadArray2);

  ck_assert_float_eq(loadArray2[0][2], 7);

  for (int i = 0; i < length; i++) {
    free(loadArray[i]);
    free(loadArray2[i]);
  }

  free(loadArray);
  free(loadArray2);
}
END_TEST

START_TEST(test4_affineTransformations) {
  int length = 1;
  int degrees = 30;

  float **loadArray = (float **)malloc(length * sizeof(float *));
  float **loadArray2 = (float **)malloc(length * sizeof(float *));

  for (int i = 0; i < length; i++) {
    loadArray[i] = (float *)malloc(3 * sizeof(float));
    loadArray2[i] = (float *)malloc(3 * sizeof(float));
  }

  loadArray[0][0] = 4.0;
  loadArray[0][1] = 5.0;
  loadArray[0][2] = 6.0;

  turnObject(loadArray, length, degrees, 1, loadArray2);

  ck_assert_float_eq(loadArray2[0][0], 4);
  ck_assert_float_eq(loadArray2[0][1], 7.33012676239013671875);
  ck_assert_float_eq(loadArray2[0][2], 2.696152210235595703125);

  for (int i = 0; i < length; i++) {
    free(loadArray[i]);
    free(loadArray2[i]);
  }

  free(loadArray);
  free(loadArray2);
}
END_TEST

START_TEST(test5_affineTransformations) {
  int length = 1;
  int degrees = 30;

  float **loadArray = (float **)malloc(length * sizeof(float *));
  float **loadArray2 = (float **)malloc(length * sizeof(float *));

  for (int i = 0; i < length; i++) {
    loadArray[i] = (float *)malloc(3 * sizeof(float));
    loadArray2[i] = (float *)malloc(3 * sizeof(float));
  }

  loadArray[0][0] = 4.0;
  loadArray[0][1] = 5.0;
  loadArray[0][2] = 6.0;

  turnObject(loadArray, length, degrees, 2, loadArray2);

  ck_assert_float_eq(loadArray2[0][0], 0.4641015529632568359375);
  ck_assert_float_eq(loadArray2[0][1], 5);
  ck_assert_float_eq(loadArray2[0][2], 7.196152210235595703125);

  for (int i = 0; i < length; i++) {
    free(loadArray[i]);
    free(loadArray2[i]);
  }

  free(loadArray);
  free(loadArray2);
}
END_TEST

START_TEST(test6_affineTransformations) {
  int length = 1;
  int degrees = 30;

  float **loadArray = (float **)malloc(length * sizeof(float *));
  float **loadArray2 = (float **)malloc(length * sizeof(float *));

  for (int i = 0; i < length; i++) {
    loadArray[i] = (float *)malloc(3 * sizeof(float));
    loadArray2[i] = (float *)malloc(3 * sizeof(float));
  }

  loadArray[0][0] = 4.0;
  loadArray[0][1] = 5.0;
  loadArray[0][2] = 6.0;

  turnObject(loadArray, length, degrees, 3, loadArray2);

  ck_assert_float_eq(loadArray2[0][0], 5.9641017913818359375);
  ck_assert_float_eq(loadArray2[0][1], 2.33012676239013671875);
  ck_assert_float_eq(loadArray2[0][2], 6);

  for (int i = 0; i < length; i++) {
    free(loadArray[i]);
    free(loadArray2[i]);
  }

  free(loadArray);
  free(loadArray2);
}
END_TEST

START_TEST(test7_affineTransformations) {
  int length = 1;
  int scale = 3;

  float **loadArray = (float **)malloc(length * sizeof(float *));
  float **loadArray2 = (float **)malloc(length * sizeof(float *));

  for (int i = 0; i < length; i++) {
    loadArray[i] = (float *)malloc(3 * sizeof(float));
    loadArray2[i] = (float *)malloc(3 * sizeof(float));
  }

  loadArray[0][0] = 4.0;
  loadArray[0][1] = 5.0;
  loadArray[0][2] = 6.0;

  scaleObject(loadArray, length, scale, loadArray2);

  ck_assert_float_eq(loadArray2[0][0], 12);
  ck_assert_float_eq(loadArray2[0][1], 15);
  ck_assert_float_eq(loadArray2[0][2], 18);

  for (int i = 0; i < length; i++) {
    free(loadArray[i]);
    free(loadArray2[i]);
  }

  free(loadArray);
  free(loadArray2);
}
END_TEST

Suite *affineTransformations_suite(void) {
  Suite *s;
  TCase *tc_affineTransformations;
  s = suite_create("affineTransformations");
  tc_affineTransformations = tcase_create("affineTransformations");
  tcase_add_test(tc_affineTransformations, test1_affineTransformations);
  tcase_add_test(tc_affineTransformations, test2_affineTransformations);
  tcase_add_test(tc_affineTransformations, test3_affineTransformations);
  tcase_add_test(tc_affineTransformations, test4_affineTransformations);
  tcase_add_test(tc_affineTransformations, test5_affineTransformations);
  tcase_add_test(tc_affineTransformations, test6_affineTransformations);
  tcase_add_test(tc_affineTransformations, test7_affineTransformations);

  suite_add_tcase(s, tc_affineTransformations);
  return s;
}

void viewer_tests(SRunner **sr) {
  *sr = srunner_create(readObj_suite());
  srunner_add_suite(*sr, affineTransformations_suite());
}

int main(void) {
  int number_failed;
  SRunner *sr = NULL;
  viewer_tests(&sr);
  srunner_run_all(sr, CK_ENV);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
