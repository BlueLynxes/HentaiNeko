#pragma once

#include <gtkmm.h>
#include "../dynamic_checkbox_list.hpp"
#include "../../backend/image_properties.hpp"
#include <memory>

namespace hn::gui::widget
{
	class CharacterEntryListItem : public Gtk::Box
	{
	public:
		CharacterEntryListItem(const std::string& characterLabel, Gtk::Box* containerWidget);
		~CharacterEntryListItem();

	public:
		Gtk::Label characterName;
		void openCharacterEditorCallback(const std::string& characterName);
		void hideCharacterEditorCallback();
		hn::backend::ImageProperties::Character returnSelectedValues();
	private:
		Gtk::Box* containerWidget;
		Gtk::Box* characterEditor;
		Gtk::Button openCharacterWindow;
		Gtk::Image buttonIcon;

		Gtk::Box* characterInfo_CharacterTypeBox;
		hn::gui::widget::DynamicCheckbox<Gtk::CheckButton>* characterTypeList;
		Gtk::Box* body_ModificationsBox;
		hn::gui::widget::DynamicCheckbox<Gtk::CheckButton>* bodyModificationsList;
		Gtk::Box* clothing_AccessoriesBox;
		hn::gui::widget::DynamicCheckbox<Gtk::CheckButton>* clothingAccessoriesList;
		Gtk::Box* clothing_ItemsBox;
		hn::gui::widget::DynamicCheckbox<Gtk::CheckButton>* clothingItemsList;
	};
}