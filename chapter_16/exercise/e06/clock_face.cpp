#include "clock_face.h"
#include "../share/ch16_helpers.h"
#include <sstream>

namespace {
const int min_radius = 64;
const int max_radius = 500;
} // namespace

int Clock_face::notch_min_len = 5;
int Clock_face::notch_hour_len = 6;

Clock_face::Clock_face(Graph_lib::Point center, int radius)
    : r(valid_r(radius))
    , fsz(24)
{
	add(center);
}
void Clock_face::draw_lines() const
{
	if (fill_color().visibility()) {
		Graph_lib::Color ocol = fl_color();
		fl_color(fill_color().as_int());
		fl_pie(center().x, center().y, radius(), radius(), 0, 360);
		fl_color(ocol.as_int());
	}

	if (color().visibility()) {
		std::ostringstream os;
		for (int i = 1; i <= 60; ++i) {
			bool is_hour = false;
			if ((i - 1) % 5 == 0) {
				is_hour = true;

				// Draw digits
				int h = (i - 1) % 12;
				os.str("");
				os << ((h == 0) ? 12 : h);

				Graph_lib::Point dig_xy{
				    ch16_hlp::point_at_angle(center(),
				                             30 * h,
				                             radius() - font_size() * 0.65
				                                 - notch_hour_len)};
				ch16_hlp::draw_text(dig_xy,
				                    os.str(),
				                    font(),
				                    font_size(),
				                    color(),
				                    ch16_hlp::Text_alignment::Center);
			}
			// Draw notches
			int notch_len = is_hour ? notch_hour_len : notch_min_len;
			int notch_thk = is_hour ? 3 : 1;
			Graph_lib::Point start_xy{
			    ch16_hlp::point_at_angle(center(),
			                             6 * (i - 1),
			                             radius() - notch_len)};
			Graph_lib::Point end_xy{
			    ch16_hlp::point_at_angle(center(), 6 * (i - 1), radius())};
			fl_line_style(Graph_lib::Line_style::solid, notch_thk);
			fl_line(start_xy.x, start_xy.y, end_xy.x, end_xy.y);
			fl_line_style(0);
		}
	}
}

//------------------------------------------------------------------------------

int Clock_face::valid_r(int r) const
{
	if (r < min_radius || r > max_radius) {
		throw std::runtime_error("Invalid radius, expected a value between "
		                         + std::to_string(min_radius) + " and "
		                         + std::to_string(max_radius) + " but got "
		                         + std::to_string(r));
	}
	return r;
}
