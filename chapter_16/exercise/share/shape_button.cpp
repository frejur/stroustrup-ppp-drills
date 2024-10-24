#include "shape_button.h"

namespace {
constexpr int default_font_size{14};

const Graph_lib::Font& default_font()
{
	static Graph_lib::Font f{Graph_lib::Font::helvetica_bold};
	return f;
};

const Graph_lib::Line_style& default_style()
{
	static Graph_lib::Line_style s{Graph_lib::Line_style::solid, 1};
	return s;
};

const Graph_lib::Color& default_color()
{
	static Graph_lib::Color c{Graph_lib::Color::white};
	return c;
}
} // namespace

const Graph_lib::Color& shp_btn::Shape_button::default_fill_color()
{
	static Graph_lib::Color c{Graph_lib::Color(fl_rgb_color(120, 180, 180))};
	return c;
}

//------------------------------------------------------------------------------

shp_btn::Shape_button::Shape_button(Graph_lib::Point top_left,
                                    int width,
                                    int height,
                                    const string& label,
                                    Graph_lib::Callback callback_fn,
                                    Graph_lib::Color bg_color)
    : Shape_button::Shape_button(top_left,
                                 width,
                                 height,
                                 width,
                                 height,
                                 label,
                                 callback_fn,
                                 bg_color)
{}

shp_btn::Shape_button::Shape_button(Graph_lib::Point top_left,
                                    int normal_width,
                                    int normal_height,
                                    int active_width,
                                    int active_height,
                                    const string& label,
                                    Graph_lib::Callback callback_fn,
                                    Graph_lib::Color bg_color)
    : Graph_lib::Button(top_left, normal_width, normal_height, label, callback_fn)

    // Initial state / position
    , is_hidden(false)
    , st(Shape_button_state::Normal)
    , normal_xy(top_left)
    , active_xy(top_left)

    // Reset style
    , reset_col(default_color())
    , reset_fill(bg_color)
    , reset_sty(default_style())

    // Reset label
    , reset_fnt_sz(default_font_size)
    , reset_lb(label)
    , reset_fnt(default_font())

    // Dimensions
    , normal_w(normal_width)
    , normal_h(normal_height)
    , active_w(active_width)
    , active_h(active_height)

    // Shape / Active button
    , box(top_left, normal_width, normal_height, label)
    , btn_act(top_left, active_width, active_height, label, callback_fn)
{
	set_color(default_color());
	set_fill_color(bg_color);
	set_style(default_style());
	set_font(default_font());
	set_font_size(default_font_size);
}

//------------------------------------------------------------------------------

void shp_btn::Shape_button::move(int offs_x, int offs_y)
{
	Graph_lib::Button::show();
	btn_act.show();
	normal_xy.x += offs_x;
	normal_xy.y += offs_y;
	active_xy.x += offs_x;
	active_xy.y += offs_y;
	Graph_lib::Button::move(offs_x, offs_y);
	btn_act.move(offs_x, offs_y);
	if (!is_active()) {
		btn_act.hide();
	} else {
		Graph_lib::Button::hide();
	}
}

void shp_btn::Shape_button::hide()
{
	is_hidden = true;
	btn_act.hide();
	Graph_lib::Button::hide();
	box.hide();
}

void shp_btn::Shape_button::show()
{
	is_hidden = false;
	if (is_active()) {
		Graph_lib::Button::show();
	} else {
		btn_act.hide();
	}
	box.show();
}

void shp_btn::Shape_button::attach(Graph_lib::Window& win)
{
	Graph_lib::Button::attach(win);
	btn_act.attach(win);

	// Hiding / showing buttons only works after attaching, check state, and
	// adjust initial visibility
	if (is_active()) {
		hide();
	} else {
		btn_act.hide();
	}
	win.attach(box);
}

void shp_btn::Shape_button::offset_active_position(int offs_x, int offs_y)
{
	btn_act.show();
	btn_act.move(offs_x, offs_y);
	active_xy.x += offs_x;
	active_xy.y += offs_y;
	if (!is_active() || !is_visible()) {
		btn_act.hide();
	}
}

void shp_btn::Shape_button::offset_normal_position(int offs_x, int offs_y)
{
	Graph_lib::Button::show();
	move(offs_x, offs_y);
	normal_xy.x += offs_x;
	normal_xy.y += offs_x;
	if (is_active() || !is_visible()) {
		Graph_lib::Button::hide();
	}
}
