
#include "Polygon.hpp"

void Polygon::draw(cairo_t *cr) {
  float xi, yi;
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
  float x;
  float y;
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

std::pair<float,float> Polygon::getCenter() {
  std::pair<float,float> center;
  std::list<Point*>::iterator it=pointsList->begin();
  for (; it != pointsList->end(); ++it) {
    center.first += (*it)->getX();
    center.second += (*it)->getY();
  }
  center.first /= pointsList->size();
  center.second /= pointsList->size();
  return center;
}

void Polygon::save(FILE *stream) {
  int added = 0;
  std::list<Point*>::iterator it=pointsList->begin();
  fprintf(stream, "\n#Add polygon\ng %s\n", getName()->c_str());
  for (; it != pointsList->end(); ++it) {
    fprintf(stream, "v %f %f 0.0 0.0\n", (*it)->getX(), (*it)->getY());
    added++;
  }
  fprintf(stream, "f 1");
  for (; added > 0; added--) {
    fprintf(stream, " %d", added);
  }
  fprintf(stream, "\n");
}

void Polygon::clip(void) {
  this->show = true;
}

Polygon::~Polygon() {
  pointsList->clear();
  delete pointsList;
}
