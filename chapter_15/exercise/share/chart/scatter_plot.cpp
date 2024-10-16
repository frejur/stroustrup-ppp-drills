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
