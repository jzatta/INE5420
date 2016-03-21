#ifndef _CG_VIEWPORT_HPP_
#define _CG_VIEWPORT_HPP_

#include <gtk/gtk.h>

class Viewport {
private:
  static int windowX, windowY;
  static int windowW, windowH;

public:
  const static int ViewportX = 600, ViewportY = 600;

  static int transformX(int xw);
  static int transformY(int yw);

  static void setWindowX(int x);
  static void setWindowY(int y);
  static void setWindowWidth(int width);
  static void setWindowHeight(int height);

  static void zoom(float factor);

  static void moveHorizontal(float factor);
  static void moveVertical(float factor);
};


#endif
