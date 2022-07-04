#include "dynamic_checkbox_list.hpp"

namespace hn
{
	namespace gui::widget
	{
		DynamicCheckbox::DynamicCheckbox(const std::string& placeholderText) :
			mainContainer{ Gtk::Box() },
			scrolledWindow{ Gtk::ScrolledWindow() },
			viewport{ Gtk::Viewport(scrolledWindow.get_hadjustment(), scrolledWindow.get_vadjustment()) },
			listbox{ Gtk::ListBox() },
			entryBox{ Gtk::Box() },
			entry{ Gtk::Entry() },
			addEntryButton{ Gtk::Button() },
			separator{ Gtk::Separator()}
		{
			viewport.add(listbox);
			scrolledWindow.add(viewport);
			scrolledWindow.set_shadow_type(Gtk::ShadowType::SHADOW_IN);
			mainContainer.add(scrolledWindow);
			mainContainer.set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
			mainContainer.set_spacing(5);
			scrolledWindow.set_hexpand(true);
			scrolledWindow.set_vexpand(true);
			viewport.set_hexpand(true);
			viewport.set_vexpand(true);

			mainContainer.add(separator);

			entryBox.set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);
			entryBox.set_spacing(5);
			entryBox.add(entry);
			entryBox.add(addEntryButton);
			addEntryButtonIcon = Gtk::Image(Gtk::StockID("gtk-add"), Gtk::IconSize(Gtk::BuiltinIconSize::ICON_SIZE_BUTTON));
			addEntryButton.add(addEntryButtonIcon);
			entry.set_hexpand(true);
			entry.set_placeholder_text(placeholderText);
			mainContainer.add(entryBox);
		}
		
		Gtk::Widget& DynamicCheckbox::operator()()
		{
			return mainContainer;
		}
	}
}