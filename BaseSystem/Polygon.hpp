#ifndef _CG_POLYGON_HPP_
#define _CG_POLYGON_HPP_

#include <gtk/gtk.h>
#include <list>
#include "Object.hpp"
#include "Point.hpp"

class Polygon : public Object {
private:
  std::list<Point*> *pointsList;
public:
  Polygon(const char *name);
  Polygon(const char *name, int x, int y);
  void draw(cairo_t *cr);
  void add(int x, int y);
  ~Polygon();
};


#endif
