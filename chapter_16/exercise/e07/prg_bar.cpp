#include "prg_bar.h"
namespace {
constexpr int progress_bar_min_width{10};
constexpr int progress_bar_min_height{4};
constexpr int progress_bar_max_width{1000};
constexpr int progress_bar_max_height{500};
} // namespace

const Graph_lib::Color Progress_bar::default_col = Graph_lib::Color::black;
const Graph_lib::Color Progress_bar::default_fill = Graph_lib::Color::green;
const Graph_lib::Color Progress_bar::default_bg = Graph_lib::Color::dark_green;

//------------------------------------------------------------------------------

Progress_bar::Progress_bar(Graph_lib::Point top_left,
                           int width,
                           int height,
                           Graph_lib::Color color,
                           Graph_lib::Color fill_color,
                           Graph_lib::Color background_color)
    : w(valid_w(width))
    , h(valid_h(height))
    , st_val(0)
    , bg_col(background_color)
{
	add(top_left);
	set_color(color);
	set_fill_color(fill_color);
}

//------------------------------------------------------------------------------

void Progress_bar::set_value(double v)
{
	st_val = valid_st_val(v);
}

//------------------------------------------------------------------------------

void Progress_bar::draw_lines() const
{
	// Draw background
	if (background_color().visibility()) {
		Graph_lib::Color ocol = fl_color();
		fl_color(background_color().as_int());
		fl_rectf(point(0).x, point(0).y, width(), height());
		fl_color(ocol.as_int());
	}

	// Draw bar
	if (fill_color().visibility()) {
		int stroke_offs = color().visibility() ? style().width() : 0;
		int bar_max_w = width() - stroke_offs * 2;
		int bar_w = bar_max_w * (st_val / 100);
		Graph_lib::Color ocol = fl_color();
		fl_color(fill_color().as_int());
		fl_rectf(point(0).x + stroke_offs,
		         point(0).y + stroke_offs,
		         bar_w,
		         height() - stroke_offs * 2);
		fl_color(ocol.as_int());
	}

	// Draw stroke
	if (color().visibility()) {
		fl_rect(point(0).x, point(0).y, width(), height());
	}
}

//------------------------------------------------------------------------------

int Progress_bar::valid_st_val(int v) const
{
	if (v < 0 || v > 100) {
		throw std::runtime_error("Invalid progress bar value, expected a value "
		                         "between 0 and 100, but got "
		                         + std::to_string(v));
	}
	return v;
}

int Progress_bar::valid_w(int n) const
{
	if (n < progress_bar_min_width || n > progress_bar_max_width) {
		throw std::runtime_error("Invalid progress bar width, expected a value "
		                         "between: "
		                         + std::to_string(progress_bar_min_width)
		                         + " and "
		                         + std::to_string(progress_bar_max_width)
		                         + " , but got " + std::to_string(n));
	}
	return n;
}

int Progress_bar::valid_h(int n) const
{
	if (n < progress_bar_min_height || n > progress_bar_max_height) {
		throw std::runtime_error("Invalid progress bar width, expected a value "
		                         "between: "
		                         + std::to_string(progress_bar_min_height)
		                         + " and "
		                         + std::to_string(progress_bar_max_height)
		                         + " , but got " + std::to_string(n));
	}
	return n;
}
