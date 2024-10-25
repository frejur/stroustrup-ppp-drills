#define _USE_MATH_DEFINES
#include "regularpoly.h"
#include "../help/helpers.h"
#include <cmath>
#include <stdexcept>
#include <vector>

namespace RPOL {

RPOL::Regular_polygon::Regular_polygon(Graph_lib::Point center,
                                       int radius,
                                       int number_of_sides,
                                       double angle_degrees)
    : c(center)
    , r(radius)
    , num_sides(number_of_sides)
    , angle{ch14_hlp::wrap_angle(angle_degrees * M_PI / 180)}
{
    // guard against incompatible numbers
	r = min(max_radius, max(min_radius, r));
	num_sides = min(16, max(3, num_sides));

	add_poly_points();
}

//------------------------------------------------------------------------------

std::vector<Graph_lib::Point> Regular_polygon::new_poly_points()
{
	std::vector<Graph_lib::Point> pts;
	double ang_incr{M_PI * 2.0 / num_sides};
	int this_x{0}, this_y{0};

	for (unsigned int i = 0; i < num_sides; ++i) {
		this_x = {(int) round(c.x + sin(M_PI - angle + ang_incr * i) * r)};
		this_y = {(int) round(c.y + cos(M_PI - angle + ang_incr * i) * r)};

		pts.push_back({this_x, this_y});
	}

	return pts;
}

void RPOL::Regular_polygon::add_poly_points()
{
	for (const Graph_lib::Point& pt : new_poly_points()) {
		add(pt);
	}
}

void RPOL::Regular_polygon::update_poly_points()
{
	std::vector<Graph_lib::Point> pts = new_poly_points();
	if (pts.size() < 1 || pts.size() != number_of_points()) {
		throw std::runtime_error("Invalid number of points");
	}
	for (int i = 0; i < pts.size(); ++i) {
		set_point(i, pts[i]);
	}
}

//------------------------------------------------------------------------------

void Regular_polygon::rotate(double offset_degrees)
{
	angle = ch14_hlp::wrap_angle(angle + offset_degrees * M_PI / 180);
	update_poly_points();
}

void Regular_polygon::move(int offset_x, int offset_y)
{
	Graph_lib::Shape::move(offset_x, offset_y);
	c.x += offset_x;
	c.y += offset_y;
}

void Regular_polygon::scale(double scale_f)
{
	if (scale_f <= 0) {
		throw std::runtime_error(
		    "Invalid scaling factor, expected a value > 0");
	}
	double new_r{scale_f * r};
	r = (std::min)(static_cast<double>(max_radius),
	               (std::max)(static_cast<double>(min_radius), new_r));
}

} // namespace RPOL
