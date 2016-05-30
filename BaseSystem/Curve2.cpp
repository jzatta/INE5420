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

std::pair<Point*,Point*> Curve::getCenter() {
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

void Curve::save(FILE *stream) {
  int added = 0;
  std::list<Point*>::iterator it=pointsList->begin();
  fprintf(stream, "\n#Add Curve\no %s\n", getName()->c_str());
  for (; it != pointsList->end(); ++it) {
    fprintf(stream, "v %f %f %f 0.0\n", (*it)->getX(), (*it)->getY(), (*it)->getZ());
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
  //matriz invertida de hermite
  float mH[4][4] = {
    { 2,-2, 1, 1},
    {-3, 3,-2, 1},
    { 0, 0, 1, 0},
    { 1, 0, 0, 0}
  };
#endif
#if 0
  //matriz invertida de bezier //must complete
  float mB[4][4] = {
    { 0, 0, 0, 0},
    { 0, 0, 0, 0},
    { 0, 0, 0, 0},
    { 0, 0, 0, 0}
  };
#endif
#if 1
  //matriz invertida da B-spline
  float mBS[4][4] = {
    {-1.0/6,  3.0/6, -3.0/6, 1.0/6},
    { 3.0/6, -6.0/6,  3.0/6, 0.0/6},
    {-3.0/6,  0.0/6,  3.0/6, 0.0/6},
    { 1.0/6,  4.0/6,  1.0/6, 0.0/6}
  };
#endif
  
  float gX[pointsList->size()];
  float gY[pointsList->size()];
  float gZ[pointsList->size()];
  it=pointsList->begin();
  for (int i = 0; it!=pointsList->end(); i++) {
    gX[i] = (*it)->getX();
    gY[i] = (*it)->getY();
    gZ[i] = (*it)->getZ();
    it++;
  }
  
  for (int m = 3; m < pointsList->size(); m++) {
    // calc curve coeficients C
    float Cx[4], Cy[4], Cz[4];
    for (int j = 0; j < 4; j++) {
      Cx[j] = 0;
      Cy[j] = 0;
      Cz[j] = 0;
      for (int i = 0; i < 4; i++) {
        Cx[j] += mBS[j][i] * gX[i+m-3];
        Cy[j] += mBS[j][i] * gY[i+m-3];
        Cz[j] += mBS[j][i] * gZ[i+m-3];
      }
    }
    float t[4];
    float step = Window::getWidth()/60000;
    if (step < (0.01/60000)) {
      step = 0.01;
    }
    t[0] = 1.0;
    t[1] = t[0] * step;
    t[2] = t[1] * step;
    t[3] = t[2] * step;
    
    float mD[4][4] = {
      {     0,      0,    0, t[0]},
      {1*t[3], 1*t[2], t[1],    0},
      {6*t[3], 2*t[2],    0,    0},
      {6*t[3],      0,    0,    0}
    };
    
    float f_x[4], f_y[4], f_z[4];
    for (int j = 0; j < 4; j++) {
      f_x[j] = 0;
      f_y[j] = 0;
      f_z[j] = 0;
      for (int i = 0; i < 4; i++) {
        f_x[j] += mD[j][i] * Cx[i];
        f_y[j] += mD[j][i] * Cy[i];
        f_z[j] += mD[j][i] * Cz[i];
      }
    }
    int n = 1/step + 1;
    drawFwdDiff(n, f_x, f_y, f_z);
  }
}

void Curve::drawFwdDiff(int n, float x[4], float y[4], float z[4]) {
  // f(x) = x[0] ___ df(x)/dx = x[1] ___ d^2f(x)/dx = x[2] ___ d^3f(x)/dx = x[3]  
  curvePoints->push_back(new Point((const char*)NULL, x[0], y[0], z[0]));
  for (int i = 0; i < n; i++) {
    x[0] += x[1];
    x[1] += x[2];
    x[2] += x[3];
    
    y[0] += y[1];
    y[1] += y[2];
    y[2] += y[3];
    
    z[0] += z[1];
    z[1] += z[2];
    z[2] += z[3];
    curvePoints->push_back(new Point((const char*)NULL, x[0], y[0], z[0]));
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
