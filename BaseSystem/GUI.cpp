
#include <iostream>
#include "GUI.hpp"
#include <string>
#include <algorithm>
#include "Matrix.hpp"
#include "DescriptorOBJ.hpp"
#include <utility>

DisplayFile *GUI::displayFile;
GtkWidget* GUI::da;
GtkWidget* GUI::oList;


GUI::GUI() {

}

// Drawing area routines -------------------------------------------------------
void GUI::clear_surface (void)
{
  cairo_t *cr;

  cr = cairo_create (surface);

  cairo_set_source_rgb (cr, 0, 0, 0);
  cairo_paint (cr);

  cairo_destroy (cr);
}

gboolean GUI::configure_event_cb (GtkWidget         *widget,
                                  GdkEventConfigure *event,
                                  gpointer           data)
{
  if (surface)
    cairo_surface_destroy (surface);

  surface = gdk_window_create_similar_surface (gtk_widget_get_window (widget),
                                              CAIRO_CONTENT_COLOR,
                                              gtk_widget_get_allocated_width (widget),
                                              gtk_widget_get_allocated_height (widget));

  clear_surface ();

  return TRUE;
}

gboolean GUI::draw_cb (GtkWidget *widget,
                      cairo_t   *cr,
                      gpointer   data)
{
  GdkRGBA color;
  cairo_set_source_rgb (cr, 0, 0, 0);
  cairo_paint (cr);
  cairo_set_source_rgb (cr, 1, 0, 0);
  cairo_set_line_width(cr, 0.5);

  cairo_move_to(cr, 20, 20);
  cairo_line_to(cr, Viewport::ViewportX - 20, 20);
  cairo_line_to(cr, Viewport::ViewportX - 20, Viewport::ViewportY - 20);
  cairo_line_to(cr, 20, Viewport::ViewportY - 20);
  cairo_line_to(cr, 20, 20);
  cairo_stroke(cr);

  cairo_set_source_rgb (cr, 1, 1, 1);
  cairo_set_line_width(cr, 0.5);

  GUI::getDisplayFile()->draw(cr);

  cairo_stroke(cr);

  return FALSE;
}

// GUI getters -----------------------------------------------------------------
DisplayFile *GUI::getDisplayFile() {
  if (GUI::displayFile == NULL) {
    //GUI::displayFile = DescriptorOBJ::load();
    GUI::displayFile = new DisplayFile();
  }
  return GUI::displayFile;
}

GtkWidget* GUI::getDA() {
  return da;
}

GtkWidget * GUI::getOlist() {
  return oList;
}

// Navigation routines
void GUI::moveDown(GtkWidget *widget, gpointer data) {
  Window::moveVertical(-10);
  gtk_widget_queue_draw(GTK_WIDGET(GUI::getDA()));
}

void GUI::moveRight(GtkWidget *widget, gpointer data) {
  Window::moveHorizontal(10);
  gtk_widget_queue_draw(GTK_WIDGET(GUI::getDA()));
}

void GUI::moveLeft(GtkWidget *widget, gpointer data) {
  Window::moveHorizontal(-10);
  gtk_widget_queue_draw(GTK_WIDGET(GUI::getDA()));
}

void GUI::moveUp(GtkWidget *widget, gpointer data) {
  Window::moveVertical(10);
  gtk_widget_queue_draw(GTK_WIDGET(GUI::getDA()));
}

void GUI::moveForward(GtkWidget *widget, gpointer data) {
  Window::moveLongitudinal(-10);
  gtk_widget_queue_draw(GTK_WIDGET(GUI::getDA()));
}

void GUI::moveBackward(GtkWidget *widget, gpointer data) {
  Window::moveLongitudinal(10);
  gtk_widget_queue_draw(GTK_WIDGET(GUI::getDA()));
}

void GUI::ZoomOut(GtkWidget *widget, gpointer data) {
  Window::zoom(1.25);
  gtk_widget_queue_draw(GTK_WIDGET(GUI::getDA()));
}

void GUI::ZoomIn(GtkWidget *widget, gpointer data) {
  Window::zoom(0.8);
  gtk_widget_queue_draw(GTK_WIDGET(GUI::getDA()));
}

void GUI::Center(GtkWidget *widget, gpointer data) {
  Window::center();
  gtk_widget_queue_draw(GTK_WIDGET(GUI::getDA()));
}

void GUI::turnUp(GtkWidget *widget, gpointer data) {
  Window::rotateX(-15);
  gtk_widget_queue_draw(GTK_WIDGET(GUI::getDA()));
}

void GUI::turnDown(GtkWidget *widget, gpointer data) {
  Window::rotateX(15);
  gtk_widget_queue_draw(GTK_WIDGET(GUI::getDA()));
}

void GUI::turnLeft(GtkWidget *widget, gpointer data) {
  Window::rotateY(-15);
  gtk_widget_queue_draw(GTK_WIDGET(GUI::getDA()));
}

void GUI::turnRight(GtkWidget *widget, gpointer data) {
  Window::rotateY(15);
  gtk_widget_queue_draw(GTK_WIDGET(GUI::getDA()));
}

void GUI::rotateLeft(GtkWidget *widget, gpointer data) {
  Window::rotateZ(-15);
  gtk_widget_queue_draw(GTK_WIDGET(GUI::getDA()));
}

void GUI::rotateRight(GtkWidget *widget, gpointer data) {
  Window::rotateZ(15);
  gtk_widget_queue_draw(GTK_WIDGET(GUI::getDA()));
}

void GUI::Reset(GtkWidget *widget, gpointer data) {
  Window::reset();
  gtk_widget_queue_draw(GTK_WIDGET(GUI::getDA()));
}

// Add point routines ----------------------------------------------------------
void GUI::addPoint(GtkWidget* widget, gpointer data) {
  ParamsPonto * paramsP = (ParamsPonto*) data;
  std::string* name =  new std::string(gtk_entry_get_text((GtkEntry*)paramsP->nome));
  const char* x = gtk_entry_get_text((GtkEntry*)paramsP->x);
  const char* y = gtk_entry_get_text((GtkEntry*)paramsP->y);
  const char* z = gtk_entry_get_text((GtkEntry*)paramsP->z);

  //GtkWidget* label = gtk_label_new(name->c_str());
  //gtk_list_box_prepend((GtkListBox*)oList, label);
  //gtk_widget_show(label);
  GUI::addToListBox(*name);

  GUI::getDisplayFile()->addObject(new Point(name, atof(x), atof(y), atof(z)));

  gtk_widget_queue_draw(GTK_WIDGET(GUI::getDA()));
}

void GUI::addPointWindow(GtkWidget *widget, gpointer data) {
  ParamsPonto * paramsP = new ParamsPonto();

  GtkWidget * auxWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(auxWindow), 300, 100);
  gtk_window_set_title(GTK_WINDOW(auxWindow), "Incluir Ponto");
  g_signal_connect(auxWindow, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);
  gtk_container_set_border_width(GTK_CONTAINER(auxWindow), 10);


  GtkWidget* auxGrid = gtk_grid_new();
  gtk_container_set_border_width(GTK_CONTAINER(auxGrid), 5);
  gtk_container_add(GTK_CONTAINER(auxWindow), auxGrid);

  GtkWidget* label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), "Nome: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 0, 1, 1);

  paramsP->nome = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsP->nome, 1, 0, 1, 1);

  label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), "x: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 1, 1, 1);

  paramsP->x = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsP->x, 1, 1, 1, 1);

  label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), " y: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 2, 1, 1);

  paramsP->y = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsP->y, 1, 2, 1, 1);

  label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), " z: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 3, 1, 1);

  paramsP->z = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsP->z, 1, 3, 1, 1);

  GtkWidget* button = gtk_button_new_with_label("Add");
  g_signal_connect(button, "clicked", G_CALLBACK(addPoint), (gpointer) paramsP);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), auxWindow);

  gtk_grid_attach(GTK_GRID(auxGrid), button, 1, 4, 2, 2);

  gtk_widget_show_all(auxWindow);
}

// Add line routines -----------------------------------------------------------
void GUI::addLine(GtkWidget* widget, gpointer data) {
  ParamsLinha * paramsL = (ParamsLinha*) data;
  std::string* name =  new std::string(gtk_entry_get_text((GtkEntry*)paramsL->nome));
  const char* xi = gtk_entry_get_text((GtkEntry*)paramsL->xi);
  const char* yi = gtk_entry_get_text((GtkEntry*)paramsL->yi);
  const char* zi = gtk_entry_get_text((GtkEntry*)paramsL->zi);
  const char* xf = gtk_entry_get_text((GtkEntry*)paramsL->xf);
  const char* yf = gtk_entry_get_text((GtkEntry*)paramsL->yf);
  const char* zf = gtk_entry_get_text((GtkEntry*)paramsL->zf);

  //GtkWidget* label = gtk_label_new(name->c_str());
  //gtk_list_box_prepend((GtkListBox*)oList, label);
  //gtk_widget_show(label);
  GUI::addToListBox(*name);

  Point * a = new Point(name, atof(xi), atof(yi), atof(zi));
  Point * b = new Point(name, atof(xf), atof(yf), atof(zf));
  //segfault se usar o construtor de pontos
  GUI::getDisplayFile()->addObject(new Line(name, a, b));

  gtk_widget_queue_draw(GTK_WIDGET(GUI::getDA()));
}

void GUI::addLineWindow(GtkWidget *widget, gpointer   data) {

  ParamsLinha * paramsL = new ParamsLinha();

  GtkWidget * auxWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(auxWindow), 300, 100);
  gtk_window_set_title(GTK_WINDOW(auxWindow), "Incluir Linha");
  g_signal_connect(auxWindow, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);
  gtk_container_set_border_width(GTK_CONTAINER(auxWindow), 10);


  GtkWidget* auxGrid = gtk_grid_new();
  gtk_container_set_border_width(GTK_CONTAINER(auxGrid), 5);
  gtk_container_add(GTK_CONTAINER(auxWindow), auxGrid);

  GtkWidget* label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), "Nome: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 0, 1, 1);

  paramsL->nome = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsL->nome, 1, 0, 1, 1);

  label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), "x1: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 1, 1, 1);

  paramsL->xi = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsL->xi, 1, 1, 1, 1);

  label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), " y1: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 2, 1, 1);

  paramsL->yi = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsL->yi, 1, 2, 1, 1);

  label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), " z1: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 3, 1, 1);

  paramsL->zi = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsL->zi, 1, 3, 1, 1);

  label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), " x2: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 4, 1, 1);

  paramsL->xf = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsL->xf, 1, 4, 1, 1);

  label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), " y2: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 5, 1, 1);

  paramsL->yf = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsL->yf, 1, 5, 1, 1);

  label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), " z2: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 6, 1, 1);

  paramsL->zf = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsL->zf, 1, 6, 1, 1);

  GtkWidget* button = gtk_button_new_with_label("Add");
  g_signal_connect(button, "clicked", G_CALLBACK(addLine), (gpointer) paramsL);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), auxWindow);
  gtk_grid_attach(GTK_GRID(auxGrid), button, 1, 7, 2, 2);

  gtk_widget_show_all(auxWindow);
}

// Add polygon routines --------------------------------------------------------
void GUI::addPolygonWindow(GtkWidget *widget, gpointer data) {
  ParamsPolygon * params;
  if(data == NULL) {
    params = new ParamsPolygon();
    params->pointsList = new std::list<Point*>();
  } else {
    params = (ParamsPolygon*) data;
  }

  GtkWidget * auxWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(auxWindow), 300, 100);
  gtk_window_set_title(GTK_WINDOW(auxWindow), "Incluir Poligono");
  g_signal_connect(auxWindow, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);
  gtk_container_set_border_width(GTK_CONTAINER(auxWindow), 10);

  GtkWidget* auxGrid = gtk_grid_new();
  gtk_container_set_border_width(GTK_CONTAINER(auxGrid), 5);
  gtk_container_add(GTK_CONTAINER(auxWindow), auxGrid);

  GtkWidget* label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), "x: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 0, 1, 1);

  params->x = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), params->x, 1, 0, 1, 1);

  label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), " y: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 1, 1, 1);

  params->y = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), params->y, 1, 1, 1, 1);

  label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), " z: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 2, 1, 1);

  params->z = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), params->z, 1, 2, 1, 1);


  GtkWidget* button = gtk_button_new_with_label("Add More");
  g_signal_connect(button, "clicked", G_CALLBACK(buildPolygon), (gpointer) params);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), auxWindow);
  gtk_grid_attach(GTK_GRID(auxGrid), button, 0, 3, 1, 2);

  button = gtk_button_new_with_label("Finish");
  g_signal_connect(button, "clicked", G_CALLBACK(addPolygonWindowName), (gpointer) params);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), auxWindow);
  gtk_grid_attach(GTK_GRID(auxGrid), button, 1, 3, 1, 2);

  gtk_widget_show_all(auxWindow);
}

void GUI::buildPolygon(GtkWidget *widget, gpointer data) {
  ParamsPolygon *params = (ParamsPolygon*) data;
  const char *x = gtk_entry_get_text((GtkEntry*)params->x);
  float xi = atof(x);
  const char *y = gtk_entry_get_text((GtkEntry*)params->y);
  float yi = atof(y);
  const char *z = gtk_entry_get_text((GtkEntry*)params->z);
  float zi = atof(z);

  Point *p = new Point("polygonPoint",xi, yi, zi);
  params->pointsList->push_back(p);

  addPolygonWindow(widget, (gpointer)params);
}

void GUI::addPolygonWindowName(GtkWidget *widget, gpointer data) {
  ParamsPolygon * params = (ParamsPolygon*) data;
  const char* x = gtk_entry_get_text((GtkEntry*)params->x);
  float xi = atof(x);
  const char* y = gtk_entry_get_text((GtkEntry*)params->y);
  float yi = atof(y);
  const char *z = gtk_entry_get_text((GtkEntry*)params->z);
  float zi = atof(z);

  Point *p = new Point("polygonPoint",xi, yi, zi);
  params->pointsList->push_back(p);

  GtkWidget * auxWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(auxWindow), 300, 100);
  gtk_window_set_title(GTK_WINDOW(auxWindow), "Incluir Poligono");
  g_signal_connect(auxWindow, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);
  gtk_container_set_border_width(GTK_CONTAINER(auxWindow), 10);

  GtkWidget* auxGrid = gtk_grid_new();
  gtk_container_set_border_width(GTK_CONTAINER(auxGrid), 5);
  gtk_container_add(GTK_CONTAINER(auxWindow), auxGrid);

  GtkWidget* label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), "Nome: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 0, 1, 1);

  params->nome = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), params->nome, 1, 0, 1, 1);

  GtkWidget* button = gtk_button_new_with_label("Add");
  gtk_grid_attach(GTK_GRID(auxGrid), button, 0, 1, 2, 1);
  g_signal_connect(button, "clicked", G_CALLBACK(addPolygon), (gpointer) params);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), auxWindow);

  gtk_widget_show_all(auxWindow);

}

void GUI::addPolygon(GtkWidget *widget, gpointer data) {
  ParamsPolygon *params = (ParamsPolygon*) data;
  std::string *name =  new std::string(gtk_entry_get_text((GtkEntry*)params->nome));

  //GtkWidget* label = gtk_label_new(name->c_str());
  //gtk_list_box_prepend((GtkListBox*)oList, label);
  //gtk_widget_show(label);
  GUI::addToListBox(*name);


  GUI::getDisplayFile()->addObject(new Polygon(name, params->pointsList));
  delete params;

  gtk_widget_queue_draw(GTK_WIDGET(GUI::getDA()));
}

// Init GUI routines -----------------------------------------------------------
void GUI::init() {
  GtkWidget* frame;
  GtkWidget* inGrid;
  GtkWidget* button;
  GtkWidget* label;

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
  gtk_window_set_title(GTK_WINDOW(window), "T1");
  g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);


  grid = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(window), grid);

  inGrid = gtk_grid_new();
  gtk_grid_attach(GTK_GRID(grid), inGrid, 0, 0, 2, 1);
  frame = gtk_frame_new("Objects");
  gtk_grid_attach(GTK_GRID(inGrid), frame, 0, 0, 2, 1);

  GtkWidget* sw;
  sw = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sw), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  gtk_container_add(GTK_CONTAINER(frame), sw);
  gtk_widget_show(sw);

  oList = gtk_list_box_new();
  GtkAllocation alloc;
  gtk_widget_get_allocation(oList, &alloc);
  gtk_widget_set_size_request(oList, 180, 200);

  GtkWidget* viewport; GtkRequisition size;
  gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(sw), oList);
  viewport = gtk_widget_get_ancestor(oList, GTK_TYPE_VIEWPORT);
  gtk_widget_size_request(viewport, &size);
  gtk_widget_set_size_request(sw, 180, 200);

  gtk_container_add(GTK_CONTAINER(frame), oList);
  gtk_list_box_set_selection_mode((GtkListBox*)oList, GTK_SELECTION_SINGLE);

  button = gtk_button_new_with_label("Edit");
  gtk_grid_attach(GTK_GRID(inGrid), button, 0,1,2,1);
  g_signal_connect(button, "clicked", G_CALLBACK(editWindow), NULL);

  frame = gtk_frame_new("Drawn");
  gtk_grid_attach(GTK_GRID(grid), frame, 0,2,1,1);

  inGrid = gtk_grid_new();

  gtk_container_set_border_width(GTK_CONTAINER(inGrid), 5);
  gtk_container_add(GTK_CONTAINER(frame), inGrid);

  button = gtk_button_new_with_label("Point");
  gtk_grid_attach(GTK_GRID(inGrid), button, 0, 1, 1, 1);
  g_signal_connect(button, "clicked", G_CALLBACK(addPointWindow), NULL);

  button = gtk_button_new_with_label("Line");
  gtk_grid_attach(GTK_GRID(inGrid), button, 0, 2, 1, 1);
  g_signal_connect(button, "clicked", G_CALLBACK(addLineWindow), NULL);

  button = gtk_button_new_with_label("Polygon");
  gtk_grid_attach(GTK_GRID(inGrid), button, 0, 3, 1, 1);
  g_signal_connect(button, "clicked", G_CALLBACK(addPolygonWindow), NULL);

  button = gtk_button_new_with_label("Curve");
  gtk_grid_attach(GTK_GRID(inGrid), button, 2, 1, 1, 1);
  g_signal_connect(button, "clicked", G_CALLBACK(addCurveWindow), NULL);

  inGrid = gtk_grid_new();
  gtk_container_set_border_width(GTK_CONTAINER(inGrid), 5);
  gtk_grid_attach(GTK_GRID(grid), inGrid, 2, 0, 1, 4);
  label = gtk_label_new("Viewport");
  gtk_grid_attach(GTK_GRID(inGrid), label, 0,0,1,1);
  da = gtk_drawing_area_new();
  gtk_widget_set_size_request(da, Viewport::ViewportX, Viewport::ViewportY);
  gtk_grid_attach(GTK_GRID(inGrid), da, 0, 1, 1, 1);
  g_signal_connect (da, "draw", G_CALLBACK (draw_cb), NULL);
  g_signal_connect (da,"configure-event", G_CALLBACK (configure_event_cb), NULL);

  frame = gtk_frame_new("View Control");
  gtk_grid_attach(GTK_GRID(grid), frame, 0,3,2,1);

  inGrid = gtk_grid_new();
  gtk_container_set_border_width(GTK_CONTAINER(inGrid), 5);
  gtk_container_add(GTK_CONTAINER(frame), inGrid);

  button = gtk_button_new_with_label("RESET");
  g_signal_connect(button, "clicked", G_CALLBACK(Reset), da);
  gtk_grid_attach(GTK_GRID(inGrid), button, 0, 1, 1, 1);

  button = gtk_button_new_with_label("Up");
  g_signal_connect(button, "clicked", G_CALLBACK(moveUp), da);
  gtk_grid_attach(GTK_GRID(inGrid), button, 1, 1, 1, 1);

  button = gtk_button_new_with_label("Left");
  g_signal_connect(button, "clicked", G_CALLBACK(moveLeft), da);
  gtk_grid_attach(GTK_GRID(inGrid), button, 0, 2, 1, 1);

  button = gtk_button_new_with_label("Center");
  g_signal_connect(button, "clicked", G_CALLBACK(Center), da);
  gtk_grid_attach(GTK_GRID(inGrid), button, 1, 2, 1, 1);

  button = gtk_button_new_with_label("Right");
  g_signal_connect(button, "clicked", G_CALLBACK(moveRight), da);
  gtk_grid_attach(GTK_GRID(inGrid), button, 2, 2, 1, 1);

  button = gtk_button_new_with_label("Fwd");
  g_signal_connect(button, "clicked", G_CALLBACK(moveForward), da);
  gtk_grid_attach(GTK_GRID(inGrid), button, 0, 3, 1, 1);

  button = gtk_button_new_with_label("Down");
  g_signal_connect(button, "clicked", G_CALLBACK(moveDown), da);
  gtk_grid_attach(GTK_GRID(inGrid), button, 1, 3, 1, 1);

  button = gtk_button_new_with_label("Bwd");
  g_signal_connect(button, "clicked", G_CALLBACK(moveBackward), da);
  gtk_grid_attach(GTK_GRID(inGrid), button, 2, 3, 1, 1);

  button = gtk_button_new_with_label("Zoom-");
  g_signal_connect(button, "clicked", G_CALLBACK(ZoomOut), da);
  gtk_grid_attach(GTK_GRID(inGrid), button, 0, 4, 1, 1);
  
  button = gtk_button_new_with_label("TurnU");
  g_signal_connect(button, "clicked", G_CALLBACK(turnUp), da);
  gtk_grid_attach(GTK_GRID(inGrid), button, 1, 4, 1, 1);

  button = gtk_button_new_with_label("Zoom+");
  g_signal_connect(button, "clicked", G_CALLBACK(ZoomIn), da);
  gtk_grid_attach(GTK_GRID(inGrid), button, 2, 4, 1, 1);
  
  button = gtk_button_new_with_label("TurnL");
  g_signal_connect(button, "clicked", G_CALLBACK(turnLeft), da);
  gtk_grid_attach(GTK_GRID(inGrid), button, 0, 5, 1, 1);
  
  button = gtk_button_new_with_label("TurnR");
  g_signal_connect(button, "clicked", G_CALLBACK(turnRight), da);
  gtk_grid_attach(GTK_GRID(inGrid), button, 2, 5, 1, 1);

  button = gtk_button_new_with_label("RoL");
  g_signal_connect(button, "clicked", G_CALLBACK(rotateLeft), da);
  gtk_grid_attach(GTK_GRID(inGrid), button, 0, 6, 1, 1);
  
  button = gtk_button_new_with_label("TurnD");
  g_signal_connect(button, "clicked", G_CALLBACK(turnDown), da);
  gtk_grid_attach(GTK_GRID(inGrid), button, 1, 6, 1, 1);

  button = gtk_button_new_with_label("RoR");
  g_signal_connect(button, "clicked", G_CALLBACK(rotateRight), da);
  gtk_grid_attach(GTK_GRID(inGrid), button, 2, 6, 1, 1);

  frame = gtk_frame_new("File");
  gtk_grid_attach(GTK_GRID(grid), frame, 0,4,2,1);

  GtkWidget * fileGrid = gtk_grid_new();
  gtk_container_set_border_width(GTK_CONTAINER(fileGrid), 5);
  gtk_container_add(GTK_CONTAINER(frame), fileGrid);

  button = gtk_button_new_with_label("Save");
  g_signal_connect(button, "clicked", G_CALLBACK(saveFile), da);
  gtk_grid_attach(GTK_GRID(fileGrid), button, 0, 0, 2, 1);

  button = gtk_button_new_with_label("Load");
  g_signal_connect(button, "clicked", G_CALLBACK(loadFile), da);
  gtk_grid_attach(GTK_GRID(fileGrid), button, 2, 0, 2, 1);



  gtk_widget_show_all(window);

}

// Edit objects ----------------------------------------------------------------
void GUI::editWindow(GtkWidget *widget, gpointer data) {
  GtkWidget * auxWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(auxWindow), 150, 100);
  gtk_window_set_title(GTK_WINDOW(auxWindow), "Editar");
  g_signal_connect(auxWindow, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);
  gtk_container_set_border_width(GTK_CONTAINER(auxWindow), 10);

  GtkWidget* auxGrid = gtk_grid_new();
  gtk_container_set_border_width(GTK_CONTAINER(auxGrid), 5);
  gtk_container_add(GTK_CONTAINER(auxWindow), auxGrid);

  GtkWidget* button;
  button = gtk_button_new_with_label("Deletar");
  g_signal_connect(button, "clicked", G_CALLBACK(deleteObject), NULL);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), auxWindow);
  gtk_grid_attach(GTK_GRID(auxGrid), button, 0, 1, 1, 1);

  button = gtk_button_new_with_label("Transladar");
  g_signal_connect(button, "clicked", G_CALLBACK(transObjectWindow), NULL);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), auxWindow);
  gtk_grid_attach(GTK_GRID(auxGrid), button, 0, 2, 1, 1);

  button = gtk_button_new_with_label("Escalonar");
  g_signal_connect(button, "clicked", G_CALLBACK(escObjectWindow), NULL);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), auxWindow);
  gtk_grid_attach(GTK_GRID(auxGrid), button, 0, 3, 1, 1);

  button = gtk_button_new_with_label("Rotacionar");
  g_signal_connect(button, "clicked", G_CALLBACK(rotObjectWindow), NULL);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), auxWindow);
  gtk_grid_attach(GTK_GRID(auxGrid), button, 0, 4, 1, 1);

  gtk_widget_show_all(auxWindow);
}

void GUI::deleteObject(GtkWidget *widget, gpointer data) {
  GtkListBoxRow * obj;
  obj = gtk_list_box_get_selected_row ((GtkListBox *)oList);
  if (obj == NULL) {
    return;
  }
  GtkWidget* test = gtk_bin_get_child(GTK_BIN(obj));

  std::string *name = new std::string(gtk_label_get_text ((GtkLabel*)test));
  GUI::getDisplayFile()->deleteObj(name);
  delete name;

  gtk_widget_queue_draw(GTK_WIDGET(GUI::getDA()));

  gtk_container_remove((GtkContainer*)oList, (GtkWidget*) obj);
}

void GUI::transObjectWindow(GtkWidget *widget, gpointer data) {
  ParamsPonto * paramsP = new ParamsPonto();

  GtkWidget * auxWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(auxWindow), 150, 100);
  gtk_window_set_title(GTK_WINDOW(auxWindow), "Transladar");
  g_signal_connect(auxWindow, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);
  gtk_container_set_border_width(GTK_CONTAINER(auxWindow), 10);

  GtkWidget* auxGrid = gtk_grid_new();
  gtk_container_set_border_width(GTK_CONTAINER(auxGrid), 5);
  gtk_container_add(GTK_CONTAINER(auxWindow), auxGrid);

  GtkWidget* label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), "x: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 0, 1, 1);

  paramsP->x = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsP->x, 1, 0, 1, 1);

  label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), " y: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 1, 1, 1);

  paramsP->y = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsP->y, 1, 1, 1, 1);
  
  label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), " z: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 2, 1, 1);

  paramsP->z = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsP->z, 1, 2, 1, 1);

  GtkWidget* button = gtk_button_new_with_label("Transladar");
  g_signal_connect(button, "clicked", G_CALLBACK(transObject), (gpointer) paramsP);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), auxWindow);

  gtk_grid_attach(GTK_GRID(auxGrid), button, 0, 2, 2, 2);

  gtk_widget_show_all(auxWindow);
}

void GUI::transObject(GtkWidget *widget, gpointer data) {
  ParamsPonto * paramsP = (ParamsPonto*) data;
  float x = atof(gtk_entry_get_text((GtkEntry*)paramsP->x));
  float y = atof(gtk_entry_get_text((GtkEntry*)paramsP->y));
  float z = atof(gtk_entry_get_text((GtkEntry*)paramsP->z));

  GtkListBoxRow * obj;
  obj = gtk_list_box_get_selected_row ((GtkListBox *)oList);
  if (obj == NULL) {
    return;
  }
  GtkWidget* test = gtk_bin_get_child(GTK_BIN(obj));

  std::string *name = new std::string(gtk_label_get_text ((GtkLabel*)test));
  GUI::getDisplayFile()->translateObj(name, x, y, z);
  delete name;

  gtk_widget_queue_draw(GTK_WIDGET(GUI::getDA()));
}

void GUI::escObjectWindow(GtkWidget *widget, gpointer data) {

  GtkWidget * auxWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(auxWindow), 150, 100);
  gtk_window_set_title(GTK_WINDOW(auxWindow), "Escalonar");
  g_signal_connect(auxWindow, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);
  gtk_container_set_border_width(GTK_CONTAINER(auxWindow), 10);

  GtkWidget* auxGrid = gtk_grid_new();
  gtk_container_set_border_width(GTK_CONTAINER(auxGrid), 5);
  gtk_container_add(GTK_CONTAINER(auxWindow), auxGrid);

  GtkWidget* label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), "Escalar: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 0, 1, 1);

  GtkWidget* escalar = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), escalar, 1, 0, 1, 1);

  GtkWidget* button = gtk_button_new_with_label("Escalonar");
  g_signal_connect(button, "clicked", G_CALLBACK(escObject), (gpointer) escalar);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), auxWindow);

  gtk_grid_attach(GTK_GRID(auxGrid), button, 0, 1, 2, 2);

  gtk_widget_show_all(auxWindow);
}

void GUI::escObject(GtkWidget *widget, gpointer data) {
  float scalar = atof(gtk_entry_get_text((GtkEntry*)data));

  GtkListBoxRow * obj;
  obj = gtk_list_box_get_selected_row ((GtkListBox *)oList);
  if (obj == NULL) {
    return;
  }
  GtkWidget* test = gtk_bin_get_child(GTK_BIN(obj));

  std::string *name = new std::string(gtk_label_get_text ((GtkLabel*)test));
  GUI::getDisplayFile()->escalonateObj(name, scalar);
  delete name;

  gtk_widget_queue_draw(GTK_WIDGET(GUI::getDA()));
}

void GUI::rotObjectWindow(GtkWidget *widget, gpointer data) {
  GtkWidget * auxWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(auxWindow), 150, 100);
  gtk_window_set_title(GTK_WINDOW(auxWindow), "Rotacionar");
  g_signal_connect(auxWindow, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);
  gtk_container_set_border_width(GTK_CONTAINER(auxWindow), 10);

  GtkWidget* auxGrid = gtk_grid_new();
  gtk_container_set_border_width(GTK_CONTAINER(auxGrid), 5);
  gtk_container_add(GTK_CONTAINER(auxWindow), auxGrid);

  GtkWidget* label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), "Angulo: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 0, 1, 1);

  GtkWidget* angulo = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), angulo, 1, 0, 1, 1);

  GtkWidget* button = gtk_button_new_with_label("Rotacionar(Centro Objeto)");
  g_signal_connect(button, "clicked", G_CALLBACK(rotObjectCenter), (gpointer) angulo);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), auxWindow);
  gtk_grid_attach(GTK_GRID(auxGrid), button, 0, 1, 2, 1);

  button = gtk_button_new_with_label("Rotacionar(Origem)");
  g_signal_connect(button, "clicked", G_CALLBACK(rotObjectOrigin), (gpointer) angulo);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), auxWindow);
  gtk_grid_attach(GTK_GRID(auxGrid), button, 0, 2, 2, 1);

  button = gtk_button_new_with_label("Rotacionar(Ponto)");
  g_signal_connect(button, "clicked", G_CALLBACK(rotObjectPointWindow), (gpointer) angulo);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), auxWindow);
  gtk_grid_attach(GTK_GRID(auxGrid), button, 0, 3, 2, 1);

  gtk_widget_show_all(auxWindow);
}

void GUI::rotObjectCenter(GtkWidget *widget, gpointer data) {
  float angle = atof(gtk_entry_get_text((GtkEntry*)data));

  GtkListBoxRow * obj;
  obj = gtk_list_box_get_selected_row ((GtkListBox *)oList);
  if (obj == NULL) {
    return;
  }
  GtkWidget* test = gtk_bin_get_child(GTK_BIN(obj));

  std::string *name = new std::string(gtk_label_get_text ((GtkLabel*)test));
  GUI::getDisplayFile()->rotateObjCenter(name, angle);
  delete name;

  gtk_widget_queue_draw(GTK_WIDGET(GUI::getDA()));

}

void GUI::rotObjectOrigin(GtkWidget *widget, gpointer data) {
  //TODO juntar com o de cima
  float angle = atof(gtk_entry_get_text((GtkEntry*)data));

  GtkListBoxRow * obj;
  obj = gtk_list_box_get_selected_row ((GtkListBox *)oList);
  if (obj == NULL) {
    return;
  }
  GtkWidget* test = gtk_bin_get_child(GTK_BIN(obj));

  std::string *name = new std::string(gtk_label_get_text ((GtkLabel*)test));
  GUI::getDisplayFile()->rotateObjOrigin(name, angle);
  delete name;

  gtk_widget_queue_draw(GTK_WIDGET(GUI::getDA()));

}

void GUI::rotObjectPointWindow(GtkWidget *widget, gpointer data) {
  //juntar com janela de transladar
  ParamsRotation * paramsR = new ParamsRotation();
  paramsR->angulo = atof(gtk_entry_get_text((GtkEntry*)data));

  GtkWidget * auxWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(auxWindow), 150, 100);
  gtk_window_set_title(GTK_WINDOW(auxWindow), "Rotacionar : Ponto");
  g_signal_connect(auxWindow, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);
  gtk_container_set_border_width(GTK_CONTAINER(auxWindow), 10);

  GtkWidget* auxGrid = gtk_grid_new();
  gtk_container_set_border_width(GTK_CONTAINER(auxGrid), 5);
  gtk_container_add(GTK_CONTAINER(auxWindow), auxGrid);

  GtkWidget* label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), "x: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 0, 1, 1);

  paramsR->x = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsR->x, 1, 0, 1, 1);

  label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), " y: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 1, 1, 1);

  paramsR->y = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsR->y, 1, 1, 1, 1);

  GtkWidget* button = gtk_button_new_with_label("Rotacionar");
  g_signal_connect(button, "clicked", G_CALLBACK(rotObjectPoint), (gpointer) paramsR);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), auxWindow);

  gtk_grid_attach(GTK_GRID(auxGrid), button, 0, 2, 2, 2);

  gtk_widget_show_all(auxWindow);
}

void GUI::rotObjectPoint(GtkWidget *widget, gpointer data) {
  ParamsRotation * paramsR = (ParamsRotation*) data;

  float x = atof(gtk_entry_get_text((GtkEntry*)paramsR->x));
  float y = atof(gtk_entry_get_text((GtkEntry*)paramsR->y));

  GtkListBoxRow * obj;
  obj = gtk_list_box_get_selected_row ((GtkListBox *)oList);
  if (obj == NULL) {
    return;
  }
  GtkWidget* test = gtk_bin_get_child(GTK_BIN(obj));

  std::string *name = new std::string(gtk_label_get_text ((GtkLabel*)test));
  Point *p = new Point((std::string *)NULL, x, y);
  GUI::getDisplayFile()->rotateObjPoint(name, paramsR->angulo, p);
  delete p;
  delete name;

  gtk_widget_queue_draw(GTK_WIDGET(GUI::getDA()));
}

void GUI::saveFile(GtkWidget *widget, gpointer data) {
  DescriptorOBJ::save(GUI::getDisplayFile());
}

void GUI::loadFile(GtkWidget *widget, gpointer data) {
  GList *children, *iter;

  children = gtk_container_get_children(GTK_CONTAINER(oList));
  for(iter = children; iter != NULL; iter = g_list_next(iter)){
    gtk_widget_destroy(GTK_WIDGET(iter->data));
  }
  g_list_free(children);

  DisplayFile * auxDisplay = DescriptorOBJ::load();

  if (auxDisplay) {
    GUI::displayFile = auxDisplay;
    gtk_widget_queue_draw(GTK_WIDGET(GUI::getDA()));
  }

  gtk_widget_show(oList);
}

void GUI::addToListBox(std::string name) {
  GtkWidget * label = gtk_label_new(name.c_str());
  gtk_list_box_prepend((GtkListBox*)oList, label);
  gtk_widget_show(label);
}


// Add Curves -------------------------------------------------
void GUI::addCurveWindow(GtkWidget *widget, gpointer data) {
  ParamsCurveB * paramsC;
  paramsC = new ParamsCurveB();
  paramsC->curveName = NULL;
  paramsC->pointsList = new std::list<Point*>();

  GtkWidget * auxWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(auxWindow), 300, 100);
  gtk_window_set_title(GTK_WINDOW(auxWindow), "Incluir Curva");
  g_signal_connect(auxWindow, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);
  gtk_container_set_border_width(GTK_CONTAINER(auxWindow), 10);


  GtkWidget* auxGrid = gtk_grid_new();
  gtk_container_set_border_width(GTK_CONTAINER(auxGrid), 5);
  gtk_container_add(GTK_CONTAINER(auxWindow), auxGrid);

  GtkWidget* label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), "Nome: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 0, 1, 1);
  
  paramsC->nome = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsC->nome, 1, 0, 5, 1);

  label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), "x1: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 1, 1, 1);

  paramsC->x1 = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsC->x1, 1, 1, 1, 1);

  label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), " y1: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 2, 1, 1, 1);

  paramsC->y1 = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsC->y1, 3, 1, 1, 1);

  label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), " z1: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 4, 1, 1, 1);

  paramsC->z1 = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsC->z1, 5, 1, 1, 1);

  label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), " x2: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 2, 1, 1);

  paramsC->x2 = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsC->x2, 1, 2, 1, 1);

  label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), " y2: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 2, 2, 1, 1);

  paramsC->y2 = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsC->y2, 3, 2, 1, 1);

  label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), " z2: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 4, 2, 1, 1);

  paramsC->z2 = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsC->z2, 5, 2, 1, 1);

  label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), " x3: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 3, 1, 1);

  paramsC->x3 = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsC->x3, 1, 3, 1, 1);

  label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), " y3: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 2, 3, 1, 1);

  paramsC->y3 = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsC->y3, 3, 3, 1, 1);

  label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), " z3: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 4, 3, 1, 1);

  paramsC->z3 = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsC->z3, 5, 3, 1, 1);

  label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), " x4: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 4, 1, 1);

  paramsC->x4 = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsC->x4, 1, 4, 1, 1);

  label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), " y4: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 2, 4, 1, 1);

  paramsC->y4 = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsC->y4, 3, 4, 1, 1);

  label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), " z4: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 4, 4, 1, 1);

  paramsC->z4 = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsC->z4, 5, 4, 1, 1);

  GtkWidget* button = gtk_button_new_with_label("Add more");
  g_signal_connect(button, "clicked", G_CALLBACK(addCurveMore), (gpointer) paramsC);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), auxWindow);
  gtk_grid_attach(GTK_GRID(auxGrid), button, 1, 5, 2, 2);
  
  button = gtk_button_new_with_label("Finish");
  g_signal_connect(button, "clicked", G_CALLBACK(addCurveFinish), (gpointer) paramsC);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), auxWindow);
  gtk_grid_attach(GTK_GRID(auxGrid), button, 3, 5, 2, 2);

  gtk_widget_show_all(auxWindow);
}

void GUI::addCurveMore(GtkWidget* widget, gpointer data) {
  ParamsCurveB * paramsC = (ParamsCurveB*)data;
  GUI::addCurve(widget, data);
  
  
  GtkWidget * auxWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(auxWindow), 300, 100);
  gtk_window_set_title(GTK_WINDOW(auxWindow), "Incluir Curva");
  g_signal_connect(auxWindow, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);
  gtk_container_set_border_width(GTK_CONTAINER(auxWindow), 10);

  GtkWidget* auxGrid = gtk_grid_new();
  gtk_container_set_border_width(GTK_CONTAINER(auxGrid), 5);
  gtk_container_add(GTK_CONTAINER(auxWindow), auxGrid);

  GtkWidget* label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), "x: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 0, 1, 1);

  paramsC->x1 = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsC->x1, 1, 0, 1, 1);

  label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), " y: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 1, 1, 1);

  paramsC->y1 = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsC->y1, 1, 1, 1, 1);

  label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), " z: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 2, 1, 1);

  paramsC->z1 = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsC->z1, 1, 2, 1, 1);


  GtkWidget* button = gtk_button_new_with_label("Add More");
  g_signal_connect(button, "clicked", G_CALLBACK(addCurveMore), (gpointer) paramsC);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), auxWindow);
  gtk_grid_attach(GTK_GRID(auxGrid), button, 0, 3, 1, 2);

  button = gtk_button_new_with_label("Finish");
  g_signal_connect(button, "clicked", G_CALLBACK(addCurveFinish), (gpointer) paramsC);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), auxWindow);
  gtk_grid_attach(GTK_GRID(auxGrid), button, 1, 3, 1, 2);

  gtk_widget_show_all(auxWindow);
}

void GUI::addCurveFinish(GtkWidget* widget, gpointer data) {
  ParamsCurveB * paramsC = (ParamsCurveB*)data;
  GUI::addCurve(widget, data);
  
  GUI::addToListBox(paramsC->curveName->c_str());
  
  Curve *newCurve = new Curve(paramsC->curveName, paramsC->pointsList);
  GUI::getDisplayFile()->addObject(newCurve);

  gtk_widget_queue_draw(GTK_WIDGET(GUI::getDA()));
}

void GUI::addCurve(GtkWidget* widget, gpointer data) {
  ParamsCurveB *paramsC = (ParamsCurveB*) data;
  
  const char *x1 = gtk_entry_get_text((GtkEntry*)paramsC->x1);
  const char *y1 = gtk_entry_get_text((GtkEntry*)paramsC->y1);
  const char *z1 = gtk_entry_get_text((GtkEntry*)paramsC->z1);
  paramsC->pointsList->push_back(new Point((const char*)NULL, atof(x1), atof(y1), atof(z1)));
  
  if (paramsC->curveName == NULL) {
    paramsC->curveName = new std::string(gtk_entry_get_text((GtkEntry*)paramsC->nome));
    
    const char *x2 = gtk_entry_get_text((GtkEntry*)paramsC->x2);
    const char *y2 = gtk_entry_get_text((GtkEntry*)paramsC->y2);
    const char *z2 = gtk_entry_get_text((GtkEntry*)paramsC->z2);
    const char *x3 = gtk_entry_get_text((GtkEntry*)paramsC->x3);
    const char *y3 = gtk_entry_get_text((GtkEntry*)paramsC->y3);
    const char *z3 = gtk_entry_get_text((GtkEntry*)paramsC->z3);
    const char *x4 = gtk_entry_get_text((GtkEntry*)paramsC->x4);
    const char *y4 = gtk_entry_get_text((GtkEntry*)paramsC->y4);
    const char *z4 = gtk_entry_get_text((GtkEntry*)paramsC->z4);
    
    paramsC->pointsList->push_back(new Point((const char*)NULL, atof(x2), atof(y2), atof(z2)));
    paramsC->pointsList->push_back(new Point((const char*)NULL, atof(x3), atof(y3), atof(z3)));
    paramsC->pointsList->push_back(new Point((const char*)NULL, atof(x4), atof(y4), atof(z4)));
  }
}
