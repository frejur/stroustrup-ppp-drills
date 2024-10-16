#include "scatter_plot.h"
namespace {
constexpr int min_point_size{1};
constexpr int max_point_size{32};

} // namespace

chart::Scatter_plot::Scatter_plot(Graph_lib::Point origin,
                                  int width,
                                  int height,
                                  int point_size)
    : Chart::Chart(origin, width, height)
    , pt_sz(point_size)
{}

void chart::Scatter_plot::add(
    std::function<Chart_element*(const Scatter_plot&)> element_callback)
{
	elem.push_back(element_callback(*this));
	refresh();
}
//------------------------------------------------------------------------------

Graph_lib::Color chart::Scatter_plot::plot_point_color(const Plot_point& pt) const
{
	Graph_lib::Color col = (cb_color) ? cb_color(pt) : default_cb_color(pt);
	return col;
}

void chart::Scatter_plot::set_color_callback(
    std::function<Graph_lib::Color(const Plot_point&)> cb)
{
	cb_color = cb;
}

chart::Point_shape_type chart::Scatter_plot::plot_point_shape_type(
    const Plot_point& pt) const
{
	Point_shape_type t = (cb_shape_tp) ? cb_shape_tp(pt)
	                                   : default_cb_shape_tp(pt);
	return t;
}

void chart::Scatter_plot::set_shape_type_callback(
    std::function<Point_shape_type(const Plot_point&)> cb)
{
	cb_shape_tp = cb;
}

//------------------------------------------------------------------------------

int chart::Scatter_plot::valid_pt_sz(const int sz)
{
	if (sz < min_point_size || sz > max_point_size) {
		throw std::runtime_error("Invalid point size: " + std::to_string(sz)
		                         + ", must be a value between "
		                         + std::to_string(min_point_size) + " and "
		                         + std::to_string(max_point_size));
	}
	return sz;
}
