#ifndef _CG_MATRIX_HPP_
#define _CG_MATRIX_HPP_

class Matrix;

#include <utility>

class Matrix {
private:
  float matrix[3][3];
public:
  Matrix(float _m[3][3]);
  Matrix();
  void setMatrix(float _m[3][3]);
  void getTransPoint(float _points[3]);
  
  void multMatrix(Matrix *m);
  void multMatrixAndDelete(Matrix *m);
  
  static void multMatrix(float a[3][3], float b[3][3]);
  
  static Matrix *constructTranslateMatrix(float dx, float dy);
  static Matrix *constructScalonateMatrix(float scale);
  static Matrix *constructScalonateMatrix(float scalex, float scaley);
  static Matrix *constructRotateMatrix(float angle);
};

#endif
