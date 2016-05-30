
#include <gtk/gtk.h>
#include <math.h>
#include "Line.hpp"

void Line::draw(cairo_t *cr) {
  this->clip();
  if (this->show) {
    cairo_move_to(cr, Viewport::transformX(pointsList->front()->getX()), Viewport::transformY(pointsList->front()->getY()));
    cairo_line_to(cr, Viewport::transformX(pointsList->back()->getX()), Viewport::transformY(pointsList->back()->getY()));
  }
  return;
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
  Point *p1 = (Point*)pointsList->front()->clone();
  Point *p2 = (Point*)pointsList->back()->clone();
  return new Line(newName, p1, p2);
}

std::pair<Point*,Point*> Line::getCenter() {
  std::pair<Point*,Point*> center;
  float xi, yi, zi, xf, yf, zf;
  yi = pointsList->front()->getY(); yf =  pointsList->back()->getY();
  zi = pointsList->front()->getZ(); zf =  pointsList->back()->getZ();
  xi = pointsList->front()->getX(); xf =  pointsList->back()->getX();
  center.first  = new Point((std::string *)NULL,
                            (yi + yf)/2,
                            (zi + zf)/2,
                            (xi + xf)/2);
  center.second = new Point((std::string *)NULL,
                            xf - xi,
                            yf - yi,
                            zf - zi);
  return center;
}

void Line::save(FILE *stream) {
  fprintf(stream, "\n#Add Line\no %s\n", getName()->c_str());
  fprintf(stream, "v %f %f %f 0.0\n",  pointsList->front()->getX(),
                                       pointsList->front()->getY(),
                                       pointsList->front()->getZ());
  fprintf(stream, "v %f %f %f 0.0\n",  pointsList->back()->getX(),
                                       pointsList->back()->getY(),
                                       pointsList->back()->getZ());
  fprintf(stream, "l 1 2\n");
}

void Line::clip(void) {
  this->show = Clipping::clipLineCS(pointsList->front(), pointsList->back());
}


Line::~Line() {
  std::list<Point*>::iterator it=pointsList->begin();
  for (; it != pointsList->end(); ++it) {
    delete *it;
  }
  pointsList->clear();
  delete pointsList;
}
