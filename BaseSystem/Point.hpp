#ifndef _CG_POINT_HPP_
#define _CG_POINT_HPP_

class Point;

#include <gtk/gtk.h>
#include "Clipping.hpp"
#include "Object.hpp"
#include "Viewport.hpp"

class Point : public Object {
private:
  float x, y;
public:
  Point(const char *name, float _x, float _y);
  Point(std::string *name, float _x, float _y);
  float getX();
  float getY();
  void setX(float _x);
  void setY(float _y);
  void setCords(float _x, float _y);
  virtual void draw(cairo_t *cr);
  virtual Object* clone();
  virtual void transform(Matrix *_m);
  virtual void save(FILE *stream);
  virtual void clip(void);
  virtual std::pair<float,float> getCenter();
  virtual ~Point();
};

#endif
