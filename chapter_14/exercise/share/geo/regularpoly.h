#ifndef REGULAR_POLY_H
#define REGULAR_POLY_H

#include "../../../lib/Graph.h"

namespace RPOL {

class RegularPolygon : public Graph_lib::Closed_polyline
{
public:
	RegularPolygon(Graph_lib::Point origin,
	               int radius,
	               int number_of_sides,
	               double angle_degrees = 0);
	int radius() const { return r; };
	Graph_lib::Point center() const { return c; };
	void rotate(double offset_degrees);
	void move(int offset_x, int offset_y) override;

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
