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

		std::function<std::function<bool(Gtk::Box&)>(const std::string&)> checkValue = [](const std::string& label)
		{
			return [&label](Gtk::Box& item) -> bool {
				if (((Gtk::CheckButton*)item.get_children().front())->get_label() == label)
				{
					return true;
				}
				return false;
			};
		};
		std::function<Gtk::CheckButton* (const std::string&)> addWidget = [](const std::string& label) -> Gtk::CheckButton*
		{
			return new Gtk::CheckButton(label);
		};
		characterInfo_CharacterTypeBox = (Gtk::Box*)hn::utils::gtk::find_children_by_name(characterEditor, "general-info-character-type-box");
		characterTypeList = new hn::gui::widget::DynamicCheckbox<Gtk::CheckButton>(addWidget, checkValue, "New character type");
		characterInfo_CharacterTypeBox->add((*characterTypeList)());
		characterInfo_CharacterTypeBox->show_all();
		
		clothing_AccessoriesBox = (Gtk::Box*)hn::utils::gtk::find_children_by_name(characterEditor, "clothing-accessories-box");
		clothingAccessoriesList = new hn::gui::widget::DynamicCheckbox<Gtk::CheckButton>(addWidget, checkValue, "New accessory");
		clothing_AccessoriesBox->add((*clothingAccessoriesList)());
		clothing_AccessoriesBox->show_all();
		
		clothing_ItemsBox = (Gtk::Box*)hn::utils::gtk::find_children_by_name(characterEditor, "clothing-clothing-items-box");
		clothingItemsList = new hn::gui::widget::DynamicCheckbox<Gtk::CheckButton>(addWidget, checkValue, "New item");
		clothing_ItemsBox->add((*clothingItemsList)());
		clothing_ItemsBox->show_all();

		Gtk::Entry* characterName = (Gtk::Entry*)hn::utils::gtk::find_children_by_name(characterEditor, "general-info-name");
		characterName->set_text(characterLabel);
	}

	CharacterEntryListItem::~CharacterEntryListItem()
	{
		delete characterTypeList;
		delete clothingAccessoriesList;
		delete clothingItemsList;
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

	hn::backend::ImageProperties::Character CharacterEntryListItem::returnSelectedValues()
	{
		// TODO: Optimize data collection
		// Instead of making a vector to then copy onto the character object, use the character object directly
		hn::backend::ImageProperties::Character character;
		// General Info
		Gtk::ComboBoxText* characterBrand = (Gtk::ComboBoxText*)hn::utils::gtk::find_children_by_name(characterEditor, "general-info-brand");
		character.generalInfo.brand = characterBrand->get_active_text();
		Gtk::Entry* characterName = (Gtk::Entry*)hn::utils::gtk::find_children_by_name(characterEditor, "general-info-name");
		character.generalInfo.characterName = characterName->get_text();
		Gtk::ComboBoxText* characterGender = (Gtk::ComboBoxText*)hn::utils::gtk::find_children_by_name(characterEditor, "general-info-gender");
		character.generalInfo.gender = characterGender->get_active_text();
		const auto characterTypeWidgets = characterTypeList->getWidgets();
		std::vector<std::string> characterTypes;
		for (const auto& iterator : characterTypeWidgets)
		{
			if (iterator->get_active())
			{
				std::string label = iterator->get_label();
				std::transform(label.begin(), label.end(), label.begin(), ::tolower);
				characterTypes.push_back(label);
			}
		}
		character.generalInfo.types = characterTypes; // UNNECESSARY COPY
		// Body
		// Clothing
		Gtk::Entry* clothingOutfitType = (Gtk::Entry*)hn::utils::gtk::find_children_by_name(characterEditor, "clothing-outfit-type");
		character.clothingDescription.outfitType = clothingOutfitType->get_text();
		
		Gtk::SpinButton* clothingBodyExposureRate = (Gtk::SpinButton*)hn::utils::gtk::find_children_by_name(characterEditor, "clothing-body-exposure-rate");
		character.clothingDescription.bodyExposureRate = std::stoi(clothingBodyExposureRate->get_text());
		
		const auto clothingAccessories = clothingAccessoriesList->getWidgets();
		std::vector<std::string> characterClothingAccessories;
		for (const auto& iterator : clothingAccessories)
		{
			if (iterator->get_active())
			{
				std::string label = iterator->get_label();
				std::transform(label.begin(), label.end(), label.begin(), ::tolower);
				characterClothingAccessories.push_back(label);
			}
		}
		character.clothingDescription.accessories = characterClothingAccessories; // UNNECESSARY COPY

		const auto clothingItems = clothingItemsList->getWidgets();
		std::vector<std::string> characterClothingItems;
		for (const auto& iterator : clothingItems)
		{
			if (iterator->get_active())
			{
				std::string label = iterator->get_label();
				std::transform(label.begin(), label.end(), label.begin(), ::tolower);
				characterClothingItems.push_back(label);
			}
		}
		character.clothingDescription.clothingItems = characterClothingItems; // UNNECESSARY COPY
		// Accessories
		// Positions
		// Expressions
		// Actions
		return character;
	}
}