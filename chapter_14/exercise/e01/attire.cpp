#define _USE_MATH_DEFINES
#include "attire.h"
#include "../share/help/helpers.h"
#include "emoticons.h"
#include <cmath>
#include <string>

//------------------------------------------------------------------------------

Graph_lib::Point emot::point_at_angle(Graph_lib::Point center,
                                      double rotation,
                                      double distance)
{
	double radians = (rotation * (M_PI / 180)) - M_PI * 0.5;
	return {center.x + static_cast<int>(cos(radians) * distance),
	        center.y + static_cast<int>(sin(radians) * distance)};
}

int emot::val_from_f(int min_val, int max_val, double f)
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

void emot::draw_mark(Graph_lib::Point xy,
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

Graph_lib::Point emot::shape_min_xy(const Graph_lib::Shape& s)
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
//------------------------------------------------------------------------------

emot::Conical_hat::Conical_hat(Graph_lib::Point position,
                               int width,
                               int height,
                               double rotation)
    : w(width)
    , rot(rotation)
    , base_pt(position)
    , cone(base_pt, width, static_cast<int>(width * 1.25), rot)
{
	cone.set_color(Graph_lib::Color::black);
	cone.set_fill_color(Graph_lib::Color::blue);
}

emot::Conical_hat::Conical_hat(const Emoticon& head,
                               double width_f,
                               double height_f,
                               double rotation)
    : w(val_from_f(head.radius(),
                   static_cast<int>(head.radius() * 1.75),
                   width_f))
    , h(val_from_f(head.radius() * 0.5, head.radius() * 3, height_f))
    , rot(rotation)
    , base_pt(point_at_angle(head.center(),
                             rotation,
                             ch14_hlp::apothem(head.radius(),
                                               static_cast<int>(w * 0.9))))
    , cone(base_pt, w, h, rot)
{}

void emot::Conical_hat::draw_lines() const
{
	cone.draw_lines();
}

//------------------------------------------------------------------------------

emot::Dunce_hat::Dunce_hat(Graph_lib::Point position, int width, double rotation)
    : Conical_hat(position, width, width * 2, rotation)
{
	cone.set_color(Graph_lib::Color::black);
	cone.set_fill_color(50);
}

emot::Dunce_hat::Dunce_hat(const Emoticon& head)
    : Conical_hat(head, 1, 1, 3)
{
	cone.set_color(Graph_lib::Color::black);
	cone.set_fill_color(50);
};
void emot::Dunce_hat::draw_lines() const
{
	cone.draw_lines();
	draw_mark(point_at_angle(base_pt, rot, h * 0.05),
	          txt,
	          Graph_lib::Font::helvetica_bold,
	          static_cast<int>(w / 1.6),
	          Graph_lib::Color::black);
}

//------------------------------------------------------------------------------

emot::Party_hat::Party_hat(Graph_lib::Point position,
                           int width,
                           const string& pattern_path,
                           double rotation)
    : Conical_hat(position, width, width * 2, rotation)
    , pattern(shape_min_xy(cone), pattern_path)
    , st(cone.point(1), 21, static_cast<int>(width * 0.3))
{
	cone.set_color(Graph_lib::Color::invisible);
	cone.set_fill_color(Graph_lib::Color::invisible);
	pattern.set_poly_mask(cone, 75, 100);
	st.set_color(Graph_lib::Color::invisible);
	st.set_fill_color(Graph_lib::Color::red);
}

emot::Party_hat::Party_hat(const Emoticon& head, const string& pattern_path)
    : Conical_hat(head, 0.8, 0.5, -9)
    , pattern(shape_min_xy(cone), pattern_path)
    , st(cone.point(1), 21, static_cast<int>(head.radius() * 0.3))
{
	cone.set_color(Graph_lib::Color::invisible);
	cone.set_fill_color(Graph_lib::Color::invisible);
	pattern.set_poly_mask(cone, 75, 100);
	st.set_color(Graph_lib::Color::invisible);
	st.set_fill_color(Graph_lib::Color::red);
}

void emot::Party_hat::draw_lines() const
{
	pattern.draw_lines();
	cone.draw_lines();
	st.draw_lines();
}
