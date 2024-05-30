#ifndef REGULAR_POLY_H
#define REGULAR_POLY_H

#include "../../../lib/Graph.h"

namespace RPOL {

class RegularPolygon : public Graph_lib::Closed_polyline
{
public:
    RegularPolygon(
        Graph_lib::Point origin, int radius, int num_sides,
        float angle = 0
    );
	int radius() const { return r; };
	Graph_lib::Point center() const { return c; };
private:
    Graph_lib::Point origin;
    Graph_lib::Point c;
    int r, num_sides;
    float angle;
    void add_poly_points();
};

} // namespace RPOL

#endif // REGULAR_POLY_H
