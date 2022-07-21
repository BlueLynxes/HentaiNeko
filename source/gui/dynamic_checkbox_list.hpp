#pragma once

#include <gtkmm.h>
#include <vector>
#include <utility>
#include <iostream>

namespace hn
{
	namespace gui::widget
	{
		template <typename WidgetType>
		class DynamicCheckbox
		{
		public:
			DynamicCheckbox(std::function<Gtk::CheckButton* (const std::string&)> initWidgetLogic,
							std::function<std::function<bool(Gtk::Box&)>(const std::string&)> comparisonLogic,
							const std::string& placeholderText = std::string("Add a new tag :3")
			) :
				initWidgetLogic{ initWidgetLogic },
				comparisonLogic{ comparisonLogic },
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
				addEntryButton.set_tooltip_text("Empty entry or item already present");
				addEntryButton.set_sensitive(false);
				entry.signal_changed().connect(sigc::mem_fun(*this, &DynamicCheckbox::lockAddButton));
			}

			void addEntryButtonCallback()
			{
				if (entry.get_text() != "" && !(findListItem(entry.get_text()) != listboxItems.end()))
				{
					WidgetType* widget = initWidgetLogic(entry.get_text());
					addWidget(*widget);
					entry.set_text("");
				}
			}

			// This is called just for a graphical reason, the actual check is still done on button click
			void lockAddButton()
			{
				if (entry.get_text() == "" || findListItem(entry.get_text()) != listboxItems.end())
				{
					addEntryButton.set_tooltip_text("Empty entry or item already present");
					addEntryButton.set_sensitive(false);
				}
				else
				{
					addEntryButton.set_tooltip_text("Add new item");
					addEntryButton.set_sensitive(true);
				}
			}

			void addWidget(WidgetType& widget)
			{
				//This should call findListItem to check if the item already exist, but how to extract the label from a custom element?
				listboxItems.push_back(Gtk::Box());
				listboxItems.back().pack_start(widget, true, true, 0);
				Gtk::Button* button = new Gtk::Button();
				Gtk::Image* deleteItemIcon = new Gtk::Image(Gtk::StockID("gtk-close"), Gtk::IconSize(Gtk::BuiltinIconSize::ICON_SIZE_BUTTON));
				button->add(*deleteItemIcon);
				listboxItems.back().pack_end(*button, false, false, 0);
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

			// For now this only works with Gtk::CheckButton
			const std::vector<Gtk::Box>::iterator findListItem(const std::string& itemLabel)
			{
				std::vector<Gtk::Box>::iterator foundElement = std::find_if(listboxItems.begin(), listboxItems.end(), comparisonLogic(itemLabel));
				return foundElement;
			}

			Gtk::Widget& operator()()
			{
				return mainContainer;
			}
		private:
			std::function<Gtk::CheckButton* (const std::string&)> initWidgetLogic;
			std::function<std::function<bool(Gtk::Box&)>(const std::string&)> comparisonLogic;
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