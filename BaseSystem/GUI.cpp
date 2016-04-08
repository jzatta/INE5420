
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
  cairo_set_source_rgb (cr, 1, 1, 1);
  cairo_set_line_width(cr, 0.5);
  
  GUI::getDisplayFile()->draw(cr);
  
  cairo_stroke(cr);
  
  return FALSE;
}

// GUI getters -----------------------------------------------------------------
DisplayFile *GUI::getDisplayFile() {
  if (GUI::displayFile == NULL) {
    GUI::displayFile = DescriptorOBJ::load();
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

void GUI::rotateLeft(GtkWidget *widget, gpointer data) {
  Window::rotate(-15);
  gtk_widget_queue_draw(GTK_WIDGET(GUI::getDA()));
}

void GUI::rotateRight(GtkWidget *widget, gpointer data) {
  Window::rotate(15);
  gtk_widget_queue_draw(GTK_WIDGET(GUI::getDA()));
}

void GUI::Reset(GtkWidget *widget, gpointer data) {
  Window::reset();
  DescriptorOBJ::save(GUI::getDisplayFile());
  gtk_widget_queue_draw(GTK_WIDGET(GUI::getDA()));
}

// Add point routines ----------------------------------------------------------
void GUI::addPoint(GtkWidget* widget, gpointer data) {
  ParamsPonto * paramsP = (ParamsPonto*) data;
  std::string* name =  new std::string(gtk_entry_get_text((GtkEntry*)paramsP->nome));
  const char* x = gtk_entry_get_text((GtkEntry*)paramsP->x);
  const char* y = gtk_entry_get_text((GtkEntry*)paramsP->y);
  
  GtkWidget* label = gtk_label_new(name->c_str());
  gtk_list_box_prepend((GtkListBox*)oList, label);
  gtk_widget_show(label);
  
  GUI::getDisplayFile()->addObject(new Point(name, atof(x), atof(y)));
  
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
  
  GtkWidget* button = gtk_button_new_with_label("Add");
  g_signal_connect(button, "clicked", G_CALLBACK(addPoint), (gpointer) paramsP);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), auxWindow);
  
  gtk_grid_attach(GTK_GRID(auxGrid), button, 1, 3, 2, 2);
  
  gtk_widget_show_all(auxWindow);
}

// Add line routines -----------------------------------------------------------
void GUI::addLine(GtkWidget* widget, gpointer data) {
  ParamsLinha * paramsL = (ParamsLinha*) data;
  std::string* name =  new std::string(gtk_entry_get_text((GtkEntry*)paramsL->nome));
  const char* xi = gtk_entry_get_text((GtkEntry*)paramsL->xi);
  const char* yi = gtk_entry_get_text((GtkEntry*)paramsL->yi);
  const char* xf = gtk_entry_get_text((GtkEntry*)paramsL->xf);
  const char* yf = gtk_entry_get_text((GtkEntry*)paramsL->yf);
  
  GtkWidget* label = gtk_label_new(name->c_str());
  gtk_list_box_prepend((GtkListBox*)oList, label);
  gtk_widget_show(label);
  
  GUI::getDisplayFile()->addObject(new Line(name, atof(xi), atof(yi), atof(xf), atof(yf)));
  
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
  gtk_label_set_text(GTK_LABEL(label), " x2: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 3, 1, 1);
  
  paramsL->xf = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsL->xf, 1, 3, 1, 1);
  
  label = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label), " y2: ");
  gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 4, 1, 1);
  
  paramsL->yf = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(auxGrid), paramsL->yf, 1, 4, 1, 1);
  
  GtkWidget* button = gtk_button_new_with_label("Add");
  g_signal_connect(button, "clicked", G_CALLBACK(addLine), (gpointer) paramsL);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), auxWindow);
  gtk_grid_attach(GTK_GRID(auxGrid), button, 1, 5, 2, 2);
  
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
  
  
  GtkWidget* button = gtk_button_new_with_label("Add More");
  g_signal_connect(button, "clicked", G_CALLBACK(buildPolygon), (gpointer) params);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), auxWindow);
  gtk_grid_attach(GTK_GRID(auxGrid), button, 0, 2, 1, 2);
  
  button = gtk_button_new_with_label("Finish");
  g_signal_connect(button, "clicked", G_CALLBACK(addPolygonWindowName), (gpointer) params);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), auxWindow);
  gtk_grid_attach(GTK_GRID(auxGrid), button, 1, 2, 1, 2);
  
  gtk_widget_show_all(auxWindow);
}

void GUI::buildPolygon(GtkWidget *widget, gpointer data) {
  ParamsPolygon *params = (ParamsPolygon*) data;
  const char *x = gtk_entry_get_text((GtkEntry*)params->x);
  float xi = atof(x);
  const char *y = gtk_entry_get_text((GtkEntry*)params->y);
  float yi = atof(y);
  
  Point *p = new Point("polygonPoint",xi, yi);
  params->pointsList->push_back(p);
  
  addPolygonWindow(widget, (gpointer)params);
}

void GUI::addPolygonWindowName(GtkWidget *widget, gpointer data) {
  ParamsPolygon * params = (ParamsPolygon*) data;
  const char* x = gtk_entry_get_text((GtkEntry*)params->x);
  float xi = atof(x);
  const char* y = gtk_entry_get_text((GtkEntry*)params->y);
  float yi = atof(y);
  
  Point *p = new Point("polygonPoint",xi, yi);
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
  
  GtkWidget* label = gtk_label_new(name->c_str());
  gtk_list_box_prepend((GtkListBox*)oList, label);
  gtk_widget_show(label);
  
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
  
  button = gtk_button_new_with_label("Poligono");
  gtk_grid_attach(GTK_GRID(inGrid), button, 0, 3, 1, 1);
  g_signal_connect(button, "clicked", G_CALLBACK(addPolygonWindow), NULL);
  
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
  
  button = gtk_button_new_with_label("Up");
  g_signal_connect(button, "clicked", G_CALLBACK(moveUp), da);
  gtk_grid_attach(GTK_GRID(inGrid), button, 1, 1, 1, 1);
  
  button = gtk_button_new_with_label("Left");
  g_signal_connect(button, "clicked", G_CALLBACK(moveLeft), da);
  gtk_grid_attach(GTK_GRID(inGrid), button, 0, 2, 1, 1);
  
  button = gtk_button_new_with_label("Right");
  g_signal_connect(button, "clicked", G_CALLBACK(moveRight), da);
  gtk_grid_attach(GTK_GRID(inGrid), button, 2, 2, 1, 1);
  
  button = gtk_button_new_with_label("Down");
  g_signal_connect(button, "clicked", G_CALLBACK(moveDown), da);
  gtk_grid_attach(GTK_GRID(inGrid), button, 1, 3, 1, 1);
  
  button = gtk_button_new_with_label("Zoom-");
  g_signal_connect(button, "clicked", G_CALLBACK(ZoomOut), da);
  gtk_grid_attach(GTK_GRID(inGrid), button, 0, 4, 1, 1);
  
  button = gtk_button_new_with_label("Zoom+");
  g_signal_connect(button, "clicked", G_CALLBACK(ZoomIn), da);
  gtk_grid_attach(GTK_GRID(inGrid), button, 2, 4, 1, 1);
  
  button = gtk_button_new_with_label("RoL");
  g_signal_connect(button, "clicked", G_CALLBACK(rotateLeft), da);
  gtk_grid_attach(GTK_GRID(inGrid), button, 0, 5, 1, 1);
  
  button = gtk_button_new_with_label("RoR");
  g_signal_connect(button, "clicked", G_CALLBACK(rotateRight), da);
  gtk_grid_attach(GTK_GRID(inGrid), button, 2, 5, 1, 1);
  
  button = gtk_button_new_with_label("Center");
  g_signal_connect(button, "clicked", G_CALLBACK(Center), da);
  gtk_grid_attach(GTK_GRID(inGrid), button, 1, 2, 1, 1);
  
  button = gtk_button_new_with_label("RESET");
  g_signal_connect(button, "clicked", G_CALLBACK(Reset), da);
  gtk_grid_attach(GTK_GRID(inGrid), button, 1, 6, 1, 1);
  
  
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
  
  GtkListBoxRow * obj;
  obj = gtk_list_box_get_selected_row ((GtkListBox *)oList);
  GtkWidget* test = gtk_bin_get_child(GTK_BIN(obj));
  
  std::string *name = new std::string(gtk_label_get_text ((GtkLabel*)test));
  GUI::getDisplayFile()->translateObj(name, x, y);
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
  GtkWidget* test = gtk_bin_get_child(GTK_BIN(obj));
  
  std::string *name = new std::string(gtk_label_get_text ((GtkLabel*)test));
  Point *p = new Point((std::string *)NULL, x, y);
  GUI::getDisplayFile()->rotateObjPoint(name, paramsR->angulo, p);
  delete p;
  delete name;
  
  gtk_widget_queue_draw(GTK_WIDGET(GUI::getDA()));
}
