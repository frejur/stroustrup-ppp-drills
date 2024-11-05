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
    : Control(top_left, normal_width, normal_height, "", callback_fn)

    // Initial state / position
    , box(top_left, normal_width, normal_height, label)
    , btn_act(top_left, active_width, active_height, label, callback_fn)
    , is_hidden(false)
    , is_attached(false)
    , st(Shape_button_state::Normal)

    // Reset style
    , normal_xy(top_left)
    , active_xy(top_left)
    , reset_col(default_color())

    // Reset label
    , reset_fill(bg_color)
    , reset_sty(default_style())
    , reset_fnt_sz(default_font_size)

    // Dimensions
    , reset_lb(label)
    , reset_fnt(default_font())
    , normal_w(normal_width)
    , normal_h(normal_height)

    // Shape / Active button
    , active_w(active_width)
    , active_h(active_height)
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
	require_attached();
	bool main_visible = !is_hidden;
	bool nrm_visible = Control::is_visible();
	bool act_visible = btn_act.is_visible();
	Control::show();
	btn_act.show();
	normal_xy.x += offs_x;
	normal_xy.y += offs_y;
	active_xy.x += offs_x;
	active_xy.y += offs_y;
	Graph_lib::Button::move(offs_x, offs_y);
	btn_act.move(offs_x, offs_y);
	box.move(offs_x, offs_y);

	if (main_visible) {
		if (!nrm_visible) {
			Control::hide();
		}
		if (!act_visible) {
			btn_act.hide();
		}
	} else {
		hide();
	}
}

void shp_btn::Shape_button::hide()
{
	require_attached();
	is_hidden = true;
	btn_act.hide();
	Graph_lib::Button::hide();
	box.hide();
}

void shp_btn::Shape_button::show()
{
	require_attached();
	is_hidden = false;
	if (!is_active()) {
		Graph_lib::Button::show();
	} else {
		btn_act.hide();
	}
	box.show();
}

void shp_btn::Shape_button::attach(Graph_lib::Window& win)
{
	if (is_attached) {
		return;
	}
	Graph_lib::Button::attach(win);
	btn_act.attach(win);

	// Hiding / showing buttons only works after attaching, check state, and
	// adjust initial visibility
	if (is_active()) {
		Graph_lib::Button::hide();
	} else {
		btn_act.hide();
	}
	win.attach(box);
	is_attached = true;

	// Check if the above changed the internal positional attrib. - Update shape
	if (normal_xy.x != loc.x || normal_xy.y != loc.y) {
		int offs_x = loc.x - normal_xy.x;
		int offs_y = loc.y - normal_xy.y;
		normal_xy = loc;
		box.move(offs_x, offs_y);
	}
}

void shp_btn::Shape_button::offset_active_position(int offs_x, int offs_y)
{
	require_attached();
	bool act_visible = btn_act.is_visible();
	btn_act.show();
	btn_act.move(offs_x, offs_y);
	active_xy.x += offs_x;
	active_xy.y += offs_y;
	if (!act_visible) {
		btn_act.hide();
	}
}

void shp_btn::Shape_button::offset_normal_position(int offs_x, int offs_y)
{
	require_attached();
	bool nrm_visible = Control::is_visible();
	Graph_lib::Button::show();
	move(offs_x, offs_y);
	normal_xy.x += offs_x;
	normal_xy.y += offs_x;
	if (!nrm_visible) {
		Graph_lib::Button::hide();
	}
}

void shp_btn::Shape_button::put_on_top()
{
	if (!is_not_attached()) {
		own->put_on_top(box);
	}
}
