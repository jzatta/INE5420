#ifndef _CG_OBJECT_HPP_
#define _CG_OBJECT_HPP_

#include <gtk/gtk.h>
#include "Viewport.hpp"
#include <utility>
#include <list>

class Object {
private:
  const char *name;
public:
  Object(const char *name) {
    this->name = name;
  }
  virtual void draw(cairo_t *cr) = 0;
  const char *getName() const {
    return name;
  }
  virtual void transform(float matrix[3][3]) = 0;
  virtual std::pair<float,float> getCenter() = 0;
};

#endif
