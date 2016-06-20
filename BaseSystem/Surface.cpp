
#include "Surface.hpp"
#include <assert.h>
#include <math.h>
#include <string.h>

#define DBG(str) std::cout << str << std::endl;
#define DBGM() { \
  std::vector<std::vector<Point*>*>::iterator vectorsIt; \
  std::vector<Point*>::iterator pointsIt; \
  vectorsIt = curveMatrix->begin(); \
  for (; vectorsIt != curveMatrix->end(); ++vectorsIt) { \
    pointsIt = (*vectorsIt)->begin(); \
    for (; pointsIt != (*vectorsIt)->end(); ++pointsIt) { \
      printf("%f\t", (*pointsIt)->getY()); \
    } \
    printf("\n"); \
  } \
}

void Surface::draw(cairo_t *cr) {
  std::vector<std::vector<Point*>*>::iterator vectorsIt;
  std::vector<Point*>::iterator pointsIt;
  float xi, yi;
  
  this->calculateCurve();
  this->clip();
  
  if (!this->show) {
    return;
  }
  
  vectorsIt = curveMatrix->begin();
  for (; vectorsIt != curveMatrix->end(); ++vectorsIt) {
    pointsIt = (*vectorsIt)->begin();
    xi = (*pointsIt)->getX();
    yi = (*pointsIt)->getY();
    cairo_move_to(cr, Viewport::transformX(xi), Viewport::transformY(yi));
    ++pointsIt;
    for (; pointsIt != (*vectorsIt)->end(); ++pointsIt) {
      cairo_line_to(cr,
                    Viewport::transformX((*pointsIt)->getX()),
                    Viewport::transformY((*pointsIt)->getY()));
    }
  }
}

Surface::Surface(const char *name, std::vector<std::vector<Point*>*> *matrix) : Object(name) {
  pointsMatrix = matrix;
  curveMatrix = new std::vector<std::vector<Point*>*>();
}

Surface::Surface(std::string *name, std::vector<std::vector<Point*>*> *matrix) : Object(name) {
  pointsMatrix = matrix;
  curveMatrix = new std::vector<std::vector<Point*>*>();
}

void Surface::transform(Matrix *_m) {
  std::vector<std::vector<Point*>*>::iterator vectorsIt = pointsMatrix->begin();
  std::vector<Point*>::iterator pointsIt;
  for (; vectorsIt != pointsMatrix->end(); ++vectorsIt) {
    pointsIt = (*vectorsIt)->begin();
    for (; pointsIt != (*vectorsIt)->end(); ++pointsIt) {
      (*pointsIt)->Point::transform(_m);
    }
  }
}

Object* Surface::clone() {
  std::vector<std::vector<Point*>*> *newMatrix;
  std::vector<Point*> *newVector;
  newMatrix = new std::vector<std::vector<Point*>*>();
  
  std::vector<std::vector<Point*>*>::iterator vectorsIt = pointsMatrix->begin();
  std::vector<Point*>::iterator pointsIt;
  
  std::string *newName = getName();
  
  Surface *oClone;
  if (newName != NULL) {
    newName = new std::string(*newName);
  }
  
  for (; vectorsIt != pointsMatrix->end(); ++vectorsIt) {
    newVector = new std::vector<Point*>();
    pointsIt = (*vectorsIt)->begin();
    for (; pointsIt != (*vectorsIt)->end(); ++pointsIt) {
      newVector->push_back((Point*)(*pointsIt)->clone());
    }
    newMatrix->push_back(newVector);
  }
  
  oClone = new Surface(newName, newMatrix);
  return oClone;

}

std::pair<Point*,Point*> Surface::getCenter() {
  std::pair<Point*,Point*> center;
  float x, y, z;
  std::vector<Point*>::iterator it=pointsMatrix->at(0)->begin();
  if (pointsMatrix->at(0)->size() == 0) {
    center.first = NULL;
    center.second = NULL;
    return center;
  }
  x = (*it)->getX();
  y = (*it)->getY();
  z = (*it)->getZ();
  it++;
  center.second = new Point((std::string *)NULL, x, y, z);
  for (; it != pointsMatrix->at(0)->end(); ++it) {
    x += (*it)->getX();
    y += (*it)->getY();
    z += (*it)->getZ();
  }
  x /= pointsMatrix->at(0)->size();
  y /= pointsMatrix->at(0)->size();
  z /= pointsMatrix->at(0)->size();
  center.first = new Point((std::string *)NULL, x, y, z);
  return center;
}

void Surface::save(FILE *stream) {
#if 0
  int added = 0;
  std::list<Point*>::iterator it=pointsList->begin();
  fprintf(stream, "\n#Add Surface\no %s\n", getName()->c_str());
  for (; it != pointsList->end(); ++it) {
    fprintf(stream, "v %f %f %f 0.0\n", (*it)->getX(), (*it)->getY(), (*it)->getZ());
    added++;
  }
  fprintf(stream, "c 1");
  for (; added > 0; added--) {
    fprintf(stream, " %d", added);
  }
#endif
}

void Surface::clip(void) {
#if 0
  std::list<Point*>::iterator it=curvePoints->begin();
  this->show = true;
  for (; it != curvePoints->end();) {
    (*it)->project();
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
#endif
}

int Surface::getSize() {
  return pointsMatrix->size();
}

void Surface::setList(std::vector<std::vector<Point*>*> *list) {
  pointsMatrix = list;
}

void Surface::calculateCurve() {
#if 1
  std::vector<std::vector<Point*>*>::iterator vectorsIt;
  std::vector<Point*>::iterator pointsIt;
  vectorsIt = curveMatrix->begin();
  for (; vectorsIt != curveMatrix->end(); ++vectorsIt) {
    pointsIt = (*vectorsIt)->begin();
    for (; pointsIt != (*vectorsIt)->end(); ++pointsIt) {
      delete *pointsIt;
    }
    (*vectorsIt)->clear();
    delete *vectorsIt;
  }
  curveMatrix->clear();
#endif
  
  //matriz invertida da B-spline
  float mBS[4][4] = {
    {-1.0/6,  3.0/6, -3.0/6, 1.0/6},
    { 3.0/6, -6.0/6,  3.0/6, 0.0/6},
    {-3.0/6,  0.0/6,  3.0/6, 0.0/6},
    { 1.0/6,  4.0/6,  1.0/6, 0.0/6}
  };
  
  int lines = pointsMatrix->size();
  int columns = pointsMatrix->at(0)->size();
  
  float gX[lines][columns];
  float gY[lines][columns];
  float gZ[lines][columns];
  
  for (int i = 0; i < lines; i++) {
    for (int j = 0; j < columns; j++) {
      gX[i][j] = pointsMatrix->at(i)->at(j)->getX();
      gY[i][j] = pointsMatrix->at(i)->at(j)->getY();
      gZ[i][j] = pointsMatrix->at(i)->at(j)->getZ();
    }
  }
  
  for (int m = 3; m < lines; m++) {
    // calc curve coeficients C
    float Cx[4][4], Cy[4][4], Cz[4][4];
    float tmpx[4][4], tmpy[4][4], tmpz[4][4];
    
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        tmpx[i][j] = 0;
        tmpy[i][j] = 0;
        tmpz[i][j] = 0;
        for (int k = 0; k < 4; k++) {
          tmpx[i][j] += mBS[i][k] * gX[k+m-3][j+m-3];
          tmpy[i][j] += mBS[i][k] * gY[k+m-3][j+m-3];
          tmpz[i][j] += mBS[i][k] * gZ[k+m-3][j+m-3];
        }
        memcpy(Cx, tmpx, sizeof(Cx));
        memcpy(Cy, tmpy, sizeof(Cy));
        memcpy(Cz, tmpz, sizeof(Cz));
      }
    }
    
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        Cx[i][j] = 0;
        Cy[i][j] = 0;
        Cz[i][j] = 0;
        for (int k = 0; k < 4; k++) {
          Cx[i][j] += tmpx[i][k] * mBS[j][k];
          Cy[i][j] += tmpy[i][k] * mBS[j][k];
          Cz[i][j] += tmpz[i][k] * mBS[j][k];
        }
      }
    }
    
    float t[4];
    float s[4];
    float fineStep = Window::getWidth()/6000;
    if (fineStep < (0.01/6000)) {
      fineStep = 0.01;
    }
    const float croaseStep = 0.1;
    
    float tmpCx[4], tmpCy[4], tmpCz[4];
    float x, y, z;
    std::vector<Point*> *tmpVector;
    
    // Um sentido
    t[3] = 1.0;
    s[3] = 1.0;
    for (float f = 0.0; f <= 1.001; f+=croaseStep) {
      t[2] = f;
      t[1] = t[2] * t[2];
      t[0] = t[1] * t[2];
      
      for (int i = 0; i < 4; i++) {
        tmpCx[i] = 0;
        tmpCy[i] = 0;
        tmpCz[i] = 0;
        for (int j = 0; j < 4; j++) {
          tmpCx[i] += Cx[i][j] * t[j];
          tmpCy[i] += Cy[i][j] * t[j];
          tmpCz[i] += Cz[i][j] * t[j];
        }
      }
      tmpVector = new std::vector<Point*>;
      for (float g = 0.0; g <= 1.001; g+=fineStep) {
        s[2] = g;
        s[1] = s[2] * s[2];
        s[0] = s[1] * s[2];
        
        x = 0;
        y = 0;
        z = 0;
        for (int i = 0; i < 4; i++) {
          x += s[i] * tmpCx[i];
          y += s[i] * tmpCy[i];
          z += s[i] * tmpCz[i];
        }
        Point *p = new Point((const char *)NULL, x, y, z);
        tmpVector->push_back(p);
      }
      curveMatrix->push_back(tmpVector);
    }
    
    // Outro sentido
    for (float f = 0.0; f <= 1.001; f+=croaseStep) {
      t[2] = f;
      t[1] = t[2] * t[2];
      t[0] = t[1] * t[2];
      
      for (int i = 0; i < 4; i++) {
        tmpCx[i] = 0;
        tmpCy[i] = 0;
        tmpCz[i] = 0;
        for (int j = 0; j < 4; j++) {
          tmpCx[i] += t[j] * Cx[j][i];
          tmpCy[i] += t[j] * Cy[j][i];
          tmpCz[i] += t[j] * Cz[j][i];
        }
      }
      tmpVector = new std::vector<Point*>;
      for (float g = 0.0; g <= 1.001; g+=fineStep) {
        s[2] = g;
        s[1] = s[2] * s[2];
        s[0] = s[1] * s[2];
        
        x = 0;
        y = 0;
        z = 0;
        for (int i = 0; i < 4; i++) {
          x += tmpCx[i] * s[i];
          y += tmpCy[i] * s[i];
          z += tmpCz[i] * s[i];
        }
        Point *p = new Point((const char *)NULL, x, y, z);
        tmpVector->push_back(p);
      }
      curveMatrix->push_back(tmpVector);
    }
  }
}

#if 0
void Surface::drawFwdDiff(int n, float x[4], float y[4], float z[4]) {
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
#endif

Surface::~Surface() {
#if 1
  std::vector<std::vector<Point*>*>::iterator vectorsIt;
  std::vector<Point*>::iterator pointsIt;
  
  // delete base points
  vectorsIt = pointsMatrix->begin();
  for (; vectorsIt != pointsMatrix->end(); ++vectorsIt) {
    pointsIt = (*vectorsIt)->begin();
    for (; pointsIt != (*vectorsIt)->end(); ++pointsIt) {
      delete *pointsIt;
    }
    (*vectorsIt)->clear();
    delete *vectorsIt;
  }
  pointsMatrix->clear();
  delete pointsMatrix;
  
  // delete curve generated points
  vectorsIt = curveMatrix->begin();
  for (; vectorsIt != curveMatrix->end(); ++vectorsIt) {
    pointsIt = (*vectorsIt)->begin();
    for (; pointsIt != (*vectorsIt)->end(); ++pointsIt) {
      delete *pointsIt;
    }
    (*vectorsIt)->clear();
    delete *vectorsIt;
  }
  curveMatrix->clear();
  delete curveMatrix;
#endif
}
