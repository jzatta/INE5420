#ifndef _CG_CURVE_HPP_
#define _CG_CURVE_HPP_

class Curve;

#include <gtk/gtk.h>
#include <list>
#include "Object.hpp"
#include "Point.hpp"
#include "Viewport.hpp"
#include <math.h>

#include <iostream>

class Curve : public Object {
private:
  std::list<Point*> *pointsList;
  std::list<Point*> *curvePoints;
  Curve *next;
public:
  Curve (const char *name, std::list<Point*> *list);
  Curve (std::string *name, std::list<Point*> *list);
  virtual void draw(cairo_t *cr);
  virtual Object* clone();
  virtual void transform(Matrix *_m);
  virtual void save(FILE *stream);
  virtual void clip(void);
  virtual std::pair<float,float> getCenter();
  Point * getPoint(int index);
  int getSize();
  void calculateCurve();
  void attach(Curve *next);

  void setList(std::list<Point*>* list);
  ~Curve ();
};


#endif
