#define NOMINMAX
#include "e10_pswin.h"

ch14_e10::Control_button::Control_button(Point origin,
                                         int width,
                                         int height,
                                         Color color,
                                         Color fill_color,
                                         int corner_radius)
    : grp_shp::Shape_group(origin)
    , w(width)
    , h(height)
    , pad(calc_padding(w, h))
    , sym_color(color)
    , btn(origin, width, height, corner_radius, BOX::CrvMethod::Radius)
{
	// Button
	btn.set_color(color);
	btn.set_fill_color(fill_color);
	btn.set_style(Graph_lib::Line_style(Graph_lib::Line_style::solid, 1));
	set_fill_color(Graph_lib::Color::invisible);
	set_color(sym_color);
}

ch14_e10::Button_padding ch14_e10::Control_button::padded_corners() const
{
	return {{pad, pad}, {pad, pad}, {pad, pad}, {pad, pad}};
}

void ch14_e10::Control_button::draw_lines() const
{
	btn.draw();
	grp_shp::Shape_group::draw_lines();
}

int ch14_e10::Control_button::calc_padding(int width, int height) const
{
	return static_cast<int>(std::round(width > height ? height : width) * 0.25);
}

//------------------------------------------------------------------------------

ch14_e10::Close_button::Close_button(Point origin,
                                     int width,
                                     int height,
                                     Color color,
                                     Color fill_color,
                                     int corner_radius)
    : Control_button::Control_button(origin,
                                     width,
                                     height,
                                     color,
                                     fill_color,
                                     corner_radius)
{
	init_symbol();
}

void ch14_e10::Close_button::init_symbol()
{
	Button_padding padc = padded_corners();
	add(new Graph_lib::Line{{padc.top_left.x + o.x, padc.top_left.y + o.y},
	                        {-padc.btm_right.x + o.x + w,
	                         -padc.btm_right.y + o.y + h}});
	add(new Graph_lib::Line{{padc.btm_left.x + o.x, -padc.btm_left.y + o.y + h},
	                        {-padc.top_right.x + o.x + w,
	                         padc.top_right.y + o.y}});
	set_fill_color(Graph_lib::Color::invisible);
	set_color(sym_color);
	set_style(Graph_lib::Line_style(Graph_lib::Line_style::solid, 2));
}

ch14_e10::Button_padding ch14_e10::Close_button::padded_corners() const
{
	// Some more pixel pushing
	int adj_pad_a = static_cast<int>(std::round(pad * 1.0));
	int adj_pad_b = static_cast<int>(std::round(pad * 1.2));

	Button_padding bp;
	bp.top_left = {pad, pad};
	bp.top_right = {adj_pad_b, adj_pad_a};
	bp.btm_right = {adj_pad_b, adj_pad_b};
	bp.btm_left = {pad, adj_pad_b};
	return bp;
}

//------------------------------------------------------------------------------

ch14_e10::Maximize_button::Maximize_button(Point origin,
                                           int width,
                                           int height,
                                           Color color,
                                           Color fill_color,
                                           int corner_radius)
    : Control_button::Control_button(origin,
                                     width,
                                     height,
                                     color,
                                     fill_color,
                                     corner_radius)
{
	init_symbol();
}

void ch14_e10::Maximize_button::init_symbol()
{
	Button_padding padc = Maximize_button::padded_corners();
	add(new Graph_lib::Rectangle{{padc.top_left.x + o.x, padc.top_left.y + o.y},
	                             {-padc.btm_right.x + o.x + w,
	                              -padc.btm_right.y + o.y + h}});
	set_style(Graph_lib::Line_style(Graph_lib::Line_style::solid, 1));

	int top_stripe = std::max(1, static_cast<int>(std::round(w * 0.15)));
	add(new Graph_lib::Rectangle{{padc.top_left.x + o.x, padc.top_left.y + o.y},
	                             {-padc.top_right.x + o.x + w,
	                              padc.top_right.y + o.y + top_stripe}});
	set_fill_color(sym_color, 1);
	set_color(sym_color);
}

//------------------------------------------------------------------------------

ch14_e10::Minimize_button::Minimize_button(Point origin,
                                           int width,
                                           int height,
                                           Color color,
                                           Color fill_color,
                                           int corner_radius)
    : Control_button::Control_button(origin,
                                     width,
                                     height,
                                     color,
                                     fill_color,
                                     corner_radius)
{
	init_symbol();
}

void ch14_e10::Minimize_button::init_symbol()
{
	Button_padding padc = Minimize_button::padded_corners();

	int btm_stripe_w = std::max(1, static_cast<int>(std::round(w * 0.3)));
	int btm_stripe_h = std::max(1, static_cast<int>(std::round(w * 0.15)));
	add(new Graph_lib::Rectangle{{padc.btm_left.x + o.x,
	                              -padc.btm_left.y + o.y + h - btm_stripe_h},
	                             {padc.btm_left.x + o.x + btm_stripe_w,
	                              -padc.btm_right.y + o.y + h}});
	set_fill_color(sym_color);
	set_color(sym_color);
}

ch14_e10::Pseudo_window::Pseudo_window(Point origin, int width, int height)
    : frame(origin,
            width,
            height,
            8,
            BOX::CrvMethod::Radius,
            BOX::Flatten_side::Bottom)
    , icon({origin.x + 16, origin.y + 12}, 8)
    , title({origin.x + 30, origin.y + 18}, "Waka-waka")
    , btn_min({origin.x + width - 24 * 3, origin.y + 2}, 21, 21)
    , btn_max({origin.x + width - 24 * 2, origin.y + 2}, 21, 21)
    , btn_close({origin.x + width - 24 * 1, origin.y + 2}, 21, 21)
    , canvas({origin.x + 4, origin.y + 26}, width - 8, height - 30)
    , content({origin.x + 2, origin.y + 26})
{
	icon.set_color(Graph_lib::Color::invisible);
	icon.set_fill_color(Graph_lib::Color::yellow);
	title.set_color(Graph_lib::Color::white);
	frame.set_color(default_window_stroke_color());
	frame.set_fill_color(default_window_fill_color());
	canvas.set_fill_color(default_canvas_color());
}

void ch14_e10::Pseudo_window::move(int offset_x, int offset_y)
{
	frame.move(offset_x, offset_y);
	icon.move(offset_x, offset_y);
	title.move(offset_x, offset_y);
	btn_min.move(offset_x, offset_y);
	btn_max.move(offset_x, offset_y);
	btn_close.move(offset_x, offset_y);
	canvas.move(offset_x, offset_y);
	content.move(offset_x, offset_y);
}

void ch14_e10::Pseudo_window::draw_lines() const
{
	frame.draw();
	icon.draw();
	title.draw();
	btn_min.draw();
	btn_max.draw();
	btn_close.draw();
	canvas.draw();
	fl_clip(canvas.point(0).x + 1,
	        canvas.point(0).y + 1,
	        canvas.width() - 2,
	        canvas.height() - 1);
	content.draw();
	fl_pop_clip();
}
