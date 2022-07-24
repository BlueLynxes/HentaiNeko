#include "image_previewer.hpp"

hn::gui::ImagePreviewer::ImagePreviewer(const std::string& imagePath, Glib::RefPtr<Gtk::Window> parentWindow)
{
	this->parentWindow = parentWindow;
	//Glib::add_exception_handler(sigc::mem_fun(*this, &ImagePreviewer::unsupportedFormatExceptionHandler));
	try
	{
		imageBuf = Gdk::Pixbuf::create_from_file(imagePath);
		imageSurface = Gdk::Cairo::create_surface_from_pixbuf(imageBuf, 1, this->parentWindow->get_window());
	}
	catch (Glib::Exception& e)
	{
		imageBuf.reset();
		imageSurface.clear();
		imageBuf = Gdk::Pixbuf::create_from_file("../resources/previewFallback.png");
		imageSurface = Gdk::Cairo::create_surface_from_pixbuf(imageBuf, 1, this->parentWindow->get_window());
		Gtk::MessageDialog dialog = Gtk::MessageDialog(
			"Could not recognize the image file format",
			false,
			Gtk::MessageType::MESSAGE_ERROR,
			Gtk::ButtonsType::BUTTONS_OK,
			true
		);
		dialog.run();
	}
}

bool hn::gui::ImagePreviewer::on_draw(const Cairo::RefPtr<Cairo::Context>& context)
{
	double scaleFactor = GetScaleFactor();
	context->scale(scaleFactor, scaleFactor);
	context->set_source(imageSurface, 0, 0);
	context->paint();
	//this->set_size_request(-1, this->GetUsefulHeight());
	return 0;
}

int hn::gui::ImagePreviewer::GetUsefulHeight()
{
	return this->get_allocated_width() / imageBuf->get_width() * imageBuf->get_height();
}

double hn::gui::ImagePreviewer::GetScaleFactor()
{
	if ((double)imageBuf->get_height() * ((double)this->get_allocated_width() / (double)imageBuf->get_width()) < (double)this->get_allocated_height())
	{
		return (double)this->get_allocated_width() / (double)imageBuf->get_width();
	}
	else
	{
		return (double)this->get_allocated_height() / (double)imageBuf->get_height();
	}
}