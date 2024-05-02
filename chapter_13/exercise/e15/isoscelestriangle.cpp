#define _USE_MATH_DEFINES
#include "isoscelestriangle.h"
#include <cmath>

namespace GL = Graph_lib;

ITRI::IsoscelesTriangle::IsoscelesTriangle(GL::Point origin,
                                           GL::Point end_opposite,
                                           double angle,
                                           bool invert)
    : GL::Closed_polyline()
{
	GL::Point offset{end_opposite.x - origin.x, end_opposite.y - origin.y};
	double side_len{
	    sqrt(pow(std::abs(offset.y), 2) + pow(std::abs(offset.x), 2))};
	double new_angle{std::atan2((double) offset.y, (double) offset.x) + angle};

	GL::Point apex{static_cast<int>(
	                   std::round(origin.x + cos(new_angle) * side_len)),
	               static_cast<int>(
	                   std::round(origin.y + sin(new_angle) * side_len))};
	if (invert) {
		add({apex.x + offset.x, apex.y + offset.y});
		add(apex);
		add(end_opposite);
	} else {
		add(origin);
		add(end_opposite);
		add(apex);
	}
}

