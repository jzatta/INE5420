
#include <gtk/gtk.h>
#include <math.h>
#include "Line.hpp"

void Line::draw(cairo_t *cr) {
  if (show) {
    cairo_move_to(cr, Viewport::transformX(pointsList->front()->getX()), Viewport::transformY(pointsList->front()->getY()));
    cairo_line_to(cr, Viewport::transformX(pointsList->back()->getX()), Viewport::transformY(pointsList->back()->getY()));
  }
  return;
}

Line::Line(const char *name, float xa, float ya, float xb, float yb) : Object(name) {
  this->pointsList = new std::list<Point*>();
  pointsList->push_back(new Point(name, xa, ya));
  pointsList->push_back(new Point(name, xb, yb));
}

Line::Line(std::string *name, float xa, float ya, float xb, float yb) : Object(name) {
  this->pointsList = new std::list<Point*>();
  pointsList->push_back(new Point(name, xa, ya));
  pointsList->push_back(new Point(name, xb, yb));
}

Line::Line(const char *name, Point *a, Point *b) : Object(name) {
  this->pointsList = new std::list<Point*>();
  pointsList->push_back(a);
  pointsList->push_back(b);
}

Line::Line(std::string *name, Point *a, Point *b) : Object(name) {
  this->pointsList = new std::list<Point*>();
  pointsList->push_back(a);
  pointsList->push_back(b);
}

float Line::lenght() {
  Point *a = pointsList->front();
  Point *b = pointsList->back();
  return sqrt( pow(a->getX() - b->getX(),2) + pow(a->getY() - b->getY(),2) );
}

void Line::transform(Matrix *_m) {
  pointsList->front()->Point::transform(_m);
  pointsList->back()->Point::transform(_m);
}

Object* Line::clone() {
  std::string *newName = getName();
  if (newName != NULL) {
    newName = new std::string(*newName);
  }
  return new Line(newName, (Point*)(pointsList->front()->clone()), (Point*)(pointsList->back()->clone()));
}

std::pair<float,float> Line::getCenter() {
  std::pair<float,float> center;
  center.first = (pointsList->front()->getX() + pointsList->back()->getX())/2;
  center.second = (pointsList->front()->getY() + pointsList->back()->getY())/2;
  return center;
}

void Line::save(FILE *stream) {
  fprintf(stream, "\n#Add Line\ng %s\n", getName()->c_str());
  fprintf(stream, "v %f %f 0.0 0.0\n",  pointsList->front()->getX(),
                                        pointsList->front()->getY());
  fprintf(stream, "v %f %f 0.0 0.0\n",  pointsList->back()->getX(),
                                        pointsList->back()->getY());
  fprintf(stream, "l 1 2\n");
}

void Line::clip(void) {
  this->show = Clipping::clipLineCS(pointsList->front(), pointsList->back());
}


Line::~Line() {
  pointsList->clear();
  delete pointsList;
}
