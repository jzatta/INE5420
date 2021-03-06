
#include "Object3D.hpp"
#include <assert.h>

void Object3D::draw(cairo_t *cr) {
  //tá clipando duas vezes, aqui e no draw do objeto
  this->clip();
  if (this->show == false) {
    return;
  }
  /*std::list<std::pair<int,int>>::iterator it=edgeList->begin();
  for (; it != edgeList->end(); ++it) {
    float xi, yi, xf, yf;
    xi = pointsList->at((*it).first)->getX();
    yi = pointsList->at((*it).first)->getY();
    xf = pointsList->at((*it).second)->getX();
    yf = pointsList->at((*it).second)->getY();
    cairo_move_to(cr, Viewport::transformX(xi), Viewport::transformY(yi));
    cairo_line_to(cr, Viewport::transformX(xf), Viewport::transformY(yf));
  }*/
  std::list<Object*>::iterator it = objectList->begin();
  for (; it != objectList->end(); ++it) {
    (*it)->draw(cr);
  }

  return;
}

//DEPRECATED
Object3D::Object3D(const char *name, std::vector<Point*> *_pointsList, std::list<std::pair<int,int>> *_edgeList): Object(name) {
  pointsList = _pointsList;
  edgeList = _edgeList;
  std::cout << "Deprecated constructor" << std::endl;
}

//DEPRECATED
Object3D::Object3D(std::string *name, std::vector<Point*> *_pointsList, std::list<std::pair<int,int>> *_edgeList): Object(name) {
  pointsList = _pointsList;
  edgeList = _edgeList;
  std::cout << "Deprecated constructor" << std::endl;
}

Object3D::Object3D(const char *name, std::list<Object*> *_objectList): Object(name) {
  objectList = _objectList;
}

Object3D::Object3D(std::string *name, std::list<Object*> *_objectList): Object(name) {
  objectList = _objectList;
}

void Object3D::transform(Matrix *_m) {
  /*std::vector<Point*>::iterator it=pointsList->begin();
  for (; it != pointsList->end(); ++it) {
    (*it)->Point::transform(_m);
  }*/
  std::list<Object*>::iterator it = objectList->begin();
  for (; it != objectList->end(); ++it) {
    (*it)->transform(_m);
  }
}

Object* Object3D::clone() {
  //std::vector<Point*> *newPointList = new std::vector<Point*>();
  //std::list<std::pair<int,int>> *newEdgeList = new std::list<std::pair<int,int>>();
  
  std::list<Object*> *newObjectList = new std::list<Object*>();

  std::string *newName = getName();
  if (newName != NULL) {
    newName = new std::string(*newName);
  }

  /*std::vector<Point*>::iterator it=pointsList->begin();
  for (; it != pointsList->end(); ++it) {
    newPointList->push_back((Point*)((*it)->clone()));
  } 
  std::list<std::pair<int,int>>::iterator itEdge=edgeList->begin();
  for (; itEdge != edgeList->end(); ++itEdge) {
    newEdgeList->push_back(*itEdge);
  }*/

  std::list<Object*>::iterator it = objectList->begin();
  for (; it != objectList->end(); ++it) {
    newObjectList->push_back((Object*)((*it)->clone())); //(Object*) necessário?
  } 

  return new Object3D(newName, newObjectList);
  //return new Object3D(newName, newPointList, newEdgeList);
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
  center.second = new Point((std::string *)NULL, 0,0,0);
  for (; it != pointsList->end(); ++it) {
    x += (*it)->getX();
    y += (*it)->getY();
    z += (*it)->getZ();
  }
  x /= pointsList->size();
  y /= pointsList->size();
  z /= pointsList->size();
  center.first = new Point((std::string *)NULL, 0,1,0);
  return center;
}

void Object3D::save(FILE *stream) {
  // TODO (Juliano)
  int added = 0;
  std::vector<Point*>::iterator it=pointsList->begin();
  fprintf(stream, "\n#Add Object3D\no %s\n", getName()->c_str());
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

//usar o project() dessa classe ou deixar aqui mesmo?
void Object3D::clip(void) {
  // NAO FUNCIONA!!11!!!1ONZE
  /*this->show = false;
  std::list<std::pair<int,int>>::iterator it=edgeList->begin();
  for (; it != edgeList->end(); ++it) {
    pointsList->at((*it).first)->project();
    pointsList->at((*it).second)->project();
    if (Clipping::clipLineCS(pointsList->at((*it).first), pointsList->at((*it).second))) {
      this->show = true;
    }
  }*/
  //*this->show = false;
  std::list<Object*>::iterator it = objectList->begin();
  for (; it != objectList->end(); ++it) {
    (*it)->project(); //projetar aqui ou usar o método dessa classe?
    (*it)->clip();
  }
}


//DEPRECATED
void Object3D::setPointsList(std::vector<Point*>* _list) {
  pointsList = _list;
  std::cout << "This function is deprecated: Object3D::setPointsList" << std::endl;
}

//DEPRECATED
void Object3D::setEdgeList(std::list<std::pair<int,int>> *_list) {
  edgeList = _list;
  std::cout << "This function is deprecated: Object3D::setEdgeList" << std::endl;
}

void Object3D::project() {
  std::list<Object*>::iterator it = objectList->begin();
  for (; it != objectList->end(); ++it) {
    (*it)->project();
  }
}

Object3D::~Object3D() {
std::list<Object*>::iterator it = objectList->begin();
  for (; it != objectList->end(); ++it) {
    delete *it;
  }
  delete objectList;
}
