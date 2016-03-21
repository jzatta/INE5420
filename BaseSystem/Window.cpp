#include "Window.hpp"

std::list<Object*> *Window::objects;

Window::Window() {

}

static void
clear_surface (void)
{
  cairo_t *cr;

  cr = cairo_create (surface);

  cairo_set_source_rgb (cr, 0, 0, 0);
  cairo_paint (cr);

  cairo_destroy (cr);
}

static gboolean
configure_event_cb (GtkWidget         *widget,
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

static gboolean
draw_cb (GtkWidget *widget,
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

static void addPointWindow(GtkWidget *widget, gpointer   data) {
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

	GtkWidget* input = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(auxGrid), input, 1, 0, 1, 1);

	label = gtk_label_new(NULL);
	gtk_label_set_text(GTK_LABEL(label), "x: ");
	gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 1, 1, 1);

	input = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(auxGrid), input, 1, 1, 1, 1);

	label = gtk_label_new(NULL);
	gtk_label_set_text(GTK_LABEL(label), " y: ");
	gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 2, 1, 1);

	input = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(auxGrid), input, 1, 2, 1, 1);

	GtkWidget* button = gtk_button_new_with_label("Add");
	//g_signal_connect(button, "clicked", G_CALLBACK(TODO), NULL);
	gtk_grid_attach(GTK_GRID(auxGrid), button, 1, 3, 2, 2);

	gtk_widget_show_all(auxWindow);
}

static void addLineWindow(GtkWidget *widget, gpointer   data) {
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

	GtkWidget* input = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(auxGrid), input, 1, 0, 1, 1);

	label = gtk_label_new(NULL);
	gtk_label_set_text(GTK_LABEL(label), "x1: ");
	gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 1, 1, 1);

	input = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(auxGrid), input, 1, 1, 1, 1);

	label = gtk_label_new(NULL);
	gtk_label_set_text(GTK_LABEL(label), " y1: ");
	gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 2, 1, 1);

	input = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(auxGrid), input, 1, 2, 1, 1);

	label = gtk_label_new(NULL);
	gtk_label_set_text(GTK_LABEL(label), " x2: ");
	gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 3, 1, 1);

	input = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(auxGrid), input, 1, 3, 1, 1);

	label = gtk_label_new(NULL);
	gtk_label_set_text(GTK_LABEL(label), " y2: ");
	gtk_grid_attach(GTK_GRID(auxGrid), label, 0, 4, 1, 1);

	input = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(auxGrid), input, 1, 4, 1, 1);

	GtkWidget* button = gtk_button_new_with_label("Add");
	//g_signal_connect(button, "clicked", G_CALLBACK(TODO), NULL);
	gtk_grid_attach(GTK_GRID(auxGrid), button, 1, 5, 2, 2);

	gtk_widget_show_all(auxWindow);
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
	//TODO connect

	g_signal_connect(button, "clicked", G_CALLBACK(addPointWindow), NULL);

	button = gtk_button_new_with_label("Line");
	gtk_grid_attach(GTK_GRID(inGrid), button, 0, 2, 1, 1);
	//TODO connect

	g_signal_connect(button, "clicked", G_CALLBACK(addLineWindow), NULL);

	button = gtk_button_new_with_label("Polygon");
	gtk_grid_attach(GTK_GRID(inGrid), button, 0, 3, 1, 1);
	//TODO connect

	inGrid = gtk_grid_new();
	gtk_container_set_border_width(GTK_CONTAINER(inGrid), 5);
	gtk_grid_attach(GTK_GRID(grid), inGrid, 2, 0, 1, 4);
	label = gtk_label_new("Viewport");
	gtk_grid_attach(GTK_GRID(inGrid), label, 0,0,1,1);
	da = gtk_drawing_area_new();
	gtk_widget_set_size_request(da, 600, 600);
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
	//g_signal_connect(button, "clicked", G_CALLBACK(TODO), NULL);
	gtk_grid_attach(GTK_GRID(inGrid), button, 1, 1, 1, 1);

	button = gtk_button_new_with_label("Left");
	//g_signal_connect(button, "clicked", G_CALLBACK(TODO), NULL);
	gtk_grid_attach(GTK_GRID(inGrid), button, 0, 2, 1, 1);

	button = gtk_button_new_with_label("Right");
	//g_signal_connect(button, "clicked", G_CALLBACK(TODO), NULL);
	gtk_grid_attach(GTK_GRID(inGrid), button, 2, 2, 1, 1);

	button = gtk_button_new_with_label("Down");
	//g_signal_connect(button, "clicked", G_CALLBACK(TODO), NULL);
	gtk_grid_attach(GTK_GRID(inGrid), button, 1, 3, 1, 1);

	button = gtk_button_new_with_label("Zoom-");
	//g_signal_connect(button, "clicked", G_CALLBACK(TODO), NULL);
	gtk_grid_attach(GTK_GRID(inGrid), button, 0, 4, 1, 1);

	button = gtk_button_new_with_label("Zoom+");
	//g_signal_connect(button, "clicked", G_CALLBACK(TODO), NULL);
	gtk_grid_attach(GTK_GRID(inGrid), button, 2, 4, 1, 1);


	gtk_widget_show_all(window);
}
