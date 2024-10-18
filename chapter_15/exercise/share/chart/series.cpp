#include "line_chart.h"

namespace {
constexpr int min_number_of_points_in_series{0};
constexpr int max_number_of_points_in_series{512};
constexpr double min_unit{0.001};
constexpr double max_unit{1000};

void throw_x_if_y_not_betw_a_b(const std::string& x, int y, int a, int b)
{
	if (y < a || y > b) {
		throw std::runtime_error("Invalid " + x + ", value must be between "
		                         + std::to_string(a) + " and "
		                         + std::to_string((b)));
	}
}

const Graph_lib::Line_style& default_line_style()
{
	static const Graph_lib::Line_style s{Graph_lib::Line_style::solid, 1};
	return s;
}

} // namespace

//------------------------------------------------------------------------------

chart::Series::Series(const Line_chart& parent_chart,
                      const string& label,
                      double start_x_value,
                      double x_unit_size,
                      std::vector<double> y_values)
    : Chart_element::Chart_element(parent_chart, label, start_x_value, 0)
    , min_x(start_x_value)
    , max_x(0.0) // Set later
    , min_y(0.0) // ---''---
    , max_y(0.0) // ---''---
    , x_unit(valid_unit(x_unit_size))
{
	int num_y_vals{valid_num_y_vals(y_values.size())};
	int count = 0;
	for (double y : y_values) {
		if (count == 0) {
			min_y = y;
			max_y = y;
		} else {
			min_y = (std::min)(min_y, y);
			max_y = (std::max)(max_y, y);
		}
		y_val_v.push_back(y);
		++count;
	}
	max_x = min_x + (num_y_vals - 1) * x_unit;

	set_style(default_line_style());
}

long double chart::Series::min_x_value() const
{
	return min_x;
}
long double chart::Series::max_x_value() const
{
	return max_x;
}
long double chart::Series::min_y_value() const
{
	return min_y;
}
long double chart::Series::max_y_value() const
{
	return max_y;
}

//------------------------------------------------------------------------------

void chart::Series::draw_lines() const
{
	if (!color().visibility()) {
		return;
	}

	Graph_lib::Color ocol = fl_color();
	fl_color(color().as_int());
	fl_line_style(style().style(), style().width());
	double prev_x = min_x;
	Graph_lib::Point prev_xy_pos{
	    par.position_from_value(prev_x, y_val_v.front())};
	for (int i = 1; i < y_val_v.size(); ++i) {
		double x = prev_x + x_unit;
		double y = y_val_v[i];
		Graph_lib::Point xy_pos{par.position_from_value(x, y)};
		fl_line(prev_xy_pos.x, prev_xy_pos.y, xy_pos.x, xy_pos.y);
		prev_x = x;
		prev_xy_pos = xy_pos;
	}
	fl_color(ocol.as_int());
	fl_line_style(0);
}

//------------------------------------------------------------------------------

double chart::Series::valid_unit(const double u) const
{
	throw_x_if_y_not_betw_a_b("unit", u, min_unit, max_unit);
	return u;
}

int chart::Series::valid_num_y_vals(const int n) const
{
	throw_x_if_y_not_betw_a_b("number of y values",
	                          n,
	                          min_number_of_points_in_series,
	                          max_number_of_points_in_series);
	return n;
}

//------------------------------------------------------------------------------
