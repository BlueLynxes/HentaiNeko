#include "application.hpp"
#include <iostream>

namespace hn
{
	namespace gui
	{
		Application::Application()
		{
			this->application = Gtk::Application::create("foss.BlueLynxes.HentaiNeko");
		}

		void Application::run()
		{
			// NOTE: This is temporary, the window to run should be the main Window
			// Other Windows will be spawned via events separately when needed by the user
			this->application->run(*this->insertData_Window);
		}

		void Application::initAboutWindow()
		{
			about_Builder = Gtk::Builder::create_from_file("../ui/HentaiNeko.glade");
			about_Builder->get_widget<Gtk::Window>("about_window", about_Window);
		}

		void Application::showAboutWindow()
		{
			about_Window->show_all();
		}

		void Application::insertDataWindow_showEntryPointPickerDialogue()
		{
			Gtk::FileChooserDialog dialog = Gtk::FileChooserDialog(
				"Select Entry point",
				Gtk::FileChooserAction::FILE_CHOOSER_ACTION_SELECT_FOLDER,
				Gtk::DialogFlags::DIALOG_MODAL
				);
			dialog.add_button("Select", Gtk::ResponseType::RESPONSE_OK);
			int response = dialog.run();
			if (response == Gtk::ResponseType::RESPONSE_OK)
			{
				collectionScanner.changeEntryPoint(dialog.get_filename());
				collectionScanner.scan();
			}
		}

		void Application::initInsertDataWindow()
		{
			insertData_Builder = Gtk::Builder::create_from_file("../ui/HentaiNeko.glade");
			insertData_Builder->get_widget<Gtk::Window>("main_window", insertData_Window);
			insertData_Builder->get_widget<Gtk::HeaderBar>("header", insertData_HeaderBar);
			insertData_Window->set_titlebar(*insertData_HeaderBar);

			insertData_Builder->get_widget<Gtk::Button>("info_button", insertData_Button_ShowAboutWindow);
			insertData_Button_ShowAboutWindow->signal_clicked().connect(sigc::mem_fun(*this, &Application::showAboutWindow));

			insertData_Builder->get_widget<Gtk::Button>("select_entry_point_button", insertData_Button_OpenEntryPointPickerDialogue);
			insertData_Button_OpenEntryPointPickerDialogue->signal_clicked().connect(sigc::mem_fun(*this, &Application::insertDataWindow_showEntryPointPickerDialogue));

		}

		void Application::showInsertDataWindow()
		{
			insertData_Window->show_all();
		}
	}
}