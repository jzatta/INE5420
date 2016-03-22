
#include "Viewport.hpp"

#define PIXEL_AREA_MIN 1000

float Viewport::windowX = -300, Viewport::windowY = -300;
float Viewport::windowW = 600, Viewport::windowH = 600;

float Viewport::transformX(float xw) {
  return (((float)xw - (float)windowX)/(float)windowW ) * (float)ViewportX;
}

float Viewport::transformY(float yw) {
  return (1 - (((float)yw - (float)windowY)/(float)windowH)) * (float)ViewportY;
}

void Viewport::defaultSize() {
//   windowW = ViewportX;
//   windowH = ViewportY;
  windowX = windowW / -2;
  windowY = windowH / -2;
}

void Viewport::setWindowX(float x) {
  windowX = x;
}

void Viewport::setWindowY(float y) {
  windowY = y;
}

void Viewport::setWindowWidth(float width) {
  windowW = width;
}

void Viewport::setWindowHeight(float height) {
  windowH = height;
}

void Viewport::zoom(float factor) {
  float cX, cY;
  if (((windowW * windowH) / (factor * factor)) <= PIXEL_AREA_MIN) {
    return;
  }
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
