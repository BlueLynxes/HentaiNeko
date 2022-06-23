#pragma once
#include <gtkmm.h>

namespace hn
{
	namespace gui
	{
		class Application
		{
		public:
			Application();
			void run();
			// Insert Data Window
			void initInsertDataWindow();
			void showInsertDataWindow();
		private:
			Glib::RefPtr<Gtk::Application> application;

			// For the moment the Main Window, in the future
			// the main Window will be a greeter/collection display
			Glib::RefPtr<Gtk::Builder> insertData_Builder;
			Gtk::Window* insertData_Window;
			Gtk::HeaderBar* insertData_HeaderBar;
		};
	}
}