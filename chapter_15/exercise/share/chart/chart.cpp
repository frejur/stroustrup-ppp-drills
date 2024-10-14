#include "chart.h"
#include "../ch15_helpers.h"
#include "elem.h"

namespace {
constexpr int min_padding{1};
constexpr int max_padding{64};
constexpr int min_width{32};
constexpr int max_width{1920};
constexpr int min_height{32};
constexpr int max_height{1920};
constexpr int default_horizontal_padding{10};
constexpr int default_vertical_padding{10};
constexpr int default_title_font_size{24};
constexpr int default_axis_title_font_size{14};
constexpr int default_label_font_size{10};
constexpr int min_font_size{6};
constexpr int max_font_size{128};

const Graph_lib::Font& default_font()
{
	static const Graph_lib::Font f{Graph_lib::Font::helvetica};
	return f;
}

const Graph_lib::Line_style& default_line_style()
{
	static const Graph_lib::Line_style s{Graph_lib::Line_style::solid, 1};
	return s;
}

const Graph_lib::Color& default_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::black};
	return c;
}
} // namespace

//------------------------------------------------------------------------------

void chart::Chart::set_x_min_value(long double m)
{
	usr_min_max.x_min = m;
	use_usr_x_min_val = true;
	upd_min_max_val();
}

void chart::Chart::set_x_max_value(long double m)
{
	usr_min_max.x_max = m;
	use_usr_x_max_val = true;
	upd_min_max_val();
}

void chart::Chart::set_y_min_value(long double m)
{
	usr_min_max.y_min = m;
	use_usr_y_min_val = true;
	upd_min_max_val();
}

void chart::Chart::set_y_max_value(long double m)
{
	usr_min_max.y_max = m;
	use_usr_y_max_val = true;
	upd_min_max_val();
}

void chart::Chart::unset_x_min_value()
{
	use_usr_x_min_val = false;
	upd_min_max_val();
}

void chart::Chart::unset_x_max_value()
{
	use_usr_x_max_val = false;
	upd_min_max_val();
}

void chart::Chart::unset_y_min_value()
{
	use_usr_y_min_val = false;
	upd_min_max_val();
}

void chart::Chart::unset_y_max_value()
{
	use_usr_y_max_val = false;
	upd_min_max_val();
}

//------------------------------------------------------------------------------

ch15_hlp::Text_alignment chart::Chart::label_alignment() const
{
	return ch15_hlp::Text_alignment::Center;
}

//------------------------------------------------------------------------------

void chart::Chart::draw_lines() const
{
	cv.draw_lines();

	if (!title.empty()) {
		draw_title();
	}
	if (!x_title.empty()) {
		draw_x_title();
	}
	if (!y_title.empty()) {
		draw_y_title();
	}

	draw_graph();

	if (show_fr) {
		Graph_lib::Color ocol = fl_color();
		fl_color(default_color().as_int());
		fl_line_style(default_line_style().style(),
		              default_line_style().width());
		fl_rect(point(0).x, point(0).y, w, h);

		fl_color(ocol.as_int());
	}
}

//------------------------------------------------------------------------------

chart::Chart::Chart(Graph_lib::Point top_left, int width, int height)
    : // Dimensions, padding
    h(height)
    , w(width)
    , pad_h(default_horizontal_padding)
    , pad_v(default_vertical_padding)
    , pad_graph_btm(0)
    , left_block_w(0)  /* Set later */
    , right_block_w(0) /* ---''---  */
    , upper_block_h(0) /* ---''---  */
    , lower_block_h(0) /* ---''---  */

    // Font size
    , title_fnt_sz(default_title_font_size)
    , x_title_fnt_sz(default_axis_title_font_size)
    , y_title_fnt_sz(default_axis_title_font_size)
    , lb_fnt_sz(default_label_font_size)

    // Value ranges, scaling
    , use_usr_x_min_val(false)
    , use_usr_x_max_val(false)
    , use_usr_y_min_val(false)
    , use_usr_y_max_val(false)

    // Visibility toggles
    , show_fr(false)
    , show_lb(false)

    // Appearance
    , ls(default_line_style())
    , title_fnt(default_font())
    , y_title_fnt(default_font())
    , x_title_fnt(default_font())
    , lb_fnt(default_font())
    , lb_color(default_color())

    // Canvas
    , cv(top_left, width, height) // Adjust later

    , layout_upd_state(Upd_state::None)
{
	Graph_lib::Shape::add(top_left);
}

//------------------------------------------------------------------------------

void chart::Chart::draw_title() const
{
	Graph_lib::Point xy{top_left_corner()};
	xy.x += static_cast<int>(std::round(w * 0.5));
	xy.y += pad_v;
	ch15_hlp::draw_text(xy,
	                    title,
	                    title_fnt,
	                    title_fnt_sz,
	                    color(),
	                    ch15_hlp::Text_alignment::Bottom);
}

void chart::Chart::draw_x_title() const
{
	Graph_lib::Point xy{top_left_corner()};
	xy.x += left_block_w + static_cast<int>(std::round(cv.width() * 0.5));
	xy.y += (h - lower_block_h) + pad_v + pad_graph_btm;
	ch15_hlp::draw_text(xy,
	                    x_title,
	                    x_title_fnt,
	                    x_title_fnt_sz,
	                    color(),
	                    ch15_hlp::Text_alignment::Bottom);
}

void chart::Chart::draw_y_title() const
{
	int title_w{
	    ch15_hlp::calc_lb_w(y_title, y_title_fnt.as_int(), y_title_fnt_sz)};
	int half_w{static_cast<int>(std::round(title_w * 0.5))};
	Graph_lib::Point xy{point(0)};
	xy.x += pad_h + y_title_fnt_sz;
	xy.y += upper_block_h + static_cast<int>(std::round(cv.height() * 0.5))
	        + half_w;
	int ofnt = fl_font();
	int osz = fl_size();
	fl_font(y_title_fnt.as_int(), y_title_fnt_sz);
	fl_draw(90, y_title.c_str(), xy.x, xy.y);
	fl_font(ofnt, osz);
}

void chart::Chart::draw_graph() const
{
	for (int i = 0; i < elem.size(); ++i) {
		elem[i].draw_lines();
	}
}

//------------------------------------------------------------------------------

void chart::Chart::upd_layout()
{
	upd_left_block();
	upd_right_block();
	upd_upper_block();
	upd_lower_block();
	upd_graph();

	// The method below can be overriden by a derived class to perform actions
	// after the layout has been updated
	validate_current_upd_state(Upd_state::Graph_done);
	upd_post_layout();
	layout_upd_state = Upd_state::All_done;
}

void chart::Chart::upd_left_block()
{
	validate_current_upd_state({Upd_state::None, Upd_state::All_done});
	int w = pad_h;
	if (!y_title.empty()) {
		w += pad_h + y_title_fnt_sz;
	}
	left_block_w = w;
	layout_upd_state = Upd_state::Left_block_done;
}

void chart::Chart::upd_right_block()
{
	validate_current_upd_state(Upd_state::Left_block_done);
	right_block_w = pad_h;
	layout_upd_state = Upd_state::Right_block_done;
}

void chart::Chart::upd_upper_block()
{
	validate_current_upd_state(Upd_state::Right_block_done);
	int this_h = pad_v;
	if (!title.empty()) {
		this_h += pad_h + title_fnt_sz;
	}
	upper_block_h = this_h;
	layout_upd_state = Upd_state::Upper_block_done;
}

void chart::Chart::upd_lower_block()
{
	validate_current_upd_state(Upd_state::Upper_block_done);
	int this_h = pad_v + pad_graph_btm;
	if (!x_title.empty()) {
		this_h += pad_v + x_title_fnt_sz;
	}
	lower_block_h = this_h;
	layout_upd_state = Upd_state::Lower_block_done;
}

void chart::Chart::upd_graph()
{
	validate_current_upd_state(Upd_state::Lower_block_done);
	int graph_h = h - (upper_block_h + lower_block_h);
	int graph_w = w - (left_block_w + right_block_w);
	Graph_lib::Point graph_tl{top_left_corner()};
	graph_tl.x += left_block_w;
	graph_tl.y += upper_block_h;
	Graph_lib::Point cv_tl{canvas_top_left_corner()};
	cv.move(graph_tl.x - cv_tl.x, graph_tl.y - cv_tl.y);
	cv.set_dimensions(graph_w, graph_h);
	layout_upd_state = Upd_state::Graph_done;
}

void chart::Chart::upd_min_max_val()
{
	Min_max_vals elem_min_max{min_max_vals_from_elements()};
	Min_max_vals new_min_max = elem_min_max;
	if (use_usr_x_min_val) {
		new_min_max.x_min = (std::min)(elem_min_max.x_min, usr_min_max.x_min);
	}
	if (use_usr_x_max_val) {
		new_min_max.x_max = (std::max)(elem_min_max.x_max, usr_min_max.x_max);
	}
	if (use_usr_y_min_val) {
		new_min_max.y_min = (std::min)(elem_min_max.y_min, usr_min_max.y_min);
	}
	if (use_usr_y_max_val) {
		new_min_max.y_max = (std::max)(elem_min_max.y_max, usr_min_max.y_max);
	}
	cv.set_x_min_value(new_min_max.x_min);
	cv.set_x_max_value(new_min_max.x_max);
	cv.set_y_min_value(new_min_max.y_min);
	cv.set_y_max_value(new_min_max.y_max);
}

//------------------------------------------------------------------------------

chart::Chart::Min_max_vals chart::Chart::min_max_vals_from_elements() const
{
	Min_max_vals min_max;
	for (int i = 0; i < elem.size(); ++i) {
		long double x_val = elem[i].x_value();
		long double y_val = elem[i].y_value();
		min_max.x_min = (i == 0) ? x_val : (std::min)(x_val, min_max.x_min);
		min_max.x_max = (i == 0) ? x_val : (std::max)(x_val, min_max.x_max);
		min_max.y_min = (i == 0) ? y_val : (std::min)(y_val, min_max.y_min);
		min_max.y_max = (i == 0) ? y_val : (std::max)(y_val, min_max.y_max);
	}
	min_max.x_min = (std::min)(min_max.x_min, 0.0L);
	min_max.x_max = (std::max)(min_max.x_max, 0.0L);
	min_max.y_min = (std::min)(min_max.y_min, 0.0L);
	min_max.y_max = (std::max)(min_max.y_max, 0.0L);
	return min_max;
}

//------------------------------------------------------------------------------

void chart::Chart::validate_current_upd_state(
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
