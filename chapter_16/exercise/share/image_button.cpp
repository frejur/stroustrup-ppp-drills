#include "image_button.h"
namespace {
const Graph_lib::Color& default_transparent_fill_color()
{
	static Graph_lib::Color c{
	    Graph_lib::Color(Graph_lib::Color::black, Graph_lib::Color::invisible)};
	return c;
}
} // namespace

//------------------------------------------------------------------------------

shp_btn::Image_button::Image_button(Graph_lib::Point top_left,
                                    int width,
                                    int height,
                                    const string& label,
                                    Graph_lib::Callback callback_fn,
                                    const string& image_path)
    : Image_button(top_left,
                   width,
                   height,
                   width,
                   height,
                   label,
                   callback_fn,
                   image_path)
{}

shp_btn::Image_button::Image_button(Graph_lib::Point top_left,
                                    int normal_width,
                                    int normal_height,
                                    int active_width,
                                    int active_height,
                                    const string& label,
                                    Graph_lib::Callback callback_fn,
                                    const string& image_path)
    : Shape_button::Shape_button(top_left,
                                 normal_width,
                                 normal_height,
                                 active_width,
                                 active_height,
                                 label,
                                 callback_fn,
                                 default_transparent_fill_color())
    , img(top_left, image_path)
{
	img.set_mask({0, 0}, normal_width, normal_height);
}

//------------------------------------------------------------------------------

void shp_btn::Image_button::move(int offs_x, int offs_y)
{
	Shape_button::move(offs_x, offs_y);
	img.move(offs_x, offs_y);
}

void shp_btn::Image_button::attach(Graph_lib::Window& win)
{
	Shape_button::attach(win);
	win.attach(img);
	win.put_on_top(box);
}

void shp_btn::Image_button::offset_image(int offs_x, int offs_y)
{
	img.set_mask({offs_x, offs_y}, width(), height());
}
