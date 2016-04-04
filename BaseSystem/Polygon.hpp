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
  Polygon(const char *name, std::list<Point*> *list);
  Polygon(std::string *name, std::list<Point*> *list);
  virtual void draw(cairo_t *cr);
  virtual Object* clone();
  virtual void transform(Matrix *_m);
  virtual std::pair<float,float> getCenter();
  ~Polygon();
};


#endif
