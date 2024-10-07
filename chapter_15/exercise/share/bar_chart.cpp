#include "bar_chart.h"
#include "ch15_helpers.h"
#include <algorithm>
#include <sstream>
#include <stdexcept>

namespace {
constexpr int default_title_font_size{24};
constexpr int default_axis_title_font_size{16};
constexpr int default_x_value_font_size{10};
constexpr int default_y_value_font_size{8};
constexpr int default_notch_width{10};
constexpr int default_horizontal_padding{5};
constexpr int default_vertical_padding{5};
constexpr int min_font_size{6};
constexpr int max_font_size{128};

static const Graph_lib::Font& default_title_font()
{
	static const Graph_lib::Font f{Graph_lib::Font::helvetica};
	return f;
}
static const Graph_lib::Font& default_axis_title_font()
{
	static const Graph_lib::Font f{Graph_lib::Font::helvetica};
	return f;
}
static const Graph_lib::Font& default_x_value_font()
{
	static const Graph_lib::Font f{Graph_lib::Font::helvetica};
	return f;
}
static const Graph_lib::Font& default_y_value_font()
{
	static const Graph_lib::Font f{Graph_lib::Font::helvetica};
	return f;
}
static const Graph_lib::Line_style& default_line_style()
{
	static const Graph_lib::Line_style s{Graph_lib::Line_style::solid, 1};
	return s;
}
static const Graph_lib::Color& default_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::black,
	                                Graph_lib::Color::Transparency::invisible};
	return c;
}

static const Graph_lib::Color& default_fill_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::dark_blue};
	return c;
}

} // namespace

//------------------------------------------------------------------------------

barch::Bar_chart::Bar_chart(Graph_lib::Point origin,
                            int width,
                            int height,
                            int bars_padding)
    : // Dimensions, padding
    h(height)
    , w(width)
    , auto_pad_bars(bars_padding == 0)
    , pad_bars(valid_pad_bars(bars_padding))
    , pad_h(default_horizontal_padding)
    , pad_v(default_vertical_padding)
    , y_w(0)

    // Font size
    , title_fnt_sz(default_title_font_size)
    , x_title_fnt_sz(default_axis_title_font_size)
    , y_title_fnt_sz(default_axis_title_font_size)
    , x_val_fnt_sz(valid_fnt_sz(default_x_value_font_size))
    , y_val_fnt_sz(default_y_value_font_size)
    , min_val(0)

    // Value ranges, scaling
    , max_val(0)
    , use_usr_min_val(false)
    , use_usr_max_val(false)
    , usr_min_val(0)
    , usr_max_val(0)
    , scale_x(0)
    , scale_y(0)
    , notch_sz(0)

    // Notch settings
    , notch_unit(1.0)
    , notch_w(default_notch_width)
    , n_nudge_neg(0)
    , n_nudge_neg_until(0)
    , n_nudge_pos(0)
    , n_nudge_pos_until(0)

    // Visibility toggles
    , show_grid(false)
    , show_title(false)
    , show_x_title(false)
    , show_y_title(false)
    , show_x_vals(true)
    , show_y_vals(true)
    , show_fr(false)

    // Appearance
    , ls(default_line_style())
    , title_fnt(default_title_font())
    , y_val_fnt(default_y_value_font())
    , x_val_fnt(default_x_value_font())
    , y_title_fnt(default_axis_title_font())
    , x_title_fnt(default_axis_title_font())
    , color({default_color()})
    , fill({default_fill_color()})

    , bars()
{
	Graph_lib::Shape::add(origin);
	set_style(default_line_style());
}

void barch::Bar_chart::add(const string& label, double value)
{
	bars.push_back(new Bar(*this, label, value));
	upd_pad_bars();
	upd_scale_y();
	upd_y_w();
	upd_scale_x();
	bars[bars.size() - 1].set_color(
	    color_by_index(bars[bars.size() - 1].ordered_index()));
	bars[bars.size() - 1].set_fill_color(
	    fill_color_by_index(bars[bars.size() - 1].ordered_index()));
	bars[bars.size() - 1].set_style(style());
}

void barch::Bar_chart::draw_lines() const
{
	if (title.size() > 0) {
		draw_title();
	}

	draw_y_axis();

	for (int i = 0; i < bars.size(); ++i) {
		bars[i].draw();
	}

	if (show_fr) {
		fl_color(default_color().as_int());
		fl_line_style(static_cast<int>(
		                  Graph_lib::Line_style::Line_style_type::solid),
		              1);
		fl_rect(point(0).x, point(0).y, w, h);
	}

	if (x_title.size() > 0) {
		draw_x_title();
	}
}

void barch::Bar_chart::set_max_value(double m)
{
	use_usr_max_val = true;
	usr_max_val = m;
	upd_scale_y();
}

void barch::Bar_chart::set_style(Graph_lib::Line_style s)
{
	ls = s;
	upd_ln_style();
}

void barch::Bar_chart::set_colors(std::initializer_list<Graph_lib::Color> cv)
{
	color.clear();
	for (Graph_lib::Color c : cv) {
		color.push_back(c);
	}
	upd_colors();
}

void barch::Bar_chart::set_fill_colors(std::initializer_list<Graph_lib::Color> cv)
{
	fill.clear();
	for (Graph_lib::Color c : cv) {
		fill.push_back(c);
	}
	upd_colors();
}

Graph_lib::Color barch::Bar_chart::color_by_index(int n) const
{
	if (color.empty()) {
		return default_color();
	}
	return color[n % color.size()];
}

Graph_lib::Color barch::Bar_chart::fill_color_by_index(int n) const
{
	if (fill.empty()) {
		return default_fill_color();
	}
	return fill[n % fill.size()];
}

void barch::Bar_chart::set_min_value(double m)
{
	use_usr_min_val = true;
	usr_min_val = m;
	upd_scale_y();
}

Graph_lib::Point barch::Bar_chart::bars_origin() const
{
	if (min_val < 0) {
		return {point(0).x + y_w,
		        static_cast<int>(std::round(
		            point(0).y + (h - calc_btm_h() + min_val * scale_y)))};
	}
	return {point(0).x + y_w, point(0).y + h - calc_btm_h()};
}

void barch::Bar_chart::sort_by_label(Order o)
{
	std::vector<int> oid_v;
	for (int i = 0; i < bars.size(); ++i) {
		oid_v.push_back(bars[i].ordered_index());
	}

	if (o == Order::Asc) {
		std::sort(oid_v.begin(), oid_v.end(), [this](int oid_a, int oid_b) {
			return bars[oid_a].label() < bars[oid_b].label();
		});
	} else {
		std::sort(oid_v.begin(), oid_v.end(), [this](int oid_a, int oid_b) {
			return bars[oid_a].label() > bars[oid_b].label();
		});
	}

	for (int j = 0; j < bars.size(); ++j) {
		bars[oid_v[j]].set_ordered_index(j);
	}
	upd_colors();
}

void barch::Bar_chart::draw_y_axis() const
{
	int min_notch_count = h / notch_sz;
	if (min_notch_count < 2) {
		return;
	}

	double unit_precise_sz{scale_y * notch_unit}; // precise as opposed to the
	                                              // height in pixels stored
	                                              // in 'notch_sz'

	// lower half notches
	double delta_lower = min_val * scale_y * -1;
	int count_lower = static_cast<int>(
	    std::floor(delta_lower / unit_precise_sz));
	for (int i = 0; i <= count_lower; ++i) {
		Graph_lib::Point xy{bars_origin()};
		xy.y += i * notch_sz + (std::min)(n_nudge_neg_until, i) * n_nudge_neg;
		fl_line(xy.x, xy.y, xy.x - notch_w, xy.y);
		if (show_grid) {
			if (i > 0) {
				fl_line_style(Graph_lib::Line_style::dot);
			}
			fl_line(xy.x, xy.y, point(0).x + w - pad_h, xy.y);
			fl_line_style(Graph_lib::Line_style::solid);
		}
		draw_y_val({xy.x - notch_w, xy.y}, -i * notch_unit);
	}

	// upper half notches
	double delta_upper = max_val * scale_y;
	int count_upper = static_cast<int>(
	    std::floor(delta_upper / unit_precise_sz));
	for (int j = 0; j <= count_upper; ++j) {
		if (j == 0 && delta_lower > 0) {
			continue; // already drew zero
		}
		Graph_lib::Point xy{bars_origin()};
		xy.y -= j * notch_sz + (std::min)(n_nudge_pos_until, j) * n_nudge_pos;
		fl_line(xy.x, xy.y, xy.x - notch_w, xy.y);
		if (show_grid) {
			fl_line_style(Graph_lib::Line_style::dot);
			fl_line(xy.x, xy.y, point(0).x + w - pad_h, xy.y);
			fl_line_style(Graph_lib::Line_style::solid);
		}
		draw_y_val({xy.x - notch_w, xy.y}, j * notch_unit);
	}

	// vertical line
	fl_line(bars_origin().x,
	        bars_origin().y - delta_upper,
	        bars_origin().x,
	        bars_origin().y + delta_lower);

	// title
	if (y_title.size() > 0) {
		draw_y_title();
	}
}

void barch::Bar_chart::draw_title() const
{
	int title_w{ch15_hlp::calc_lb_w(title, title_fnt.as_int(), title_fnt_sz)};
	int half_w{static_cast<int>(std::round(title_w * 0.5))};
	Graph_lib::Point xy{point(0)};
	xy.x += static_cast<int>(std::round(w * 0.5)) - half_w;
	xy.y += pad_v + title_fnt_sz;
	int ofnt = fl_font();
	int osz = fl_size();
	fl_font(title_fnt.as_int(), title_fnt_sz);
	fl_draw(title.c_str(), xy.x, xy.y - (fl_descent() / 2));
	fl_font(ofnt, osz);
}

void barch::Bar_chart::draw_y_val(Graph_lib::Point xy, double val) const
{
	int y_offs = static_cast<int>(std::round(y_val_fnt_sz * 0.5));
	std::ostringstream oss;
	oss << val;
	int w = ch15_hlp::calc_lb_w(oss.str(), y_val_fnt, y_val_fnt_sz);
	int x_offs = -1 * (w + pad_h);
	int ocol = fl_color();
	int ofnt = fl_font();
	int osz = fl_size();
	fl_color(default_color().as_int());
	fl_font(y_val_fnt.as_int(), y_val_fnt_sz);
	fl_draw(oss.str().c_str(), xy.x + x_offs, xy.y + y_offs);
	fl_font(ofnt, osz);
	fl_color(ocol);
}

void barch::Bar_chart::draw_y_title() const
{
	int title_w{
	    ch15_hlp::calc_lb_w(y_title, y_title_fnt.as_int(), y_title_fnt_sz)};
	int half_w{static_cast<int>(std::round(title_w * 0.5))};
	Graph_lib::Point xy{point(0)};
	xy.x += pad_h + y_title_fnt_sz;
	xy.y += calc_top_h() + static_cast<int>(std::round(calc_graph_h() * 0.5))
	        + half_w;
	int ofnt = fl_font();
	int osz = fl_size();
	fl_font(y_title_fnt.as_int(), y_title_fnt_sz);
	fl_draw(90, y_title.c_str(), xy.x, xy.y);
	fl_font(ofnt, osz);
}

void barch::Bar_chart::draw_x_title() const
{
	int title_w{
	    ch15_hlp::calc_lb_w(x_title, x_title_fnt.as_int(), x_title_fnt_sz)};
	int half_w{static_cast<int>(std::round(title_w * 0.5))};
	Graph_lib::Point xy{bars_origin()};
	int half_graph_w = static_cast<int>(
	    std::round((w - calc_y_axis_w() - pad_h) * 0.5));
	xy.x += half_graph_w - half_w;
	xy.y = point(0).y + h - pad_v;
	int ofnt = fl_font();
	int osz = fl_size();
	fl_font(x_title_fnt.as_int(), x_title_fnt_sz);
	fl_draw(x_title.c_str(), xy.x, xy.y - (fl_descent() / 2));
	fl_font(ofnt, osz);
}

int barch::Bar_chart::calc_top_h() const
{
	int title_h = (pad_v + title_fnt_sz) * (title.size() > 0);
	int x_vals_h = (max_val == 0) ? (x_val_fnt_sz * 2) * show_x_vals : 0;
	return pad_v + x_vals_h + title_h;
}

int barch::Bar_chart::calc_btm_h() const
{
	int x_vals_h = (min_val == 0) ? (x_val_fnt_sz * 2) * show_x_vals : 0;
	int x_title_h = (x_title_fnt_sz + pad_v) * (x_title.size() > 0);
	return pad_v + x_vals_h + x_title_h;
}

int barch::Bar_chart::calc_graph_h() const
{
	int gh = h;
	gh -= calc_top_h();
	gh -= calc_btm_h();
	return gh;
}

void barch::Bar_chart::upd_y_w()
{
	// needs to be called AFTER upd_scale_x() / upd_min_max_val()
	y_w = calc_y_axis_w();
}

int barch::Bar_chart::calc_y_axis_w() const
{
	std::ostringstream oss;
	oss << 0;
	int max_w{ch15_hlp::calc_lb_w(oss.str(), y_val_fnt, y_val_fnt_sz)};
	int count_pos_notches{static_cast<int>(
	    std::floor((scale_y * max_val) / (scale_y * notch_unit)))};
	for (int i = 1; i <= count_pos_notches; ++i) {
		oss.str({});
		oss << (i * notch_unit);
		max_w = (std::max)(max_w,
		                   ch15_hlp::calc_lb_w(oss.str(),
		                                       y_val_fnt,
		                                       y_val_fnt_sz));
	}
	int count_neg_notches{static_cast<int>(
	    std::floor((scale_y * -min_val) / (scale_y * notch_unit)))};
	for (int j = 1; j <= count_neg_notches; ++j) {
		oss.str({});
		oss << (-j * notch_unit);
		max_w = (std::max)(max_w,
		                   ch15_hlp::calc_lb_w(oss.str(),
		                                       y_val_fnt,
		                                       y_val_fnt_sz));
	}

	// Text rotated 90 deg. Width == Height
	int title_w = (pad_h + y_title_fnt_sz) * (y_title.size() > 0);

	return max_w + 2 * pad_h + notch_w + title_w;
}

int barch::Bar_chart::valid_pad_bars(int p) const
{
	if (p < 0) {
		throw std::runtime_error("Bars padding may not be <0");
	}
	return p;
}

void barch::Bar_chart::upd_pad_bars()
{
	if (bars.size() == 0 || !auto_pad_bars) {
		return;
	}
	pad_bars = static_cast<int>(std::round(w / number_of_bars() * 0.1));
}

void barch::Bar_chart::upd_min_max_val()
{
	int min = 0;
	int max = 0;
	for (int i = 0; i < bars.size(); ++i) {
		if (i == 0) {
			min = bars[i].value();
			max = bars[i].value();
		} else {
			min = (std::min)(min, bars[i].value());
			max = (std::max)(max, bars[i].value());
		}
	}
	min_val = (min > 0) ? 0 : min;
	max_val = (max < 0) ? 0 : max;

	if (use_usr_min_val) {
		min_val = (std::min)(min_val, usr_min_val);
	}

	if (use_usr_max_val) {
		max_val = (std::max)(max_val, usr_max_val);
	}
}

void barch::Bar_chart::upd_scale_x()
{
	// needs to be called AFTER upd_y_w()
	scale_x = (w - (y_w + (pad_bars * number_of_bars())) - pad_h)
	          / number_of_bars();
}

void barch::Bar_chart::upd_scale_y()
{
	upd_min_max_val();
	double delta_val{max_val - min_val};
	scale_y = calc_graph_h() / delta_val;
	upd_notch_sz();
}

void barch::Bar_chart::upd_colors()
{
	for (int i = 0; i < bars.size(); ++i) {
		bars[i].set_color(color_by_index(bars[i].ordered_index()));
		bars[i].set_fill_color(fill_color_by_index(bars[i].ordered_index()));
	}
}

void barch::Bar_chart::upd_ln_style()
{
	for (int i = 0; i < bars.size(); ++i) {
		bars[i].set_style(ls);
	}
}

void barch::Bar_chart::upd_notch_sz()
{
	// should only be called through upd_scale_y()
	double target_sz = scale_y * notch_unit;
	notch_sz = (std::max)(static_cast<int>(target_sz), 2);
	upd_n_nudge(Sign::Neg);
	upd_n_nudge(Sign::Pos);
}

void barch::Bar_chart::upd_n_nudge(Sign s)
{
	// should only be called through upd_notch_sz()
	double delta = (s == Sign::Neg) ? min_val * -scale_y : max_val * scale_y;
	int count = static_cast<int>(std::floor(delta / (scale_y * notch_unit)));
	int y_limit = static_cast<int>(std::floor(count * scale_y * notch_unit));
	int px_diff = y_limit - (count * notch_sz);
	int px_diff_per_i = (count > 0) ? (std::max)(px_diff / count, 1) : 0;
	int nudge_until = (count > 0) ? px_diff / px_diff_per_i : 0;
	if (s == Sign::Neg) {
		n_nudge_neg = px_diff_per_i;
		n_nudge_neg_until = nudge_until;
	} else {
		n_nudge_pos = px_diff_per_i;
		n_nudge_pos_until = nudge_until;
	}
}

int barch::Bar_chart::valid_fnt_sz(const int sz) const
{
	if (sz < min_font_size || sz > max_font_size) {
		throw std::runtime_error("Invalid font size");
	}
	return sz;
}

double barch::Bar_chart::valid_unit(const double u) const
{
	if (u <= 0) {
		throw std::runtime_error("Invalid unit");
	}
	return u;
}
