
#include "Viewport.hpp"


// hpp defined
// const static int ViewportX = 600, ViewportY = 600;

#define WINDOWSIZE (300.0/300.0)

float Viewport::transformX(float xw) {
  return ((xw + WINDOWSIZE)/2 ) * ((float)ViewportX - 40) + 20;
}

float Viewport::transformY(float yw) {
  return (1 - ((yw + WINDOWSIZE)/2) ) * ((float)ViewportY - 40) + 20;
}
