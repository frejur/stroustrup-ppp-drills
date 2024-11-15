#include "tgl.h"

namespace {
constexpr int padding{4};
const Graph_lib::Color& default_inactive_color()
{
	static const Graph_lib::Color c{
	    Graph_lib::Color(fl_rgb_color(155, 155, 155))};
	return c;
}
const Graph_lib::Color& default_square_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::white};
	return c;
}
const Graph_lib::Color& transparent()
{
	static const Graph_lib::Color c{Graph_lib::Color::black,
	                                Graph_lib::Color::Transparency::invisible};
	return c;
}
} // namespace

//------------------------------------------------------------------------------

Toggle::Toggle(Graph_lib::Point top_left,
               int width,
               int height,
               Graph_lib::Callback callback_fn,
               Graph_lib::Color active_bg_color)
    : shp_btn::Shape_button(top_left,
                            width,
                            height,
                            "",
                            callback_fn,
                            active_bg_color)
    , is_on_(false)
    , on_fill(active_bg_color)
    , off_fill(default_inactive_color())
    , tgl_square({top_left.x + width / 2, top_left.y + padding},
                 width / 2 - padding,
                 height - 2 * padding)
{
	tgl_square.set_color(transparent());
	tgl_square.set_fill_color(default_square_color());
}

//------------------------------------------------------------------------------

void Toggle::toggle()
{
	if (is_on()) {
		turn_off();
	} else {
		turn_on();
	}
}

void Toggle::turn_on()
{
	normalize();
	is_on_ = true;
}

void Toggle::turn_off()
{
	activate();
	is_on_ = false;
}
//------------------------------------------------------------------------------

void Toggle::activate()
{
	if (is_active()) {
		return;
	}
	Shape_button::activate();

	tgl_square.move(tgl_square.width(), 0);
	tgl_square.set_fill_color(on_fill);
}

void Toggle::normalize()
{
	if (is_normal()) {
		return;
	}
	Shape_button::normalize();

	tgl_square.move(-tgl_square.width(), 0);
	tgl_square.set_fill_color(off_fill);
}
//------------------------------------------------------------------------------

void Toggle::move(int offs_x, int offs_y)
{
	Shape_button::move(offs_x, offs_y);
	tgl_square.move(offs_x, offs_y);
}

void Toggle::hide()
{
	Shape_button::hide();
	Graph_lib::Color temp_clr{color()};
	temp_clr.set_visibility(Graph_lib::Color::Transparency::invisible);
	tgl_square.set_fill_color(temp_clr);
}

void Toggle::show()
{
	Shape_button::show();
	Graph_lib::Color temp_clr{color()};
	temp_clr.set_visibility(Graph_lib::Color::Transparency::visible);
	tgl_square.set_fill_color(temp_clr);
}
//------------------------------------------------------------------------------

void Toggle::attach(Graph_lib::Window& win)
{
	Shape_button::attach(win);
	win.attach(tgl_square);
}

void Toggle::set_fill_color(Graph_lib::Color col)
{
	on_fill = col;
	if (is_on()) {
		Shape_button::set_fill_color(col);
	}
}
//------------------------------------------------------------------------------

void Toggle::set_inactive_fill_color(Graph_lib::Color col)
{
	off_fill = col;
	if (!is_on()) {
		Shape_button::set_fill_color(col);
	}
}

void Toggle::set_square_color(Graph_lib::Color col)
{
	// Update color, maintain visibility
	Graph_lib::Color temp_clr{tgl_square.color()};
	col.set_visibility(
	    static_cast<Graph_lib::Color::Transparency>(temp_clr.visibility()));
	tgl_square.set_fill_color(Graph_lib::Color(col));
}
//------------------------------------------------------------------------------
