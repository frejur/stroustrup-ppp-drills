#ifndef INSCR_POLY_H
#define INSCR_POLY_H

#include "../../lib/Graph.h"

class RegularPolygon : public Graph_lib::Closed_polyline
{
public:
    RegularPolygon(Graph_lib::Point origin, int radius, int num_sides, float angle = 0);
private:
    Graph_lib::Point origin;
    int radius, num_sides;
    float angle;
    void draw_poly();
};

#endif // INSCR_POLY_H
