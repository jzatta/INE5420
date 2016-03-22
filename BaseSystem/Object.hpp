#ifndef _CG_OBJECT_HPP_
#define _CG_OBJECT_HPP_

#include <gtk/gtk.h>
#include "Viewport.hpp"

class Object {
private:
  const char *name;
public:
  Object(const char *name) {
    this->name = name;
  }
  virtual void draw(cairo_t *cr) = 0;
  const char *getName() {
    return name;
  }
};


#endif
