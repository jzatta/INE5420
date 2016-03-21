#ifndef _CG_WINDOW_HPP_
#define _CG_WINDOW_HPP_

#include <gtk/gtk.h>

static cairo_surface_t *surface = NULL;

class Window {
private:
	GtkWidget* window;
	GtkWidget* grid;
	GtkWidget* da;
	GtkWidget* oList;

public:
	Window();
	void init();
    

};


#endif