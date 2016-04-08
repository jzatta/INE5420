#ifndef _CG_DESCRIPTOROBJ_HPP_
#define _CG_DESCRIPTOROBJ_HPP_

class DescriptorOBJ;

#include <gtk/gtk.h>
#include "DisplayFile.hpp"

class DescriptorOBJ {
private:
public:
  static void save(DisplayFile *df) {
    FILE *file = fopen("teste.obj","w");
    df->save(file);
    fclose(file);
  }
  
  static DisplayFile *load() {
    FILE *file = fopen("teste.obj","r");
    DisplayFile *df = new DisplayFile(file);
    fclose(file);
    return df;
  }
};


#endif
