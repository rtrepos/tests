#include <glibmm/spawn.h>
#include <glibmm/miscutils.h>
#include <gtkmm/stock.h>
#include <gtkmm/filechooserdialog.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/main.h>
#include <gtkmm/builder.h>
#include <glib/gstdio.h>
#include <iostream>

int main (int argc, char *argv[])
{

	std::cout << " main starts " << std::endl;

	try {
		Gtk::Main application(&argc, &argv);
		Glib::RefPtr< Gtk::Builder > refBuilder = Gtk::Builder::create();
		refBuilder->add_from_file("gvle.glade");
	}	catch(...) {
		std::cout << " error " << std::endl;
		return 1;
	}
    return 0;
}

