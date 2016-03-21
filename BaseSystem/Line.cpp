
#include <gtk/gtk.h>
#include "Line.hpp"

void Line::draw(cairo_t *cr) {
  // Fazer transformada de Viewport
  cairo_move_to(cr, a->getX(), a->getY());
  cairo_line_to(cr, b->getX(), b->getY());
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

}
