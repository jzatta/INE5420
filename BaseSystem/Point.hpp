#ifndef _CG_POINT_HPP_
#define _CG_POINT_HPP_

#include <gtk/gtk.h>
#include "Object.hpp"
#include "Point.hpp"

class Point : public Object {
private:
  int x, y;
public:
  Point(const char *name, int _x, int _y);
  void draw(cairo_t *cr);
  int getX();
  int getY();
};

#endif
