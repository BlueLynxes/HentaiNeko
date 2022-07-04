#pragma once

#include <gtkmm.h>

namespace hn
{
	namespace gui::widget
	{
		class DynamicCheckbox
		{
		public:
			DynamicCheckbox(const std::string& placeholderText = std::string("Add a new tag :3"));
			Gtk::Widget& operator()();
		private:
			Gtk::Box mainContainer;
			Gtk::ScrolledWindow scrolledWindow;
			Gtk::Viewport viewport;
			Gtk::ListBox listbox;
			Gtk::Separator separator;
			Gtk::Box entryBox;
			Gtk::Entry entry;
			Gtk::Image addEntryButtonIcon;
			Gtk::Button addEntryButton;
		};
	}
}