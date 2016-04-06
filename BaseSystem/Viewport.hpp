#ifndef _CG_VIEWPORT_HPP_
#define _CG_VIEWPORT_HPP_

class Viewport;

#include <gtk/gtk.h>
#include "Window.hpp"

class Viewport {
private:
public:
  // GUI size defined
  const static int ViewportX = 600, ViewportY = 600;
  
  static float transformX(float xw);
  static float transformY(float yw);
};


#endif
