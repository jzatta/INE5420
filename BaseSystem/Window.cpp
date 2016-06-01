
#include <math.h>
#include <string>
#include "Window.hpp"

#define PIXEL_AREA_MIN 1000
#define HWSIZE 300

#define DISTANCE 5
#define HEIGHT 2

Point *Window::wc  = new Point("WindowCenter", 0, 0, 0);
// Line *Window::vup = new Line("Vup", new Point((std::string*)NULL, -HWSIZE,  -HWSIZE, 0), new Point((std::string*)NULL, -HWSIZE, HWSIZE, 0));
float Window::distance = DISTANCE;
float Window::height = HEIGHT;
float Window::wAngleX = 0;
float Window::wAngleY = 0;
float Window::wAngleZ = 0;

Point *Window::vectX = new Point("Axis X", 1, 0, 0);
Point *Window::vectY = new Point("Axis Y", 0, 1, 0);
Point *Window::vectZ = new Point("Axis Z", 0, 0, 1);


void Window::center() {
  delete wc;
  wc = new Point((std::string*)NULL, 0, 0, 0);
}

void Window::reset() {
  Window::center();
  height = HEIGHT;
  wAngleX = 0;
  wAngleY = 0;
  wAngleZ = 0;
  distance = DISTANCE;
}

float Window::getWidth() {
  // Window is a square
  return getHeight();
}

float Window::getHeight() {
  return height;
}

float Window::getX() {
  return wc->getX();
}

float Window::getY() {
  return wc->getY();
}

float Window::getZ() {
  return wc->getZ();
}

Matrix *Window::getTransform() {
  Matrix *mTrans = Matrix::constructTranslateMatrix(0-(wc->getX()), 0-(wc->getY()), 0-(wc->getZ()));
  mTrans->multMatrixAndDelete(Matrix::constructRotateMatrixX(wAngleX));
  mTrans->multMatrixAndDelete(Matrix::constructRotateMatrixY(wAngleY));
  mTrans->multMatrixAndDelete(Matrix::constructRotateMatrixZ(wAngleZ));
  mTrans->multMatrixAndDelete(Matrix::constructScalonateMatrix(1.0/getWidth(), 1.0/getHeight(), 1.0/getHeight()));
  mTrans->multMatrixAndDelete(Matrix::constructTranslateMatrix(0, 0, distance));
  return mTrans;
}

void Window::zoom(float factor) {
  height *= factor;
}

void Window::moveHorizontal(float pixel) {
  float radX = (wAngleX*M_PI)/180;
  float radY = (wAngleY*M_PI)/180;
  float radZ = (wAngleZ*M_PI)/180;
  pixel *= 0.1*height;
  Matrix *mTrans;
  mTrans = Matrix::constructTranslateMatrix(pixel * cosf(radY) * cosf(radZ),
                                            pixel * (sinf(radX) * sinf(radY) * cosf(radZ) - cosf(radX) * sinf(radZ) ),
                                            pixel * (cosf(radX) * sinf(radY) * cosf(radZ) + sinf(radX) * sinf(radZ) )
                                           );
  wc->transform(mTrans);
  delete mTrans;
}

void Window::moveVertical(float pixel) {
  float radX = (wAngleX*M_PI)/180;
  float radY = (wAngleY*M_PI)/180;
  float radZ = (wAngleZ*M_PI)/180;
  pixel *= 0.1*height;
  Matrix *mTrans;
  mTrans = Matrix::constructTranslateMatrix(pixel * cosf(radY) * sinf(radZ),
                                            pixel * (sinf(radX) * sinf(radY) * sinf(radZ) + cosf(radX) * cosf(radZ) ),
                                            pixel * (cosf(radX) * sinf(radY) * sinf(radZ) - sinf(radX) * cosf(radZ) )
                                           );
  wc->transform(mTrans);
  delete mTrans;
}

void Window::moveLongitudinal(float pixel) {
  float radX = (wAngleX*M_PI)/180;
  float radY = (wAngleY*M_PI)/180;
  float radZ = (wAngleZ*M_PI)/180;
  pixel *= 0.1*height;
  Matrix *mTrans;
  mTrans = Matrix::constructTranslateMatrix(-1 * pixel * sinf(radY),
                                            pixel * sinf(radX) * cosf(radY),
                                            pixel * cosf(radX) * cosf(radY)
                                           );
  wc->transform(mTrans);
  delete mTrans;
}

void Window::rotateX(float angle) {
  wAngleX -= angle;
  if (wAngleX >= 360) {
    wAngleX -= 360;
  }
  if (wAngleX < 0) {
    wAngleX += 360;
  }
}

void Window::rotateY(float angle) {
  wAngleY -= angle;
  if (wAngleY >= 360) {
    wAngleY -= 360;
  }
  if (wAngleY < 0) {
    wAngleY += 360;
  }
}

void Window::rotateZ(float angle) {
  wAngleZ -= angle;
  if (wAngleZ >= 360) {
    wAngleZ -= 360;
  }
  if (wAngleZ < 0) {
    wAngleZ += 360;
  }
}

float Window::getDistance() {
  return distance;
}
