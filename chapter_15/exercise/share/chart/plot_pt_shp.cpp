#include "chart.h"

void chart::draw_plot_point(Graph_lib::Point xy, Point_shape_type t, int size)
{
	int rad{static_cast<int>(std::round(size * 0.5))};
	switch (t) {
	case Point_shape_type::Point:
		fl_pie(xy.x, xy.y, size, size, 0, 360);
		break;
	case Point_shape_type::Circle: {
		int strk_w = (std::max)(1, static_cast<int>(std::round(size * 0.2)));
		fl_line_style(Graph_lib::Line_style::solid, strk_w);
		fl_circle(xy.x, xy.y, rad);
		fl_line_style(0);
		break;
	}
	case Point_shape_type::Diamond:
		int incr_rad{static_cast<int>(std::round(rad * 1.15))};
		fl_polygon(xy.x - incr_rad,
		           xy.y,
		           xy.x,
		           xy.y - incr_rad,
		           xy.x + incr_rad,
		           xy.y,
		           xy.x,
		           xy.y + incr_rad);
		break;
	}
}
