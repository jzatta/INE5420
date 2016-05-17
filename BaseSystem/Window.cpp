
#include <math.h>
#include <string>
#include "Window.hpp"

#define PIXEL_AREA_MIN 1000
#define HWSIZE 300

Point *Window::wc = new Point("WindowCenter", 0, 0, 0);
Line *Window::vup = new Line("Vup", new Point((std::string*)NULL, -HWSIZE,  -HWSIZE, 0), new Point((std::string*)NULL, -HWSIZE, HWSIZE, 0));
float Window::wAngleX = 0;
float Window::wAngleY = 0;
float Window::wAngleZ = 0;

Point *vectX = new Point("Axis X", 1, 0, 0);
Point *vectY = new Point("Axis Y", 0, 1, 0);
Point *vectZ = new Point("Axis Z", 0, 0, 1);


void Window::center() {
  delete wc;
  wc = new Point((std::string*)NULL, 0, 0);
}

void Window::reset() {
  Window::center();
  delete vup;
  vup = new Line("Vup", new Point((std::string*)NULL, -HWSIZE,  -HWSIZE), new Point((std::string*)NULL, -HWSIZE, HWSIZE));
  wAngle = 0;
}

float Window::getWidth() {
  // Window is a square
  return getHeight();
}

float Window::getHeight() {
  return vup->lenght();
}

float Window::getX() {
  return wc->getX();
}

float Window::getY() {
  return wc->getY();
}

Matrix *Window::getTransform() {
  Matrix *mTrans = Matrix::constructTranslateMatrix(0-(wc->getX()), 0-(wc->getY()));
  mTrans->multMatrixAndDelete(Matrix::constructRotateMatrix(wAngle));
  mTrans->multMatrixAndDelete(Matrix::constructScalonateMatrix(1.0/getWidth(), 1.0/getHeight()));
  return mTrans;
}

void Window::zoom(float factor) {
  Matrix *mTrans = Matrix::constructTranslateMatrix(0-(wc->getX()), 0-(wc->getY()));
  mTrans->multMatrixAndDelete(Matrix::constructScalonateMatrix(factor));
  mTrans->multMatrixAndDelete(Matrix::constructTranslateMatrix(wc->getX(), wc->getY()));
  vup->transform(mTrans);
  delete mTrans;
}

void Window::moveHorizontal(float pixel) {
  float rad = (wAngle*M_PI)/180;
  Matrix *mTrans = Matrix::constructTranslateMatrix(pixel * cosf(rad), pixel * sinf(rad));
//   Matrix *mTrans = Matrix::constructTranslateMatrix(pixel, 0);
  wc->transform(mTrans);
  vup->transform(mTrans);
  delete mTrans;
}

void Window::moveVertical(float pixel) {
  float rad = (wAngle*M_PI)/180;
  Matrix *mTrans = Matrix::constructTranslateMatrix(pixel * sinf(-rad), pixel * cosf(rad));
//   Matrix *mTrans = Matrix::constructTranslateMatrix(0, pixel);
  wc->transform(mTrans);
  vup->transform(mTrans);
  delete mTrans;
}

void Window::rotate(float angle) {
  Matrix *mTrans = Matrix::constructTranslateMatrix(0-(wc->getX()), 0-(wc->getY()));
  mTrans->multMatrixAndDelete(Matrix::constructRotateMatrix(-angle));
  mTrans->multMatrixAndDelete(Matrix::constructTranslateMatrix(wc->getX(), wc->getY()));
  vup->transform(mTrans);
  delete mTrans;
  wAngle -= angle;
  if (wAngle >= 360) {
    wAngle -= 360;
  }
  if (wAngle < 0) {
    wAngle += 360;
  }
}
