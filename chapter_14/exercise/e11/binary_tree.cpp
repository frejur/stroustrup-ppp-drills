#include "binary_tree.h"
#include "../share/help/helpers.h"
#include <cmath>

namespace GL = Graph_lib;

namespace {
constexpr int max_node_level{10};
constexpr int minimum_node_height{8};
constexpr int maximum_node_height{32};
constexpr int minimum_min_node_padding{2};
constexpr int maximum_min_node_padding{32};
constexpr int node_label_max_length{16};
} // namespace

void draw_label(GL::Point pos, const std::string& s)
{
	fl_draw(s.c_str(), pos.x, pos.y - fl_descent());
}

//------------------------------------------------------------------------------

void ch14_e11::Binary_tree::draw_arrow(GL::Point start,
                                       GL::Point end,
                                       int head_size) const
{
	fl_line(start.x, start.y, end.x, end.y);
	draw_arrow_head(start, end, head_size);
}

void ch14_e11::Binary_tree::draw_arrow_head(GL::Point start,
                                            GL::Point end,
                                            int head_size) const
{
	float line_angle = std::atan2(end.y - start.y, end.x - start.x);
	constexpr float head_angle{0.4};
	fl_begin_complex_polygon();
	fl_vertex(std::round(end.x - head_size * std::cos(line_angle + head_angle)),
	          std::round(end.y - head_size * std::sin(line_angle + head_angle)));
	fl_vertex(end.x, end.y);
	fl_vertex(std::round(end.x - head_size * std::cos(line_angle - head_angle)),
	          std::round(end.y - head_size * std::sin(line_angle - head_angle)));
	fl_end_complex_polygon();
}

void ch14_e11::Binary_tree::draw_lines() const
{
	int ofnt = fl_font();
	int osz = fl_size();
	fl_font(font().as_int(), font_size());

	for (int i = 0; i < nodes.size(); ++i) {
		GL::Point curr_pos = node_position(i);
		int curr_w = node_width(i);
		if (i > 0) {
			// Draw line
			int par_w = node_width(parent_index(i));
			GL::Point start = node_position(parent_index(i));
			start.y += node_height() / 2;
			start.x += is_l_child(i) ? -par_w / 4 : par_w / 4;
			GL::Point end = curr_pos;
			end.y -= node_height() / 2;

			if (ln_t == Line_type::Down_arrow) {
				draw_arrow(start, end, node_height() / 2);
			} else if (ln_t == Line_type::Up_arrow) {
				draw_arrow(end, start, node_height() / 2);
			} else {
				fl_line(start.x, start.y, end.x, end.y);
			}
		}
		draw_node(i);
		draw_label({curr_pos.x
		                - static_cast<int>(
		                    std::round(std::round(curr_w * 0.5) - label_pad())),
		            curr_pos.y
		                + static_cast<int>(std::round(node_height() * 0.3))},
		           labels[i]);
	}

	fl_font(ofnt, osz);
}

//------------------------------------------------------------------------------
// Virtual getters, Circle

int ch14_e11::Circle_binary_tree::node_width(int n) const
{
	return dynamic_cast<const GL::Ellipse&>(nodes[valid_index(n)]).major() * 2;
}

GL::Point ch14_e11::Circle_binary_tree::node_position(int n) const
{
	return dynamic_cast<const GL::Ellipse&>(nodes[valid_index(n)]).center();
}
//------------------------------------------------------------------------------
// Misc. virtual functions, Circle

void ch14_e11::Circle_binary_tree::draw_node(int index) const
{
	dynamic_cast<const GL::Ellipse&>(nodes[index]).draw_lines();
}

void ch14_e11::Circle_binary_tree::add_node(int y, int height)
{
	nodes.push_back(new GL::Ellipse({0, y}, height / 2, height / 2));
}

bool ch14_e11::Circle_binary_tree::point_is_on_node(GL::Point pt,
                                                    int index) const
{
	const GL::Ellipse& e = dynamic_cast<const GL::Ellipse&>(nodes[index]);
	double x = (pt.x - e.center().x) / (double) e.major();
	double y = (pt.y - e.center().y) / (double) e.minor();
	return (x * x + y * y) <= 1;
}

void ch14_e11::Circle_binary_tree::upd_node_w(int index)
{
	GL::Ellipse& e = dynamic_cast<GL::Ellipse&>(nodes[index]);
	e.set_major((std::max)(e.minor(),
	                       static_cast<int>(
	                           calc_lb_width(labels[index], font(), font_size()))
	                               / 2
	                           + label_pad()));
}

//------------------------------------------------------------------------------
// Virtual getters, Box

int ch14_e11::Box_binary_tree::node_width(int n) const
{
	return dynamic_cast<const BOX::Box&>(nodes[valid_index(n)]).width();
}

GL::Point ch14_e11::Box_binary_tree::node_position(int n) const
{
	const BOX::Box& b = dynamic_cast<const BOX::Box&>(nodes[valid_index(n)]);
	return {b.bbox_origin().x + b.width() / 2,
	        b.bbox_origin().y + node_height() / 2};
}
//------------------------------------------------------------------------------
// Misc. virtual functions, Box

void ch14_e11::Box_binary_tree::draw_node(int index) const
{
	dynamic_cast<const BOX::Box&>(nodes[index]).draw_lines();
}

void ch14_e11::Box_binary_tree::add_node(int y, int height)
{
	nodes.push_back(
	    new BOX::Box({-height / 2, y - height / 2}, height, height, 0.7));
}

bool ch14_e11::Box_binary_tree::point_is_on_node(GL::Point pt, int index) const
{
	const BOX::Box& e = dynamic_cast<const BOX::Box&>(nodes[index]);
	int r = e.corner_radius();
	Graph_lib::Point o = e.bbox_origin();

	if (pt.x < o.x || pt.x > o.x + e.width() || pt.y < o.y
	    || pt.y > o.y + e.height()) {
		return false;
	}

	Graph_lib::Point nw = {o.x + r, o.y + r};
	Graph_lib::Point ne = {o.x + e.width() - r, nw.y};
	Graph_lib::Point sw = {nw.x, o.y + e.height() - r};
	Graph_lib::Point se = {ne.x, sw.y};
	if (((pt.x > nw.x && pt.x < ne.x)
	     && (pt.y >= o.y || pt.y <= o.y + e.height()))
	    || ((pt.x >= o.x && pt.x <= o.x + e.width())
	        && (pt.y > nw.y && pt.y > sw.y))) {
		return true;
	}

	if (ch14_hlp::distance_between(pt, nw) <= e.corner_radius()) {
		return true;
	}
	if (ch14_hlp::distance_between(pt, ne) <= e.corner_radius()) {
		return true;
	}
	if (ch14_hlp::distance_between(pt, se) <= e.corner_radius()) {
		return true;
	}
	if (ch14_hlp::distance_between(pt, sw) <= e.corner_radius()) {
		return true;
	}
	return false;
}

void ch14_e11::Box_binary_tree::upd_node_w(int index)
{
	BOX::Box& e = dynamic_cast<BOX::Box&>(nodes[index]);
	int old_w = e.width();
	e.updateSize((std::max)(node_height(),
	                        static_cast<int>(
	                            std::round(calc_lb_width(labels[index],
	                                                     font(),
	                                                     font_size())))
	                            + label_pad() * 2),
	             node_height());
	int new_w = e.width();
	e.move(-(new_w - old_w) / 2, 0);
}

//------------------------------------------------------------------------------

void ch14_e11::Binary_tree::move(int offset_x, int offset_y)
{
	GL::Shape::move(offset_x, offset_y);
	for (int i = 0; i < nodes.size(); ++i) {
		nodes[i].move(offset_x, offset_y);
	}
}

void ch14_e11::Binary_tree::move_sub_tree(const int parent,
                                          int offset_x,
                                          int offset_y)
{
	if (parent == 0) {
		move(offset_x, offset_y);
		return;
	}
	int node = valid_index(parent);
	nodes[node].move(offset_x, offset_y);

	if (!is_leaf_node(node)) {
		move_sub_tree(l_child_index(node), offset_x, offset_y);
		move_sub_tree(r_child_index(node), offset_x, offset_y);
	}
}

//------------------------------------------------------------------------------

void ch14_e11::Binary_tree::set_label(const string& address,
                                      const string& new_txt)
{
	int idx = valid_index(address_to_index(address));
	labels[idx] = new_txt;
	upd_node_w(idx);
	upd_nodes_x_pos();
}

int ch14_e11::Binary_tree::find_node_at_point(GL::Point pt) const
{
	int found = -1;
	for (int i = 0; i < nodes.size(); ++i) {
		if (point_is_on_node(pt, i)) {
			found = i;
			break;
		}
	}
	return found;
}

void ch14_e11::Binary_tree::add_nodes()
{
	int lv_num_nodes = 1;
	int y = 0;
	for (int i = 1; i <= levels(); ++i) {
		for (int n = 0; n < lv_num_nodes; ++n) {
			add_node(y, node_height());
			nodes[nodes.size() - 1].set_color(GL::Color::black);
			nodes[nodes.size() - 1].set_fill_color(GL::Color::invisible);
		}
		lv_num_nodes *= 2;
		y += node_height() * 3;
	}
	move(point(0).x, point(0).y);
	upd_nodes_x_pos();
}

void ch14_e11::Binary_tree::upd_nodes_x_pos()
{
	int start_node{number_of_nodes()};
	int lv_num_nodes = (num_nodes + 1) / 2;
	for (int i = levels(); i > 1; --i) {
		start_node -= lv_num_nodes;
		for (int j = 0; j < lv_num_nodes; j += 2) {
			int n = start_node + j;
			int width_l{sub_tree_width(n)};
			int width_r{sub_tree_width(n + 1)};
			int par_idx = parent_index(n);
			int par_x{node_position(par_idx).x};
			int offs_x_l{width_l / 2 + min_node_padding() / 2};
			int offs_x_r{width_r / 2 + min_node_padding() / 2};
			int offs_x = (std::max)(offs_x_l, offs_x_r);
			move_sub_tree(n, (par_x - offs_x) - node_position(n).x, 0);
			move_sub_tree(n + 1, (par_x + offs_x) - node_position(n + 1).x, 0);
		}
		lv_num_nodes /= 2;
	}
}

int ch14_e11::Binary_tree::sub_tree_min_x(int n) const
{
	int start = valid_index(n);
	int min_x = node_position(start).x - node_width(start) / 2;
	if (!is_leaf_node(start)) {
		return (std::min)(min_x, sub_tree_min_x(l_child_index(start)));
	}
	return min_x;
}

int ch14_e11::Binary_tree::sub_tree_max_x(int n) const
{
	int start = valid_index(n);
	int max_x = node_position(start).x + node_width(start) / 2;
	if (!is_leaf_node(start)) {
		return (std::max)(max_x, sub_tree_max_x(r_child_index(start)));
	}
	return max_x;
}

int ch14_e11::Binary_tree::sub_tree_width(int n) const
{
	int min_x = sub_tree_min_x(n);
	int max_x = sub_tree_max_x(n);
	int mid_x = node_position(n).x;
	int min_w = mid_x - min_x;
	int max_w = max_x - mid_x;
	return (std::max)(min_w, max_w) * 2;
}

int ch14_e11::Binary_tree::parent_index(int index) const
{
	if (index == 0) {
		throw std::runtime_error("Root has no parent");
	}
	return (index - 1) / 2;
}

int ch14_e11::Binary_tree::address_to_index(const string& address) const
{
	if (address.size() == 0) {
		throw std::runtime_error("Address is empty");
	}
	int idx = 0;
	for (int i = 0; i < address.size(); ++i) {
		const char c{address[i]};
		if (i == 0 && (c == 'l' || c == 'r')) {
			continue; // root
		}
		if (c == 'l') {
			idx = l_child_index(idx);
		} else if (c == 'r') {
			idx = r_child_index(idx);
		} else {
			throw std::runtime_error("Invalid char in address: "
			                         + std::to_string('\'' + c + '\''));
		}
	}
	return idx;
}

std::string ch14_e11::Binary_tree::index_to_address(int index) const
{
	std::string address;
	while (index >= 0) {
		address = (is_l_child(index) ? 'l' : 'r') + address;
		if (index == 0) {
			break;
		}
		index = parent_index(index);
	}
	return address;
}

int ch14_e11::Binary_tree::calc_font_size(int height) const
{
	// Calculate the font size that fits within the given height
	int padded_h = static_cast<int>(height * 0.7);
	int size = 1;
	int dummy; // not needed
	int y_pos = 0, y_neg = 0;
	int font_backup = fl_font();
	int size_backup = fl_size();
	const std::string test_str{"Ag"};
	do {
		fl_font(font().as_int(), size);
		fl_text_extents(test_str.c_str(),
		                test_str.size(),
		                dummy,
		                dummy,
		                y_pos,
		                y_neg);
		++size;
	} while (y_pos + y_neg < padded_h);
	fl_font(font_backup, size_backup);
	return y_pos + y_neg;
}

int ch14_e11::Binary_tree::node_level(int n) const
{
	return static_cast<int>(std::log2(n + 1));
}

bool ch14_e11::Binary_tree::is_leaf_node(int n) const
{
	return index_is_valid(n) && !index_is_valid(l_child_index(n));
}

bool ch14_e11::Binary_tree::index_is_valid(int i) const
{
	return (0 <= i && i < num_nodes);
}

bool ch14_e11::Binary_tree::is_lmost(int i) const
{
	++i;
	return (i) && (std::log2(i) == static_cast<int>(std::log2(i)));
}

bool ch14_e11::Binary_tree::is_rmost(int i) const
{
	return is_lmost(++i);
}

int ch14_e11::Binary_tree::valid_index(int i) const
{
	if (!index_is_valid(i)) {
		throw std::runtime_error("Invalid node index");
	}
	return i;
}

int ch14_e11::Binary_tree::valid_level(int l) const
{
	if (0 > l || l > max_node_level) {
		throw std::runtime_error("Invalid node level, expected a value between "
		                         "0 and "
		                         + std::to_string(max_node_level));
	}
	return l;
}

int ch14_e11::Binary_tree::valid_node_h(int h) const
{
	if (h < minimum_node_height || h > maximum_node_height) {
		throw std::runtime_error(
		    "Invalid node height, expected a value between "
		    + std::to_string(minimum_node_height) + " and "
		    + std::to_string(maximum_node_height));
	}
	return h;
}

int ch14_e11::Binary_tree::valid_node_pad(int p) const
{
	if (p < minimum_min_node_padding || p > maximum_min_node_padding) {
		throw std::runtime_error(
		    "Invalid node padding value, expected a value between "
		    + std::to_string(minimum_min_node_padding) + " and "
		    + std::to_string(maximum_min_node_padding));
	}
	return p;
}
int ch14_e11::Binary_tree::calc_lb_width(const string& s,
                                         GL::Font font,
                                         int font_size) const
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
