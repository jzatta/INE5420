
#include <gtk/gtk.h>
#include "Line.hpp"

void Line::draw(cairo_t *cr) {
  // Fazer transformada de Viewport
  cairo_move_to(cr, Viewport::transformX(a->getX()), Viewport::transformY(a->getY()));
  cairo_line_to(cr, Viewport::transformX(b->getX()), Viewport::transformY(b->getY()));
  return;
}

Line::Line(Point *_a, Point *_b) {
  a = _a;
  b = _b;
}

Line::Line(int xa, int ya, int xb, int yb) {
  a = new Point(xa, ya);
  b = new Point(xb, yb);
}

Line::~Line() {
  delete a;
  delete b;
}
