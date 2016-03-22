#ifndef _CG_POLYGON_HPP_
#define _CG_POLYGON_HPP_

#include <gtk/gtk.h>
#include <list>
#include "Object.hpp"
#include "Point.hpp"

class Polygon : public Object {
private:
  std::list<std::pair<float,float>> *pointsList;
public:
  Polygon(const char *name, std::list<std::pair<float,float>> *list);
  void draw(cairo_t *cr);
  ~Polygon();
};


#endif
