#define _USE_MATH_DEFINES
#include "shp_distr.h"
#include <cmath>

//------------------------------------------------------------------------------

bool ch14_e17::is_sentinel(const Graph_lib::Shape& s)
{
	return &s == &Shape_distributor::sentinel();
}

//------------------------------------------------------------------------------

void ch14_e17::Shape_distributor::move(int offs_x, int offs_y)
{
	o.x += offs_x;
	o.y += offs_y;
	for (int i = 0; i < shp.size(); ++i) {
		shp[i].move(offs_x, offs_y);
	}
}

void ch14_e17::Shape_distributor::move_element(int offs_x,
                                               int offs_y,
                                               const Graph_lib::Shape& shape)
{
	if (is_sentinel(shape)) {
		return;
	}
	move_shape(offs_x, offs_y, find_element(shape));
}

const Graph_lib::Shape& ch14_e17::Shape_distributor::element_at_point(
    Graph_lib::Point point) const
{
	int match = find_element_at_pt(point);
	if (match == -1) {
		return sentinel();
	}
	return shp[match];
}

const Graph_lib::Shape& ch14_e17::Shape_distributor::leftmost_element() const
{
	if (shp.size() == 0) {
		return sentinel();
	}

	return get_shp(shp_order[0]);
}

const Graph_lib::Shape& ch14_e17::Shape_distributor::rightmost_element() const
{
	if (shp.size() == 0) {
		return sentinel();
	}

	return get_shp(shp_order[shp_order.size() - 1]);
}

const Graph_lib::Shape& ch14_e17::Shape_distributor::element_below(
    const Graph_lib::Shape& element) const
{
	if (shp.size() < 3) {
		return sentinel();
	}

	int index = ordered_index(find_element(element));
	if (in_middle(index)) {
		return sentinel();
	}

	if (index < shp.size() / 2) {
		return get_shp(shp_order[index + 1]);
	} else {
		return get_shp(shp_order[index - 1]);
	}
}

const Graph_lib::Shape& ch14_e17::Shape_distributor::element_left_of(
    const Graph_lib::Shape& element) const
{
	if (shp.size() == 0) {
		return sentinel();
	}

	int index = ordered_index(find_element(element));
	if (at_far_left(index)) {
		return sentinel();
	}

	return get_shp(shp_order[index - 1]);
}

const Graph_lib::Shape& ch14_e17::Shape_distributor::element_right_of(
    const Graph_lib::Shape& element) const
{
	if (shp.size() == 0) {
		return sentinel();
	}

	int index = ordered_index(find_element(element));
	if (at_far_right(index)) {
		return sentinel();
	}

	return get_shp(shp_order[index + 1]);
}

//------------------------------------------------------------------------------

void ch14_e17::Shape_distributor::distribute()
{
	if (shp.size() == 0) {
		return;
	}
	int mid_count = (shp.size() % 2 == 0) ? 2 : 1;
	int side_count = (shp.size() - mid_count) / 2;

	int left_w = 0;
	int right_w = 0;
	std::vector<int> height;
	int level_y = 0;
	for (int i = 0; i < side_count; ++i) {
		int l_idx = shp_order[i];
		int r_idx = shp_order[shp.size() - 1 - i];
		if (i == 0) {
			left_w += shape_width(l_idx);
			right_w += shape_width(r_idx);
		} else {
			left_w += std::round(shape_width(l_idx) * 0.5);
			right_w += std::round(shape_width(r_idx) * 0.5);
		}
		int curr_h = (std::max)(shape_height(l_idx), shape_height(r_idx));
		move_shape(0,
		           level_y + (curr_h - shape_height(l_idx)) / 2
		               - shape_origin(l_idx).y,
		           l_idx);
		move_shape(0,
		           level_y + (curr_h - shape_height(r_idx)) / 2
		               - shape_origin(r_idx).y,
		           r_idx);
		level_y += curr_h + v_space;
	}

	int btm_y = level_y;
	int max_w = (std::max)(left_w, right_w);
	int w_diff = std::abs(left_w - right_w);
	int h_space = v_space;

	for (int j = 0; j < mid_count; ++j) {
		int mid_idx = shp_order[side_count + j];
		int offs_x = (mid_count > 1)
		                 ? shape_width(mid_idx) + std::round(h_space * 0.5)
		                 : std::round(shape_width(mid_idx) * 0.5);
		if (j == 0) {
			move_shape(-offs_x - shape_origin(mid_idx).x,
			           btm_y - shape_origin(mid_idx).y,
			           mid_idx);
		} else {
			move_shape(std::round(h_space * 0.5) - shape_origin(mid_idx).x,
			           btm_y - shape_origin(mid_idx).y,
			           mid_idx);
		}
	}

	int l_mid_w = 0;
	int r_mid_w = 0;
	if (mid_count == 1) {
		l_mid_w = std::abs(shape_origin(shp_order[side_count]).x);
		r_mid_w = -l_mid_w + +shape_width(shp_order[side_count]);
	} else {
		l_mid_w = std::abs(shape_origin(shp_order[side_count]).x);
		r_mid_w = std::round(0.5 * h_space)
		          + + +shape_width(shp_order[side_count + 1]);
	}

	int w_diff_left = w_diff;
	int w_diff_unit = std::round(w_diff / (side_count - 1.f));

	int l_x_pos = -max_w - l_mid_w;
	for (int k = 0; k < side_count; ++k) {
		int l_idx = shp_order[k];
		if (k > 0) {
			int prev_idx = shp_order[k - 1];
			l_x_pos += shape_width(prev_idx)
			           - std::round(shape_width(l_idx) * 0.5);
			if ((left_w < right_w) && (w_diff_left > 0)) {
				l_x_pos += (w_diff_left < w_diff_unit) ? w_diff_left
				                                       : w_diff_unit;
				w_diff_left -= w_diff_unit;
			}
		}
		move_shape(l_x_pos - shape_origin(l_idx).x, 0, l_idx);
	}

	int r_x_pos = max_w - shape_width(shp_order[shp_order.size() - 1])
	              + r_mid_w;
	for (int l = 0; l < side_count; ++l) {
		int r_idx = shp_order[shp.size() - 1 - l];
		if (l > 0) {
			r_x_pos -= std::round(shape_width(r_idx) * 0.5);
			if ((right_w <= left_w) && (w_diff_left > 0)) {
				r_x_pos -= (w_diff_left < w_diff_unit) ? w_diff_left
				                                       : w_diff_unit;
				w_diff_left -= w_diff_unit;
			}
		}
		move_shape(r_x_pos - shape_origin(r_idx).x, 0, r_idx);
	}

	int offs_y = (left_w < right_w)
	                 ? offset_to_align_with_angle(Alignment_side::Left)
	                 : offset_to_align_with_angle(Alignment_side::Right);

	for (int s = 0; s < shp.size(); ++s) {
		move_shape(origin().x, origin().y + offs_y, shp_order[s]);
	}
}

void ch14_e17::Shape_distributor::sort_by_w_asc()
{
	for (int i = 0; i < shp_order.size(); ++i) {
		int min_w = shape_width(shp_order[i]);
		int min_idx = -1;
		for (int j = i + 1; j < shp_order.size(); ++j) {
			if (shape_width(shp_order[j]) <= min_w) {
				min_w = shape_width(shp_order[j]);
				min_idx = j;
			}
		}
		if (min_idx != -1) {
			swap(i, min_idx);
		}
	}
}

void ch14_e17::Shape_distributor::sort_by_w_desc()
{
	for (int i = 0; i < shp_order.size(); ++i) {
		int max_w = shape_width(shp_order[i]);
		int max_idx = -1;
		for (int j = i + 1; j < shp_order.size(); ++j) {
			if (shape_width(shp_order[j]) >= max_w) {
				max_w = shape_width(shp_order[j]);
				max_idx = j;
			}
		}
		if (max_idx != -1) {
			swap(i, max_idx);
		}
	}
}
void ch14_e17::Shape_distributor::sort(bool reverse)
{
	if (shp.size() == 0) {
		return;
	}

	// Sort by width
	if (!reverse) {
		sort_by_w_asc();
	} else {
		sort_by_w_desc();
	}

	// Rearrange, depending on the sorting order in the previous step,
	// put all the widest / smallest shapes along the sides and
	// increment / shrink towards the middle.
	std::vector<int> rearranged;

	int offset = 0;
	if (shp_order.size() % 2 == 1) {
		rearranged.push_back(shp_order[shp_order.size() - 1]);
		offset = 1;
	}
	for (int j = 0; j < shp_order.size() / 2; ++j) {
		rearranged.push_back(
		    shp_order[shp_order.size() - 1 - offset * 2 - j * 2]);
	}

	for (int k = 0; k < (shp_order.size() - offset) / 2; ++k) {
		rearranged.push_back(shp_order[offset + k * 2]);
	}

	for (int l = 0; l < shp_order.size(); ++l) {
		shp_order[l] = rearranged[l];
	}
}

Graph_lib::Point ch14_e17::Shape_distributor::element_origin(
    const Graph_lib::Shape& s) const
{
	int match = find_element(s);
	if (match == -1) {
		throw std::runtime_error("The given element could not be found");
	}

	return shape_origin(match);
}

int ch14_e17::Shape_distributor::element_width(const Graph_lib::Shape& s) const
{
	int match = find_element(s);
	if (match == -1) {
		throw std::runtime_error("The given element could not be found");
	}

	return shape_width(match);
}

int ch14_e17::Shape_distributor::element_height(const Graph_lib::Shape& s) const
{
	int match = find_element(s);
	if (match == -1) {
		throw std::runtime_error("The given element could not be found");
	}

	return shape_height(match);
}

void ch14_e17::Shape_distributor::place_in_middle(
    const Graph_lib::Shape& element_to_move)
{
	if (is_sentinel(element_to_move)) {
		return;
	}
	if (shp.size() < 3) {
		return;
	}
	change_place(element_to_move,
	             get_shp(shp_order[(number_of_elements() - 1) / 2]));
}

void ch14_e17::Shape_distributor::set_color(Graph_lib::Color color)
{
	for (int i = 0; i < number_of_elements(); ++i) {
		shp[i].set_color(color);
	}
}

void ch14_e17::Shape_distributor::set_fill_color(Graph_lib::Color color)
{
	for (int i = 0; i < number_of_elements(); ++i) {
		shp[i].set_fill_color(color);
	}
}

void ch14_e17::Shape_distributor::set_color_of_element(
    Graph_lib::Color color, const Graph_lib::Shape& element)
{
	if (is_sentinel(element)) {
		return;
	}
	int match = find_element(element);
	if (match == -1) {
		throw std::runtime_error("The given element could not be found");
	}
	shp[match].set_color(color);
}

void ch14_e17::Shape_distributor::set_fill_color_of_element(
    Graph_lib::Color color, const Graph_lib::Shape& element)
{
	if (is_sentinel(element)) {
		return;
	}
	int match = find_element(element);
	if (match == -1) {
		throw std::runtime_error("The given element could not be found");
	}
	shp[match].set_fill_color(color);
}

bool ch14_e17::Shape_distributor::element_is_visible(
    const Graph_lib::Shape& element) const
{
	if (is_sentinel(element)) {
		return false;
	}
	int match = find_element(element);
	if (match == -1) {
		throw std::runtime_error("The given element could not be found");
	}
	Graph_lib::Color c = shp[match].color();
	Graph_lib::Color fc = shp[match].fill_color();
	return (c.visibility() || fc.visibility());
}

void ch14_e17::Shape_distributor::hide_element(const Graph_lib::Shape& element)
{
	if (is_sentinel(element)) {
		return;
	}
	int match = find_element(element);
	if (match == -1) {
		throw std::runtime_error("The given element could not be found");
	}
	Graph_lib::Color c = shp[match].color();
	Graph_lib::Color fc = shp[match].fill_color();
	if (c.visibility()) {
		c.set_visibility(Graph_lib::Color::Transparency::invisible);
		shp[match].set_color(c);
	}
	if (fc.visibility()) {
		fc.set_visibility(Graph_lib::Color::Transparency::invisible);
		shp[match].set_fill_color(fc);
	}
}

void ch14_e17::Shape_distributor::show_element(const Graph_lib::Shape& element)
{
	if (is_sentinel(element)) {
		return;
	}
	int match = find_element(element);
	if (match == -1) {
		throw std::runtime_error("The given element could not be found");
	}
	Graph_lib::Color c = shp[match].color();
	Graph_lib::Color fc = shp[match].fill_color();
	if (!c.visibility()) {
		c.set_visibility(Graph_lib::Color::Transparency::visible);
		shp[match].set_color(c);
	}
	if (!fc.visibility()) {
		fc.set_visibility(Graph_lib::Color::Transparency::visible);
		shp[match].set_fill_color(fc);
	}
}

void ch14_e17::Shape_distributor::change_place(const Graph_lib::Shape& to_move,
                                               const Graph_lib::Shape& to_shift)
{
	if (is_sentinel(to_move) || is_sentinel(to_shift)) {
		return;
	}
	int a_idx = ordered_index(find_element(to_move));
	int b_idx = ordered_index(find_element(to_shift));

	if (a_idx == b_idx) {
		return;
	}

	if (std::abs(a_idx - b_idx) == 1) {
		swap(a_idx, b_idx);
		return;
	}

	if (b_idx < a_idx) {
		for (int i = 0; i < a_idx - b_idx; ++i) {
			swap(a_idx - i, a_idx - i - 1);
		}
	} else {
		for (int i = 0; i < b_idx - a_idx; ++i) {
			swap(a_idx + i, a_idx + i + 1);
		}
	}
}

void ch14_e17::Shape_distributor::swap(int a_idx, int b_idx)
{
	a_idx = valid_idx(a_idx);
	b_idx = valid_idx(b_idx);
	int tmp = shp_order[a_idx];
	shp_order[a_idx] = shp_order[b_idx];
	shp_order[b_idx] = tmp;
}
void ch14_e17::Shape_distributor::move_shape(int offs_x, int offs_y, int index)
{
	if (index == -1) {
		return;
	}
	shp[valid_idx(index)].move(offs_x, offs_y);
}

bool ch14_e17::Shape_distributor::in_middle(int ordered_index) const
{
	if (shp_order.size() == 0) {
		return false;
	}
	if (shp_order.size() <= 2) {
		return true;
	} else if (shp_order.size() % 2 == 0) {
		return (ordered_index == shp_order.size() / 2)
		       || (ordered_index == shp_order.size() / 2 + 1);
	} else {
		return ordered_index == shp_order.size() / 2;
	}
	return false;
}

bool ch14_e17::Shape_distributor::at_far_left(int ordered_index) const
{
	return (shp.size() > 0 && ordered_index == 0);
}

bool ch14_e17::Shape_distributor::at_far_right(int ordered_index) const
{
	return (shp.size() > 0 && ordered_index == shp.size() - 1);
}

int ch14_e17::Shape_distributor::ordered_index(int idx) const
{
	idx = valid_idx(idx);
	int match = -1;
	for (int i = 0; i < shp_order.size(); ++i) {
		if (shp_order[i] == idx) {
			match = i;
			break;
		}
	}

	if (match == -1) {
		// If it comes to this something really went south
		throw std::runtime_error("Could not find ordered index");
	}
	return match;
}

int ch14_e17::Shape_distributor::find_element(const Graph_lib::Shape& s) const
{
	for (int i = 0; i < shp.size(); ++i) {
		if (&shp[i] == &s) {
			return i;
		}
	}
	return -1;
}

void ch14_e17::Shape_distributor::add_shp(Graph_lib::Shape& s)
{
	if (is_sentinel(s)) {
		throw std::runtime_error("Cannot add a sentinel shape");
	}
	shp.push_back(s);
	shp_order.push_back(shp.size() - 1);
}

const Graph_lib::Shape& ch14_e17::Shape_distributor::get_shp(int idx) const
{
	return shp[valid_idx(idx)];
}

//------------------------------------------------------------------------------

int ch14_e17::Shape_distributor::valid_idx(int i) const
{
	if (i < 0 || i >= shp.size()) {
		throw std::runtime_error("No shape at that index: " + std::to_string(i));
	}
	return i;
}

float ch14_e17::Shape_distributor::valid_angle(int a) const
{
	if (a < min_a || a > max_a) {
		throw std::runtime_error("Spread angle must be a value between "
		                         + std::to_string(min_a) + " and "
		                         + std::to_string(max_a));
	};
	return (M_PI / 180) * a;
}

int ch14_e17::Shape_distributor::offset_to_align_with_angle(Alignment_side s)
{
	int idx = 0;
	float adj_a = 0;
	Graph_lib::Point node_c{};
	if (s == Alignment_side::Left) {
		idx = shp_order[0];
		adj_a = (M_PI - angle) / 2;
		node_c = shape_origin(idx);
		node_c.x += static_cast<int>(std::round(shape_width(idx) * 0.5));
	} else {
		idx = shp_order[shp_order.size() - 1];
		adj_a = M_PI - (M_PI - angle) / 2;
		node_c = shape_origin(idx);
		node_c.x -= static_cast<int>(std::round(shape_width(idx) * 0.5));
	}
	return static_cast<int>(std::round(std::abs(node_c.x * std::tan(adj_a))));
}

int ch14_e17::Node_distributor::find_element_at_pt(Graph_lib::Point point) const
{
	int match = -1;
	for (int i = 0; i < number_of_elements(); ++i) {
		if (reinterpret_cast<const Node&>(get_shp(i)).point_is_on_node(point)) {
			match = i;
			break;
		}
	}
	return match;
}
