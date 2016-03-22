
#include <iostream>
#include "Window.hpp"

std::list<Object*> *Window::objects;
GtkWidget* Window::da;


Window::Window() {

}

void Window::clear_surface (void)
{
  cairo_t *cr;

  cr = cairo_create (surface);

  cairo_set_source_rgb (cr, 0, 0, 0);
  cairo_paint (cr);

  cairo_destroy (cr);
}

gboolean Window::configure_event_cb (GtkWidget         *widget,
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

gboolean Window::draw_cb (GtkWidget *widget,
 cairo_t   *cr,
 gpointer   data)
{
  GdkRGBA color;
  cairo_set_source_rgb (cr, 0, 0, 0);
  cairo_paint (cr);
//   cairo_set_source_surface (cr, surface, 0, 0);
  cairo_set_source_rgb (cr, 1, 1, 1);
  cairo_set_line_width(cr, 0.5);

  std::list<Object*>::iterator it=Window::getObjects()->begin();
  for (; it != Window::getObjects()->end(); ++it) {
    (*it)->draw(cr);
  }
  cairo_stroke(cr);

  return FALSE;
}

std::list<Object*> *Window::getObjects() {
  if (Window::objects == NULL) {
    Window::objects = new std::list<Object*>();
  }
  return Window::objects;
}

GtkWidget* Window::getDA() {
  return da;
}

void Window::moveDown(GtkWidget *widget, gpointer data) {
  Viewport::moveVertical(-0.1);
  gtk_widget_queue_draw(GTK_WIDGET(Window::getDA()));
}

void Window::moveRight(GtkWidget *widget, gpointer data) {
  Viewport::moveHorizontal(0.1);
  gtk_widget_queue_draw(GTK_WIDGET(Window::getDA()));
}

void Window::moveLeft(GtkWidget *widget, gpointer data) {
  Viewport::moveHorizontal(-0.1);
  gtk_widget_queue_draw(GTK_WIDGET(Window::getDA()));
}

void Window::moveUp(GtkWidget *widget, gpointer data) {
  Viewport::moveVertical(0.1);
  gtk_widget_queue_draw(GTK_WIDGET(Window::getDA()));
}

void Window::ZoomOut(GtkWidget *widget, gpointer data) {
  Viewport::zoom(0.8);
  gtk_widget_queue_draw(GTK_WIDGET(Window::getDA()));
}

void Window::ZoomIn(GtkWidget *widget, gpointer data) {
  Viewport::zoom(1.25);
  gtk_widget_queue_draw(GTK_WIDGET(Window::getDA()));
}

void Window::Center(GtkWidget *widget, gpointer data) {
  Viewport::defaultSize();
  gtk_widget_queue_draw(GTK_WIDGET(Window::getDA()));
}

void Window::addPoint(GtkWidget* widget, gpointer data){
	ParamsPonto * paramsP = (ParamsPonto*) data;
	const char* name = gtk_entry_get_text((GtkEntry*)paramsP->nome);
	const char* x = gtk_entry_get_text((GtkEntry*)paramsP->x);
	const char* y = gtk_entry_get_text((GtkEntry*)paramsP->y);
  Window::getObjects()->push_back(new Point(name, atoi(x), atoi(y)));
  gtk_widget_queue_draw(GTK_WIDGET(Window::getDA()));
}

void Window::addLine(GtkWidget* widget, gpointer data){
	ParamsLinha * paramsL = (ParamsLinha*) data;
	const char* name = gtk_entry_get_text((GtkEntry*)paramsL->nome);
	const char* xi = gtk_entry_get_text((GtkEntry*)paramsL->xi);
	const char* yi = gtk_entry_get_text((GtkEntry*)paramsL->yi);
	const char* xf = gtk_entry_get_text((GtkEntry*)paramsL->xf);
	const char* yf = gtk_entry_get_text((GtkEntry*)paramsL->yf);

  Window::getObjects()->push_back(new Line(name, atoi(xi), atoi(yi), atoi(yf), atoi(yf)));
  gtk_widget_queue_draw(GTK_WIDGET(Window::getDA()));
}


void Window::addPointWindow(GtkWidget *widget, gpointer data) {
	
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

void Window::addLineWindow(GtkWidget *widget, gpointer   data) {

	ParamsLinha * paramsL = new ParamsLinha();

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
void Window::addPoligonWindowName(GtkWidget *widget, gpointer   data) {
gtk_widget_queue_draw(GTK_WIDGET(Window::getDA()));
	/*GtkWidget * auxWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
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

	paramsPol.nome = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(auxGrid), paramsPol.nome, 1, 0, 1, 1);

	GtkWidget* button = gtk_button_new_with_label("Next");
	//TODO connect
	g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), auxWindow);
	gtk_grid_attach(GTK_GRID(auxGrid), button, 1, 1, 2, 2);

	gtk_widget_show_all(auxWindow);*/
        
        
        
// Instancia quando tiver o nome        // tambem pode ser para o primeiro ponto
Polygon *poly = new Polygon(name);      Polygon *poly = new Polygon(name, atoi(x), atoi(y));
// adiciona no displayFile
Window::getObjects()->push_back(poly);
// Adiciona os pontos no poligono
poly->add(atoi(x), atoi(y));
// atualiza a tela




}

void Window::init(){
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

	frame = gtk_frame_new("Objects");
	gtk_grid_attach(GTK_GRID(grid), frame, 0, 0, 2, 1);
	oList = gtk_list_box_new();
	gtk_container_add(GTK_CONTAINER(frame), oList);
	GtkAllocation alloc;
	gtk_widget_get_allocation(oList, &alloc);
	gtk_widget_set_size_request(oList, alloc.width, 200);
	//TODO connect

	frame = gtk_frame_new("Add");
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

	button = gtk_button_new_with_label("Poligon");
	gtk_grid_attach(GTK_GRID(inGrid), button, 0, 3, 1, 1);
	g_signal_connect(button, "clicked", G_CALLBACK(addPoligonWindowName), NULL);

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

	//TODO connect


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

  button = gtk_button_new_with_label("Center");
	g_signal_connect(button, "clicked", G_CALLBACK(Center), da);
	gtk_grid_attach(GTK_GRID(inGrid), button, 1, 2, 1, 1);


	gtk_widget_show_all(window);
}
