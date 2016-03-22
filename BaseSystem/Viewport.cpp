
#include "Viewport.hpp"

int Viewport::windowX = -300, Viewport::windowY = -300;
int Viewport::windowW = 600, Viewport::windowH = 600;

int Viewport::transformX(int xw) {
  return (((float)xw - (float)windowX)/(float)windowW ) * (float)ViewportX;
}

int Viewport::transformY(int yw) {
  return (1 - (((float)yw - (float)windowY)/(float)windowH)) * (float)ViewportY;
}

void Viewport::defaultSize() {
  windowX = -300;
  windowY = -300;
  windowW = ViewportX;
  windowH = ViewportY;
}

void Viewport::setWindowX(int x) {
  windowX = x;
}

void Viewport::setWindowY(int y) {
  windowY = y;
}

void Viewport::setWindowWidth(int width) {
  windowW = width;
}

void Viewport::setWindowHeight(int height) {
  windowH = height;
}

void Viewport::zoom(float factor) {
  int cX, cY;
  cX = windowW / 2 + windowX;
  cY = windowH / 2 + windowY;
  windowW /= factor;
  windowH /= factor;
  windowX = cX - (windowW / 2);
  windowY = cY - (windowH / 2);
}

void Viewport::moveHorizontal(float factor) {
  windowX += factor * 100;
}

void Viewport::moveVertical(float factor) {
  windowY += factor * 100;
}
