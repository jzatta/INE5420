#ifndef _CG_LINE_HPP_
#define _CG_LINE_HPP_

#include <gtk/gtk.h>
#include "Object.hpp"
#include "Point.hpp"
#include <list>

class Line : public Object {
private:
  std::list<Point*> *pointsList;
public:
  Line(const char *name, float xa, float ya, float xb, float yb);
  Line(std::string *name, float xa, float ya, float xb, float yb);
  Line(std::string *name, Point *a, Point *b);
  virtual void draw(cairo_t *cr);
  virtual Object* clone();
  virtual void transform(Matrix *_m);
  virtual std::pair<float,float> getCenter();
  virtual ~Line();
};


#endif
