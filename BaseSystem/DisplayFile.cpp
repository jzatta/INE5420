#include "DisplayFile.hpp"

DisplayFile::DisplayFile() {
  this->objectsWorld = new std::list<Object*>;
  this->objectsTransformed = new std::list<Object*>;
  transformMatrix = new Matrix();
}

DisplayFile::DisplayFile(FILE *obj) {
  this->objectsWorld = new std::list<Object*>;
  this->objectsTransformed = new std::list<Object*>;
  std::list<Point*> *pointsList= new std::list<Point*>;
  Object *tmpObj;
  char name[150];
  int ch;
  transformMatrix = new Matrix();
  while ( (ch = fgetc(obj) ) != EOF) {
    if (ch == '#') {
      while (ch != '\n') {
        ch = fgetc(obj);
        if (ch == EOF) {
          break;
        }
      }
    }
    if (ch == 'g') {
      fscanf(obj, " %s\n", name);
    }
    if (ch == 'v') {
      float x, y, z, nil;
      fscanf(obj, " %f %f %f %f\n", &x, &y, &z, &nil);
      pointsList->push_back(new Point((std::string*) NULL, x, y, z));
    }
    if (ch == 'p') {
      tmpObj = new Point(name, pointsList->front()->getX(), pointsList->front()->getY(), pointsList->front()->getZ());
      GUI::addToListBox(std::string(name));
      this->objectsWorld->push_back(tmpObj);
      tmpObj = tmpObj->clone();
      tmpObj->transform(transformMatrix);
      this->objectsTransformed->push_back(tmpObj);
      std::list<Point*>::iterator it=pointsList->begin();
      for (; it != pointsList->end(); ++it) {
        delete *it;
      }
      pointsList->clear();
      ch = fgetc(obj);
    }
    if (ch == 'l') {
      tmpObj = new Line(name, pointsList->front(), pointsList->back());
      GUI::addToListBox(std::string(name));
      pointsList->pop_back();
      pointsList->pop_front();
      this->objectsWorld->push_back(tmpObj);
      tmpObj = tmpObj->clone();
      tmpObj->transform(transformMatrix);
      this->objectsTransformed->push_back(tmpObj);
      std::list<Point*>::iterator it=pointsList->begin();
      for (; it != pointsList->end(); ++it) {
        delete *it;
      }
      pointsList->clear();
      ch = fgetc(obj);
    }
    if (ch  == 'f') {
      tmpObj = new Polygon(name, pointsList);
      GUI::addToListBox(std::string(name));
      this->objectsWorld->push_back(tmpObj);
      tmpObj = tmpObj->clone();
      tmpObj->transform(transformMatrix);
      this->objectsTransformed->push_back(tmpObj);
      pointsList = new std::list<Point*>;
      ch = fgetc(obj);
    }
    if (ch  == 'c') {
      tmpObj = new Curve(name, pointsList);
      GUI::addToListBox(std::string(name));
      this->objectsWorld->push_back(tmpObj);
      tmpObj = tmpObj->clone();
      tmpObj->transform(transformMatrix);
      this->objectsTransformed->push_back(tmpObj);
      pointsList = new std::list<Point*>;
      ch = fgetc(obj);
    }
  }
  delete pointsList;
}

std::list<Object*>::iterator DisplayFile::getObjIt(std::string *name) {
}

void DisplayFile::addObject(Object *_obj) {
  this->objectsWorld->push_back(_obj);
  _obj = _obj->clone();
  _obj->transform(transformMatrix);
  this->objectsTransformed->push_back(_obj);
  return;
}

void DisplayFile::deleteObj(std::string *name) {
  std::list<Object*>::iterator it=objectsWorld->begin();
  for (; it != objectsWorld->end(); ++it) {
    if (!(*it)->getName()->compare(*name)) {
      delete *it;
      objectsWorld->erase(it);
      break;
    }
  }
  it=objectsTransformed->begin();
  for (; it != objectsTransformed->end(); ++it) {
    if (!(*it)->getName()->compare(*name)) {
      delete *it;
      objectsTransformed->erase(it);
      break;
    }
  }
  return;
}

Object *DisplayFile::getObjW(std::string *name) {
  std::list<Object*>::iterator it=objectsWorld->begin();
  for (; it != objectsWorld->end(); ++it) {
    if (!(*it)->getName()->compare(*name)) {
      return *it;
    }
  }
}

void DisplayFile::translateObj(std::string *name, float x, float y, float z) {
  Object* chObj = getObjW(name);
  Matrix *mTrans = Matrix::constructTranslateMatrix(x, y, z);
  chObj->transform(mTrans);
  delete mTrans;
  this->transform();
}

void DisplayFile::escalonateObj(std::string *name, float scalar) {
  Object* chObj = getObjW(name);
  std::pair<Point*,Point*> center = chObj->getCenter();
  Matrix *mTrans = Matrix::constructTranslateMatrix(0-(center.first->getX()),
                                                    0-(center.first->getY()),
                                                    0-(center.first->getZ())
                                                   );
  mTrans->multMatrixAndDelete(Matrix::constructScalonateMatrix(scalar));
  mTrans->multMatrixAndDelete(Matrix::constructTranslateMatrix(center.first->getX(),
                                                               center.first->getY(),
                                                               center.first->getZ()
                                                              ));
  chObj->transform(mTrans);
  delete mTrans;
  this->transform();
}

void DisplayFile::rotateObjOrigin(std::string *name, float angle, int ctrl) {
  Object* chObj = getObjW(name);
  Matrix *mTrans;
  switch (ctrl) {
    case 2 : mTrans = Matrix::constructRotateMatrixX(angle);
              break;
    case 1 : mTrans = Matrix::constructRotateMatrixY(angle);
              break;
    case 0 : mTrans = Matrix::constructRotateMatrixZ(angle);
  }
  chObj->transform(mTrans);
  delete mTrans;
  this->transform();
}

void DisplayFile::rotateObjPoint(std::string *name, float angle, Point *p, int ctrl) {
  Object* chObj = getObjW(name);
  std::pair<Point*,Point*> center = chObj->getCenter();
  Matrix *mTrans = Matrix::constructTranslateMatrix(p->getX() - center.first->getX(),
                                                    p->getY() - center.first->getY(),
                                                    p->getZ() - center.first->getZ()
                                                   );
  
  switch (ctrl) {
    case 2 : mTrans = Matrix::constructRotateMatrixX(angle);
              break;
    case 1 : mTrans = Matrix::constructRotateMatrixY(angle);
              break;
    case 0 : mTrans = Matrix::constructRotateMatrixZ(angle);
  }
  
 mTrans->multMatrixAndDelete(Matrix::constructTranslateMatrix(0-(p->getX()),
                                                               0-(p->getY()),
                                                               0-(p->getZ())
                                                              ));
  chObj->transform(mTrans);
  delete mTrans;
  this->transform();
}

void DisplayFile::rotateObjCenter(std::string *name, float angle, int ctrl) {
  Object* chObj = getObjW(name);
  float objAngleXY, objAngleZY;
  std::pair<Point*,Point*> center = chObj->getCenter();
  float x = center.first->getX();
  float y = center.first->getY();
  float z = center.first->getZ();
  Matrix *mTrans = Matrix::constructTranslateMatrix(0-(center.first->getX()),
                                                    0-(center.first->getY()),
                                                    0-(center.first->getZ())
                                                   );
  
  /*
  // vectX to plan ZY
  objAngleZY = 90 - Point::vectorAngle(center.second, Window::vectX);
  // vectZ to plan XY
  objAngleXY = 90 - Point::vectorAngle(center.second, Window::vectZ);
  
  mTrans->multMatrixAndDelete(Matrix::constructRotateMatrixZ(0-objAngleXY));
  mTrans->multMatrixAndDelete(Matrix::constructRotateMatrixX(0-objAngleZY));
  
  mTrans->multMatrixAndDelete(Matrix::constructRotateMatrixY(angle));
  
  mTrans->multMatrixAndDelete(Matrix::constructRotateMatrixX(objAngleZY));
  mTrans->multMatrixAndDelete(Matrix::constructRotateMatrixZ(objAngleXY));
  */

  switch (ctrl) {
    case 2 : mTrans = Matrix::constructRotateMatrixX(angle);
              break;
    case 1 : mTrans = Matrix::constructRotateMatrixY(angle);
              break;
    case 0 : mTrans = Matrix::constructRotateMatrixZ(angle);
  }
  
  mTrans->multMatrixAndDelete(Matrix::constructTranslateMatrix(x,y,z));
  chObj->transform(mTrans);
  delete center.first;
  delete center.second;
  delete mTrans;
  this->transform();
}

void DisplayFile::draw(cairo_t *cr) {
  this->transform();
  std::list<Object*>::iterator it=this->objectsTransformed->begin();
  for (; it != this->objectsTransformed->end(); ++it) {
    (*it)->draw(cr);
  }
}

void DisplayFile::transform() {
  Object *tmpObj;
  std::list<Object*>::iterator it;
  delete transformMatrix;
  transformMatrix = Window::getTransform();
  it=objectsTransformed->begin();
  for (; it != objectsTransformed->end(); ++it) {
    delete *it;
  }
  objectsTransformed->clear();
  it=objectsWorld->begin();
  for (; it != objectsWorld->end(); ++it) {
    tmpObj = (*it)->clone();
    tmpObj->transform(transformMatrix);
//     tmpObj->clip();
    objectsTransformed->push_back(tmpObj);
  }
  return;
}

void DisplayFile::save(FILE *obj) {
  std::list<Object*>::iterator it=objectsWorld->begin();
  for (; it != objectsWorld->end(); ++it) {
    (*it)->save(obj);
  }
}

DisplayFile::~DisplayFile() {
  std::list<Object*>::iterator it=objectsWorld->begin();
  for (; it != objectsWorld->end(); ++it) {
    delete *it;
  }
  it=objectsTransformed->begin();
  for (; it != objectsTransformed->end(); ++it) {
    delete *it;
  }
  objectsWorld->clear();
  objectsTransformed->clear();
  delete this->objectsWorld;
  delete this->objectsTransformed;
  delete this->transformMatrix;
}
