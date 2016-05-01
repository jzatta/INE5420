#ifndef _CG_CLIPPING_HPP_
#define _CG_CLIPPING_HPP_

class Clipping;

#include "Point.hpp"
#include "Polygon.hpp"
#include <iostream>

class Clipping {


protected:

	static const short INSIDE = 0; // 0000
	static const short LEFT = 1;   // 0001
	static const short RIGHT = 2;  // 0010
	static const short BOTTOM = 4; // 0100
	static const short LEFTBOTTOM = 5; // 0101
	static const short RIGHTBOTTOM = 6; //0110; 
	static const short TOP = 8;    // 1000
	static const short LEFTTOP = 9; //1001
	static const short RIGHTTOP = 10; //1010

	static short getCode(Point p);
	static void calculateCS(short codeP, Point * p1, Point * p2, bool k);
	static Point* intersection(Point * p1, Point * p2, int index);
	static bool verifyPoint(float x, float y, int index);

public:
  static bool clipPoint(float x, float y);
  static bool clipLineLB(Point *p1, Point *p2);
  static bool clipLineCS(Point *p1, Point *p2);
  static bool clipPolygon(Polygon * polygon);
};


#endif
