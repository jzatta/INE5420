#ifndef _CG_OBJECT3D_HPP_
#define _CG_OBJECT3D_HPP_

class Object3D;

#include <gtk/gtk.h>
#include <list>
#include "Object.hpp"
#include "Point.hpp"
#include "Viewport.hpp"

#include <iostream>

class Object3D : public Object {
private:
  std::vector<Point*> *pointsList;
  std::list<std::pair<int,int>> *edgeList;
public:
  Object3D(const char *name, std::vector<Point*> *_pointsList, std::list<std::pair<int,int>> *_edgeList);
  Object3D(std::string *name, std::vector<Point*> *_pointsList, std::list<std::pair<int,int>> *_edgeList);
  virtual void draw(cairo_t *cr);
  virtual Object* clone();
  virtual void transform(Matrix *_m);
  virtual void save(FILE *stream);
  virtual void clip(void);
  virtual std::pair<Point*,Point*> getCenter();
  Point * getPoint(int index);
  int getSize();

  void setPointsList(std::vector<Point*>* _list);
  void setEdgeList(std::list<std::pair<int,int>> *_list);
  virtual ~Object3D();
};


#endif
