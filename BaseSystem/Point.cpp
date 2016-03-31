
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

void Point::transform(float matrix[3][3]){
	float _x = x*matrix[0][0] + y*matrix[1][0] + matrix[2][0];
	float _y = x*matrix[0][1] + y*matrix[1][1] + matrix[2][1];
	x = _x;
	y = _y;
}

void Point::setCords(float _x, float _y) {
	x = _x;
	y = _y;
}

std::pair<float,float> Point::getCenter(){
	std::pair<float,float> center;
	center.first = x;
	center.second = y;
	return center;
}
