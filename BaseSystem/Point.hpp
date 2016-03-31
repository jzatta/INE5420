#ifndef _CG_POINT_HPP_
#define _CG_POINT_HPP_

#include <gtk/gtk.h>
#include "Object.hpp"
#include "Point.hpp"

class Point : public Object {
private:
  float x, y;
public:
  Point(const char *name, float _x, float _y);
  void draw(cairo_t *cr);
  float getX();
  float getY();
  void transform(float matrix[3][3]);
  void setCords(float _x, float _y);
  std::pair<float,float> getCenter();
};

#endif
