
#include "DisplayFile.hpp"

DisplayFile::DisplayFile() {
  this->objectsWorld = new std::list<Object*>;
  this->objectsTransformed = new std::list<Object*>;
  transformMatrix = new Matrix();
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
  this->transform(transformMatrix);
}

void DisplayFile::escalonateObj(std::string *name, float scalar) {
  Object* chObj = getObjW(name);
  Matrix *mTrans = Matrix::constructTranslateMatrix(0-(chObj->getCenter().first), 0-(chObj->getCenter().second));
  mTrans->multMatrixAndDelete(Matrix::constructScalonateMatrix(scalar));
  mTrans->multMatrixAndDelete(Matrix::constructTranslateMatrix(chObj->getCenter().first, chObj->getCenter().second));
  chObj->transform(mTrans);
  delete mTrans;
  this->transform(transformMatrix);
}

void DisplayFile::rotateObjOrigin(std::string *name, float angle) {
  Object* chObj = getObjW(name);
  Matrix *mTrans = Matrix::constructRotateMatrix(angle);
  chObj->transform(mTrans);
  delete mTrans;
  this->transform(transformMatrix);
}

void DisplayFile::rotateObjPoint(std::string *name, float angle, Point *p) {
  Object* chObj = getObjW(name);
  Matrix *mTrans = Matrix::constructTranslateMatrix(0-(p->getX()), 0-(p->getY()));
  mTrans->multMatrixAndDelete(Matrix::constructRotateMatrix(angle));
  mTrans->multMatrixAndDelete(Matrix::constructTranslateMatrix(p->getX(), p->getY()));
  chObj->transform(mTrans);
  delete mTrans;
  this->transform(transformMatrix);
}

void DisplayFile::rotateObjCenter(std::string *name, float angle) {
  Object* chObj = getObjW(name);
  Matrix *mTrans = Matrix::constructTranslateMatrix(0-(chObj->getCenter().first), 0-(chObj->getCenter().second));
  mTrans->multMatrixAndDelete(Matrix::constructRotateMatrix(angle));
  mTrans->multMatrixAndDelete(Matrix::constructTranslateMatrix(chObj->getCenter().first, chObj->getCenter().second));
  chObj->transform(mTrans);
  delete mTrans;
  this->transform(transformMatrix);
}

void DisplayFile::draw(cairo_t *cr) {
  std::list<Object*>::iterator it=this->objectsTransformed->begin();
  for (; it != this->objectsTransformed->end(); ++it) {
    (*it)->draw(cr);
  }
}

void DisplayFile::transform(Matrix *_m) {
  Object *tmpObj;
  std::list<Object*>::iterator it;
  objectsTransformed->clear();
  it=objectsWorld->begin();
  for (; it != objectsWorld->end(); ++it) {
    tmpObj = (*it)->clone();
    tmpObj->transform(transformMatrix);
    objectsTransformed->push_back(tmpObj);
  }
  return;
}

DisplayFile::~DisplayFile() {
  objectsWorld->clear();
  objectsTransformed->clear();
  delete this->objectsWorld;
  delete this->objectsTransformed;
  delete this->transformMatrix;
}
