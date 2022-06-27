#include "application.hpp"
#include <thread>
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
			about_Window->set_keep_above(true);
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
				// There is always an imagePreviewer in the previewBox, remove it.
				Gtk::Box* previewBox;
				insertData_Builder->get_widget<Gtk::Box>("PreviewBox", previewBox);
				delete previewBox->get_children().front();
				Gtk::Spinner* spinner = new Gtk::Spinner();
				spinner->start();
				spinner->show();
				previewBox->pack_start(*spinner, true, true, 0);
				collectionScanner.changeEntryPoint(dialog.get_filename());
				std::thread scanThread(&hn::backend::CollectionScanner::threadedScan, &collectionScanner, std::ref(initData_scanCompletedDispatcher));
				scanThread.detach();
			}
		}

		void Application::insertDataWindow_onScanCompleted()
		{
			// Delete the spinner
			Gtk::Box* previewBox;
			insertData_Builder->get_widget<Gtk::Box>("PreviewBox", previewBox);
			delete previewBox->get_children().front();
			std::cout << "VECTOR SIZE: " << collectionScanner.imagesPaths.size() << std::endl;
			insertData_imagePreviewer = new hn::gui::ImagePreviewer(collectionScanner.imagesPaths.front(), Glib::RefPtr<Gtk::Window>(insertData_Window));
			insertData_imagePreviewer->show();
			previewBox->pack_start(*insertData_imagePreviewer, true, true, 0);
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

			insertData_imagePreviewer = new hn::gui::ImagePreviewer("../resources/previewFallback.png", Glib::RefPtr<Gtk::Window>(insertData_Window));
			Gtk::Box* previewBox;
			insertData_Builder->get_widget<Gtk::Box>("PreviewBox", previewBox);
			Gtk::Label* label = new Gtk::Label("test label");
			previewBox->pack_start(*insertData_imagePreviewer, true, true, 0);

			// Dispatcher callback event for the file picker spinner
			initData_scanCompletedDispatcher.connect(sigc::mem_fun(*this, &hn::gui::Application::insertDataWindow_onScanCompleted));
		}

		void Application::showInsertDataWindow()
		{
			insertData_Window->show_all();
		}
	}
}