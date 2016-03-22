#ifndef _CG_WINDOW_HPP_
#define _CG_WINDOW_HPP_

#include <gtk/gtk.h>
#include <list>
#include "Object.hpp"
#include "Line.hpp"
#include "Viewport.hpp"

static cairo_surface_t *surface = NULL;

class Window {

struct ParamsPonto {
	GtkWidget *nome;
	GtkWidget *x;
	GtkWidget *y;
};

struct ParamsLinha {
	GtkWidget *nome;
	GtkWidget *xi;
	GtkWidget *yi;
	GtkWidget *xf;
	GtkWidget *yf;
};

struct ParamsPoligon{
	GtkWidget *nome;
	GtkWidget *x;
	GtkWidget *y;
	std::list<std::pair<int,int>> pointsList;
};
private:
	GtkWidget* window;
	GtkWidget* grid;
	static GtkWidget* da;
	GtkWidget* oList;


  static std::list<Object*> *objects;

public:
	Window();
	void init();
  	static std::list<Object*> *getObjects();
        static GtkWidget* getDA();
  	static void clear_surface (void);
  	static void addPoint(GtkWidget* widget, gpointer data);
  	static gboolean configure_event_cb (GtkWidget         *widget,
            GdkEventConfigure *event,
            gpointer           data);
  	static gboolean draw_cb (GtkWidget *widget,
 cairo_t   *cr,
 gpointer   data);
  	static void moveDown(GtkWidget *widget, gpointer data);
  	static void moveRight(GtkWidget *widget, gpointer data);
  	static void moveLeft(GtkWidget *widget, gpointer data);
  	static void moveUp(GtkWidget *widget, gpointer data);
  	static void ZoomOut(GtkWidget *widget, gpointer data);
  	static void ZoomIn(GtkWidget *widget, gpointer data);
  	static void Center(GtkWidget *widget, gpointer data);
  	static void addLine(GtkWidget* widget, gpointer data);
  	static void addPointWindow(GtkWidget *widget, gpointer data);
  	static void addLineWindow(GtkWidget *widget, gpointer   data);
  	static void addPoligonWindowName(GtkWidget *widget, gpointer   data);


};


#endif
