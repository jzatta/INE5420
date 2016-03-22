
#include <gtk/gtk.h>
#include <math.h>
#include "Point.hpp"

void Point::draw(cairo_t *cr) {
  // Fazer transformada de Viewport
  cairo_move_to(cr, Viewport::transformX(x), Viewport::transformY(y));
  cairo_arc(cr, Viewport::transformX(x), Viewport::transformY(y), 1, 0, 2*M_PI);
  return;
}

float Point::getX() {
  return x;
}

float Point::getY() {
  return y;
}

Point::Point(const char *name, float _x, float _y) : Object(name) {
  x = _x;
  y = _y;
}
