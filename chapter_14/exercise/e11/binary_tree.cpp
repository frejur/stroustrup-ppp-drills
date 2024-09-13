#include "binary_tree.h"
#include <cmath>

namespace {
constexpr int max_node_level{10};
constexpr int minimum_node_height{8};
constexpr int maximum_node_height{32};
constexpr int minimum_min_node_padding{2};
constexpr int maximum_min_node_padding{32};
constexpr int node_label_max_length{16};
} // namespace

void ch14_e11::Binary_tree::move(int offset_x, int offset_y)
{
	Graph_lib::Shape::move(offset_x, offset_y);
	for (int i = 0; i < nodes.size(); ++i) {
		nodes[i].move(offset_x, offset_y);
	}
}

void ch14_e11::Binary_tree::draw_lines() const
{
	for (int i = 0; i < nodes.size(); ++i) {
		dynamic_cast<const Circle_node&>(nodes[i]).draw_lines();
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

void ch14_e11::Binary_tree::add_nodes()
{
	// TODO: Add nodes
	int lv_num_nodes = 1;
	int y = 0;
	int max_w = std::pow(2, lv - 1) * node_h * 4;
	for (int i = 1; i <= lv; ++i) {
		int x_incr = max_w / std::pow(2, i);
		int x = -x_incr * lv_num_nodes / 2 - x_incr / 2;
		for (int n = 0; n < lv_num_nodes; ++n) {
			x += x_incr;
			nodes.push_back(new Circle_node{{x, y}, node_h, fnt_sz});
		}
		y += node_h * 2;
		lv_num_nodes *= 2;
	}
	move(point(0).x, point(0).y);
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

int ch14_e11::Binary_tree::calc_font_size(int height) const
{
	// Calculate the font size that fits within the given height
	int size = 1;
	int dummy; // not needed
	int y_pos = 0, y_neg = 0;
	int font_backup = fl_font();
	int size_backup = fl_size();
	const std::string test_str{"Ag"};
	do {
		fl_font(fnt.as_int(), size);
		fl_text_extents(test_str.c_str(),
		                test_str.size(),
		                dummy,
		                dummy,
		                y_pos,
		                y_neg);
	} while (y_pos + y_neg < height);
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

void ch14_e11::Circle_node::draw_lines() const
{
	Graph_lib::Ellipse::draw_lines();
}

int ch14_e11::Circle_node::calc_lb_width(const string& s, int font_size) const
{
	if (s.empty()) {
		return 0;
	}

	// Calculate the label width with the given font and font size
	int dummy; // not needed
	int x_pos = 0, x_neg = 0;
	int font_backup = fl_font();
	int size_backup = fl_size();
	fl_font(fnt.as_int(), font_size);
	fl_text_extents(lb.c_str(), lb.size(), x_neg, x_pos, dummy, dummy);
	fl_font(font_backup, size_backup);
	return x_pos + x_neg;
}
