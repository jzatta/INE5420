
#include <gtk/gtk.h>
#include "Line.hpp"

void Line::draw(cairo_t *cr) {
  // Fazer transformada de Viewport
  cairo_move_to(cr, Viewport::transformX(xa), Viewport::transformY(ya));
  cairo_line_to(cr, Viewport::transformX(xb), Viewport::transformY(yb));
  return;
}

Line::Line(const char *name, int xa, int ya, int xb, int yb) : Object(name) {
  this->xa = xa;
  this->ya = ya;
  this->xb = xb;
  this->yb = yb;
}
