#include <gtkmm.h>
#include <iostream>

int main (int argc, char **argv)
{
    Gtk::Main kit(argc, argv);
    std::string file_path("c:\\tests\\mingw_glade\\data\\toto_2_24.glade");
    Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
    try {
        refBuilder->add_from_file(file_path);
    }
    catch(const Glib::FileError& ex)
    {
        std::cerr << "FileError: " << ex.what() << std::endl;
        return 1;
    }
    catch(const Gtk::BuilderError& ex)
    {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
        return 1;
    }
    //won't work (BuilderError) because win gtkmm binaries are 2.22 and glade requires 2.24
    return 0;
}
