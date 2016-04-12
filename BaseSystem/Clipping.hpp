#ifndef _CG_CLIPPING_HPP_
#define _CG_CLIPPING_HPP_

class Clipping;

#include "Point.hpp"

class Clipping {
private:
public:
  static bool clipPoint(float x, float y);
  static bool clipLineLB(Point *p1, Point *p2);
};


#endif
