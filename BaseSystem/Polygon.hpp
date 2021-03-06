#ifndef _CG_POLYGON_HPP_
#define _CG_POLYGON_HPP_

class Polygon;

#include <gtk/gtk.h>
#include <list>
#include "Object.hpp"
#include "Point.hpp"
#include "Viewport.hpp"

#include <iostream>

class Polygon : public Object {
private:
  std::list<Point*> *pointsList;
public:
  Polygon(const char *name, std::list<Point*> *list);
  Polygon(std::string *name, std::list<Point*> *list);
  virtual void draw(cairo_t *cr);
  virtual Object* clone();
  virtual void transform(Matrix *_m);
  virtual void save(FILE *stream);
  virtual void clip(void);
  virtual std::pair<Point*,Point*> getCenter();
  virtual void project();
  Point * getPoint(int index);
  int getSize();

  void setList(std::list<Point*>* list);
  virtual ~Polygon();
};


#endif
