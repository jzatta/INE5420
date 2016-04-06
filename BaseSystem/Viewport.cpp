
#include "Viewport.hpp"


// hpp defined
// const static int ViewportX = 600, ViewportY = 600;

float Viewport::transformX(float xw) {
  return ((xw + 1)
  /2 ) * (float)ViewportX;
}

float Viewport::transformY(float yw) {
  return (1 - ((yw + 1)
  /2)) * (float)ViewportY;
}
