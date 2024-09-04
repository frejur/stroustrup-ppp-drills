#define _USE_MATH_DEFINES
#include "helpers.h"
#include <algorithm>
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

double ch14_hlp::wrap_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);

	if (angle < 0) {
		angle += 2 * M_PI;
	}

	return angle;
}

//------------------------------------------------------------------------------

double ch14_hlp::apothem(int radius, int chord)
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
		if (s.point(i).y > max_xy.y) {
			max_xy.y = s.point(i).y;
		}
	}
	return max_xy;
}

//------------------------------------------------------------------------------

bool ch14_hlp::scanline_has_intersection(int scan_y, Line_points line)
{
	if (scan_y == line.start.y && line.start.y == line.end.y) {
		return false;
	}
	return (scan_y <= line.start.y && scan_y >= line.end.y)
	       || (scan_y <= line.end.y && scan_y >= line.start.y);
}

Graph_lib::Point ch14_hlp::scanline_intersection_point(int scan_y,
                                                       Line_points line)
{
	int x_delta = line.end.x - line.start.x;
	int y_delta = line.end.y - line.start.y;
	int xsect_x = line.start.x + (scan_y - line.start.y) * x_delta / y_delta;
	return {xsect_x, scan_y};
}

std::vector<int> ch14_hlp::scanline_sorted_intersection_x_coords(
    int scan_y, const std::vector<Graph_lib::Point>& points)
{
	std::vector<int> inters_x;

	for (int i = 0; i < points.size(); ++i) {
		int j = (i == points.size() - 1) ? 0 : i + 1;
		ch14_hlp::Line_points ln{points[i], points[j]};
		if (scanline_has_intersection(scan_y, ln)) {
			inters_x.push_back(scanline_intersection_point(scan_y, ln).x);
		}
	}

	std::sort(inters_x.begin(), inters_x.end());
	return inters_x;
}

std::vector<int> ch14_hlp::scanline_sorted_intersection_x_coords(
    int scan_y, const Graph_lib::Closed_polyline& polyline)
{
	std::vector<int> inters_x;

	for (int i = 0; i < polyline.number_of_points(); ++i) {
		int j = (i == polyline.number_of_points() - 1) ? 0 : i + 1;
		ch14_hlp::Line_points ln{polyline.point(i), polyline.point(j)};
		if (scanline_has_intersection(scan_y, ln)) {
			inters_x.push_back(scanline_intersection_point(scan_y, ln).x);
		}
	}

	std::sort(inters_x.begin(), inters_x.end());
	return inters_x;
}

//------------------------------------------------------------------------------

ch14_hlp::Polyline_v_dir ch14_hlp::Polyline_vertical_direction(
    const Graph_lib::Point& start,
    const Graph_lib::Point& mid,
    const Graph_lib::Point& end)
{
	Polyline_v_dir d = Polyline_v_dir::Flat;
	if (start.y < mid.y && end.y < mid.y) {
		d = Polyline_v_dir::Down;
	} else if (start.y > mid.y && end.y > mid.y) {
		d = Polyline_v_dir::Up;
	}
	return d;
}

ch14_hlp::Polyline_h_dir ch14_hlp::Polyline_horizontal_direction(
    const Graph_lib::Point& start,
    const Graph_lib::Point& mid,
    const Graph_lib::Point& end)
{
	Polyline_h_dir d = Polyline_h_dir::Flat;
	if (start.x < mid.x && end.x < mid.x) {
		d = Polyline_h_dir::Right;
	} else if (start.x > mid.x && end.x > mid.x) {
		d = Polyline_h_dir::Left;
	}
	return d;
}
