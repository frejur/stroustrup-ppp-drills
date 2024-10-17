#include "scatter_plot.h"

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
	draw_plot_point(xy, t, plot.plot_point_size());
	fl_color(ocol.as_int());
}
