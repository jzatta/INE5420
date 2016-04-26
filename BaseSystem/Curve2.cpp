#include "Curve2.hpp"
#include <assert.h>

void Curve::draw(cairo_t *cr) {
  /*float xi, yi;
  std::list<Point*>::iterator it=pointsList->begin();
  xi = (*it)->getX();
  yi = (*it)->getY();
  cairo_move_to(cr, Viewport::transformX(xi), Viewport::transformY(yi));
  ++it;
  for (; it != pointsList->end(); ++it) {
    cairo_line_to(cr, Viewport::transformX((*it)->getX()), Viewport::transformY((*it)->getY()));
  }
  cairo_line_to(cr, Viewport::transformX(xi), Viewport::transformY(yi));
  return; */
  std::list<Point*>::iterator it=curvePoints->begin();
  for (; it != curvePoints->end(); ++it) {
    (*it)->draw(cr);
  }
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
}

Object* Curve::clone() {
  std::list<Point*> *newList = new std::list<Point*>();
  std::list<Point*>::iterator it=pointsList->begin();
  std::string *newName = getName();
  if (newName != NULL) {
    newName = new std::string(*newName);
  }
  for (; it != pointsList->end(); ++it) {
    newList->push_back((Point*)((*it)->clone()));
  }
  return new Curve(newName, newList);
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
  fprintf(stream, "f 1");
  for (; added > 0; added--) {
    fprintf(stream, " %d", added);
  }
  fprintf(stream, "\n");
}

void Curve::clip(void) {
  //this->show = Clipping::clipPolygon(this);
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

void Curve::calculateCurve(){
  curvePoints->clear();
  
  //por no Matrix
  float matrix[][4] = { { -1, 3, -3, 1 }, { 3, -6, 3, 0 }, { -3, 3, 0, 0 }, { 1,
      0, 0, 0 } };
  float vX[4];
  float vY[4];
  int i = 0;
  std::list<Point*>::iterator it=pointsList->begin();
  for (; it != pointsList->end(); ++it) {
    vX[i] = (*it)->getX();
    vY[i] = (*it)->getY();
    i++;
  }


  float t[4];
  for (double i = 0; i < 1; i += 0.001) {
    t[0] = pow(i, 3);
    t[1] = pow(i, 2);
    t[2] = pow(i, 1);
    t[3] = 1;

    float tMb[4];
   
    for (int jb = 0; jb < 4; jb++) {
      tMb[jb] = 0;
      for (int ja = 0; ja < 4; ja++) {
        tMb[jb] += t[ja] * matrix[ja][jb];
      }
    }

    float x = 0;
    for (int i = 0; i < 4; i++) {
      x += tMb[i] * vX[i];
    }
    float y = 0;
    for (int i = 0; i < 4; i++) {
      y += tMb[i] * vY[i];
    }

    curvePoints->push_back(new Point("CurvePoint", x, y));
  }


}

Curve::~Curve() {
  pointsList->clear();
  delete pointsList;
}
