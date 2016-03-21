
#include "Viewport.hpp"

int Viewport::windowX = 0, Viewport::windowY = 0;
int Viewport::windowW = 6000, Viewport::windowH = 6000;

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
  windowW = windowW * factor;
  windowX = windowX * factor;
}

void Viewport::moveRight(int pixels) {
  windowX += pixels;
}

void Viewport::moveLeft(int pixels)  {
  windowX -= pixels;
}

void Viewport::moveUp(int pixels)  {
  windowY += pixels;
}

void Viewport::moveDown(int pixels)  {
  windowY -= pixels;
}
