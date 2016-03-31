
#include <gtk/gtk.h>
#include "Line.hpp"

void Line::draw(cairo_t *cr) {
  cairo_move_to(cr, Viewport::transformX(pointsList.front().getX()), Viewport::transformY(pointsList.front().getY()));
  cairo_line_to(cr, Viewport::transformX(pointsList.back().getX()), Viewport::transformY(pointsList.back().getY()));
  return;
}

Line::Line(const char *name, float xa, float ya, float xb, float yb) : Object(name) {
  pointsList.push_back(Point(name, xa, ya));
  pointsList.push_back(Point(name, xb, yb));
}
void Line::transform(float matrix[3][3]){
	pointsList.front().Point::transform(matrix);
	pointsList.back().Point::transform(matrix);

}

std::pair<float,float> Line::getCenter(){
	std::pair<float,float> center;
	center.first = (pointsList.front().getX() + pointsList.back().getX())/2;
	center.second = (pointsList.front().getY() + pointsList.back().getY())/2;
	return center;
}
