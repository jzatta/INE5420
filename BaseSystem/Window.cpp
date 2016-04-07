
#include "Window.hpp"
#include <math.h>
#include <string>

#define PIXEL_AREA_MIN 1000

Point *Window::wc = new Point((std::string*)NULL, 0, 0);
Line *Window::vup = new Line((std::string*)NULL, -300,  -300, -300, 300);
float Window::wAngle = 0;


void Window::center() {
  delete wc;
  wc = new Point((std::string*)NULL, 0, 0);
}

void Window::reset() {
  Window::center();
  delete vup;
  vup = new Line((std::string*)NULL, -300,  -300, -300, 300);
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
