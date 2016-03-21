#ifndef _CG_POINT_HPP_
#define _CG_POINT_HPP_

#include <gtk/gtk.h>
#include "Object.hpp"

class Point : public Object {
private:
    int x, y;
public:
    void draw(cairo_t *cr);
};


#endif