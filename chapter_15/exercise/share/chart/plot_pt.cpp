#include "scatter_plot.h"
#include <algorithm>

chart::Plot_point::Plot_point(const Scatter_plot& parent_chart,
                              const string& label,
                              long double x_value,
                              long double y_value)
    : Chart_element::Chart_element(parent_chart, label, x_value, y_value)
{}

void chart::Plot_point::draw_lines() const
{
	Graph_lib::Color ocol = fl_color();
	const Scatter_plot& plot = dynamic_cast<const Scatter_plot&>(par);
	Graph_lib::Color col = plot.plot_point_color(*this);
	fl_color(col.as_int());
	Graph_lib::Point xy{par.position_from_value(x_value(), y_value())};
	Point_shape_type t{plot.plot_point_shape_type(*this)};
	draw_point(xy, t, plot.plot_point_size());
	fl_color(ocol.as_int());
}

void chart::Plot_point::draw_point(Graph_lib::Point xy,
                                   Point_shape_type t,
                                   int size) const
{
	int rad{static_cast<int>(std::round(size * 0.5))};
	switch (t) {
	case Point_shape_type::Point:
		fl_pie(xy.x, xy.y, size, size, 0, 360);
		break;
	case Point_shape_type::Circle: {
		int strk_w = (std::max)(1, static_cast<int>(std::round(size * 0.2)));
		fl_line_style(Graph_lib::Line_style::solid, strk_w);
		fl_circle(xy.x, xy.y, rad);
		fl_line_style(0);
		break;
	}
	case Point_shape_type::Diamond:
		int incr_rad{static_cast<int>(std::round(rad * 1.15))};
		fl_polygon(xy.x - incr_rad,
		           xy.y,
		           xy.x,
		           xy.y - incr_rad,
		           xy.x + incr_rad,
		           xy.y,
		           xy.x,
		           xy.y + incr_rad);
		break;
	}
}
