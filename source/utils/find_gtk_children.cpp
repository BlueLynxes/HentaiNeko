#include "find_gtk_children.hpp"
#include <iostream>

namespace hn::utils::gtk
{
	Gtk::Widget* find_children_by_name(Gtk::Container* parent, const std::string& childName)
	{
		auto childrens = parent->get_children();
		for (const auto& child : childrens)
		{
			if (child->property_name() == childName)
			{
				return child;
			}
			if (Gtk::Container* container = dynamic_cast<Gtk::Container*>(child); container != nullptr)
			{
				Gtk::Widget* result = find_children_by_name((Gtk::Container*)child, childName);
				if (result != nullptr)
				{
					return result;
				}
			}
		}
		return nullptr;
	}
}