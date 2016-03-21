
#include "Viewport.hpp"

int Viewport::windowX = 0, Viewport::windowY = 0;
int Viewport::windowW = 600, Viewport::windowH = 600;

int Viewport::transformX(int xw) {
  return (((float)xw - (float)windowX)/(float)windowW ) * (float)ViewportX;
}

int Viewport::transformY(int yw) {
  return (1 - (((float)yw - (float)windowY)/(float)windowH)) * (float)ViewportY;
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
  windowW /= factor;
  windowH /= factor;
}

void Viewport::moveHorizontal(float factor) {
  windowX += factor * windowW;
}

void Viewport::moveVertical(float factor) {
  windowY += factor * windowH;
}
