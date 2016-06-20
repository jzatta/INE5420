#ifndef _CG_SURFACE_HPP_
#define _CG_SURFACE_HPP_

class Surface;

#include <gtk/gtk.h>
#include <list>
#include "Object.hpp"
#include "Point.hpp"
#include "Viewport.hpp"
#include <math.h>
#include <vector>

#include <iostream>

class Surface : public Object {
private:
  std::vector<std::vector<Point*>*> *pointsMatrix;
  std::vector<std::vector<Point*>*> *curveMatrix;
public:
  Surface (const char *name,  std::vector<std::vector<Point*>*> *matrix);
  Surface (std::string *name, std::vector<std::vector<Point*>*> *matrix);
  virtual void draw(cairo_t *cr);
  virtual void calculateCurve();
  virtual Object* clone();
  virtual void transform(Matrix *_m);
  virtual void save(FILE *stream);
  virtual void clip(void);
  virtual std::pair<Point*,Point*> getCenter();
  int getSize();
  void calculateSurface();
//   void drawFwdDiff(int n, float x[4], float y[4], float z[4]);

  void setList(std::vector<std::vector<Point*>*> *matrix);
  virtual ~Surface();
};


#endif
