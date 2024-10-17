#ifndef BAR_CHART_NEW_H
#define BAR_CHART_NEW_H

#include "chart.h"
#include "elem.h"

namespace chart {

//------------------------------------------------------------------------------

class Bar_chart; // Forward declare

class Bar : public Chart_element
{
public:
	Bar(const Bar_chart& parent_chart,
	    const std::string& label,
	    long double x_value,
	    long double y_value);
	virtual int number_of_bars() const = 0;

	// Hide base class color methods
	Graph_lib::Color color() const { return bar_color(0); };
	Graph_lib::Color fill_color() const { return bar_fill_color(0); };
	void set_color(Graph_lib::Color col) { set_bar_color(col, 0); };
	void set_fill_color(Graph_lib::Color col) { set_bar_fill_color(col, 0); };

	Graph_lib::Color bar_color(int bar_idx) const;
	Graph_lib::Color bar_fill_color(int bar_idx) const;
	void set_bar_color(Graph_lib::Color col, int bar_idx);
	void set_bar_fill_color(Graph_lib::Color col, int bar_index);

protected:
	std::vector<Graph_lib::Color> col_v;
	std::vector<Graph_lib::Color> fill_v;

	Graph_lib::Point label_offset() const;
	void init_colors();
};

class Bar_single : public Bar
{
public:
	Bar_single(const Bar_chart& parent_chart,
	           const std::string& label,
	           long double x_value,
	           long double y_value);
	virtual void draw_lines() const override;
	virtual int number_of_bars() const override { return 1; };

private:
};

class Bar_pair : public Bar
{
public:
	Bar_pair(const Bar_chart& parent_chart,
	         const std::string& label,
	         long double x_value,
	         long double y_value_a,
	         long double y_value_b);
	long double y_value_a() const { return y_value(); };
	long double y_value_b() const { return y_val_b; };
	void set_y_value_a(double y) { set_y_value(y); };
	void set_y_value_b(double y) { y_val_b = y; };
	virtual void draw_lines() const override;
	virtual int number_of_bars() const override { return 2; };

private:
	long double y_val_b;
};

//------------------------------------------------------------------------------

enum class Order { Asc, Desc };

class Bar_chart : public Chart
{
public:
	Bar_chart(Graph_lib::Point origin,
	          int width,
	          int height,
	          int bars_padding = 0);
	void add(const std::string& label, long double value);
	void add(const std::string& label, long double value_a, long double value_b);

	void set_colors(std::initializer_list<Graph_lib::Color> cv);
	void set_fill_colors(std::initializer_list<Graph_lib::Color> cv);
	Graph_lib::Color color_by_index(int n) const;
	Graph_lib::Color fill_color_by_index(int n) const;

	int number_of_bars() const { return elem.size(); }
	int bar_width() const
	{
		return static_cast<int>(x_scale_factor()) - pad_bars;
	};
	int bars_padding() const { return pad_bars; }
	void set_bars_padding(int p);
	void unset_bars_padding();

	void show_grid_lines() { cv.show_horizontal_grid_lines(); };
	void set_unit(long double u) { cv.set_y_unit(u); };
	void set_min_value(long double m) { cv.set_y_min_value(m); };
	void set_max_value(long double m) { cv.set_y_max_value(m); };

	void sort_by_label(Order o = Order::Asc);
	void sort_by_value(Order o = Order::Asc);

	virtual int label_padding() const override { return pad_v; };
	virtual ch15_hlp::Text_alignment label_alignment() const override;

private:
	bool auto_pad_bars{true};
	int pad_bars;
	std::vector<Graph_lib::Color> color;
	std::vector<Graph_lib::Color> fill;

	virtual void upd_post_layout() override;
	void upd_colors();

	void show_horizontal_grid_lines();   /* hide base class methods */
	void show_vertical_grid_lines();     /*                         */
	void set_x_unit(long double u);      /*                         */
	void set_y_unit(long double u);      /*                         */
	void set_x_min_value(long double m); /*                         */
	void set_x_max_value(long double m); /*                         */
	void set_y_min_value(long double m); /*                         */
	void set_y_max_value(long double m); /*                         */
	void unset_x_min_value();            /*                         */
	void unset_x_max_value();            /*                         */
	void unset_y_min_value();            /*                         */
	void unset_y_max_value();            /*                         */
};
} // namespace chart

#endif // BAR_CHART_NEW_H
