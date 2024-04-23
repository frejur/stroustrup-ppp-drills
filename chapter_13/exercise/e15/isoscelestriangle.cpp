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
	add(origin);
	add(end_opposite);
	double side_len {
		sqrt(
			pow(std::abs(end_opposite.y - origin.y), 2) +
			pow(std::abs(end_opposite.x - origin.x), 2)
		)
		};
	double new_angle{std::atan2((double) end_opposite.y - origin.y,
	                            (double) end_opposite.x - origin.x)
	                 + angle};
	float sign{invert ? -1.0f : 1.0f};
	add({static_cast<int>(
	         std::round(origin.x + cos(new_angle) * sign * side_len)),
	     static_cast<int>(
	         std::round(origin.y + sin(new_angle) * sign * side_len))});
}

