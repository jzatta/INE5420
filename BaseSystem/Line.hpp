#ifndef _CG_LINE_HPP_
#define _CG_LINE_HPP_

class Line;

#include <gtk/gtk.h>
#include "Object.hpp"
#include "Point.hpp"
#include "Viewport.hpp"
#include <list>

class Line : public Object {
private:
  std::list<Point*> *pointsList;
public:
  Line(const char *name, float xa, float ya, float xb, float yb);
  Line(std::string *name, float xa, float ya, float xb, float yb);
  Line(const char *name, Point *a, Point *b);
  Line(std::string *name, Point *a, Point *b);
  float lenght();
  virtual void draw(cairo_t *cr);
  virtual Object* clone();
  virtual void transform(Matrix *_m);
  virtual std::pair<float,float> getCenter();
  virtual void save(FILE *stream);
  virtual ~Line();
};


#endif
