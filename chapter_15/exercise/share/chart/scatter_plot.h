#ifndef SCATTER_PLOT_H
#define SCATTER_PLOT_H
#include "chart.h"
#include "elem.h"

namespace chart {

enum class Point_shape { Point, Circle, Triangle, Square };

class Scatter_plot; // Forward declare

class Plot_point : public Chart_element
{
public:
	Plot_point(const Scatter_plot& parent_chart,
	           const std::string& label,
	           long double x_value,
	           long double y_value);
	virtual void draw_lines() const override;

private:
	std::function<Graph_lib::Color()> cb_color;
	std::function<Point_shape()> cb_shape;

	Graph_lib::Color default_cb_color() { return color(); };
	static Point_shape default_cb_shape() { return Point_shape::Point; };
};

class Scatter_plot : public Chart
{
public:
	Scatter_plot(Graph_lib::Point origin,
	             int width,
	             int height,
	             int point_size = default_pt_sz);
	void add(std::function<Chart_element*(const Scatter_plot&)> element_callback);

private:
	int pt_sz;
	int valid_pt_sz(const int sz);
	static constexpr int default_pt_sz{4};
};

} // namespace chart

#endif // SCATTER_PLOT_H
