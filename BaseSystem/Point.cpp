
#include <gtk/gtk.h>
#include "Point.hpp"

void Point::draw(cairo_t *cr) {
  // Fazer transformada de Viewport
  cairo_rectangle(cr, Viewport::transformX(x), Viewport::transformY(y), 1, 1);
  return;
}

int Point::getX() {
  return x;
}

int Point::getY() {
  return y;
}

Point::Point(int _x, int _y) {
  x = _x;
  y = _y;
}
