#include "canvas.h"
#include "../ch15_helpers.h"
#include <cmath>

namespace {
constexpr int min_padding{1};
constexpr int max_padding{64};
constexpr int min_width{32};
constexpr int max_width{1920};
constexpr int min_height{32};
constexpr int max_height{1920};
constexpr long double minimum_min_value{-10'000};
constexpr long double maximum_max_value{10'000};
constexpr double min_unit{0.001};
constexpr double max_unit{1000};
constexpr int default_horizontal_padding{10};
constexpr int default_vertical_padding{10};
constexpr int default_value_font_size{10};
constexpr int min_font_size{6};
constexpr int max_font_size{128};
constexpr int default_notch_length{4};

const Graph_lib::Font& default_value_font()
{
	static const Graph_lib::Font f{Graph_lib::Font::helvetica};
	return f;
}

const Graph_lib::Line_style& default_line_style()
{
	static const Graph_lib::Line_style s{Graph_lib::Line_style::solid, 1};
	return s;
}

const Graph_lib::Line_style& default_grid_line_style()
{
	static const Graph_lib::Line_style s{Graph_lib::Line_style::dot, 1};
	return s;
}

const Graph_lib::Color& default_fill_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::white,
	                                Graph_lib::Color::Transparency::invisible};
	return c;
}

const Graph_lib::Color& default_grid_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::black};
	return c;
}

void throw_x_if_y_not_betw_a_b(const std::string& x, int y, int a, int b)
{
	if (y < a || y > b) {
		throw std::runtime_error("Invalid " + x + ", value must be between "
		                         + std::to_string(a) + " and "
		                         + std::to_string((b)));
	}
}

} // namespace
//------------------------------------------------------------------------------

chart::Canvas::Canvas(Graph_lib::Point top_left, int width, int height)
    : origin_(top_left)

    // Dimensions, padding
    , w(valid_w(width))
    , h(valid_h(height))
    , pad_h(valid_pad(default_horizontal_padding))
    , pad_v(valid_pad(default_vertical_padding))
    , x_ax_h(0) // set later
    , y_ax_w(0) // ---''---

    // Font size
    , x_val_fnt_sz(valid_fnt_sz(default_value_font_size))
    , y_val_fnt_sz(valid_fnt_sz(default_value_font_size))

    // Value ranges, scaling
    , x_min_val(0)
    , x_max_val(1)
    , y_min_val(0)
    , y_max_val(1)
    , x_unit_(1.0)
    , y_unit_(1.0)
    , scale_x(0) // set later
    , scale_y(0) // ---''---

    // Visibility toggles
    , show_x_grid(false)
    , show_y_grid(false)
    , show_x_notches(true)
    , show_y_notches(true)
    , show_x_vals(true)
    , show_y_vals(true)

    // Appearance
    , x_val_fnt(default_value_font())
    , y_val_fnt(default_value_font())
    , grid_ls(default_grid_line_style())
    , grid_color(default_grid_color())

    , layout_upd_state(Upd_state::None)
{
	Graph_lib::Shape::add(top_left);
	set_fill_color(default_fill_color());
	x_notch.len = default_notch_length;
	y_notch.len = default_notch_length;
	upd_layout();
}

//------------------------------------------------------------------------------

Graph_lib::Point chart::Canvas::position_from_value(long double x,
                                                    long double y) const
{
	int x_offs = val_to_px_offs(x, Axis::X);
	int y_offs = val_to_px_offs(y, Axis::Y);
	return {origin_.x + x_offs, origin_.y + y_offs};
}

int chart::Canvas::val_to_px_offs(long double val, Axis a) const
{
	if (val == 0) {
		return 0;
	}

	double scale = (a == Axis::X) ? scale_x : scale_y;
	double unit = (a == Axis::X) ? x_unit_ : y_unit_;
	double precise_dist = std::abs(scale * val);
	double num_notches{precise_dist / (scale * unit)};
	int min_num_notches{static_cast<int>(std::floor(num_notches))};
	double notches_diff_f{num_notches - min_num_notches};

	const Notch& n = (a == Axis::X) ? x_notch : y_notch;
	int dist_to_closest{min_num_notches * n.base_dist};
	int dist_to_after_closest{dist_to_closest + n.base_dist};
	int last_nudged = (val >= 0) ? n.pos_nudge_until : n.neg_nudge_until;
	int nudge_count_closest = (std::min)(min_num_notches, last_nudged);
	int nudge_count_after = (std::min)(min_num_notches + 1, last_nudged);
	int nudge_dist_closest = (val >= 0) ? nudge_count_closest * n.pos_nudge_by
	                                    : nudge_count_closest * n.neg_nudge_by;
	int nudge_dist_after = (val >= 0) ? nudge_count_after * n.pos_nudge_by
	                                  : nudge_count_after * n.neg_nudge_by;
	int nudge_dist_delta = (dist_to_after_closest + nudge_dist_after)
	                       - (dist_to_closest + nudge_dist_closest);
	int nudge_diff{
	    static_cast<int>(std::round(notches_diff_f * nudge_dist_delta))};

	int neg_sign = (a == Axis::X) ? -1 : 1;
	int pos_sign = (a == Axis::X) ? 1 : -1;
	return ((val >= 0) ? pos_sign : neg_sign)
	       * (min_num_notches * n.base_dist + nudge_dist_closest + nudge_diff);
}

//------------------------------------------------------------------------------

void chart::Canvas::set_x_min_value(double m)
{
	x_min_val = valid_min(x_max_val, m);
	upd_layout();
}

void chart::Canvas::set_x_max_value(double m)
{
	x_max_val = valid_max(x_min_val, m);
	upd_layout();
}

void chart::Canvas::set_y_min_value(double m)
{
	y_min_val = valid_min(y_max_val, m);
	upd_layout();
}

void chart::Canvas::set_y_max_value(double m)
{
	y_max_val = valid_max(y_min_val, m);
	upd_layout();
}

//------------------------------------------------------------------------------

void chart::Canvas::set_x_unit(double u)
{
	x_unit_ = valid_unit(u);
	upd_layout();
}

void chart::Canvas::set_y_unit(double u)
{
	y_unit_ = valid_unit(u);
	upd_layout();
}

//------------------------------------------------------------------------------

int chart::Canvas::notch_nudge_distance(Axis a, Sign s) const
{
	if (a == Axis::X) {
		return (s == Sign::Neg) ? x_notch.neg_nudge_by : x_notch.pos_nudge_by;
	} else {
		return (s == Sign::Neg) ? y_notch.neg_nudge_by : y_notch.pos_nudge_by;
	}
}

int chart::Canvas::last_nudged_notch(Axis a, Sign s) const
{
	if (a == Axis::X) {
		return (s == Sign::Neg) ? x_notch.neg_nudge_until
		                        : x_notch.pos_nudge_until;
	} else {
		return (s == Sign::Neg) ? y_notch.neg_nudge_until
		                        : y_notch.pos_nudge_until;
	}
}
//------------------------------------------------------------------------------

void chart::Canvas::draw_lines() const
{
	Graph_lib::Point tl{point(0)};
	// Draw background
	if (fill_color().visibility()) {
		fl_rectf(tl.x, tl.y, w, h);
	}

	// Draw X axis
	int x_ax_x = tl.x;
	int x_ax_y = origin_.y;
	if (color().visibility()) {
		draw_axis(Axis::X);
		draw_axis(Axis::Y);
	}
}

void chart::Canvas::draw_axis(Axis a) const
{
	const Notch& n = (a == Axis::X) ? x_notch : y_notch;
	double unit = (a == Axis::X) ? x_unit_ : y_unit_;
	long double min = (a == Axis::X) ? x_min_val : y_min_val;
	long double max = (a == Axis::X) ? x_max_val : y_max_val;
	double scale = (a == Axis::X) ? scale_x : scale_y;
	Axis grid_a = (a == Axis::Y) ? Axis::X : Axis::Y;
	bool show_grid = (grid_a == Axis::X) ? show_x_grid : show_y_grid;
	bool show_notches = (a == Axis::X) ? show_x_notches : show_y_notches;
	bool show_vals = (a == Axis::X) ? show_x_vals : show_y_vals;
	int min_notch_count = (a == Axis::X) ? w / n.base_dist : h / n.base_dist;
	if (min_notch_count < 2) {
		return;
	}

	double unit_precise_sz{scale * unit}; // precise as opposed to the
	                                      // height in pixels stored
	                                      // in 'base_dist'

	// negative half notches
	double delta_neg = min * scale * -1;
	int count_neg = static_cast<int>(std::floor(delta_neg / unit_precise_sz));
	for (int i = 0; i <= count_neg; ++i) {
		Graph_lib::Point xy{origin_};
		int offs = i * n.base_dist
		           + (std::min)(n.neg_nudge_until, i) * n.neg_nudge_by;
		int px_val = 0;
		if (a == Axis::X) {
			xy.x -= offs;
			px_val = xy.x;
		} else {
			xy.y += offs;
			px_val = xy.y;
		}
		if (show_notches) {
			draw_notch(px_val, a);
		}
		if (show_grid && i != 0) {
			draw_grid_line(px_val, grid_a);
		}
		if (show_vals) {
			draw_value(-i * unit, px_val, a);
		}
	}

	// positive half notches
	double delta_pos = max * scale;
	int count_pos = static_cast<int>(std::floor(delta_pos / unit_precise_sz));
	for (int j = 0; j <= count_pos; ++j) {
		if (j == 0 && delta_pos > 0) {
			continue; // already drew zero
		}
		Graph_lib::Point xy{origin_};
		int offs = j * n.base_dist
		           + (std::min)(n.pos_nudge_until, j) * n.pos_nudge_by;
		int px_val = 0;
		if (a == Axis::X) {
			xy.x += offs;
			px_val = xy.x;
		} else {
			xy.y -= offs;
			px_val = xy.y;
		}
		if (show_notches) {
			draw_notch(px_val, a);
		}
		if (show_grid && j != 0) {
			draw_grid_line(px_val, grid_a);
		}
		if (show_vals) {
			draw_value(j * unit, px_val, a);
		}
	}

	// line
	int ocol = fl_color();
	fl_color(color().as_int());
	int limit = (a == Axis::X) ? top_left_corner().x + w : top_left_corner().y;
	Graph_lib::Point tl = (min == 0 || max == 0) ? origin() : top_left_corner();
	if (a == Axis::X) {
		fl_line(tl.x, origin_.y, tl.x + (limit - tl.x), origin_.y);
	} else {
		fl_line(origin_.x, tl.y, origin_.x, tl.y + (limit - tl.y));
	}
	fl_color(ocol);
}

void chart::Canvas::draw_notch(int px_val, Axis a) const
{
	int ocol = fl_color();
	fl_color(color().as_int());
	fl_line_style(style().style(), style().width());
	if (a == Axis::X) {
		fl_line(px_val, origin_.y, px_val, origin_.y + x_notch.len);
	} else {
		fl_line(origin_.x - y_notch.len, px_val, origin_.x, px_val);
	}
	fl_color(ocol);
}

void chart::Canvas::draw_grid_line(int px_val, Axis a) const
{
	int ocol = fl_color();
	fl_color(grid_color.as_int());
	fl_line_style(grid_ls.style(), grid_ls.width());
	long double min = (a == Axis::X) ? x_min_val : y_min_val;
	long double max = (a == Axis::X) ? x_max_val : y_max_val;
	int limit = (a == Axis::X) ? top_left_corner().x + w
	                           : top_left_corner().y + h;
	Graph_lib::Point tl = (min == 0 || max == 0) ? origin() : top_left_corner();
	if (a == Axis::Y) {
		fl_line(px_val, tl.y, px_val, tl.y + (limit - tl.y));
	} else {
		fl_line(tl.x, px_val, tl.x + (limit - tl.x), px_val);
	}
	fl_color(ocol);

	// Reset line style
	fl_line_style(default_line_style().style(), default_line_style().width());
}

void chart::Canvas::draw_value(int val, int px_val, Axis a) const
{
	Graph_lib::Point xy;
	Graph_lib::Font f{0};
	int fsz = 0;
	int notch_offs = (a == Axis::X) ? show_x_notches * x_notch.len
	                                : show_y_notches * y_notch.len;
	int y_offs = 0;
	if (a == Axis::X) {
		xy.x = px_val;
		xy.y = origin_.y;
		f = x_val_fnt;
		fsz = x_val_fnt_sz;
		y_offs = pad_v + fsz + notch_offs;
	} else {
		xy.x = origin_.x;
		xy.y = px_val;
		f = y_val_fnt;
		fsz = y_val_fnt_sz;
		y_offs = static_cast<int>(std::round(y_val_fnt_sz * 0.5));
	}
	std::ostringstream oss;
	oss << val;
	int w = ch15_hlp::calc_lb_w(oss.str(), y_val_fnt, y_val_fnt_sz);
	int x_offs = (a == Axis::X) ? static_cast<int>(std::round(w * 0.5))
	                            : -1 * (w + pad_h + notch_offs);
	int ocol = fl_color();
	int ofnt = fl_font();
	int osz = fl_size();
	fl_color(color().as_int());
	fl_font(f.as_int(), fsz);
	fl_draw(oss.str().c_str(), xy.x + x_offs, xy.y + y_offs);
	fl_font(ofnt, osz);
	fl_color(ocol);
}

//------------------------------------------------------------------------------

void chart::Canvas::upd_x_ax_h()
{
	validate_current_upd_state({Upd_state::None, Upd_state::All_done});
	int ax_h = 1;
	ax_h += (show_x_notches) ? x_notch.len : 0;
	ax_h += (show_x_vals) ? pad_v + x_val_fnt_sz : 0;
	throw_x_if_y_not_betw_a_b("X axis height", ax_h, 1, h);
	x_ax_h = ax_h;
	layout_upd_state = Upd_state::X_axis_done;
}

int chart::Canvas::calc_y_vals_w() const
{
	std::ostringstream oss;
	oss << 0;
	int max_w{ch15_hlp::calc_lb_w(oss.str(), y_val_fnt, y_val_fnt_sz)};
	int count_pos_notches{static_cast<int>(std::floor(y_max_val / y_unit_))};
	for (int i = 1; i <= count_pos_notches; ++i) {
		oss.str({});
		oss << (i * y_unit_);
		max_w = (std::max)(max_w,
		                   ch15_hlp::calc_lb_w(oss.str(),
		                                       y_val_fnt,
		                                       y_val_fnt_sz));
	}
	int count_neg_notches{static_cast<int>(std::floor(y_min_val / y_unit_))};
	for (int j = 1; j <= count_neg_notches; ++j) {
		oss.str({});
		oss << (j * y_unit_);
		max_w = (std::max)(max_w,
		                   ch15_hlp::calc_lb_w(oss.str(),
		                                       y_val_fnt,
		                                       y_val_fnt_sz));
	}
	return max_w;
}

void chart::Canvas::upd_layout()
{
	upd_x_ax_h();
	upd_y_ax_w();
	upd_origin();
	upd_scale_x();
	upd_scale_y();
	upd_x_notch();
	upd_y_notch();
}

void chart::Canvas::upd_y_ax_w()
{
	validate_current_upd_state(Upd_state::X_axis_done);
	int ax_w = 1;
	ax_w += (show_y_notches) ? y_notch.len : 0;
	ax_w += (show_y_vals) ? calc_y_vals_w() + pad_h : 0;

	throw_x_if_y_not_betw_a_b("Y axis width", ax_w, 1, w);
	y_ax_w = ax_w;
	layout_upd_state = Upd_state::Y_axis_done;
}

void chart::Canvas::upd_origin()
{
	validate_current_upd_state(Upd_state::Y_axis_done);
	int x = 0;
	const long double delta_val_x{x_max_val - x_min_val};
	int neg_w = y_ax_w;
	if (x_min_val < 0) {
		long double neg_w_f{(x_min_val * -1) / delta_val_x};
		neg_w = static_cast<int>(std::floor(w * neg_w_f));
	}
	x = neg_w;

	int y = 0;
	const long double delta_val_y{y_max_val - y_min_val};
	int neg_h = x_ax_h;
	if (y_min_val < 0) {
		long double neg_h_f{(y_min_val * -1) / delta_val_y};
		neg_h = static_cast<int>(std::floor(h * neg_h_f));
	}
	y = neg_h;

	Graph_lib::Point tl{top_left_corner()};
	origin_ = {tl.x + x, tl.y + h - y};
	layout_upd_state = Upd_state::Origin_done;
}

void chart::Canvas::upd_scale_x()
{
	validate_current_upd_state(Upd_state::Origin_done);
	if (x_max_val > x_min_val * -1) {
		int pos_x_dist{(top_left_corner().x + w) - origin_.x};
		scale_x = pos_x_dist / x_max_val;
	} else {
		int neg_x_dist{origin_.x + top_left_corner().x};
		scale_x = neg_x_dist / x_min_val * -1;
	}
	layout_upd_state = Upd_state::Scale_x_done;
}

void chart::Canvas::upd_scale_y()
{
	validate_current_upd_state(Upd_state::Scale_x_done);
	if (y_max_val > y_min_val * -1) {
		int pos_y_dist{origin_.y - top_left_corner().y};
		scale_y = pos_y_dist / y_max_val;
	} else {
		int neg_y_dist{(origin_.y + h) - top_left_corner().y};
		scale_y = neg_y_dist / y_min_val * -1;
	}
	layout_upd_state = Upd_state::Scale_y_done;
}

void chart::Canvas::upd_x_notch()
{
	validate_current_upd_state(Upd_state::Scale_y_done);
	double target_dist = scale_x * x_unit_;
	x_notch.base_dist = (std::max)(static_cast<int>(target_dist), 2);
	upd_n_nudge(Axis::X, Sign::Neg);
	upd_n_nudge(Axis::X, Sign::Pos);
	layout_upd_state = Upd_state::X_notch_done;
}

void chart::Canvas::upd_y_notch()
{
	validate_current_upd_state(Upd_state::X_notch_done);
	double target_dist = scale_y * y_unit_;
	y_notch.base_dist = (std::max)(static_cast<int>(target_dist), 2);
	upd_n_nudge(Axis::Y, Sign::Neg);
	upd_n_nudge(Axis::Y, Sign::Pos);
	layout_upd_state = Upd_state::All_done;
}

void chart::Canvas::upd_n_nudge(Axis a, Sign s)
{
	if (a == Axis::X) {
		validate_current_upd_state(Upd_state::Scale_y_done);
	} else {
		validate_current_upd_state(Upd_state::X_notch_done);
	}
	Notch& n = (a == Axis::X) ? x_notch : y_notch;
	long double min = (a == Axis::X) ? x_min_val : y_min_val;
	long double max = (a == Axis::X) ? x_max_val : y_max_val;
	double unit = (a == Axis::X) ? x_unit_ : y_unit_;
	double scale = (a == Axis::X) ? scale_x : scale_y;
	long double delta = (s == Sign::Neg) ? min * -scale : max * scale;
	int count = static_cast<int>(std::floor(delta / (scale * unit)));
	int limit = static_cast<int>(std::floor(count * scale * unit));
	int px_diff = limit - (count * n.base_dist);
	int px_diff_per_i = (count > 0) ? (std::max)(px_diff / count, 1) : 0;
	int nudge_until = (count > 0) ? px_diff / px_diff_per_i : 0;

	if (s == Sign::Neg) {
		n.neg_nudge_by = px_diff_per_i;
		n.neg_nudge_until = nudge_until;
	} else {
		n.pos_nudge_by = px_diff_per_i;
		n.pos_nudge_until = nudge_until;
	}
}

//------------------------------------------------------------------------------

int chart::Canvas::valid_w(const int width) const
{
	throw_x_if_y_not_betw_a_b("width", width, min_width, max_width);
	return width;
}

int chart::Canvas::valid_h(const int height) const
{
	throw_x_if_y_not_betw_a_b("height", height, min_height, max_height);
	return height;
}

double chart::Canvas::valid_pad(const int p) const
{
	throw_x_if_y_not_betw_a_b("padding", p, min_padding, max_padding);
	return p;
}

long double chart::Canvas::valid_min(const long double max,
                                     const long double min) const
{
	if (min > max - min_unit) {
		throw std::runtime_error("Invalid min, cannot exceed max");
	}
	throw_x_if_y_not_betw_a_b("min", min, minimum_min_value, 0);
	return min;
}

long double chart::Canvas::valid_max(const long double min,
                                     const long double max) const
{
	if (max < min + min_unit) {
		throw std::runtime_error("Invalid max, cannot be less than min");
	}
	throw_x_if_y_not_betw_a_b("max", max, 0, maximum_max_value);
	return max;
}

double chart::Canvas::valid_unit(const double u) const
{
	throw_x_if_y_not_betw_a_b("unit", u, min_unit, max_unit);
	return u;
}

int chart::Canvas::valid_fnt_sz(const int sz) const
{
	throw_x_if_y_not_betw_a_b("font size", sz, min_font_size, max_font_size);
	return sz;
}

void chart::Canvas::validate_current_upd_state(
    std::initializer_list<Upd_state> expected) const
{
	int match = false;
	for (const Upd_state& s : expected) {
		if (s == layout_upd_state) {
			match = true;
			break;
		}
	}

	if (!match) {
		int count = 0;
		std::string exp_list{"("};
		for (const Upd_state& e : expected) {
			exp_list += std::to_string(static_cast<int>(e));
			if (count > 0 && count != expected.size() - 1) {
				exp_list += ", ";
			}
		}
		exp_list += ")";
		throw std::runtime_error(
		    "Invalid state when updating layout, expected index" + exp_list
		    + " but got index "
		    + std::to_string(static_cast<int>(layout_upd_state)));
	}
}
