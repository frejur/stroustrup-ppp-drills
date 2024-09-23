#include "nodes.h"
#include "../share/help/helpers.h"

namespace {

using box_hlp = BOX::ConnectionPointHelper;

constexpr double curvedness{0.8};
constexpr int min_height{6};
constexpr int max_height{64};
constexpr float font_size_factor{0.7f};
constexpr float width_padding_from_height_factor{0.2f};
inline const Graph_lib::Font& node_font()
{
	static const Graph_lib::Font f{Graph_lib::Font::courier};
	return f;
}
} // namespace

ch14_e17::Node::Node(Graph_lib::Point origin, const string& label, int height)
    : BOX::Box::Box(origin,
                    calc_lb_width(label,
                                  node_font(),
                                  static_cast<int>(std::round(
                                      valid_h(height) * font_size_factor)))
                        + static_cast<int>(std::round(
                            height * width_padding_from_height_factor * 2)),
                    height,
                    curvedness)
    , has_tie(false)
    , has_sym(false)
    , h(height)
    , tie({0, 0})
    , lb(label)
{
	set_color(Graph_lib::Color::black);
	set_fill_color(Graph_lib::Color::white);
}

ch14_e17::Node::Node(Graph_lib::Point origin,
                     const string& label,
                     int height,
                     Graph_lib::Point tied_point)
    : Node(origin, label, height)
{
	tie_to_point(tied_point);
}

void ch14_e17::Node::tie_to_point(Graph_lib::Point pt)
{
	tie = pt;
	has_tie = true;
}

void ch14_e17::Node::cut_tie()
{
	has_tie = false;
}

Graph_lib::Font ch14_e17::Node::font() const
{
	return node_font();
}

int ch14_e17::Node::font_size() const
{
	return static_cast<int>(std::round(h * font_size_factor));
}

//------------------------------------------------------------------------------

void ch14_e17::Node::draw_lines() const
{

	BOX::Box::draw_lines();

	if (!color().visibility()) {
		return;
	}

	if (has_tie) {
		box_hlp::PtID dir = best_aligned_direction(*this, tie);
		if (dir != box_hlp::PtID::C) {
			Graph_lib::Point conn_pt{box_hlp::get(*this, dir)};
			draw_arrow(tie, conn_pt, h / 2);
		}
	}

	int ofnt = fl_font();
	int osz = fl_size();
	fl_font(font().as_int(), font_size());

	draw_label({static_cast<int>(std::round(
	                bbox_origin().x + h * width_padding_from_height_factor)),
	            static_cast<int>(std::round(
	                bbox_origin().y + 0.5 * h * (1 + font_size_factor)))},
	           lb);

	fl_font(ofnt, osz);

	if (has_sym) {
		int sym_h = static_cast<int>(std::round(h * 0.4));
		int sym_offs = static_cast<int>(std::round(sym_h * 0.3));
		draw_symbol({bbox_origin().x + width(), bbox_origin().y + h + sym_offs},
		            sym_h,
		            color(),
		            fill_color());
	}
}

bool ch14_e17::Node::point_is_on_node(Graph_lib::Point pt) const
{
	int r = static_cast<int>(std::round(corner_radius()));
	Graph_lib::Point o = bbox_origin();

	if (pt.x < o.x || pt.x > o.x + width() || pt.y < o.y
	    || pt.y > o.y + height()) {
		return false;
	}

	Graph_lib::Point nw = {o.x + r, o.y + r};
	Graph_lib::Point ne = {o.x + width() - r, nw.y};
	Graph_lib::Point sw = {nw.x, o.y + height() - r};
	Graph_lib::Point se = {ne.x, sw.y};
	if (((pt.x > nw.x && pt.x < ne.x) && (pt.y >= o.y || pt.y <= o.y + height()))
	    || ((pt.x >= o.x && pt.x <= o.x + width())
	        && (pt.y > nw.y && pt.y > sw.y))) {
		return true;
	}

	if (ch14_hlp::distance_between(pt, nw) <= corner_radius()) {
		return true;
	}
	if (ch14_hlp::distance_between(pt, ne) <= corner_radius()) {
		return true;
	}
	if (ch14_hlp::distance_between(pt, se) <= corner_radius()) {
		return true;
	}
	if (ch14_hlp::distance_between(pt, sw) <= corner_radius()) {
		return true;
	}
	return false;
}

//------------------------------------------------------------------------------

void ch14_e17::Node::draw_label(Graph_lib::Point pos, const string& s)
{
	fl_draw(s.c_str(), pos.x, pos.y - fl_descent());
};

void ch14_e17::Node::draw_arrow(Graph_lib::Point start,
                                Graph_lib::Point end,
                                int head_size)
{
	fl_line(start.x, start.y, end.x, end.y);
	draw_arrow_head(start, end, head_size);
}

void ch14_e17::Node::draw_arrow_head(Graph_lib::Point start,
                                     Graph_lib::Point end,
                                     int head_size)
{
	float line_angle = static_cast<float>(
	    std::atan2(end.y - start.y, end.x - start.x));
	constexpr float head_angle{0.4f};
	fl_begin_complex_polygon();
	fl_vertex(std::round(end.x - head_size * std::cos(line_angle + head_angle)),
	          std::round(end.y - head_size * std::sin(line_angle + head_angle)));
	fl_vertex(end.x, end.y);
	fl_vertex(std::round(end.x - head_size * std::cos(line_angle - head_angle)),
	          std::round(end.y - head_size * std::sin(line_angle - head_angle)));
	fl_end_complex_polygon();
}

void ch14_e17::Node::draw_symbol(Graph_lib::Point origin,
                                 int height,
                                 Graph_lib::Color bg_color,
                                 Graph_lib::Color fg_color)
{
	// Note that origin is the bottom right corner
	int mid_h = static_cast<int>(std::round(height * 0.5));
	int new_h = 2 * mid_h;
	int w_div = static_cast<int>(std::round(new_h * 2.5 / 4));
	int new_w = w_div * 4;
	int sym_r = static_cast<int>(std::floor(w_div * 0.4));
	Graph_lib::Color oc = fl_color();

	// Background
	fl_color(bg_color.as_int());
	fl_begin_polygon();
	fl_vertex(origin.x - new_w, origin.y - new_h);
	fl_vertex(origin.x, origin.y - new_h);
	fl_vertex(origin.x, origin.y);
	fl_vertex(origin.x - new_w, origin.y);
	fl_end_polygon();

	// Symbol(s)
	fl_color(fg_color.as_int());
	for (int i = 1; i <= 3; ++i) {
		fl_circle(origin.x - w_div * i, origin.y - mid_h, sym_r);
	}

	fl_color(oc.as_int());
}

//------------------------------------------------------------------------------

int ch14_e17::Node::calc_lb_width(const string& s,
                                  Graph_lib::Font font,
                                  int font_size)
{
	if (s.empty()) {
		return 0;
	}

	// Calculate the label width with the given font and font size
	int dummy; // not needed
	int w;
	int font_backup = fl_font();
	int size_backup = fl_size();
	fl_font(font.as_int(), font_size);
	fl_text_extents(s.c_str(), dummy, dummy, w, dummy);
	fl_font(font_backup, size_backup);
	return w;
}

constexpr int ch14_e17::Node::valid_h(const int hh) const
{
	if (hh < min_height || hh > max_height) {
		throw std::invalid_argument("Height must be in range: "
		                            + std::to_string(min_height) + " to "
		                            + std::to_string(max_height));
	}
	return hh;
}

//------------------------------------------------------------------------------

box_hlp::PtID ch14_e17::best_aligned_direction(const Node& node,
                                               Graph_lib::Point tied_pt)
{
	Graph_lib::Point node_o = node.bbox_origin();
	int node_w = node.width();
	int node_half_w = static_cast<int>(std::round(node_w * 0.5));
	int node_h = node.height();
	int node_half_h = static_cast<int>(std::round(node_h * 0.5));
	Graph_lib::Point node_c = {node_o.x + node_half_w, node_o.y + node_half_h};

	bool tied_is_within_x_bnds{
	    (tied_pt.x >= node_o.x && tied_pt.x <= node_o.x + node_w)};
	bool tied_is_within_y_bnds{
	    (tied_pt.y >= node_o.y && tied_pt.y <= node_o.y + node_h)};

	box_hlp::PtID dir = box_hlp::PtID::C;
	if (tied_is_within_y_bnds) {
		if (tied_is_within_x_bnds) {
			dir = (tied_pt.x < node_c.x) ? box_hlp::PtID::W : box_hlp::PtID::E;
		}
	} else {
		bool tied_is_above = (tied_pt.y < node_c.y);
		double tied_a = std::atan2(tied_pt.y - node_c.y, tied_pt.x - node_c.x);

		double x_delta = 0;
		if (tied_is_within_x_bnds) {
			x_delta = tied_pt.x - node_c.x;
		} else {
			x_delta = tied_is_above ? -node_half_h / std::tan(tied_a)
			                        : node_half_h / std::tan(tied_a);
		}
		double corner_x_threshold = node_half_w * 0.75;

		if (x_delta < -corner_x_threshold) {
			dir = tied_is_above ? box_hlp::PtID::NW : box_hlp::PtID::SW;
		} else if (x_delta > corner_x_threshold) {
			dir = tied_is_above ? box_hlp::PtID::NE : box_hlp::PtID::SE;
		} else {
			dir = tied_is_above ? box_hlp::PtID::N : box_hlp::PtID::S;
		}
	}

	return dir;
}
