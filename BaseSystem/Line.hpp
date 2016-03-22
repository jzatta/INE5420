#ifndef _CG_LINE_HPP_
#define _CG_LINE_HPP_

#include <gtk/gtk.h>
#include "Object.hpp"
#include "Point.hpp"

class Line : public Object {
private:
    float xa, ya, xb, yb;
public:
  Line(const char *name, float xa, float ya, float xb, float yb);
  void draw(cairo_t *cr);
};


#endif
