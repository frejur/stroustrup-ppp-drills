#define _USE_MATH_DEFINES
#include "isoscelestriangle.h"
#include <cmath>

namespace GL = Graph_lib;

itri::IsoscelesTriangle::IsoscelesTriangle(GL::Point origin,
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

itri::IsoscelesTriangle::IsoscelesTriangle(Graph_lib::Point base_pt,
                                           int width,
                                           int height,
                                           double rotation)
{
	int half_w{static_cast<int>(width * 0.5)};
	double rot_rad = rotation * (M_PI / 180);

	// Calculate the offset for the base points
	Graph_lib::Point rot_offs{static_cast<int>(cos(rot_rad) * half_w),
	                          static_cast<int>(sin(rot_rad) * half_w)};

	Graph_lib::Point
	    apex{base_pt.x + static_cast<int>(cos(rot_rad - M_PI * 0.5) * height),
	         base_pt.y + static_cast<int>(sin(rot_rad - M_PI * 0.5) * height)};

	add({base_pt.x - rot_offs.x, base_pt.y - rot_offs.y});
	add(apex);
	add({base_pt.x + rot_offs.x, base_pt.y + rot_offs.y});
}
