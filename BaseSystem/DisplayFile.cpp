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
      float x, y, nil;
      fscanf(obj, " %f %f %f %f\n", &x, &y, &nil, &nil);
      pointsList->push_back(new Point((std::string*) NULL, x, y));
    }
    if (ch == 'p') {
      tmpObj = new Point(name, pointsList->front()->getX(), pointsList->front()->getY());
      GUI::addToListBox(std::string(name));
      this->objectsWorld->push_back(tmpObj);
      tmpObj = tmpObj->clone();
      tmpObj->transform(transformMatrix);
      this->objectsTransformed->push_back(tmpObj);
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

void DisplayFile::translateObj(std::string *name, float x, float y) {
  Object* chObj = getObjW(name);
  Matrix *mTrans = Matrix::constructTranslateMatrix(x, y);
  chObj->transform(mTrans);
  delete mTrans;
  this->transform();
}

void DisplayFile::escalonateObj(std::string *name, float scalar) {
  Object* chObj = getObjW(name);
  Matrix *mTrans = Matrix::constructTranslateMatrix(0-(chObj->getCenter().first), 0-(chObj->getCenter().second));
  mTrans->multMatrixAndDelete(Matrix::constructScalonateMatrix(scalar));
  mTrans->multMatrixAndDelete(Matrix::constructTranslateMatrix(chObj->getCenter().first, chObj->getCenter().second));
  chObj->transform(mTrans);
  delete mTrans;
  this->transform();
}

void DisplayFile::rotateObjOrigin(std::string *name, float angle) {
  Object* chObj = getObjW(name);
  Matrix *mTrans = Matrix::constructRotateMatrix(angle);
  chObj->transform(mTrans);
  delete mTrans;
  this->transform();
}

void DisplayFile::rotateObjPoint(std::string *name, float angle, Point *p) {
  Object* chObj = getObjW(name);
  Matrix *mTrans = Matrix::constructTranslateMatrix(0-(p->getX()), 0-(p->getY()));
  mTrans->multMatrixAndDelete(Matrix::constructRotateMatrix(angle));
  mTrans->multMatrixAndDelete(Matrix::constructTranslateMatrix(p->getX(), p->getY()));
  chObj->transform(mTrans);
  delete mTrans;
  this->transform();
}

void DisplayFile::rotateObjCenter(std::string *name, float angle) {
  Object* chObj = getObjW(name);
  Matrix *mTrans = Matrix::constructTranslateMatrix(0-(chObj->getCenter().first), 0-(chObj->getCenter().second));
  mTrans->multMatrixAndDelete(Matrix::constructRotateMatrix(angle));
  mTrans->multMatrixAndDelete(Matrix::constructTranslateMatrix(chObj->getCenter().first, chObj->getCenter().second));
  chObj->transform(mTrans);
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
  objectsTransformed->clear();
  it=objectsWorld->begin();
  for (; it != objectsWorld->end(); ++it) {
    tmpObj = (*it)->clone();
    tmpObj->transform(transformMatrix);
#if 0
    tmpObj->clip();
#endif
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
  objectsWorld->clear();
  objectsTransformed->clear();
  delete this->objectsWorld;
  delete this->objectsTransformed;
  delete this->transformMatrix;
}
