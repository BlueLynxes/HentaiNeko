#pragma once

#include <gtkmm.h>

namespace hn
{
	namespace gui
	{
		class ImagePreviewer : public Gtk::DrawingArea
		{
		public:
			ImagePreviewer() = delete;
			ImagePreviewer(const std::string& imagePath, Glib::RefPtr<Gtk::Window> parentWindow);
		private:
			Glib::RefPtr<Gtk::Window> parentWindow;
			Glib::RefPtr<Gdk::Pixbuf> imageBuf;
			Cairo::RefPtr<Cairo::ImageSurface> imageSurface;

			int GetUsefulHeight();
			double GetScaleFactor();
		protected:
			bool on_draw(const Cairo::RefPtr<Cairo::Context>& context) override;
		};
	}
}