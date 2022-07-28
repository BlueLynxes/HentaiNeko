#pragma once

#include <gtkmm.h>

// Utility function to find a Gtk widget by name

namespace hn::utils::gtk
{
	Gtk::Widget* find_children_by_name(Gtk::Container* parent, const std::string& childName);
}