#ifndef SCATTER_PLOT_H
#define SCATTER_PLOT_H
#include "chart.h"
#include "elem.h"

namespace chart {

enum class Point_shape_type { Point, Circle, Diamond };

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
	void draw_point(Graph_lib::Point xy, Point_shape_type t, int pt_sz) const;
};

class Scatter_plot : public Chart
{
public:
	Scatter_plot(Graph_lib::Point origin,
	             int width,
	             int height,
	             int point_size = default_pt_sz);
	void add(std::function<Chart_element*(const Scatter_plot&)> element_callback);
	Graph_lib::Color plot_point_color(const Plot_point& pt) const;
	void set_color_callback(
	    std::function<Graph_lib::Color(const Plot_point&)> cb);
	Point_shape_type plot_point_shape_type(const Plot_point& pt) const;
	void set_shape_type_callback(
	    std::function<Point_shape_type(const Plot_point&)> cb);
	int plot_point_size() const { return pt_sz; };
	void set_plot_point_size(int sz) { pt_sz = valid_pt_sz(sz); };

private:
	int pt_sz;
	int valid_pt_sz(const int sz);
	static constexpr int default_pt_sz{16};

	std::function<Graph_lib::Color(const Plot_point&)> cb_color;
	std::function<Point_shape_type(const Plot_point&)> cb_shape_tp;

	static Graph_lib::Color default_cb_color(const Plot_point& pt)
	{
		return pt.color();
	};
	static Point_shape_type default_cb_shape_tp(const Plot_point& pt)
	{
		return Point_shape_type::Point;
	};
};

} // namespace chart

#endif // SCATTER_PLOT_H
