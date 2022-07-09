#pragma once

#include <gtkmm.h>
#include <vector>
#include <utility>

namespace hn
{
	namespace gui::widget
	{
		template <typename WidgetType>
		class DynamicCheckbox
		{
		public:
			DynamicCheckbox(const std::string& placeholderText = std::string("Add a new tag :3")) :
				mainContainer{ Gtk::Box() },
				scrolledWindow{ Gtk::ScrolledWindow() },
				viewport{ Gtk::Viewport(scrolledWindow.get_hadjustment(), scrolledWindow.get_vadjustment()) },
				listbox{ Gtk::ListBox() },
				entryBox{ Gtk::Box() },
				entry{ Gtk::Entry() },
				addEntryButton{ Gtk::Button() },
				separator{ Gtk::Separator() }
			{
				listbox.set_selection_mode(Gtk::SelectionMode::SELECTION_NONE);
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

				addEntryButton.signal_clicked().connect(sigc::mem_fun(*this, &DynamicCheckbox::addEntryButtonCallback));
			}

			void addEntryButtonCallback()
			{
				if (entry.get_text() != "")
				{
					WidgetType* widget = new WidgetType(entry.get_text());
					addWidget(*widget);
					entry.set_text("");
				}
			}

			void addWidget(WidgetType& widget)
			{
				//Gtk::Box newItem = Gtk::Box();
				listboxItems.push_back(Gtk::Box());
				listboxItems.back().pack_start(widget, true, true, 0);
				Gtk::Button* button = new Gtk::Button();
				Gtk::Image* deleteItemIcon = new Gtk::Image(Gtk::StockID("gtk-close"), Gtk::IconSize(Gtk::BuiltinIconSize::ICON_SIZE_BUTTON));
				button->add(*deleteItemIcon);
				listboxItems.back().pack_end(*button, false, false, 0);
				listboxItems.back().show_all();
				listboxItems.back().show_all();
				listbox.add(listboxItems.back());
			}

			const std::vector<WidgetType*> getWidgets()
			{
				std::vector<WidgetType*> itemsReferences;
				for (const auto& iterator : listboxItems)
				{
					itemsReferences.push_back((WidgetType*)iterator.get_children().front());
				}
				return std::move(itemsReferences);
			}

			Gtk::Widget& operator()()
			{
				return mainContainer;
			}
		private:
			std::vector<Gtk::Box> listboxItems;
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