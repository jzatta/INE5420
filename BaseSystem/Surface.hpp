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
  std::vector<Point*> *drawFwdDiff(int n, const float c_x[4], const float c_y[4], const float c_z[4]);
public:
  Surface (const char *name,  std::vector<std::vector<Point*>*> *matrix);
  Surface (std::string *name, std::vector<std::vector<Point*>*> *matrix);
  virtual void draw(cairo_t *cr);
  virtual void calculateCurve();
  virtual Object* clone();
  virtual void transform(Matrix *_m);
  virtual void save(FILE *stream);
  virtual void clip(void);
  void project();
  virtual std::pair<Point*,Point*> getCenter();
  int getSize();
  void calculateSurface();

  void setList(std::vector<std::vector<Point*>*> *matrix);
  virtual ~Surface();
};


#endif
