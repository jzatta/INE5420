#ifndef _CG_LINE_HPP_
#define _CG_LINE_HPP_

#include <gtk/gtk.h>
#include "Object.hpp"
#include "Point.hpp"

class Line : public Object {
private:
    int xa, ya, xb, yb;
public:
  Line(const char *name, int xa, int ya, int xb, int yb);
  void draw(cairo_t *cr);
};


#endif
