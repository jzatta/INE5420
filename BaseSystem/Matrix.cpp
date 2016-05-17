
//#include "Point.hpp"
#include <utility>
#include <math.h>
#include <string.h>
#include "Matrix.hpp"
#include <stdio.h>

#define PI 3.14159265

Matrix::Matrix(float _m[MSIZE][MSIZE]) {
  this->setMatrix(_m);
}

Matrix::Matrix() {
  int l, c;
  for (l = 0; l < MSIZE; l++) {
    for (c = 0; c < MSIZE; c++) {
      this->matrix[l][c] = (l == c)? 1 : 0;
    }
  }
}

void Matrix::setMatrix(float _m[MSIZE][MSIZE]) {
  int l, c;
  for (l = 0; l < MSIZE; l++) {
    for (c = 0; c < MSIZE; c++) {
      this->matrix[l][c] = _m[l][c];
    }
  }
}

void Matrix::getTransPoint(float _points[MSIZE]) {
  float tmpP[MSIZE];
  int i, j;
  for (i = 0; i < MSIZE; i++) {
    tmpP[i] = 0;
    for (j = 0; j < MSIZE; j++) {
      tmpP[i] += _points[j]*this->matrix[j][i];
    }
  }
  memcpy(_points, tmpP, MSIZE*sizeof(float));
}

void Matrix::multMatrix(Matrix *m) {
  float ret[MSIZE][MSIZE];
  int i, j, k;
  for (i = 0; i < MSIZE; i++) {
    for (j = 0; j < MSIZE; j++) {
      ret[i][j] = 0;
      for (k = 0; k < MSIZE; k++) {
        ret[i][j] += m->matrix[i][k]*this->matrix[k][j];
      }
    }
  }
  memcpy(this->matrix, ret, MSIZE*MSIZE*sizeof(float));
}

void Matrix::multMatrixAndDelete(Matrix *m) {
  this->multMatrix(m);
  delete m;
}

void Matrix::multMatrix(float a[4][4], float b[4][4]) {
  float ret[MSIZE][MSIZE];
  int i, j, k;
  for (i = 0; i < MSIZE; i++) {
    for (j = 0; j < MSIZE; j++) {
      ret[i][j] = 0;
      for (k = 0; k < MSIZE; k++) {
        ret[i][j] += a[i][k]*b[k][j];
      }
    }
  }
  memcpy(a, ret, MSIZE*MSIZE*sizeof(float));
}

Matrix *Matrix::constructTranslateMatrix(float dx, float dy, float dz) {
  Matrix *ret = new Matrix(); // constrct ID matrix
  ret->matrix[3][0] = dx;
  ret->matrix[3][1] = dy;
  ret->matrix[3][2] = dz;
  return ret;
}

Matrix *Matrix::constructScalonateMatrix(float scale) {
  return Matrix::constructScalonateMatrix(scale, scale, scale);
}

Matrix *Matrix::constructScalonateMatrix(float scalex, float scaley, float scalez) {
  Matrix *ret = new Matrix(); // constrct ID matrix
  ret->matrix[0][0] = scalex;
  ret->matrix[1][1] = scaley;
  ret->matrix[2][2] = scalez;
  return ret;
}

Matrix *Matrix::constructRotateMatrixX(float angle) {
  Matrix *ret = new Matrix(); // constrct ID matrix
  float rad = (angle*PI)/180;
  ret->matrix[1][1] = cosf(rad);
  ret->matrix[2][1] = -sinf(rad);
  ret->matrix[1][2] = sinf(rad);
  ret->matrix[2][2] = cosf(rad);
  return ret;
}

Matrix *Matrix::constructRotateMatrixY(float angle) {
  Matrix *ret = new Matrix(); // constrct ID matrix
  float rad = (angle*PI)/180;
  ret->matrix[0][0] = cosf(rad);
  ret->matrix[2][0] = sinf(rad);
  ret->matrix[0][2] = -sinf(rad);
  ret->matrix[2][2] = cosf(rad);
  return ret;
}

Matrix *Matrix::constructRotateMatrixZ(float angle) {
  Matrix *ret = new Matrix(); // constrct ID matrix
  float rad = (angle*PI)/180;
  ret->matrix[0][0] = cosf(rad);
  ret->matrix[0][1] = sinf(rad);
  ret->matrix[1][0] = -sinf(rad);
  ret->matrix[1][1] = cosf(rad);
  return ret;
}
