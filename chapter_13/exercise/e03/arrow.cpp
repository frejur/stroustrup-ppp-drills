#include "arrow.h"
#include <math.h>

namespace GL = Graph_lib;

Arrow::Arrow(GL::Point origin, GL::Point end)
{
	draw_arrow(origin, end);
}

void Arrow::draw_arrow(GL::Point origin, GL::Point end)
{
	float angle = atan2(end.y - origin.y, end.x - origin.x);
	draw_line(origin, end);
	draw_arrow_head(end, angle);
	set_fill_color(GL::Color::black);
}

void Arrow::draw_line(GL::Point origin, GL::Point end)
{
	add(origin);
	add(end);
}

void Arrow::draw_arrow_head(GL::Point end, float angle)
{
	constexpr float hd_ang{ 0.4 }; // Arrow head angle (Roughly 30 deg)
	constexpr float hd_size{ 12 };
	add(end);
	add
	(
		{ static_cast<int>(round(end.x - hd_size * cos(angle + hd_ang))),
		  static_cast<int>(round(end.y - hd_size * sin(angle + hd_ang))) }
	);
	add
	(
		{ static_cast<int>(round(end.x - hd_size * cos(angle - hd_ang))),
		  static_cast<int>(round(end.y - hd_size * sin(angle - hd_ang))) }
	);
	add(end);
}
