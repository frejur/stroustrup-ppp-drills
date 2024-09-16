#define _USE_MATH_DEFINES
#include "pac.h"
#include <cmath>

void pac::Pacman::draw_lines() const
{
	int rr = radius();
	float full_a{pacman_open_jaw_angle * jaw};
	float offs_a = -static_cast<int>(dir) * 90;
	float half_a{full_a * 0.5f};

	if (fill_color().visibility()) {
		fl_color(fill_color().as_int());
		fl_pie(point(0).x,
		       point(0).y,
		       rr + rr,
		       rr + rr,
		       offs_a + half_a,
		       offs_a + 360 - half_a);
		fl_color(color().as_int()); // reset color
	}
	if (color().visibility()) {
		fl_arc(point(0).x,
		       point(0).y,
		       rr + rr,
		       rr + rr,
		       offs_a + half_a,
		       offs_a + 360 - half_a);
		if (jaw > 0) {
			fl_line(center().x
			            + std::cos((-offs_a - half_a) * M_PI / 180) * radius(),
			        center().y
			            + std::sin((-offs_a - half_a) * M_PI / 180) * radius(),
			        center().x,
			        center().y);
			fl_line(center().x,
			        center().y,
			        center().x
			            + std::cos((-offs_a + half_a) * M_PI / 180) * radius(),
			        center().y
			            + std::sin((-offs_a + half_a) * M_PI / 180) * radius());
		}
	}
}
