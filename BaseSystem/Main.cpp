
#include <gtk/gtk.h>
#include "Window.hpp"
//#include "Navigation.hpp"
//#include "DisplayFile.hpp"

int main(int argc, char** argv) {
	gtk_init(&argc, &argv);
	
	Window interface;
	interface.init();

	gtk_main();
}