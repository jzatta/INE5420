#ifndef _CG_LINE_HPP_
#define _CG_LINE_HPP_

class Line;

#include <gtk/gtk.h>
#include "Clipping.hpp"
#include "Object.hpp"
#include "Point.hpp"
#include "Viewport.hpp"
#include <list>

class Line : public Object {
private:
  std::list<Point*> *pointsList;
public:
  Line(const char *name, Point *a, Point *b);
  Line(std::string *name, Point *a, Point *b);
  float lenght();
  virtual void draw(cairo_t *cr);
  virtual Object* clone();
  virtual void transform(Matrix *_m);
  virtual std::pair<Point*,Point*> getCenter();
  virtual void save(FILE *stream);
  virtual void clip(void);
  virtual ~Line();
};


#endif
