
#include "Polygon.hpp"
#include <assert.h>

void Polygon::draw(cairo_t *cr) {
  float xi, yi;
  this->clip();
  if (this->show == false) {
    return;
  }
  std::list<Point*>::iterator it=pointsList->begin();
  xi = (*it)->getX();
  yi = (*it)->getY();
  cairo_move_to(cr, Viewport::transformX(xi), Viewport::transformY(yi));
  ++it;
  for (; it != pointsList->end(); ++it) {
    cairo_line_to(cr, Viewport::transformX((*it)->getX()), Viewport::transformY((*it)->getY()));
  }
  cairo_line_to(cr, Viewport::transformX(xi), Viewport::transformY(yi));
  return;
}

Polygon::Polygon(const char *name, std::list<Point*> *list) : Object(name) {
  pointsList = list;
}

Polygon::Polygon(std::string *name, std::list<Point*> *list) : Object(name) {
  pointsList = list;
}

void Polygon::transform(Matrix *_m) {
  std::list<Point*>::iterator it=pointsList->begin();
  for (; it != pointsList->end(); ++it) {
    (*it)->Point::transform(_m);
  }
}

Object* Polygon::clone() {
  std::list<Point*> *newList = new std::list<Point*>();
  std::list<Point*>::iterator it=pointsList->begin();
  std::string *newName = getName();
  if (newName != NULL) {
    newName = new std::string(*newName);
  }
  for (; it != pointsList->end(); ++it) {
    newList->push_back((Point*)((*it)->clone()));
  }
  return new Polygon(newName, newList);
}

std::pair<Point*,Point*> Polygon::getCenter() {
  std::pair<Point*,Point*> center;
  float x, y, z;
  std::list<Point*>::iterator it=pointsList->begin();
  if (pointsList->size() == 0) {
    center.first = NULL;
    center.second = NULL;
    return center;
  }
  x = (*it)->getX();
  y = (*it)->getY();
  z = (*it)->getZ();
  it++;
  center.second = new Point((std::string *)NULL, x, y, z);
  for (; it != pointsList->end(); ++it) {
    x += (*it)->getX();
    y += (*it)->getY();
    z += (*it)->getZ();
  }
  x /= pointsList->size();
  y /= pointsList->size();
  z /= pointsList->size();
  center.first = new Point((std::string *)NULL, x, y, z);
  return center;
}

void Polygon::save(FILE *stream) {
  int added = 0;
  std::list<Point*>::iterator it=pointsList->begin();
  fprintf(stream, "\n#Add polygon\no %s\n", getName()->c_str());
  for (; it != pointsList->end(); ++it) {
    fprintf(stream, "v %f %f %f 0.0\n", (*it)->getX(), (*it)->getY(), (*it)->getZ());
    added++;
  }
  fprintf(stream, "f");
  for (; added > 0; added--) {
    fprintf(stream, " %d", added);
  }
  fprintf(stream, "\n");
}

void Polygon::clip(void) {
  this->show = Clipping::clipPolygon(this);
}

Point * Polygon::getPoint(int index) {
  assert(index >= 0);
  assert(index < pointsList->size());
  std::list<Point*>::iterator it = pointsList->begin();
  int i;
  for (i = 1; i <= index; i++){
    it++;
  }
  Point * ret = (*it);
  return ret;
}

int Polygon::getSize() {
  return pointsList->size();
}

void Polygon::setList(std::list<Point*>* list) {
  pointsList = list;
}

void Polygon::project() {
  std::list<Point*>::iterator it=pointsList->begin();
  for (; it != pointsList->end(); ++it) {
    (*it)->project();
  }
}

Polygon::~Polygon() {
  std::list<Point*>::iterator it=pointsList->begin();
  for (; it != pointsList->end(); ++it) {
    delete *it;
  }
  pointsList->clear();
  delete pointsList;
}
