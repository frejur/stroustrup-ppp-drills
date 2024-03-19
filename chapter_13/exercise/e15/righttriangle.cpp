#define _USE_MATH_DEFINES
#include "righttriangle.h"
#include <cmath>

namespace GL = Graph_lib;

RTRI::RightTriangle::RightTriangle(
	GL::Point origin, GL::Point end_opposite, int len_adjacent)
 : GL::Closed_polyline()
{
	add(origin);
	add(end_opposite);
	double angle{
		std::atan2(
			(double)end_opposite.y - origin.y,
			(double)end_opposite.x - origin.x
		)
	};
	angle += 0.25 * M_PI;
	add({
		static_cast<int>(std::round(origin.x + cos(angle) * len_adjacent)),
		static_cast<int>(std::round(origin.y + sin(angle) * len_adjacent))
	});
}

