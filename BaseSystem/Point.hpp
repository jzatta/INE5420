#ifndef _CG_POINT_HPP_
#define _CG_POINT_HPP_

class Point;

#include <gtk/gtk.h>
#include "Clipping.hpp"
#include "Object.hpp"
#include "Viewport.hpp"

class Point : public Object {
private:
  float x, y, z;
public:
  Point(const char *name, float _x, float _y);
  Point(const char *name, float _x, float _y, float _z);
  Point(std::string *name, float _x, float _y);
  Point(std::string *name, float _x, float _y, float _z);
  float getX();
  float getY();
  float getZ();
  void setX(float _x);
  void setY(float _y);
  void setZ(float _z);
  void setCords(float _x, float _y);
  void setCords(float _x, float _y, float _z);
  virtual void draw(cairo_t *cr);
  virtual Object* clone();
  virtual void transform(Matrix *_m);
  virtual void save(FILE *stream);
  virtual void clip(void);
  virtual std::pair<Point*,Point*> getCenter();
  virtual ~Point();
  
  static float scalarProd(Point *a, Point *b);
  static float norm(Point *a);
  static float vectorAngle(Point *a, Point *b);
};

#endif
