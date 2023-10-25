#define _USE_MATH_DEFINES
#include "regularpoly.h"
#include <cmath>

RegularPolygon::RegularPolygon(
    Graph_lib::Point o, int rr, int n, float a
) :
    origin ( o ), r ( rr ), num_sides ( n ),
    angle { a }
{
    // guard against incompatible numbers
    r = min(1280, max(10, r));
    num_sides = min(16, max(3, num_sides));

    draw_poly();
}

void RegularPolygon::draw_poly()
{
    double ang_incr { M_PI * 2.0 / num_sides };
    int this_x { 0 }, this_y { 0 },
        offset_x{ 0 }, offset_y{ 0 };

    for (unsigned int i = 0; i < num_sides ; ++i) {
        this_x = {
            (int)round(
                origin.x +
                sin(M_PI - angle + ang_incr * i) * r
            )
        };
        this_y = {
            (int)round(
                origin.y +
                cos(M_PI - angle + ang_incr * i) * r
            )
        };
        if (i == 0) {
            add(origin);
            offset_x = this_x - origin.x;
            offset_y = this_y - origin.y;
            continue;
        }
        add({ this_x - offset_x, this_y - offset_y });
    }
}

