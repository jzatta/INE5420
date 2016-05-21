
#include "Object3D.hpp"
#include <assert.h>

void Object3D::draw(cairo_t *cr) {
  this->clip();
  if (this->show == false) {
    return;
  }
  std::list<std::pair<int,int> *>::iterator it=edgeList->begin();
  for (; it != edgeList->end(); ++it) {
    float xi, yi, xf, yf;
    xi = pointsList->at((*it)->first)->getX();
    yi = pointsList->at((*it)->first)->getY();
    xf = pointsList->at((*it)->second)->getX();
    yf = pointsList->at((*it)->second)->getY();
    cairo_move_to(cr, Viewport::transformX(xi), Viewport::transformY(yi));
    cairo_line_to(cr, Viewport::transformX(xf), Viewport::transformY(yf));
  }
  return;
}

Object3D::Object3D(const char *name, std::vector<Point*> *_pointsList, std::list<std::pair<int,int> *> *_edgeList): Object(name) {
  pointsList = _pointsList;
  edgeList = _edgeList;
}

Object3D::Object3D(std::string *name, std::vector<Point*> *_pointsList, std::list<std::pair<int,int> *> *_edgeList): Object(name) {
  pointsList = _pointsList;
  edgeList = _edgeList;
}

void Object3D::transform(Matrix *_m) {
  std::vector<Point*>::iterator it=pointsList->begin();
  for (; it != pointsList->end(); ++it) {
    (*it)->Point::transform(_m);
  }
}

Object* Object3D::clone() {
  std::vector<Point*> *newPointList = new std::vector<Point*>();
  std::list<std::pair<int,int> *> *newEdgeList = new std::list<std::pair<int,int> *>();
  std::string *newName = getName();
  if (newName != NULL) {
    newName = new std::string(*newName);
  }
  std::vector<Point*>::iterator it=pointsList->begin();
  for (; it != pointsList->end(); ++it) {
    newPointList->push_back((Point*)((*it)->clone()));
  }
  std::list<std::pair<int,int> *>::iterator itEdge=edgeList->begin();
  for (; itEdge != edgeList->end(); ++itEdge) {
    std::pair<int,int> *newPair = new std::pair<int,int>(**itEdge);
    newEdgeList->push_back(newPair);
  }
  return new Object3D(newName, newPointList, newEdgeList);
}

std::pair<Point*,Point*> Object3D::getCenter() {
  std::pair<Point*,Point*> center;
  float x, y, z;
  std::vector<Point*>::iterator it=pointsList->begin();
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

void Object3D::save(FILE *stream) {
  // REVER
  int added = 0;
  std::vector<Point*>::iterator it=pointsList->begin();
  fprintf(stream, "\n#Add Object3D\ng %s\n", getName()->c_str());
  for (; it != pointsList->end(); ++it) {
    fprintf(stream, "v %f %f %f 0.0\n", (*it)->getX(), (*it)->getY(), (*it)->getZ());
    added++;
  }
  fprintf(stream, "f 1");
  for (; added > 0; added--) {
    fprintf(stream, " %d", added);
  }
  fprintf(stream, "\n");
}

void Object3D::clip(void) {
  this->show = false;
  std::list<std::pair<int,int> *>::iterator it=edgeList->begin();
  for (; it != edgeList->end(); ++it) {
    if (Clipping::clipLineCS(pointsList->at((*it)->first), pointsList->at((*it)->second))) {
      this->show = true;
    }
  }
}

void Object3D::setPointsList(std::vector<Point*>* _list) {
  pointsList = _list;
}

void Object3D::setEdgeList(std::list<std::pair<int,int> *> *_list) {
  edgeList = _list;
}

Object3D::~Object3D() {
  std::vector<Point*>::iterator it=pointsList->begin();
  for (; it != pointsList->end(); ++it) {
    delete *it;
  }
  pointsList->clear();
  edgeList->clear();
  delete edgeList;
  delete pointsList;
}
