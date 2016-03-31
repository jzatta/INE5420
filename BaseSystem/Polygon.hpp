#ifndef _CG_POLYGON_HPP_
#define _CG_POLYGON_HPP_

#include <gtk/gtk.h>
#include <list>
#include "Object.hpp"
#include "Point.hpp"

class Polygon : public Object {
private:
  std::list<Point> pointsList;
public:
  Polygon(const char *name, std::list<Point> list);
  void draw(cairo_t *cr);
  void transform(float matrix[3][3]);
  std::pair<float,float> getCenter();
  ~Polygon();
};


#endif
