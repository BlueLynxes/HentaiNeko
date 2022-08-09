#pragma once

#include <gtkmm.h>
#include <memory>

namespace hn::gui::widget
{
	class DoubleFieldEntry : public Gtk::Box
	{
	public:
		DoubleFieldEntry(const std::string& rightFieldPlaceholder,
						 const std::string& leftFieldValue, const std::string& rightFieldValue);
	public:
		std::shared_ptr<Gtk::Label> leftEntry  = std::make_shared<Gtk::Label>();
		std::shared_ptr<Gtk::Entry> rightEntry = std::make_shared<Gtk::Entry>();
		std::shared_ptr<Gtk::CheckButton> checkButton = std::make_shared<Gtk::CheckButton>();
	};
}