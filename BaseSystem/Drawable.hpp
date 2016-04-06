#ifndef _CG_DRAWABLE_HPP_
#define _CG_DRAWABLE_HPP_

#include <gtk/gtk.h>

class Drawable {
public:
  virtual void draw(cairo_t *cr) = 0;
};

#endif
