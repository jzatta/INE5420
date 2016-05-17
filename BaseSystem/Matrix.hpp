#ifndef _CG_MATRIX_HPP_
#define _CG_MATRIX_HPP_

class Matrix;

#include <utility>

#define MSIZE 4

class Matrix {
private:
  float matrix[MSIZE][MSIZE];
public:
  Matrix(float _m[MSIZE][MSIZE]);
  Matrix();
  void setMatrix(float _m[MSIZE][MSIZE]);
  void getTransPoint(float _points[MSIZE]);
  
  void multMatrix(Matrix *m);
  void multMatrixAndDelete(Matrix *m);
  
  static void multMatrix(float a[MSIZE][MSIZE], float b[MSIZE][MSIZE]);
  
  static Matrix *constructTranslateMatrix(float dx, float dy, float dz);
  static Matrix *constructScalonateMatrix(float scale);
  static Matrix *constructScalonateMatrix(float scalex, float scaley, float scalez);
  static Matrix *constructRotateMatrixX(float angle);
  static Matrix *constructRotateMatrixY(float angle);
  static Matrix *constructRotateMatrixZ(float angle);
};

#endif
