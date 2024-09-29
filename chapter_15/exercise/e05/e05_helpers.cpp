#include "e05.h"

ch15_e05::Graph_canvas::Graph_canvas(Graph_lib::Point canvas_origin,
                                     int width,
                                     int height,
                                     Graph_lib::Point graph_origin,
                                     int notch_size_x,
                                     int notch_size_y)
    : w{width}
    , h{height}
    , sz_x{notch_size_x}
    , sz_y{notch_size_y}
    , o_canvas{canvas_origin}
    , o_graph{graph_origin}
{
	int x_target_neg_len{graph_origin.x - canvas_origin.x};
	count_x_neg = x_target_neg_len / sz_x;
	int x_target_pos_len{width - x_target_neg_len};
	count_x_pos = x_target_pos_len / sz_x;

	int y_target_neg_len{graph_origin.y - canvas_origin.y};
	count_y_neg = y_target_neg_len / sz_y;
	int y_target_pos_len{height - y_target_neg_len};
	count_y_pos = y_target_pos_len / sz_y;
};

Graph_lib::Point ch15_e05::Graph_canvas::x_axis_start() const
{
	return {o_graph.x - count_x_neg * sz_x, o_graph.y};
}
Graph_lib::Point ch15_e05::Graph_canvas::y_axis_start() const
{
	return {o_graph.x, o_graph.y + count_y_pos * sz_y};
}

//------------------------------------------------------------------------------

void ch15_e05::Label_style::apply_to(Graph_lib::Text& t)
{
	t.set_font(font);
	t.set_font_size(font_size);
	t.set_color(color);

	int w = calc_lb_w(t.label(), font, font_size);
	int x_offs{};
	switch (text_alignment) {
	case Text_alignment::Top_left:
	case Text_alignment::Mid_left:
	case Text_alignment::Btm_left:
		x_offs = -(w + horizontal_padding);
		break;
	case Text_alignment::Top_center:
	case Text_alignment::Mid_center:
	case Text_alignment::Btm_center:
		x_offs = -static_cast<int>(w * 0.5 + 0.5);
		break;
	case Text_alignment::Top_right:
	case Text_alignment::Mid_right:
	case Text_alignment::Btm_right:
		x_offs = horizontal_padding;
		break;
	}

	int y_offs{};
	switch (text_alignment) {
	case Text_alignment::Top_left:
	case Text_alignment::Top_center:
	case Text_alignment::Top_right:
		y_offs = -vertical_padding;
		break;
	case Text_alignment::Mid_left:
	case Text_alignment::Mid_center:
	case Text_alignment::Mid_right:
		y_offs = static_cast<int>(font_size * 0.5 + 0.5);
		break;
	case Text_alignment::Btm_left:
	case Text_alignment::Btm_center:
	case Text_alignment::Btm_right:
		y_offs = font_size + vertical_padding;
		break;
	}

	t.move(x_offs, y_offs);
}

//------------------------------------------------------------------------------

int ch15_e05::calc_lb_w(const std::string& txt, Graph_lib::Font f, int f_sz)
{
	int dummy; // not needed
	int w;
	int font_backup = fl_font();
	int size_backup = fl_size();
	fl_font(f.as_int(), f_sz);
	fl_text_extents(txt.c_str(), dummy, dummy, w, dummy);
	fl_font(font_backup, size_backup);
	return w;
}
