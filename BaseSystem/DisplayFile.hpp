#ifndef _CG_DISPLAYFILE_HPP_
#define _CG_DISPLAYFILE_HPP_

class DisplayFile;

#include <gtk/gtk.h>
#include <list>
#include <string>
#include "Drawable.hpp"
#include "GUI.hpp"
#include "Line.hpp"
#include "Matrix.hpp"
#include "Object.hpp"
#include "Point.hpp"
#include "Polygon.hpp"
#include "Viewport.hpp"
#include "Window.hpp"
#include "DescriptorOBJ.hpp"

class DisplayFile: public Drawable {
private:
  std::list<Object*> *objectsWorld;
  std::list<Object*> *objectsTransformed;
  Matrix *transformMatrix;
  
  std::list<Object*>::iterator getObjIt(std::string *name);

public:
  DisplayFile();
  DisplayFile(const char *fileName);
  
  void addObject(Object *_obj);
  void deleteObj(std::string *name);
  Object *getObjW(std::string *name);
  void translateObj(std::string *name, float x, float y, float z);
  void escalonateObj(std::string *name, float scalar);
  void rotateObjOrigin(std::string *name, float angle, int ctrl);
  void rotateObjPoint(std::string *name, float angle, Point *p, int ctrl);
  void rotateObjCenter(std::string *name, float angle, int ctrl);
  
  virtual void draw(cairo_t *cr);
  virtual void transform();
  
  virtual void save(FILE *obj);
  
  virtual ~DisplayFile();
};


#endif
