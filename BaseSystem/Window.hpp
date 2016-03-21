#ifndef _CG_WINDOW_HPP_
#define _CG_WINDOW_HPP_

#include <gtk/gtk.h>
#include <list>
#include "Object.hpp"
#include "Line.hpp"
#include "Viewport.hpp"

static cairo_surface_t *surface = NULL;

class Window {
private:
	GtkWidget* window;
	GtkWidget* grid;
	GtkWidget* da;
	GtkWidget* oList;

  static std::list<Object*> *objects;

public:
	Window();
	void init();
  static std::list<Object*> *getObjects();

};


#endif
