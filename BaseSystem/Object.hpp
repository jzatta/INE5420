#ifndef _CG_OBJECT_HPP_
#define _CG_OBJECT_HPP_

#include <gtk/gtk.h>
#include "Viewport.hpp"

class Object {
private:
  char *name;
public:
  virtual void draw(cairo_t *cr) = 0;
  char *getName() {
    return name;
  }
};


#endif
