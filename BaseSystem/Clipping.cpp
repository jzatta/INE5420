#include "Clipping.hpp"

static float max(float a, float b, float c) {
  if (a > b) {
    return (a > c)?a:c;
  }
  return (b > c)?b:c;
}

static float min(float a, float b, float c) {
  if (a < b) {
    return (a < c)?a:c;
  }
  return (b < c)?b:c;
}

bool Clipping::clipPoint(float x, float y) {
  if ( (x < -1) || (x > 1) || (y < -1) || (y > 1) ) {
    return false;
  }
  return true;
}

bool Clipping::clipLineLB(Point *p1, Point *p2) {
  float dx, dy;
  float p[4], q[4], u[4];
  float maxP, minP;
  int it;

  dx = p2->getX() - p1->getX();
  dy = p2->getY() - p1->getY();

  p[0] = -dx; p[1] = dx;
  p[2] = -dy; p[3] = dy;

  q[0] = (p1->getX() - (-1));
  q[1] = (1 - p1->getX());
  q[2] = (p1->getY() - (-1));
  q[3] = (1 - p1->getY());

  // test and clip if is parallel to window cordinates
  for (it = 0; it < 4; it++) {
    if (p[it] == 0) {
      if (it & 0x02) { // dy == 0
        if ((p1->getY() > 1) || (p1->getY() < -1)) { // outside window
          return false;
        }
        if (p1->getX() > 1) {
          p1->setX(1);
        }
        else if (p1->getX() < -1) {
          p1->setX(-1);
        }
        if (p2->getX() > 1) {
          p2->setX(1);
        }
        else if (p2->getX() < -1) {
          p2->setX(-1);
        }
        return true;
      } else { // dx == 0
        if ((p1->getX() > 1) || (p1->getX() < -1)) { // outside window
          return false;
        }
        if (p1->getY() > 1) {
          p1->setY(1);
        }
        else if (p1->getY() < -1) {
          p1->setY(-1);
        }
        if (p2->getY() > 1) {
          p2->setY(1);
        }
        else if (p2->getY() < -1) {
          p2->setY(-1);
        }
        return true;
      }
    }
  }
  
  u[0] = q[0]/p[0];
  u[1] = q[1]/p[1];
  u[2] = q[2]/p[2];
  u[3] = q[3]/p[3];
  
  if ((p[0] <= 0) && (p[2] <= 0)) {
    maxP = max(0, u[0], u[2]);
    minP = min(1, u[1], u[3]);
  }
  else if ((p[1] <= 0) && (p[2] <= 0)) {
    maxP = max(0, u[1], u[2]);
    minP = min(1, u[0], u[3]);
  }
  else if ((p[0] <= 0) && (p[3] <= 0)) {
    maxP = max(0, u[0], u[3]);
    minP = min(1, u[1], u[2]);
  }
  else if ((p[1] <= 0) && (p[3] <= 0)) {
    maxP = max(0, u[1], u[3]);
    minP = min(1, u[0], u[2]);
  }
  
  // Outside Window
  if (maxP > minP) {
    return false;
  }
  
  
  // Inside Window
  if (minP < 1) {
    p2->setX(p1->getX() + (minP*dx) );
    p2->setY(p1->getY() + (minP*dy) );
  }
  if (maxP > 0) {
    p1->setX(p1->getX() + (maxP*dx) );
    p1->setY(p1->getY() + (maxP*dy) );
  }
  return true;
}
