
//#include "Point.hpp"
#include <utility>
#include <math.h>
#include <string.h>
#include "Matrix.hpp"

#define PI 3.14159265

Matrix::Matrix(float _m[3][3]) {
  this->matrix[0][0] = _m[0][0];
  this->matrix[0][1] = _m[0][1];
  this->matrix[0][2] = _m[0][2];
  this->matrix[1][0] = _m[1][0];
  this->matrix[1][1] = _m[1][1];
  this->matrix[1][2] = _m[1][2];
  this->matrix[2][0] = _m[2][0];
  this->matrix[2][1] = _m[2][1];
  this->matrix[2][2] = _m[2][2];
}

Matrix::Matrix() {
  this->matrix[0][0] = 1;
  this->matrix[0][1] = 0;
  this->matrix[0][2] = 0;
  this->matrix[1][0] = 0;
  this->matrix[1][1] = 1;
  this->matrix[1][2] = 0;
  this->matrix[2][0] = 0;
  this->matrix[2][1] = 0;
  this->matrix[2][2] = 1;
}

void Matrix::setMatrix(float _m[3][3]) {
  this->matrix[0][0] = _m[0][0];
  this->matrix[0][1] = _m[0][1];
  this->matrix[0][2] = _m[0][2];
  this->matrix[1][0] = _m[1][0];
  this->matrix[1][1] = _m[1][1];
  this->matrix[1][2] = _m[1][2];
  this->matrix[2][0] = _m[2][0];
  this->matrix[2][1] = _m[2][1];
  this->matrix[2][2] = _m[2][2];
}

void Matrix::getTransPoint(float _points[3]) {
  float tmpP[3];
  tmpP[0] = _points[0]*matrix[0][0] + _points[1]*matrix[1][0] + _points[2]*matrix[2][0];
  tmpP[1] = _points[0]*matrix[0][1] + _points[1]*matrix[1][1] + _points[2]*matrix[2][1];
  tmpP[2] = _points[0]*matrix[0][2] + _points[1]*matrix[1][2] + _points[2]*matrix[2][2];
  memcpy(_points, tmpP, 3*sizeof(float));
}

void Matrix::multMatrix(Matrix *m) {
  float ret[3][3];
  ret[0][0] = matrix[0][0]*m->matrix[0][0] + matrix[0][1]*m->matrix[1][0] + matrix[0][2]*m->matrix[2][0];
  ret[0][1] = matrix[0][0]*m->matrix[0][1] + matrix[0][1]*m->matrix[1][1] + matrix[0][2]*m->matrix[2][1];
  ret[0][2] = matrix[0][0]*m->matrix[0][2] + matrix[0][1]*m->matrix[1][2] + matrix[0][2]*m->matrix[2][2];
  ret[1][0] = matrix[1][0]*m->matrix[0][0] + matrix[1][1]*m->matrix[1][0] + matrix[1][2]*m->matrix[2][0];
  ret[1][1] = matrix[1][0]*m->matrix[0][1] + matrix[1][1]*m->matrix[1][1] + matrix[1][2]*m->matrix[2][1];
  ret[1][2] = matrix[1][0]*m->matrix[0][2] + matrix[1][1]*m->matrix[1][2] + matrix[1][2]*m->matrix[2][2];
  ret[2][0] = matrix[2][0]*m->matrix[0][0] + matrix[2][1]*m->matrix[1][0] + matrix[2][2]*m->matrix[2][0];
  ret[2][1] = matrix[2][0]*m->matrix[0][1] + matrix[2][1]*m->matrix[1][1] + matrix[2][2]*m->matrix[2][1];
  ret[2][2] = matrix[2][0]*m->matrix[0][2] + matrix[2][1]*m->matrix[1][2] + matrix[2][2]*m->matrix[2][2];
  memcpy(matrix, ret, 3*3*sizeof(float));
}

void Matrix::multMatrixAndDelete(Matrix *m) {
  this->multMatrix(m);
  delete m;
}

void Matrix::multMatrix(float a[3][3], float b[3][3]) {
  float ret[3][3];
  ret[0][0] = a[0][0]*b[0][0] + a[0][1]*b[1][0] + a[0][2]*b[2][0];
  ret[0][1] = a[0][0]*b[0][1] + a[0][1]*b[1][1] + a[0][2]*b[2][1];
  ret[0][2] = a[0][0]*b[0][2] + a[0][1]*b[1][2] + a[0][2]*b[2][2];
  ret[1][0] = a[1][0]*b[0][0] + a[1][1]*b[1][0] + a[1][2]*b[2][0];
  ret[1][1] = a[1][0]*b[0][1] + a[1][1]*b[1][1] + a[1][2]*b[2][1];
  ret[1][2] = a[1][0]*b[0][2] + a[1][1]*b[1][2] + a[1][2]*b[2][2];
  ret[2][0] = a[2][0]*b[0][0] + a[2][1]*b[1][0] + a[2][2]*b[2][0];
  ret[2][1] = a[2][0]*b[0][1] + a[2][1]*b[1][1] + a[2][2]*b[2][1];
  ret[2][2] = a[2][0]*b[0][2] + a[2][1]*b[1][2] + a[2][2]*b[2][2];
  memcpy(a, ret, 3*3*sizeof(float));
}

Matrix *Matrix::constructTranslateMatrix(float dx, float dy) {
  Matrix *ret = new Matrix();
  ret->matrix[0][0] = 1;
  ret->matrix[0][1] = 0;
  ret->matrix[1][0] = 0;
  ret->matrix[1][1] = 1;
  ret->matrix[2][0] = dx;
  ret->matrix[2][1] = dy;
  return ret;
}

Matrix *Matrix::constructScalonateMatrix(float scale) {
  return Matrix::constructScalonateMatrix(scale, scale);
}

Matrix *Matrix::constructScalonateMatrix(float scalex, float scaley) {
  Matrix *ret = new Matrix();
  ret->matrix[0][0] = scalex;
  ret->matrix[0][1] = 0;
  ret->matrix[1][0] = 0;
  ret->matrix[1][1] = scaley;
  ret->matrix[2][0] = 0;
  ret->matrix[2][1] = 0;
  return ret;
}

Matrix *Matrix::constructRotateMatrix(float angle) {
  Matrix *ret = new Matrix();
  float rad = (angle*PI)/180;
  ret->matrix[0][0] = cosf(rad);
  ret->matrix[0][1] = -sinf(rad);
  ret->matrix[1][0] = sinf(rad);
  ret->matrix[1][1] = cosf(rad);
  ret->matrix[2][0] = 0;
  ret->matrix[2][1] = 0;
  return ret;
}