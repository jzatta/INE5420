
#include <gtk/gtk.h>
#include <math.h>
#include "Point.hpp"
#include <iostream>

void Point::draw(cairo_t *cr) {
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

Point::Point(std::string *name, float _x, float _y) : Object(name) {
  x = _x;
  y = _y;
}

void Point::transform(Matrix *_m) {
  float tmpPoints[3] = {x, y, 1};
  _m->getTransPoint(tmpPoints);
  x = tmpPoints[0];
  y = tmpPoints[1];
}

void Point::setCords(float _x, float _y) {
  x = _x;
  y = _y;
}

Object* Point::clone() {
  std::string *newName = getName();
  if (newName != NULL) {
    newName = new std::string(*newName);
  }
  return new Point(newName, this->getX(), this->getY());
}

std::pair<float,float> Point::getCenter() {
  std::pair<float,float> center;
  center.first = x;
  center.second = y;
  return center;
}
