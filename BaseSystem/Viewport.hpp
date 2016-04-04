#ifndef _CG_VIEWPORT_HPP_
#define _CG_VIEWPORT_HPP_

#include <gtk/gtk.h>

class Viewport {
private:
  static float windowX, windowY;
  static float windowW, windowH;
  
public:
  // GUI size defined
  const static int ViewportX = 600, ViewportY = 600;
  
  static float transformX(float xw);
  static float transformY(float yw);
  
  static void setWindowX(float x);
  static void setWindowY(float y);
  static void setWindowWidth(float width);
  static void setWindowHeight(float height);
  
  static void defaultSize();
  
  static void zoom(float factor);
  
  static void moveHorizontal(float factor);
  static void moveVertical(float factor);
};


#endif
