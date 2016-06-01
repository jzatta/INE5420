#ifndef _CG_WINDOW_HPP_
#define _CG_WINDOW_HPP_

class Window;

#include <gtk/gtk.h>
#include "Line.hpp"
#include "Matrix.hpp"
#include "Point.hpp"

class Window {
private:
  static Point *wc;
  static float distance;
//   static Line *vup;
  static float height;
  static float wAngleX;
  static float wAngleY;
  static float wAngleZ;
public:
  static Point *vectX;
  static Point *vectY;
  static Point *vectZ;
  static void center();
  static void reset();
  
  static float getWidth();
  static float getHeight();
  static float getX();
  static float getY();
  static float getZ();
  
  static Matrix *getTransform();
  
  static void zoom(float factor);
  static void moveHorizontal(float pixel);
  static void moveVertical(float pixel);
  static void moveLongitudinal(float pixel);
  static void rotateX(float angle);
  static void rotateY(float angle);
  static void rotateZ(float angle);
  
  static float getDistance();
};


#endif
