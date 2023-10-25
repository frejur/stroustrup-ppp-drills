#ifndef REGULAR_POLY_H
#define REGULAR_POLY_H

#include "../../lib/Graph.h"

class RegularPolygon : public Graph_lib::Closed_polyline
{
public:
    RegularPolygon(
        Graph_lib::Point origin, int radius, int num_sides,
        float angle = 0
    );
	int radius() const { return r; };
private:
    Graph_lib::Point origin;
    int r, num_sides;
    float angle;
    void draw_poly();
};

#endif // REGULAR_POLY_H
