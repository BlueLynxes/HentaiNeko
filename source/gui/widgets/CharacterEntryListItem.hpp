#pragma once

#include <gtkmm.h>
#include "../dynamic_checkbox_list.hpp"
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
		std::unordered_map<std::string, std::vector<std::string>> returnSelectedValues();
	private:
		Gtk::Box* containerWidget;
		Gtk::Box* characterEditor;
		Gtk::Button openCharacterWindow;
		Gtk::Image buttonIcon;

		Gtk::Box* characterInfo_CharacterTypeBox;
		hn::gui::widget::DynamicCheckbox<Gtk::CheckButton>* characterTypeList;
	};
}