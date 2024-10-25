#ifndef REGULAR_POLY_H
#define REGULAR_POLY_H

#include "../../../lib/Graph.h"

namespace RPOL {

constexpr int min_radius{10};
constexpr int max_radius{1280};

class Regular_polygon : public Graph_lib::Closed_polyline
{
public:
	Regular_polygon(Graph_lib::Point origin,
	                int radius,
	                int number_of_sides,
	                double angle_degrees = 0);
	int radius() const { return r; };
	Graph_lib::Point center() const { return c; };
	double angle_radians() const { return angle; };
	void rotate(double offset_degrees);
	void move(int offset_x, int offset_y) override;
	void scale(double scale_f);

private:
	Graph_lib::Point c;
	int r, num_sides;
	double angle;

	std::vector<Graph_lib::Point> new_poly_points();
	void add_poly_points();
	void update_poly_points();
};

} // namespace RPOL

#endif // REGULAR_POLY_H
