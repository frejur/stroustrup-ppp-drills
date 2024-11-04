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
    , mask_x(0)
    , mask_y(0)
    , mask_w(normal_width)
    , mask_h(normal_height)
    , img(top_left, image_path)
{
	img.set_mask({mask_x, mask_y}, mask_w, mask_h);
}

//------------------------------------------------------------------------------

void shp_btn::Image_button::show()
{
	Shape_button::show();
	img.set_mask({mask_x, mask_y}, mask_w, mask_h); // TODO: Less Hacky
}

void shp_btn::Image_button::hide()
{
	Shape_button::hide();
	img.set_mask({-999, -999}, 1, 1); // TODO: Less Hacky
}

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
	win.put_on_top(img);
}

void shp_btn::Image_button::set_mask(int x, int y, int width, int height)
{
	mask_x = x;
	mask_y = y;
	mask_w = width;
	mask_h = height;
	img.set_mask({x, y}, width, height);
}

void shp_btn::Image_button::offset_image(int offs_x, int offs_y)
{
	mask_x = offs_x;
	mask_y = offs_y;
	mask_w = width();
	mask_h = height();
	img.set_mask({offs_x, offs_y}, width(), height());
}

void shp_btn::Image_button::put_on_top()
{
	if (!is_not_attached()) {
		own->put_on_top(img);
	}
	shp_btn::Shape_button::put_on_top();
}
