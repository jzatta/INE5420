#ifndef _CG_GUI_HPP_
#define _CG_GUI_HPP_

#include <gtk/gtk.h>
#include <list>
#include "Object.hpp"
#include "Line.hpp"
#include "Polygon.hpp"
#include "Viewport.hpp"
#include "DisplayFile.hpp"

static cairo_surface_t *surface = NULL;

class GUI {
  
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
  
  struct ParamsPolygon{
    GtkWidget *nome;
    GtkWidget *x;
    GtkWidget *y;
    std::list<Point*> *pointsList;
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
  
  
  static DisplayFile *displayFile;
  
public:
  GUI();
  void init();
  static void editWindow(GtkWidget *widget, gpointer data);
  static DisplayFile *getDisplayFile();
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
  static void addPolygonWindow(GtkWidget *widget, gpointer   data);
  static void buildPolygon(GtkWidget *widget, gpointer   data);
  static void addPolygonWindowName(GtkWidget *widget, gpointer data);
  static void addPolygon(GtkWidget *widget, gpointer data);
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
