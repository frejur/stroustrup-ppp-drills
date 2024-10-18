#ifndef LINE_CHART_H
#define LINE_CHART_H

#include "chart.h"
#include "elem.h"

namespace chart {

class Line_chart; // Forward declare

class Series : public Chart_element
{
public:
	Series(const Line_chart& parent_chart,
	       const std::string& label,
	       double start_x_value,
	       double x_unit_size,
	       std::vector<double> y_values);

	virtual long double min_x_value() const override;
	virtual long double max_x_value() const override;
	virtual long double min_y_value() const override;
	virtual long double max_y_value() const override;

	virtual void draw_lines() const override;

private:
	double min_x;
	double max_x;
	double min_y;
	double max_y;
	double x_unit;
	std::vector<double> y_val_v;

	// Hide base fill color methods
	Graph_lib::Color fill_color() const { return 0; };
	void set_fill_color(Graph_lib::Color col){};

	double valid_unit(const double sz) const;
	int valid_num_y_vals(const int n) const;
};

//------------------------------------------------------------------------------

class Line_chart : public Chart
{
public:
	Line_chart(Graph_lib::Point top_left_corner, int width, int height);
	void add(const std::string& label,
	         double start_x_value,
	         double x_unit_size,
	         std::vector<double> y_values,
	         Graph_lib::Color color);

	void set_color_by_index(Graph_lib::Color color, int line_idx)
	{
		elem[valid_idx(line_idx)].set_color(color);
	};

	Graph_lib::Color color_by_index(int line_idx) const
	{
		return elem[valid_idx(line_idx)].color();
	};

	void set_style_by_index(Graph_lib::Line_style style, int line_idx)
	{
		elem[valid_idx(line_idx)].set_style(style);
	};
	Graph_lib::Line_style style_by_index(int line_idx) const
	{
		return elem[valid_idx(line_idx)].style();
	};

private:
	virtual void upd_post_layout() override{};
	int valid_idx(int idx) const;
};

} // namespace chart

#endif // LINE_CHART_H
