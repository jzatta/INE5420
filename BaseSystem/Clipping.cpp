#include "Clipping.hpp"

static float max(float a, float b, float c) {
  if (a > b) {
    return (a > c)?a:c;
  }
  return (b > c)?b:c;
}

static float min(float a, float b, float c) {
  if (a < b) {
    return (a < c)?a:c;
  }
  return (b < c)?b:c;
}

bool Clipping::clipPoint(float x, float y) {
  if ( (x < -1) || (x > 1) || (y < -1) || (y > 1) ) {
    return false;
  }
  return true;
}

bool Clipping::clipLineLB(Point *p1, Point *p2) {
  float dx, dy;
  float p[4], q[4], u[4];
  float maxP, minP;
  int it;

  dx = p2->getX() - p1->getX();
  dy = p2->getY() - p1->getY();

  p[0] = -dx; p[1] = dx;
  p[2] = -dy; p[3] = dy;

  q[0] = (p1->getX() - (-1));
  q[1] = (1 - p1->getX());
  q[2] = (p1->getY() - (-1));
  q[3] = (1 - p1->getY());

  // test and clip if is parallel to window cordinates
  for (it = 0; it < 4; it++) {
    if (p[it] == 0) {
      if (it & 0x02) { // dy == 0
        if ((p1->getY() > 1) || (p1->getY() < -1)) { // outside window
          return false;
        }
        if (p1->getX() > 1) {
          p1->setX(1);
        }
        else if (p1->getX() < -1) {
          p1->setX(-1);
        }
        if (p2->getX() > 1) {
          p2->setX(1);
        }
        else if (p2->getX() < -1) {
          p2->setX(-1);
        }
        return true;
      } else { // dx == 0
        if ((p1->getX() > 1) || (p1->getX() < -1)) { // outside window
          return false;
        }
        if (p1->getY() > 1) {
          p1->setY(1);
        }
        else if (p1->getY() < -1) {
          p1->setY(-1);
        }
        if (p2->getY() > 1) {
          p2->setY(1);
        }
        else if (p2->getY() < -1) {
          p2->setY(-1);
        }
        return true;
      }
    }
  }
  
  u[0] = q[0]/p[0];
  u[1] = q[1]/p[1];
  u[2] = q[2]/p[2];
  u[3] = q[3]/p[3];
  
  if ((p[0] <= 0) && (p[2] <= 0)) {
    maxP = max(0, u[0], u[2]);
    minP = min(1, u[1], u[3]);
  }
  else if ((p[1] <= 0) && (p[2] <= 0)) {
    maxP = max(0, u[1], u[2]);
    minP = min(1, u[0], u[3]);
  }
  else if ((p[0] <= 0) && (p[3] <= 0)) {
    maxP = max(0, u[0], u[3]);
    minP = min(1, u[1], u[2]);
  }
  else if ((p[1] <= 0) && (p[3] <= 0)) {
    maxP = max(0, u[1], u[3]);
    minP = min(1, u[0], u[2]);
  }
  
  // Outside Window
  if (maxP > minP) {
    return false;
  }
  
  
  // Inside Window
  if (minP < 1) {
    p2->setX(p1->getX() + (minP*dx) );
    p2->setY(p1->getY() + (minP*dy) );
  }
  if (maxP > 0) {
    p1->setX(p1->getX() + (maxP*dx) );
    p1->setY(p1->getY() + (maxP*dy) );
  }
  return true;
}

short Clipping::getCode(Point p) {
  short code;

  code = INSIDE;          

  if (p.getX() < -1){       
    if (p.getY() > 1){
      code |= LEFTTOP;
    } else if(p.getY() < -1) {
      code |= LEFTBOTTOM;

    } else {
      code |= LEFT;;
    }
  } else if (p.getX() > 1) {     
    if (p.getY() > 1){
      code |= RIGHTTOP;
    } else if(p.getY() < -1) {
      code |= RIGHTBOTTOM;
    } else {
      code |= RIGHT;
    }
  } 
  if (p.getY() < -1) {           
    code |= BOTTOM;
  } else if (p.getY() > 1) {     
    code |= TOP;
  }

  return code;
}

void Clipping::calculateCS(short codeP, Point * p1, Point * p2, bool k){
   Point * p;
   if(k){
    p = p1;
   } else {
    p = p2;
   }
   double xAux;
   double yAux;

   switch (codeP) {
    case TOP : p->setX(p1->getX() + (p2->getX() - p1->getX()) * (1 - p1->getY()) / (p2->getY() - p1->getY()));
               p->setY(1);
               break;
    case BOTTOM : p->setX(p1->getX() + (p2->getX() - p1->getX()) * (-1 - p1->getY()) / (p2->getY() - p1->getY()));
                  p->setY(-1);
                  break;
    case RIGHT: p->setY(p1->getY() + (p2->getY() - p1->getY()) * (1 - p1->getX()) / (p2->getX() - p1->getX()));
                p->setX(1);
                break;
    case LEFT: p->setY(p1->getY() + (p2->getY() - p1->getY()) * (-1 - p1->getX()) / (p2->getX() - p1->getX()));
                p->setX(-1);
                break;
    case RIGHTTOP : xAux = p1->getX() + (p2->getX() - p1->getX()) * (1 - p1->getY()) / (p2->getY() - p1->getY());
                    if (xAux <= 1){
                      p->setX(xAux);
                      p->setY(1);
                    } else {
                      p->setY(p1->getY() + (p2->getY() - p1->getY()) * (1 - p1->getX()) / (p2->getX() - p1->getX()));
                      p->setX(1);
                    }
                    break;
    case RIGHTBOTTOM : xAux = p1->getX() + (p2->getX() - p1->getX()) * (-1 - p1->getY()) / (p2->getY() - p1->getY());
                      if (xAux <= 1){
                      p->setX(xAux);
                      p->setY(-1);
                    } else {
                      p->setY(p1->getY() + (p2->getY() - p1->getY()) * (1 - p1->getX()) / (p2->getX() - p1->getX()));
                      p->setX(1);
                    }
                    break;
    case LEFTTOP : xAux = p1->getX() + (p2->getX() - p1->getX()) * (1 - p1->getY()) / (p2->getY() - p1->getY());
                      if (xAux >= -1){
                      p->setX(xAux);
                      p->setY(1);
                    } else {
                      p->setY(p1->getY() + (p2->getY() - p1->getY()) * (-1 - p1->getX()) / (p2->getX() - p1->getX()));
                      p->setX(-1);
                    }
                    break;
    case LEFTBOTTOM : xAux = p1->getX() + (p2->getX() - p1->getX()) * (-1 - p1->getY()) / (p2->getY() - p1->getY());
                      if (xAux >= -1){
                      p->setX(xAux);
                      p->setY(-1);
                    } else {
                      p->setY(p1->getY() + (p2->getY() - p1->getY()) * (-1 - p1->getX()) / (p2->getX() - p1->getX()));
                      p->setX(-1);
                    }
  }
}

bool Clipping::clipLineCS(Point *p1, Point *p2){
  short codeP1 = Clipping::getCode(*p1);
  short codeP2 = Clipping::getCode(*p2);

  if(!(codeP1 | codeP2)){
    return true;
  } else if (codeP1 & codeP2) {
    return false;
  }
  calculateCS(codeP1, p1, p2, true);
  calculateCS(codeP2, p1, p2, false);
  return true;

}

bool Clipping::clipPolygon(Polygon * polygon) {
  int i;
  int j;

 std::list<Point*>* newList; // = new std::list<Point*>();
  
  for(j = 1; j < 5; j++){
    newList = new std::list<Point*>();
    for (i = 0; i < polygon->getSize(); i++){
      
      Point * p1 = polygon->getPoint(i);
      Point * p2 = polygon->getPoint((i+1)%(polygon->getSize()));
      
      if (verifyPoint(p1->getX(), p1->getY(), j)) {
        if (verifyPoint(p2->getX(), p2->getY(), j)){
          newList->push_back(p2);
        } else {
          newList->push_back(Clipping::intersection(p1, p2, j));
        }
      } else {
        if (verifyPoint(p2->getX(), p2->getY(), j)){
          newList->push_back(Clipping::intersection(p1, p2, j));
          newList->push_back(p2);
        }
      }
    }
    polygon->setList(newList);
  }
  return true;
}

Point* Clipping::intersection(Point * p1, Point * p2, int index){
  float m;
  float c;

  m = (p2->getY() - p1->getY()) / (p2->getX() - p1->getX());
  c = p1->getY() - m * p1->getX();

float x;
float y;
  switch (index){
    case 1: y = 1;
            if (p2->getX() != p1->getX()){
              x = (y - c) / m;
            } else {
              x = p1->getX();
            } 
          break;
    case 2: x = 1;
            y = x*m + c;
          break;
    case 3: y = -1;
          if (p2->getX() != p1->getX()){
            x = (y - c) / m;
          } else {
            x = p1->getX();
          } 
          break;
    case 4: x = -1;
          y = x*m + c;
          break;
  }

  Point * intersec = new Point("", x, y);
  return intersec;
}

bool Clipping::verifyPoint(float x, float y, int index){
  switch(index){
    case 1: return (y < 1);
    case 2: return (x < 1);
    case 3: return (y > -1);
    case 4: return (x > -1);
  }
}
