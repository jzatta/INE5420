#include "Curve2.hpp"
#include <assert.h>

void Curve::draw(cairo_t *cr) {
  float xi, yi;
  if (this->show) {
    std::list<Point*>::iterator it=curvePoints->begin();
    xi = (*it)->getX();
    yi = (*it)->getY();
    cairo_move_to(cr, Viewport::transformX(xi), Viewport::transformY(yi));
    ++it;
    for (; it != curvePoints->end(); ++it) {
      cairo_line_to(cr, Viewport::transformX((*it)->getX()), Viewport::transformY((*it)->getY()));
    }
  }
  if (this->next) {
    this->next->draw(cr);
  }
  return;
}

Curve::Curve(const char *name, std::list<Point*> *list) : Object(name) {
  pointsList = list;
  curvePoints = new std::list<Point*>();
  this->next = NULL;
}

Curve::Curve(std::string *name, std::list<Point*> *list) : Object(name) {
  pointsList = list;
  curvePoints = new std::list<Point*>();
  this->next = NULL;
}

void Curve::transform(Matrix *_m) {
  std::list<Point*>::iterator it=pointsList->begin();
  float x;
  float y;
  for (; it != pointsList->end(); ++it) {
    (*it)->Point::transform(_m);
  }
  this->calculateCurve();
  this->clip();
  if (this->next) {
    this->next->transform(_m);
  }
}

Object* Curve::clone() {
  std::list<Point*> *newList = new std::list<Point*>();
  std::list<Point*>::iterator it=pointsList->begin();
  std::string *newName = getName();
  Curve *clone;
  if (newName != NULL) {
    newName = new std::string(*newName);
  }
  for (; it != pointsList->end(); ++it) {
    newList->push_back((Point*)((*it)->clone()));
  }
  clone = new Curve(newName, newList);
  if (this->next) {
    clone->attach((Curve*)this->next->clone());
  }
  return clone;
}

std::pair<float,float> Curve::getCenter() {
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

void Curve::save(FILE *stream) {
  int added = 0;
  std::list<Point*>::iterator it=pointsList->begin();
  fprintf(stream, "\n#Add polygon\ng %s\n", getName()->c_str());
  for (; it != pointsList->end(); ++it) {
    fprintf(stream, "v %f %f 0.0 0.0\n", (*it)->getX(), (*it)->getY());
    added++;
  }
  fprintf(stream, "c 1");
  for (; added > 0; added--) {
    fprintf(stream, " %d", added);
  }
  fprintf(stream, "\n");
  if (this->next) {
    this->next->save(stream);
  }
}

void Curve::clip(void) {
  std::list<Point*>::iterator it=curvePoints->begin();
  this->show = true;
  for (; it != curvePoints->end();) {
    if (!Clipping::clipPoint((*it)->getX(), (*it)->getY())) {
      delete *it;
      it = curvePoints->erase(it);
      continue;
    }
    ++it;
  }
  if (curvePoints->empty()) {
    this->show = false;
  }
}

Point * Curve::getPoint(int index) {
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

int Curve::getSize() {
  return pointsList->size();
}

void Curve::setList(std::list<Point*>* list) {
  pointsList = list;
}

void Curve::calculateCurve() {
  curvePoints->clear();
  
  //por no Matrix
  float mB[4][4] = {{-1,  3, -3, 1},
                    { 3, -6,  3, 0},
                    {-3,  3,  0, 0},
                    { 1,  0,  0, 0}};
  float vX[4];
  float vY[4];
  std::list<Point*>::iterator it=pointsList->begin();
  for (int i = 0; it != pointsList->end(); ++it) {
    vX[i] = (*it)->getX();
    vY[i] = (*it)->getY();
    i++;
  }
  
  // points are constant to this object,
  //                so multiply points to mB are constant too
  float mBgBX[4];
  float mBgBY[4];
  for (int j = 0; j < 4; j++) {
    mBgBX[j] = 0;
    mBgBY[j] = 0;
    for (int i = 0; i < 4; i++) {
      mBgBX[j] += mB[j][i] * vX[i];
      mBgBY[j] += mB[j][i] * vY[i];
    }
  }

  float t[4];
  for (double i = 0; i <= 1; i += Window::getWidth()/6000) {
    t[3] = 1;
    t[2] = i;
    t[1] = t[2] * i;
    t[0] = t[1] * i;
    
    float x = 0;
    float y = 0;
    for (int i = 0; i < 4; i++) {
      x += t[i] * mBgBX[i];
      y += t[i] * mBgBY[i];
    }
    
    curvePoints->push_back(new Point("CurvePoint", x, y));
  }
}

void Curve::attach(Curve *_next) {
  this->next = _next;
}

Curve::~Curve() {
  pointsList->clear();
  curvePoints->clear();
  delete pointsList;
  delete curvePoints;
}
