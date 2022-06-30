#include <gtkmm.h>
#include "backend/image_properties.hpp"
#include "gui/application.hpp"

#include <iostream>
#include "backend/collection_scanner.hpp"

int main(int argc, char* argv[])
{
    hn::gui::Application app = hn::gui::Application();
    app.showInsertDataWindow();
    app.run();
    return 0;
}