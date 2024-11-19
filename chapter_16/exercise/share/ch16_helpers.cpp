#define _USE_MATH_DEFINES
#include "ch16_helpers.h"
#include <cmath>

ch16_hlp::Text_extents ch16_hlp::calc_lb_ext(const std::string& txt,
                                             Graph_lib::Font f,
                                             int f_sz)
{
	int dummy; // not needed
	int w, h;
	int font_backup = fl_font();
	int size_backup = fl_size();
	fl_font(f.as_int(), f_sz);
	fl_text_extents(txt.c_str(), dummy, dummy, w, h);
	fl_font(font_backup, size_backup);
	return {w, h};
};

int ch16_hlp::calc_lb_w(const std::string& txt, Graph_lib::Font f, int f_sz)
{
	return calc_lb_ext(txt, f, f_sz).width;
}

int ch16_hlp::calc_lb_h(const std::string& txt, Graph_lib::Font f, int f_sz)
{
	return calc_lb_ext(txt, f, f_sz).height;
}

void ch16_hlp::draw_text(Graph_lib::Point xy,
                         const string& text,
                         Graph_lib::Font font,
                         int font_size,
                         Graph_lib::Color text_color,
                         Text_alignment alignment,
                         int px_offset)
{
	if (text.empty()) {
		return;
	}
	int ofnt = fl_font();
	int osz = fl_size();
	int ocol = fl_color();
	fl_font(font.as_int(), font_size);
	fl_color(text_color.as_int());
	Text_extents ext = calc_lb_ext(text, font, font_size);
	int offs_x = 0;
	int offs_y = static_cast<int>(std::round(font_size * 0.5));
	if (alignment == Text_alignment::Right) {
		offs_x = px_offset;
	} else {
		if (alignment == Text_alignment::Left) {
			offs_x = -(ext.width + px_offset);
		} else {
			offs_x = -(static_cast<int>(std::round(ext.width * 0.5)));
		}

		if (alignment == Text_alignment::Top) {
			offs_y -= ext.height + px_offset;
		} else if (alignment == Text_alignment::Bottom) {
			offs_y += ext.height + px_offset;
		}
	}
	fl_draw(text.c_str(), xy.x + offs_x, xy.y - fl_descent() + offs_y);
	fl_font(ofnt, osz);
	fl_color(ocol);
}

//------------------------------------------------------------------------------

Graph_lib::Point ch16_hlp::point_at_angle(Graph_lib::Point center,
                                          double rotation,
                                          double distance)
{
	double radians = (rotation * (M_PI / 180)) - M_PI * 0.5;
	return {center.x + static_cast<int>(cos(radians) * distance),
	        center.y + static_cast<int>(sin(radians) * distance)};
}

double ch16_hlp::distance_between(Graph_lib::Point a, Graph_lib::Point b)
{
	double tmp{static_cast<double>(a.x - b.x) * (a.x - b.x)
	           + (a.y - b.y) * (a.y - b.y)};
	return tmp == 0 ? 0 : sqrt(tmp);
}

double ch16_hlp::angle_between(Graph_lib::Point a, Graph_lib::Point b)
{
	return atan2(static_cast<double>(a.y - b.y), static_cast<double>(a.x - b.x));
}

//------------------------------------------------------------------------------

int ch16_hlp::val_from_f(int min_val, int max_val, double f)
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

double ch16_hlp::wrap_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);

	if (angle < 0) {
		angle += 2 * M_PI;
	}

	return angle;
}
