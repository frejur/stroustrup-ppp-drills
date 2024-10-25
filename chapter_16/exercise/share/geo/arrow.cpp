#include "arrow.h"
#include <math.h>

namespace GL = Graph_lib;

Arrow::Arrow(GL::Point origin, GL::Point end)
    : is_hidden(false)
{
	add(origin);
	add(end);
}

void Arrow::draw_lines() const
{
	if (is_hidden) {
		return;
	}
	Graph_lib::Color ocol = fl_color();
	fl_color(color().as_int());
	fl_line(point(0).x, point(0).y, point(1).x, point(1).y);
	draw_arrow(point(0), point(1));
	fl_color(ocol.as_int());
}

void Arrow::draw_arrow(GL::Point origin, GL::Point end) const
{
	if (is_hidden) {
		return;
	}
	float angle = atan2(end.y - origin.y, end.x - origin.x);
	draw_arrow_head(end, angle);
}

void Arrow::draw_arrow_head(GL::Point end, float angle) const
{
	constexpr float hd_ang{ 0.4 }; // Arrow head angle (Roughly 30 deg)
	constexpr float hd_size{ 8 };
	fl_begin_complex_polygon();
	Graph_lib::Point pt_a{static_cast<int>(
	                          round(end.x - hd_size * cos(angle + hd_ang))),
	                      static_cast<int>(
	                          round(end.y - hd_size * sin(angle + hd_ang)))};
	fl_vertex(pt_a.x, pt_a.y);
	Graph_lib::Point pt_b{static_cast<int>(
	                          round(end.x - hd_size * cos(angle - hd_ang))),
	                      static_cast<int>(
	                          round(end.y - hd_size * sin(angle - hd_ang)))};
	fl_vertex(pt_b.x, pt_b.y);
	fl_vertex(end.x, end.y);
	fl_end_complex_polygon();
}

void Arrow::new_start_and_end_points(Graph_lib::Point start,
                                     Graph_lib::Point end)
{
	set_point(0, start);
	set_point(1, end);
}
