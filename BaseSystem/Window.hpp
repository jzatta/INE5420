#ifndef _CG_WINDOW_HPP_
#define _CG_WINDOW_HPP_

#include <gtk/gtk.h>
#include <list>
#include "Object.hpp"
#include "Line.hpp"
#include "Polygon.hpp"
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
	std::list<Point> pointsList;
};

struct ParamsRotation {
  double angulo;
  GtkWidget *x;
  GtkWidget *y;
};
protected:
	GtkWidget* window;
	GtkWidget* grid;
	static GtkWidget* da;
	static GtkWidget* oList;


  static std::list<Object*> *objects;

public:
	Window();
	void init();
  static void editWindow(GtkWidget *widget, gpointer data);
  static std::list<Object*> *getObjects();
  static GtkWidget* getDA();
  static GtkWidget* getOlist();
  static void clear_surface (void);
  static void addPoint(GtkWidget* widget, gpointer data);
  static gboolean configure_event_cb (GtkWidget *widget, GdkEventConfigure *event, gpointer data);
  static gboolean draw_cb (GtkWidget *widget, cairo_t *cr, gpointer data);
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
  static void addPoligonWindow(GtkWidget *widget, gpointer   data);
  static void buildPoligon(GtkWidget *widget, gpointer   data);
  static void addPoligonWindowName(GtkWidget *widget, gpointer data);
  static void addPoligon(GtkWidget *widget, gpointer data);
  static void deleteObject(GtkWidget *widget, gpointer data);
  static void transObjectWindow(GtkWidget *widget, gpointer data);
  static void transObject(GtkWidget *widget, gpointer data);
  static void escObjectWindow(GtkWidget *widget, gpointer data);
  static void escObject(GtkWidget *widget, gpointer data);
  static void rotObjectWindow(GtkWidget *widget, gpointer data);
  static void rotObjectCenter(GtkWidget *widget, gpointer data);
  static void rotObjectOrigin(GtkWidget *widget, gpointer data);
  static void rotObjectPointWindow(GtkWidget *widget, gpointer data);
  static void rotObjectPoint(GtkWidget *widget, gpointer data);

};


#endif
