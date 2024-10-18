#include "bar_chart.h"

namespace {
constexpr int minimum_sub_bar_width{2};
constexpr double sub_bar_width_factor{0.95};
} // namespace

chart::Bar_pair::Bar_pair(const Bar_chart& parent_chart,
                          const string& label,
                          long double x_value,
                          long double y_value_a,
                          long double y_value_b)
    : Bar::Bar(parent_chart, label, x_value, y_value_a)
    , y_val_b(y_value_b)
{
	Bar_pair::init_colors();
}

void chart::Bar_pair::draw_lines() const
{
	if ((y_value_a() == 0 && y_value_b() == 0)) {
		return;
	}

	const Bar_chart& bc{static_cast<const Bar_chart&>(par)};
	int sub_bar_w_max{
	    static_cast<int>(std::round((double) bc.bar_width() / number_of_bars()))
	    - (number_of_bars() - 1)};
	int sub_bar_w{(std::max)(minimum_sub_bar_width,
	                         static_cast<int>(std::round(
	                             sub_bar_w_max * sub_bar_width_factor)))};
	int pad_sub_bar{static_cast<int>(
	    std::floor((double) bc.bar_width() - (sub_bar_w * number_of_bars())))};
	for (int i = 0; i < number_of_bars(); ++i) {
		Graph_lib::Point tr{
		    par.position_from_value(x_value(), y_value_by_index(i))};
		int tl_x = (i == number_of_bars() - 1)
		               ? tr.x - bc.bar_width()
		               : tr.x - (i * pad_sub_bar + (i + 1) * sub_bar_w);
		int h{std::abs(par.origin().y - tr.y)};
		int tl_y{tr.y};

		if (bar_fill_color(i).visibility()) { // fill
			fl_color(bar_fill_color(i).as_int());
			fl_rectf(tl_x, tl_y, sub_bar_w, h);
		}

		if (bar_color(i).visibility()) { // lines on top of fill
			fl_color(bar_color(i).as_int());
			fl_rect(tl_x, tl_y, sub_bar_w, h);
		}
	}

	draw_label();
}

inline long double chart::Bar_pair::y_value_by_index(int bar_index) const
{
	long double y;
	if (bar_index == 0) {
		y = y_value();
	} else if (bar_index == 1) {
		y = y_value_b();
	} else {
		throw std::runtime_error("Invalid index");
	}
	return y;
}

long double chart::Bar_pair::min_y_value() const
{
	return (std::min)(y_val, y_val_b);
}

long double chart::Bar_pair::max_y_value() const
{
	return (std::max)(y_val, y_val_b);
}
