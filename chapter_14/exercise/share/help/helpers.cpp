#define _USE_MATH_DEFINES
#include "helpers.h"
#include <cmath>

Graph_lib::Point ch14_hlp::point_at_angle(Graph_lib::Point center,
                                          double rotation,
                                          double distance)
{
	double radians = (rotation * (M_PI / 180)) - M_PI * 0.5;
	return {center.x + static_cast<int>(cos(radians) * distance),
	        center.y + static_cast<int>(sin(radians) * distance)};
}

//------------------------------------------------------------------------------

int ch14_hlp::val_from_f(int min_val, int max_val, double f)
{
	if (f < 0 || f > 1) {
		throw std::runtime_error(
		    "Invalid factor, expected a value between 0 and 1");
	}

	if (min_val >= max_val) {
		throw std::runtime_error("Min. val has to be less than max.");
	}
	return static_cast<int>(min_val + (max_val - min_val) * f);
}

//------------------------------------------------------------------------------

double apothem(int radius, int chord)
{
	return sqrt(radius * radius - (chord * chord) / 4);
}

//------------------------------------------------------------------------------

void ch14_hlp::draw_mark(Graph_lib::Point xy,
                         char c,
                         Graph_lib::Font fnt,
                         int fnt_sz,
                         Graph_lib::Color color)
{
	int ofnt = fl_font();
	int osz = fl_size();
	Fl_Color oldc = fl_color();
	fl_color(color.as_int());
	fl_font(fnt.as_int(), fnt_sz);
	std::string m(1, c); // string holding a single char c
	int offs_x{static_cast<int>(fl_width(m.c_str()) * 0.5)};
	fl_draw(m.c_str(), xy.x - offs_x, xy.y);
	fl_font(ofnt, osz);
	fl_color(oldc);
}

//------------------------------------------------------------------------------

Graph_lib::Point ch14_hlp::shape_min_xy(const Graph_lib::Shape& s)
{
	if (s.number_of_points() < 1) {
		throw std::runtime_error(
		    "Shape is empty, cannot calculate min. X and Y");
	}
	Graph_lib::Point min_xy{s.point(0)};
	for (int i = 1; i < s.number_of_points(); ++i) {
		if (s.point(i).x < min_xy.x) {
			min_xy.x = s.point(i).x;
		}
		if (s.point(i).y < min_xy.y) {
			min_xy.y = s.point(i).y;
		}
	}
	return min_xy;
}

Graph_lib::Point ch14_hlp::shape_max_xy(const Graph_lib::Shape& s)
{
	if (s.number_of_points() < 1) {
		throw std::runtime_error(
		    "Shape is empty, cannot calculate max. X and Y");
	}
	Graph_lib::Point max_xy{s.point(0)};
	for (int i = 1; i < s.number_of_points(); ++i) {
		if (s.point(i).x > max_xy.x) {
			max_xy.x = s.point(i).x;
		}
		if (s.point(i).y < max_xy.y) {
			max_xy.y = s.point(i).y;
		}
	}
	return max_xy;
}
