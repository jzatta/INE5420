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
  static Line *vup;
  static float wAngle;
public:
  static void center();
  static void reset();
  
  static float getWidth();
  static float getHeight();
  static float getX();
  static float getY();
  
  static Matrix *getTransform();
  
  static void zoom(float factor);
  static void moveHorizontal(float pixel);
  static void moveVertical(float pixel);
  static void rotate(float angle);
};


#endif
