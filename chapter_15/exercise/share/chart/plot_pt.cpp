#include "scatter_plot.h"

chart::Plot_point::Plot_point(const Scatter_plot& parent_chart,
                              const string& label,
                              long double x_value,
                              long double y_value)
    : Chart_element::Chart_element(parent_chart, label, x_value, y_value)
{}

void chart::Plot_point::draw_lines() const
{
	Graph_lib::Point xy{par.position_from_value(x_value(), y_value())};
	fl_rect(xy.x - 2, xy.y - 2, 4, 4);
}
