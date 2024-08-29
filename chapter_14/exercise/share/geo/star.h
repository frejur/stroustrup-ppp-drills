#ifndef STAR_H
#define STAR_H
#define _USE_MATH_DEFINES
#include "../../lib/Graph.h"
#include <cmath>

constexpr int default_radius{64};

namespace stella {

class Star : public Graph_lib::Closed_polyline
{
public:
	Star(Graph_lib::Point center, int num_pts, int radius = default_radius);

private:
	int r;
	int npts;
	Graph_lib::Point c;
};

// Helpers --------------------------------------------------------------------

int valid_num_pts(int num);

Graph_lib::Point pt_along_circle(Graph_lib::Point center,
                                 int radius,
                                 double angle);

int pts_distance(Graph_lib::Point pt_0, Graph_lib::Point pt_1);

double half_inters_angle(int num_pts, int radius, double angle);

} // namespace stella

#endif // STAR_H
