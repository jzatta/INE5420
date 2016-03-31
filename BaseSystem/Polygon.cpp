
#include <gtk/gtk.h>
#include "Polygon.hpp"

void Polygon::draw(cairo_t *cr) {
  float xi, yi;
  std::list<Point>::iterator it=pointsList.begin();
  xi = (*it).getX();
  yi = (*it).getY();
  cairo_move_to(cr, Viewport::transformX(xi), Viewport::transformY(yi));
  ++it;
  for (; it != pointsList.end(); ++it) {
    cairo_line_to(cr, Viewport::transformX((*it).getX()), Viewport::transformY((*it).getY()));
  }
  cairo_line_to(cr, Viewport::transformX(xi), Viewport::transformY(yi));
  return;
}

Polygon::Polygon(const char *name, std::list<Point> list) : Object(name) {
  pointsList = list;
}

void Polygon::transform(float matrix[3][3]) {
  std::list<Point>::iterator it=pointsList.begin();
  float x;
  float y;
  for (; it != pointsList.end(); ++it) {
    (*it).Point::transform(matrix);
  }

}
std::pair<float,float> Polygon::getCenter() {
  std::pair<float,float> center;
  std::list<Point>::iterator it=pointsList.begin();
  for (; it != pointsList.end(); ++it) {
    center.first += (*it).getX();
    center.second += (*it).getY();
  }
  center.first /= pointsList.size();
  center.second /= pointsList.size();
  return center;
}

Polygon::~Polygon() {
}
