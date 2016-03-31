#ifndef _CG_MATRIX_HPP_
#define _CG_MATRIX_HPP_


class Matrix {
public:
  static void multMatrix(float a[3][3], float b[3][3], float ret[3][3]);
  static void constructScalonateMatrix(float a[3][3], float size, std::pair<float,float> center);
  static void constructRotateMatrix(float a[3][3], float angle, std::pair<float,float> center);
};

#endif
