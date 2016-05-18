
#include <gtk/gtk.h>
#include <math.h>
#include "Point.hpp"
#include <iostream>

void Point::draw(cairo_t *cr) {
  this->clip();
  if (this->show) {
    cairo_move_to(cr, Viewport::transformX(x), Viewport::transformY(y));
    cairo_arc(cr, Viewport::transformX(x), Viewport::transformY(y), 1, 0, 2*M_PI);
  }
  return;
}

float Point::getX() {
  return x;
}

float Point::getY() {
  return y;
}

float Point::getZ() {
  return z;
}

void Point::setX(float _x) {
  x = _x;
}
void Point::setY(float _y) {
  y = _y;
}
void Point::setZ(float _z) {
  z = _z;
}

Point::Point(const char *name, float _x, float _y) : Object(name) {
  x = _x;
  y = _y;
  z = 0;
  std::cout << "This contructor is deprecated" << std::endl;
}

Point::Point(std::string *name, float _x, float _y) : Object(name) {
  x = _x;
  y = _y;
  z = 0;
  std::cout << "This contructor is deprecated" << std::endl;
}

Point::Point(std::string *name, float _x, float _y, float _z) : Object(name) {
  x = _x;
  y = _y;
  z = _z;
}

Point::Point(const char *name, float _x, float _y, float _z) : Object(name) {
  x = _x;
  y = _y;
  z = _z;
}

void Point::transform(Matrix *_m) {
  float tmpPoints[4] = {x, y, z, 1};
  _m->getTransPoint(tmpPoints);
  x = tmpPoints[0];
  y = tmpPoints[1];
  z = tmpPoints[2];
}

void Point::setCords(float _x, float _y) {
  x = _x;
  y = _y;
}

void Point::setCords(float _x, float _y, float _z) {
  x = _x;
  y = _y;
  z = _z;
}

Object* Point::clone() {
  std::string *newName = getName();
  if (newName != NULL) {
    newName = new std::string(*newName);
  }
  return new Point(newName, this->getX(), this->getY(), this->getZ());
}

std::pair<Point*,Point*> Point::getCenter() {
  std::pair<Point*,Point*> center;
  center.first = (Point*)this->clone();
  center.second = new Point((const char *)NULL, 1,1,1);
  return center;
}

void Point::save(FILE *stream) {
  fprintf(stream, "\n#Add Point\ng %s\n", getName()->c_str());
  fprintf(stream, "v %f %f %f 0.0\n", x, y, z);
  fprintf(stream, "p 1\n");
}

void Point::clip(void) {
  this->show = Clipping::clipPoint(x, y);
}

Point::~Point() {
}

float Point::scalarProd(Point *a, Point *b) {
  float x, y, z;
  x = a->getX() * b->getX();
  y = a->getY() * b->getY();
  z = a->getZ() * b->getZ();
  return (x+y+z);
}

float Point::norm(Point *a) {
  return sqrt(scalarProd(a, a));
}

float Point::vectorAngle(Point *a, Point *b) {
  float angle;
  angle = scalarProd(a, b);
  angle /= (norm(a)*norm(b));
  angle = acos(angle);
  return angle*180/M_PI;
}