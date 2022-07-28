#pragma once

#include <gtkmm.h>
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
	private:

		Gtk::Box* containerWidget;
		Gtk::Box* characterEditor;
		Gtk::Button openCharacterWindow;
		Gtk::Image buttonIcon;
	};
}