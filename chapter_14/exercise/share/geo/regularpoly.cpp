#define _USE_MATH_DEFINES
#include "regularpoly.h"
#include "../help/helpers.h"
#include <cmath>
#include <stdexcept>
#include <vector>

namespace RPOL {

RPOL::RegularPolygon::RegularPolygon(Graph_lib::Point center,
                                     int radius,
                                     int number_of_sides,
                                     double angle_degrees)
    : c(center)
    , r(radius)
    , num_sides(number_of_sides)
    , angle{ch14_hlp::wrap_angle(angle_degrees * M_PI / 180)}
{
    // guard against incompatible numbers
    r = min(1280, max(10, r));
    num_sides = min(16, max(3, num_sides));

	add_poly_points();
}

//------------------------------------------------------------------------------

std::vector<Graph_lib::Point> RegularPolygon::new_poly_points()
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

void RPOL::RegularPolygon::add_poly_points()
{
	for (const Graph_lib::Point& pt : new_poly_points()) {
		add(pt);
	}
}

void RPOL::RegularPolygon::update_poly_points()
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

void RegularPolygon::rotate(double offset_degrees)
{
	angle = ch14_hlp::wrap_angle(angle + offset_degrees * M_PI / 180);
	update_poly_points();
}

} // namespace RPOL
