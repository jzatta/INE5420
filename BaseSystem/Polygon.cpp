
#include <gtk/gtk.h>
#include "Polygon.hpp"

void Polygon::draw(cairo_t *cr) {
  std::list<Point*>::iterator it=pointsList->begin();
  // Fazer transformada de Viewport
  cairo_move_to(cr, Viewport::transformX((*it)->getX()), Viewport::transformY((*it)->getY()));
  ++it;
  for (; it != pointsList->end(); ++it) {
    cairo_line_to(cr, Viewport::transformX((*it)->getX()), Viewport::transformY((*it)->getY()));
  }
  return;
}

Polygon::Polygon(const char *name, int x, int y) : Object(name) {
  Point *pt = new Point("", x, y);
  pointsList = new std::list<Point*>();
  pointsList->push_back(pt);
}

Polygon::Polygon(const char *name) : Object(name) {
  pointsList = new std::list<Point*>();
}

void Polygon::add(int x, int y) {
  Point *pt = new Point("", x, y);
  pointsList->push_back(pt);
}

Polygon::~Polygon() {
  std::list<Point*>::iterator it=pointsList->begin();
  for (; it != pointsList->end(); ++it) {
    delete *it;
  }
  delete pointsList;
}
