#ifndef INTERS_H
#define INTERS_H

#include "../../../lib/Graph.h"

namespace inters {

//------------------------------------------------------------------------------

inline double dot(Graph_lib::Point a, Graph_lib::Point b)
{
	return static_cast<double>(a.x * b.x + a.y * b.y);
}

inline float pt_dist(Graph_lib::Point p0, Graph_lib::Point p1)
{
	float dx = p1.x - p0.x;
	float dy = p1.y - p0.y;
	return sqrt(dx * dx + dy * dy);
}

inline float tri_area(Graph_lib::Point p0,
                      Graph_lib::Point p1,
                      Graph_lib::Point p2)
{
	float a = ((p1.x * p0.y - p0.x * p1.y) + (p2.x * p1.y - p1.x * p2.y)
	           + (p0.x * p2.y - p2.x * p0.y))
	          * 0.5;
	if (a < 0) {
		a *= -1;
	}
	return a;
}

//------------------------------------------------------------------------------
struct Bary_coords
{
	double v;
	double w;
	double u;
};

inline Bary_coords bary(Graph_lib::Point p,
                        Graph_lib::Point a,
                        Graph_lib::Point b,
                        Graph_lib::Point c)
{
	Graph_lib::Point v0 = {b.x - a.x, b.y - a.y};
	Graph_lib::Point v1 = {c.x - a.x, c.y - a.y};
	Graph_lib::Point v2 = {p.x - a.x, p.y - a.y};

	double d00 = dot(v0, v0);
	double d01 = dot(v0, v1);
	double d11 = dot(v1, v1);
	double d20 = dot(v2, v0);
	double d21 = dot(v2, v1);

	double denom = d00 * d11 - d01 * d01;
	if (denom == 0) {
		return {-1, -1, -1};
	}

	double v = (d11 * d20 - d01 * d21) / denom;
	double w = (d00 * d21 - d01 * d20) / denom;
	return {v, w, (1.0 - v - w)};
}

inline bool is_inside_tri(const Bary_coords& c)
{
	return 0 <= c.v && c.v <= 1 && 0 <= c.w && c.w <= 1 && (c.v + c.w) <= 1;
}

//------------------------------------------------------------------------------
// Calculates the intersection point of two lines
inline Graph_lib::Point intersect_pt(Graph_lib::Point pt_0,
                                     Graph_lib::Point pt_1,
                                     Graph_lib::Point pt_2,
                                     Graph_lib::Point pt_3)
{
	int den = (pt_3.y - pt_2.y) * (pt_1.x - pt_0.x)
	          - (pt_3.x - pt_2.x) * (pt_1.y - pt_0.y);
	int num = (pt_3.x - pt_2.x) * (pt_0.y - pt_2.y)
	          - (pt_3.y - pt_2.y) * (pt_0.x - pt_2.x);
	double q = static_cast<double>(num) / den;

	double x = static_cast<double>(pt_0.x + q * (pt_1.x - pt_0.x));
	double y = static_cast<double>(pt_0.y + q * (pt_1.y - pt_0.y));

	return {static_cast<int>(x * 10 + 5) / 10,
	        static_cast<int>(y * 10 + 0.5) / 10};
}

//------------------------------------------------------------------------------
// Checks if two line segments intersect
inline bool segments_intersect(Graph_lib::Point pt_0,
                               Graph_lib::Point pt_1,
                               Graph_lib::Point pt_2,
                               Graph_lib::Point pt_3)
{
	int d_0 = (pt_3.x - pt_2.x) * (pt_0.y - pt_2.y)
	          - (pt_3.y - pt_2.y) * (pt_0.x - pt_2.x);
	int d_1 = (pt_3.x - pt_2.x) * (pt_1.y - pt_2.y)
	          - (pt_3.y - pt_2.y) * (pt_1.x - pt_2.x);
	int d_2 = (pt_1.x - pt_0.x) * (pt_2.y - pt_0.y)
	          - (pt_1.y - pt_0.y) * (pt_2.x - pt_0.x);
	int d_3 = (pt_1.x - pt_0.x) * (pt_3.y - pt_0.y)
	          - (pt_1.y - pt_0.y) * (pt_3.x - pt_0.x);

	return ((d_0 > 0 && d_1 < 0) || (d_0 < 0 && d_1 > 0))
	       && ((d_2 > 0 && d_3 < 0) || (d_2 < 0 && d_3 > 0));
}

//------------------------------------------------------------------------------
// Checks if two polylines intersect
inline bool lines_intersect(const std::vector<Graph_lib::Point>& pts_a,
                            const std::vector<Graph_lib::Point>& pts_b)
{
	if (pts_a.size() < 3 || pts_b.size() < 3) {
		throw std::runtime_error(
		    "Cannot calculate intersection of incomplete shapes");
	}
	for (int a = 0; a < pts_a.size(); ++a) {
		int a_end_idx = (a == pts_a.size() - 1) ? 0 : a + 1;
		for (int b = 0; b < pts_b.size(); ++b) {
			int b_end_idx = (b == pts_b.size() - 1) ? 0 : b + 1;
			if (segments_intersect(pts_a[a],
			                       pts_a[a_end_idx],
			                       pts_b[b],
			                       pts_b[b_end_idx])) {
				return true;
			}
		}
	}

	return false;
}

} // namespace inters

#endif // INTERS_H
