#ifndef _CG_LINE_HPP_
#define _CG_LINE_HPP_

#include <gtk/gtk.h>
#include "Object.hpp"
#include "Point.hpp"
#include <list>

class Line : public Object {
private:
    std::list<Point> pointsList;
public:
  Line(const char *name, float xa, float ya, float xb, float yb);
  void draw(cairo_t *cr);
  void transform(float matrix[3][3]);
  std::pair<float,float> getCenter();
};


#endif
