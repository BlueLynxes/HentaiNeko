#include "CharacterEntryListItem.hpp"
#include "../../utils/find_gtk_children.hpp"
#include <iostream>

namespace hn::gui::widget
{
	CharacterEntryListItem::CharacterEntryListItem(const std::string& characterLabel, Gtk::Box* containerWidget) :
		characterName{ Gtk::Label(characterLabel) },
		containerWidget{ containerWidget },
		openCharacterWindow{ Gtk::Button() }
	{
		set_margin_start(5);
		set_margin_end(5);
		characterName.set_halign(Gtk::Align::ALIGN_START);
		buttonIcon.set_from_icon_name("go-next", Gtk::IconSize(Gtk::BuiltinIconSize::ICON_SIZE_BUTTON));
		openCharacterWindow.add(buttonIcon);
		openCharacterWindow.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &CharacterEntryListItem::openCharacterEditorCallback), characterLabel));
		pack_start(characterName, true, true);
		pack_end(openCharacterWindow, false, true);
		show_all();

		Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("../ui/HentaiNeko.glade");
		builder->get_widget<Gtk::Box>("character-editor-box", characterEditor);
		Glib::ValueBase propertyValue;
		characterEditor->property_name().set_value(characterLabel);
		containerWidget->add(*characterEditor);
		Gtk::Button* closeEditorButton = (Gtk::Button*)hn::utils::gtk::find_children_by_name(characterEditor, "close_character_editor");
		if (closeEditorButton == nullptr)
		{
			throw std::runtime_error("Close character editor button not found");
		}
		closeEditorButton->signal_clicked().connect(sigc::mem_fun(*this, &CharacterEntryListItem::hideCharacterEditorCallback));
		characterEditor->set_visible(false);
		Gtk::Label* characterNameLabel = (Gtk::Label*)hn::utils::gtk::find_children_by_name(characterEditor, "character_label");
		if (characterNameLabel == nullptr)
		{
			throw std::runtime_error("Character editor title label not found");
		}
		characterNameLabel->set_text(characterLabel);
	}

	CharacterEntryListItem::~CharacterEntryListItem()
	{
		delete characterEditor;
	}

	void CharacterEntryListItem::openCharacterEditorCallback(const std::string& characterName)
	{
		containerWidget->get_children().front()->set_visible(false);
		characterEditor->set_visible(true);
	}

	void CharacterEntryListItem::hideCharacterEditorCallback()
	{
		characterEditor->set_visible(false);
		containerWidget->get_children().front()->set_visible(true);
	}
}