#ifndef _CG_LINE_HPP_
#define _CG_LINE_HPP_

#include <gtk/gtk.h>
#include "Object.hpp"
#include "Point.hpp"

class Line : public Object {
private:
    Point *a, *b;
public:
  Line(Point *_a, Point *_b);
  Line(int xa, int ya, int xb, int yb);
  void draw(cairo_t *cr);
  ~Line();
};


#endif
