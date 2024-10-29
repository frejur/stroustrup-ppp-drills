#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

#include "../../lib/Graph.h"

class Progress_bar : public Graph_lib::Shape
{
public:
	Progress_bar(Graph_lib::Point top_left,
	             int width,
	             int height,
	             Graph_lib::Color color = default_col,
	             Graph_lib::Color fill_color = default_fill,
	             Graph_lib::Color background_color = default_bg);
	void set_value(double v);
	double value() const { return st_val; };
	Graph_lib::Point position() const { return point(0); };
	int width() const { return w; };
	int height() const { return h; };

	void draw_lines() const override;

	Graph_lib::Color background_color() const { return bg_col; };
	void set_background_color(Graph_lib::Color c) { bg_col = c; };

private:
	static const Graph_lib::Color default_col;
	static const Graph_lib::Color default_fill;
	static const Graph_lib::Color default_bg;
	int w;
	int h;
	double st_val;
	Graph_lib::Color bg_col;

	int valid_st_val(int v) const;
	int valid_w(int n) const;
	int valid_h(int n) const;
};

#endif // PROGRESS_BAR_H
