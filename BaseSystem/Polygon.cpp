
#include <gtk/gtk.h>
#include "Polygon.hpp"

void Polygon::draw(cairo_t *cr) {
  std::list<Point*>::iterator it=pointsList->begin();
  // Fazer transformada de Viewport
  cairo_move_to(cr, (*it)->getX(), (*it)->getY());
  ++it;
  for (; it != pointsList->end(); ++it) {
    cairo_line_to(cr, (*it)->getX(), (*it)->getY());
  }
  return;
}


Polygon::Polygon(Point *pt) {
  pointsList = new std::list<Point*>();
  pointsList->push_back(pt);
}

Polygon::Polygon(int x, int y) {
  Point *pt = new Point(x, y);
  pointsList = new std::list<Point*>();
  pointsList->push_back(pt);
}

Polygon::Polygon() {
  pointsList = new std::list<Point*>();
}

void Polygon::add(int x, int y) {
  Point *pt = new Point(x, y);
  pointsList->push_back(pt);
}

Polygon::~Polygon() {
  // Dellocate all points
}
