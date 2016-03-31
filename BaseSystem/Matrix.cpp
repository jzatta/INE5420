
//#include "Point.hpp"
#include <utility>
#include <math.h>
#include <string.h>
#include "Matrix.hpp"

#define PI 3.14159265

// multiply and sabe in a
static void multMatrix(float a[3][3], float b[3][3]) {
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
  memcpy(ret, a, 3*3*sizeof(float));
}

void Matrix::constructScalonateMatrix(float a[3][3], float size, std::pair<float,float> center) {
	a[0][0] = size;
	a[0][1] = 0;
	a[0][2] = 0;
	a[1][0] = 0;
	a[1][1] = size;
	a[1][2] = 0;
	a[2][0] = center.first * (1 - size);
	a[2][1] = center.second * (1 - size);
	a[2][2] = 1;
}

void Matrix::constructRotateMatrix(float a[3][3], float angle, std::pair<float,float> center) {
	float rad = (angle*PI)/180;
	a[0][0] = cosf(rad);
	a[0][1] = -sinf(rad);
	a[0][2] = 0;
	a[1][0] = sinf(rad);
	a[1][1] = cosf(rad);
	a[1][2] = 0;
	a[2][0] = center.first * -cosf(rad) - center.second * sinf(rad) + center.first;
	a[2][1] = center.first * sinf(rad) - center.second * cosf(rad) + center.second;
	a[2][2] = 1;

}