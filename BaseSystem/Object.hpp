#ifndef _CG_OBJECT_HPP_
#define _CG_OBJECT_HPP_

class Object;

#include <gtk/gtk.h>
#include "Matrix.hpp"
#include "Drawable.hpp"
#include <list>
#include <string>

class Object: public Drawable {
private:
  std::string *name;
public:
  Object(const char *name) {
    if (name == NULL) {
      this->name = NULL;
    } else {
      this->name = new std::string(name);
    }
  }
  Object(std::string *name) {
    this->name = name;
  }
  
  std::string *getName() const {
    return name;
  }
  
  virtual void draw(cairo_t *cr) = 0;
  
  virtual void transform(Matrix *_m) = 0;
  virtual Object* clone() = 0;
  virtual std::pair<float,float> getCenter() = 0;
  virtual void save(FILE *stream) = 0;
  
  virtual ~Object() {
    if (name != NULL) {
      delete name;
    }
  }
};

#endif
