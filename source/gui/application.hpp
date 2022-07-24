#pragma once
#include <gtkmm.h>

#include "../backend/collection_scanner.hpp"
#include "../backend/image_properties.hpp"
#include "image_previewer.hpp"
#include "dynamic_checkbox_list.hpp"

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
			void insertDataWindow_onScanCompleted();
			void insertDataWindow_onScanError();
			void insertDataWindow_updateImagePreviewerLabels();
			void insertDataWindow_buttonPreviewNext();
			void insertDataWindow_buttonPreviewPrevious();
			void insertDataWindow_collectImageProperties();
			// Preview Json Window
			void initPreviewJsonWindow();
			void showPreviewJsonWindow();
		private:
			Glib::RefPtr<Gtk::Application> application;
			hn::backend::CollectionScanner collectionScanner = hn::backend::CollectionScanner("../resources");
			hn::backend::ImageProperties imageProperties;

			// For the moment the Main Window, in the future
			// the main Window will be a greeter/collection display
			// NOTE: I'm making one builder per component, since in the
			// future those component will each have it's own UI file.
			// For the moment those are useless/wasteful.
			Glib::RefPtr<Gtk::Builder> insertData_Builder;
			Glib::RefPtr<Gtk::Window> insertData_Window;
			Gtk::HeaderBar* insertData_HeaderBar;
			Gtk::Button* insertData_Button_ShowAboutWindow;
			Gtk::Button* insertData_Button_OpenEntryPointPickerDialogue;
			std::string collectionEntryPointPath = "../resources";
			Glib::Dispatcher insertData_Dispatcher_scanSuccess;
			Glib::Dispatcher insertData_Dispatcher_scanError;
			hn::gui::ImagePreviewer* insertData_imagePreviewer;
			std::vector<std::string>::iterator insertData_picturesIndex;
			Gtk::Button* insertData_Button_previewNextPicture;
			Gtk::Button* insertData_Button_previewPreviousPicture;
			Gtk::Label* insertData_Label_currentImageNumber;
			Gtk::Label* insertData_Label_currentImagePath;
			Gtk::Box* insertData_Box_previewBox;
			Gtk::Button* insertData_Button_openJsonPreview;
			Gtk::Box* insertData_Box_General_SceneType;
			hn::gui::widget::DynamicCheckbox<Gtk::CheckButton>* insertData_DynamicCheckbox_SceneType;
			Gtk::Box* insertData_Box_Setting_LocationProperties;
			hn::gui::widget::DynamicCheckbox<Gtk::CheckButton>* insertData_Setting_LocationProperties;
			Gtk::ComboBoxText* insertData_ComboBoxText_Setting_TimeOfDay;
			Gtk::ComboBoxText* insertData_ComboBoxText_Setting_Season;
			Gtk::Entry* insertData_ComboBoxText_Setting_Light;
			Gtk::Box* insertData_Box_Genres;
			hn::gui::widget::DynamicCheckbox<Gtk::CheckButton>* insertData_Genres;
			Gtk::Box* insertData_Box_Tags;
			hn::gui::widget::DynamicCheckbox<Gtk::CheckButton>* insertData_Tags;

			Glib::RefPtr<Gtk::Builder> about_Builder;
			Gtk::Window* about_Window;
			Gtk::Label* about_Label_version;

			Glib::RefPtr<Gtk::Builder> previewJson_Builder;
			Gtk::Window* previewJson_Window;
			Gtk::TextView* previewJson_TextView_previewTextView;
			Glib::RefPtr<Gtk::TextBuffer> previewJson_TextBuffer;

		};
	}
}