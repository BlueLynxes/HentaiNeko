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
			initInsertDataWindow();
			initAboutWindow();
			initPreviewJsonWindow();
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

			about_Builder->get_widget<Gtk::Label>("about_version_label", about_Label_version);
#ifdef APPLICATION_VERSION
			about_Label_version->set_text(APPLICATION_VERSION);
			
#endif
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
				insertData_Button_OpenEntryPointPickerDialogue->set_sensitive(false);
				// There is always an imagePreviewer in the previewBox, remove it.
				Gtk::Box* previewBox;
				insertData_Builder->get_widget<Gtk::Box>("PreviewBox", previewBox);
				previewBox->remove(*previewBox->get_children().front());
				Gtk::Spinner* spinner = new Gtk::Spinner();
				spinner->start();
				spinner->show();
				previewBox->pack_start(*spinner, true, true, 0);
				collectionScanner.changeEntryPoint(dialog.get_filename());
				std::thread scanThread(&hn::backend::CollectionScanner::threadedScan, &collectionScanner, std::ref(insertData_Dispatcher_scanSuccess), std::ref(insertData_Dispatcher_scanError));
				scanThread.detach();
			}
		}

		void Application::insertDataWindow_onScanCompleted()
		{
			insertData_picturesIndex = collectionScanner.imagesPaths.begin();
			// Delete the spinner
			Gtk::Box* previewBox;
			insertData_Builder->get_widget<Gtk::Box>("PreviewBox", previewBox);
			previewBox->remove(*previewBox->get_children().front());
			insertData_imagePreviewer = new hn::gui::ImagePreviewer(collectionScanner.imagesPaths.front(), Glib::RefPtr<Gtk::Window>(insertData_Window));
			insertData_imagePreviewer->show();
			previewBox->pack_start(*insertData_imagePreviewer, true, true, 0);
			insertDataWindow_updateImagePreviewerLabels();
			insertData_Button_OpenEntryPointPickerDialogue->set_sensitive(true);
		}

		void Application::insertDataWindow_onScanError()
		{
			insertData_Label_currentImagePath->set_text("Image Path");
			insertData_Label_currentImageNumber->set_text("- / -");
			insertData_imagePreviewer = new hn::gui::ImagePreviewer("../resources/previewFallback.png", Glib::RefPtr<Gtk::Window>(insertData_Window));
			Gtk::Box* previewBox;
			insertData_Builder->get_widget<Gtk::Box>("PreviewBox", previewBox);
			previewBox->pack_start(*insertData_imagePreviewer, true, true, 0);
			previewBox->show_all();
			Gtk::MessageDialog dialog = Gtk::MessageDialog(
				"An error has occurred while scanning your collection...\nMake you sure you have permission to access the files.",
				false,
				Gtk::MessageType::MESSAGE_ERROR,
				Gtk::ButtonsType::BUTTONS_OK,
				true
			);
			dialog.run();
			insertData_Button_OpenEntryPointPickerDialogue->set_sensitive(true);
		}

		// The buttons changing the image preview have to destroy the old previewer, init a new one
		// and then update the labels
		void Application::insertDataWindow_buttonPreviewNext()
		{
			if (insertData_picturesIndex + 1 < collectionScanner.imagesPaths.end())
			{
				insertData_picturesIndex++;
				insertData_Box_previewBox->remove(*insertData_Box_previewBox->get_children().front());
				//delete insertData_imagePreviewer;
				insertData_imagePreviewer = new hn::gui::ImagePreviewer(*insertData_picturesIndex, Glib::RefPtr<Gtk::Window>(insertData_Window));
				insertData_imagePreviewer->show();
				insertData_Box_previewBox->pack_start(*insertData_imagePreviewer, true, true, 0);
				insertDataWindow_updateImagePreviewerLabels();
			}
		}

		void Application::insertDataWindow_buttonPreviewPrevious()
		{
			if (insertData_picturesIndex - 1 >= collectionScanner.imagesPaths.begin())
			{
				insertData_picturesIndex--;
				insertData_Box_previewBox->remove(*insertData_Box_previewBox->get_children().front());
				//delete insertData_imagePreviewer;
				insertData_imagePreviewer = new hn::gui::ImagePreviewer(*insertData_picturesIndex, Glib::RefPtr<Gtk::Window>(insertData_Window));
				insertData_imagePreviewer->show();
				insertData_Box_previewBox->pack_start(*insertData_imagePreviewer, true, true, 0);
				insertDataWindow_updateImagePreviewerLabels();
			}
		}

		void Application::insertDataWindow_updateImagePreviewerLabels()
		{
			insertData_Label_currentImagePath->set_text(*insertData_picturesIndex);
			std::string currentImageNumber = 
				std::to_string(insertData_picturesIndex - collectionScanner.imagesPaths.begin() + 1)
				+ " / "
				+ std::to_string(collectionScanner.imagesPaths.end() - collectionScanner.imagesPaths.begin());
			insertData_Label_currentImageNumber->set_text(currentImageNumber);
		}

		void Application::insertDataWindow_General_SceneType_AddLabel()
		{
			Gtk::ListBoxRow* newRow = Gtk::manage(new Gtk::ListBoxRow());
			newRow->add(*new Gtk::CheckButton(insertData_Entry_General_SceneType->get_text()));
			newRow->set_margin_top(5);
			newRow->set_margin_bottom(5);
			newRow->set_margin_start(5);
			newRow->set_margin_end(5);
			newRow->show_all();
			insertData_ListBox_General_SceneType->add(*newRow);
			insertData_Entry_General_SceneType->set_text("");
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
			previewBox->pack_start(*insertData_imagePreviewer, true, true, 0);

			// Dispatcher callback event for the file picker spinner
			insertData_Dispatcher_scanSuccess.connect(sigc::mem_fun(*this, &hn::gui::Application::insertDataWindow_onScanCompleted));
			insertData_Dispatcher_scanError.connect(sigc::mem_fun(*this, &hn::gui::Application::insertDataWindow_onScanError));

			insertData_Builder->get_widget("buttonNextImage", insertData_Button_previewNextPicture);
			insertData_Builder->get_widget("buttonPreviousImage", insertData_Button_previewPreviousPicture);
			insertData_Button_previewNextPicture->signal_clicked().connect(sigc::mem_fun(*this, &Application::insertDataWindow_buttonPreviewNext));
			insertData_Button_previewPreviousPicture->signal_clicked().connect(sigc::mem_fun(*this, &Application::insertDataWindow_buttonPreviewPrevious));

			insertData_Builder->get_widget("image-previewer-path", insertData_Label_currentImagePath);
			insertData_Builder->get_widget("label_current_picture", insertData_Label_currentImageNumber);

			insertData_Builder->get_widget<Gtk::Box>("PreviewBox", insertData_Box_previewBox);

			insertData_Builder->get_widget<Gtk::Button>("check_json_preview_button", insertData_Button_openJsonPreview);
			insertData_Button_openJsonPreview->signal_clicked().connect(sigc::mem_fun(*this, &Application::showPreviewJsonWindow));

			insertData_Builder->get_widget<Gtk::Entry>("insert_general_scenetype_newlabel", insertData_Entry_General_SceneType);
			insertData_Builder->get_widget<Gtk::Button>("insert_general_scenetype_newlabel_button", insertData_Button_General_SceneType);
			insertData_Button_General_SceneType->signal_clicked().connect(sigc::mem_fun(*this, &Application::insertDataWindow_General_SceneType_AddLabel));
			insertData_Builder->get_widget<Gtk::ListBox>("insert_general_scenetype_listbox", insertData_ListBox_General_SceneType);
		}

		void Application::showInsertDataWindow()
		{
			insertData_Window->show_all();
		}

		// Use the `previewJsonWindow_setText` method to set the text inside
		void Application::initPreviewJsonWindow()
		{
			previewJson_Builder = Gtk::Builder::create_from_file("../ui/HentaiNeko.glade");

			previewJson_Builder->get_widget("json_preview_window", previewJson_Window);
			previewJson_Window->set_default_size(800, 800);
			previewJson_Builder->get_widget("json_preview_text_view", previewJson_TextView_previewTextView);
			// As it turns out, I could probably use a TextBuffer from Glade and save doing it here
			previewJson_TextBuffer = Gtk::TextBuffer::create();
			previewJson_TextView_previewTextView->set_buffer(previewJson_TextBuffer);
		}

		void Application::showPreviewJsonWindow()
		{
			previewJson_TextBuffer->set_text(imageProperties.ExportJson());
			previewJson_Window->show_all();
		}
	}
}