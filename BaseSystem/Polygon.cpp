
#include <gtk/gtk.h>
#include "Polygon.hpp"

void Polygon::draw(cairo_t *cr) {
  float xi, yi;
  std::list<std::pair<float,float>>::iterator it=pointsList->begin();
  xi = (*it).first;
  yi = (*it).second;
  cairo_move_to(cr, Viewport::transformX(xi), Viewport::transformY(yi));
  ++it;
  for (; it != pointsList->end(); ++it) {
    cairo_line_to(cr, Viewport::transformX((*it).first), Viewport::transformY((*it).second));
  }
  cairo_line_to(cr, Viewport::transformX(xi), Viewport::transformY(yi));
  return;
}

Polygon::Polygon(const char *name, std::list<std::pair<float,float>> *list) : Object(name) {
  pointsList = list;
}

Polygon::~Polygon() {
}
