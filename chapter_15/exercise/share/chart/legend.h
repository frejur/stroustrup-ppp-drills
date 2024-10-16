#ifndef LEGEND_H
#define LEGEND_H
#include "scatter_plot.h"

namespace chart {

enum class Legend_flow { Horizontal, Vertical };
enum class Legend_type { Color, Shape };

struct Legend
{
	Legend(const std::string& label_val,
	       Point_shape_type shape_type_val,
	       Graph_lib::Color color_val = Graph_lib::Color::black)
	    : legend_type(Legend_type::Shape)
	    , shape_type(shape_type_val)
	    , color(color_val)
	    , label(label_val){};
	Legend(const std::string& label_val, Graph_lib::Color color_val)
	    : legend_type(Legend_type::Color)
	    , shape_type(static_cast<Point_shape_type>(0))
	    , color(color_val)
	    , label(label_val){};
	Legend_type legend_type;
	Point_shape_type shape_type;
	Graph_lib::Color color;
	std::string label;
};

class Legend_box : public Graph_lib::Shape
{
public:
	Legend_box(Graph_lib::Point top_left,
	           int font_size,
	           Legend_flow element_flow);
	void add_color_legend(const std::string& label, Graph_lib::Color color)
	{
		leg.push_back({label, color});
	};
	void add_shape_legend(const std::string& label, Point_shape_type shape_type)
	{
		leg.push_back({label, shape_type, color()});
	};
	virtual void draw_lines() const;
	Graph_lib::Point top_left_corner() const { return point(0); };
	int width() const { return calc_w(); };
	int height() const { return calc_h(); };

private:
	int fnt_sz;
	int pad_h;
	int pad_v;
	int swatch_h;
	int swatch_w;
	int shp_sz;
	Legend_flow flow;
	std::vector<Legend> leg;
	Graph_lib::Font fnt;

	int calc_w() const;
	int calc_h() const;
	int valid_pad(int p) const;
	int valid_fnt_sz(int sz) const;
	void draw_frame() const;
	void draw_swatch(Graph_lib::Point xy,
	                 Graph_lib::Color color,
	                 int width,
	                 int h) const;
	std::string comb_lb() const;
	int max_lb_w() const;
	int num_shp() const;
};
} // namespace chart

#endif // LEGEND_H
