
#include <gtk/gtk.h>
#include "GUI.hpp"

int main(int argc, char** argv) {
	gtk_init(&argc, &argv);
	
	GUI interface;
	interface.init();

	gtk_main();
}