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
			// About Window
			void initAboutWindow();
			void showAboutWindow();
			// Insert Data Window
			void initInsertDataWindow();
			void showInsertDataWindow();
			void insertDataWindow_showEntryPointPickerDialogue();
		private:
			Glib::RefPtr<Gtk::Application> application;

			// For the moment the Main Window, in the future
			// the main Window will be a greeter/collection display
			// NOTE: I'm making one builder per component, since in the
			// future those component will each have it's own UI file.
			// For the moment those are useless/wasteful.
			Glib::RefPtr<Gtk::Builder> insertData_Builder;
			Gtk::Window* insertData_Window;
			Gtk::HeaderBar* insertData_HeaderBar;
			Gtk::Button* insertData_Button_ShowAboutWindow;
			Gtk::Button* insertData_Button_OpenEntryPointPickerDialogue;
			std::string collectionEntryPointPath = "../resources";

			Glib::RefPtr<Gtk::Builder> about_Builder;
			Gtk::Window* about_Window;

		};
	}
}