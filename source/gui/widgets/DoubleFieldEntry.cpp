#include "DoubleFieldEntry.hpp"

namespace hn::gui::widget
{
	DoubleFieldEntry::DoubleFieldEntry(const std::string& rightFieldPlaceholder,
									   const std::string& leftFieldValue, const std::string& rightFieldValue)
	{
		this->set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);
		leftEntry->set_name("left-entry");
		leftEntry->set_text(leftFieldValue);
		rightEntry->set_placeholder_text(rightFieldPlaceholder);
		rightEntry->set_text(rightFieldValue);
		this->set_spacing(20);
		rightEntry->set_hexpand(true);
		rightEntry->set_halign(Gtk::Align::ALIGN_FILL);
		this->set_valign(Gtk::Align::ALIGN_FILL);
		this->set_margin_start(5);
		this->set_margin_end(5);
		checkButton->set_can_focus(false);
		this->add(*checkButton);
		this->add(*leftEntry);
		this->add(*rightEntry);
	}
}