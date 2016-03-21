#ifndef _CG_OBJECT_HPP_
#define _CG_OBJECT_HPP_

#include <gtk/gtk.h>

class Object {
public:
    virtual void draw(cairo_t *cr) = 0;
};


#endif