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
  return;
}

Curve::Curve(const char *name, std::list<Point*> *list) : Object(name) {
  pointsList = list;
  curvePoints = new std::list<Point*>();
}

Curve::Curve(std::string *name, std::list<Point*> *list) : Object(name) {
  pointsList = list;
  curvePoints = new std::list<Point*>();
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
}

Object* Curve::clone() {
  std::list<Point*> *newList = new std::list<Point*>();
  std::list<Point*>::iterator it=pointsList->begin();
  std::string *newName = getName();
  Curve *oClone;
  if (newName != NULL) {
    newName = new std::string(*newName);
  }
  for (; it != pointsList->end(); ++it) {
    newList->push_back((Point*)((*it)->clone()));
  }
  oClone = new Curve(newName, newList);
  return oClone;
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
  fprintf(stream, "\n#Add Curve\ng %s\n", getName()->c_str());
  for (; it != pointsList->end(); ++it) {
    fprintf(stream, "v %f %f 0.0 0.0\n", (*it)->getX(), (*it)->getY());
    added++;
  }
  fprintf(stream, "c 1");
  for (; added > 0; added--) {
    fprintf(stream, " %d", added);
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

Point *Curve::getPoint(int index) {
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
  std::list<Point*>::iterator it=curvePoints->begin();
  for (; it != curvePoints->end(); ++it) {
    delete *it;
  }
  curvePoints->clear();
  
#if 1
  float mBS[4][4] = {{-1.0/6,  1.0/2, -1.0/2, 1.0/6},
                    {  1.0/2, -1.0  ,  1.0/2, 0.0  },
                    { -1.0/2,  0.0  ,  1.0/2, 0.0  },
                    {  1.0/6,  2.0/3,  1.0/6, 0.0  }};
#else
  //por no Matrix
  float mBS[4][4] = {{-1,  3, -3, 1},
                    { 3, -6,  3, 0},
                    {-3,  3,  0, 0},
                    { 1,  0,  0, 0}};

#endif
  
  float gBSX[pointsList->size()];
  float gBSY[pointsList->size()];
  it=pointsList->begin();
  for (int i = 0; it!=pointsList->end(); i++) {
    gBSX[i] = (*it)->getX();
    gBSY[i] = (*it)->getY();
    it++;
  }
  
  for (int m = 3; m < pointsList->size(); m++) {
    // points are constant to this object,
    //                so multiply points to mBS are constant too
    float mBSgBSX[4];
    float mBSgBSY[4];
    for (int j = 0; j < 4; j++) {
      mBSgBSX[j] = 0;
      mBSgBSY[j] = 0;
      for (int i = 0; i < 4; i++) {
        mBSgBSX[j] += mBS[j][i] * gBSX[i+m-3];
        mBSgBSY[j] += mBS[j][i] * gBSY[i+m-3];
      }
    }
    float t[4];
    float step = Window::getWidth()/60000;
    if (step < (0.01/60000)) {
      step = 0.01;
    }
    for (float i = 0; i <= 1; i += step) {
      t[3] = 1;
      t[2] = i;
      t[1] = t[2] * i;
      t[0] = t[1] * i;
      
      float x = 0;
      float y = 0;
      for (int j = 0; j < 4; j++) {
        x += t[j] * mBSgBSX[j];
        y += t[j] * mBSgBSY[j];
      }
      curvePoints->push_back(new Point("CurvePoint", x, y));
    }
  }
}

Curve::~Curve() {
  std::list<Point*>::iterator it=pointsList->begin();
  for (; it != pointsList->end(); ++it) {
    delete *it;
  }
  it=curvePoints->begin();
  for (; it != curvePoints->end(); ++it) {
    delete *it;
  }
  pointsList->clear();
  curvePoints->clear();
  delete pointsList;
  delete curvePoints;
}
