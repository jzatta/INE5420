#ifndef _CG_DESCRIPTOROBJ_HPP_
#define _CG_DESCRIPTOROBJ_HPP_

class DescriptorOBJ;

#include <gtk/gtk.h>
#include <list>
#include <vector>
#include "Point.hpp"
#include "Line.hpp"
#include "Polygon.hpp"
#include "Object3D.hpp"
#include "Curve2.hpp"
#include "DisplayFile.hpp"

class DescriptorOBJ {
private:
  static std::list<Point*> *readPoints(const std::vector<Point*> *points, const char *line);
  static std::list<int> *readPointsNumber(const char *line);
public:
  static void save(DisplayFile *df, const char *fileName);
  static std::list<Object*> *load(const char *fileName);
};


#endif
