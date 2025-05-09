#include "regularhexagon.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include <algorithm>

#include "../../lib/Graph.h"

RegularHexagon::RegularHexagon(Graph_lib::Point xy, int radius)
	: RegularPolygon({ xy.x + radius, xy.y }, radius, num_sides, 90 * M_PI/180),
	side_states( std::vector<bool>(num_sides, true))
{
	Graph_lib::Shape::set_color(Graph_lib::Color::black);
	set_font_size(8);
}

void RegularHexagon::close_side(int n)
{
	side_states[n%num_sides] = false;
}

void RegularHexagon::close_sides_before(int n)
{
	std::fill(side_states.begin(), side_states.begin() + n, false);
}

bool RegularHexagon::side_is_open(int n) const
{
	return side_states[n%num_sides];
}

void RegularHexagon::draw_lines() const
{
	RegularPolygon::draw_lines();

//	Fl_Font old_font{ fl_font() };
//	Fl_Fontsize old_sz{ fl_size() };
//	fl_font(font().as_int(), font_size());
//	for (int i=0; i < 6; ++i) {
//		std::string s{ std::to_string(i) };
//		auto bbox{ get_bbox_size(s) };
//		int x{
//			static_cast<int>(
//				(point(i).x + point((i+1)%6).x + center().x) / 3
//				- static_cast<int>(0.5 * bbox.first)
//			)
//		};
//		int y{
//			static_cast<int>(
//				(point(i).y + point((i+1)%6).y + center().y) / 3
//				+ static_cast<int>(0.5 * bbox.second)
//			)
//		};
//		Fl_Color oc = fl_color();
//		fl_color((side_is_open(i)) ? 68 : FL_RED);
//		fl_draw(std::to_string(i).c_str(), x, y);
//		fl_color(oc);
//	}
//	fl_font(old_font, old_sz);
}

std::pair<int, int> RegularHexagon::get_bbox_size(const string &s) const {
	int mv_x = 0, mv_y = 0, sz_x = 0, sz_y = 0;
	Fl_Font old_font{ fl_font() };
	Fl_Fontsize old_sz{ fl_size() };
	fl_font(font().as_int(), font_size());
	fl_text_extents(s.c_str(), mv_x, mv_y, sz_x, sz_y);
	fl_font(old_font, old_sz);
	return std::pair<int, int>(sz_x, sz_y);
}
