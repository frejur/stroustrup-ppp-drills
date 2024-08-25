#include "star.h"

stella::Star::Star(Graph_lib::Point center, int num_pts, int radius)
    : r(radius)
    , npts(valid_num_pts(num_pts))
    , c(center)
{
	// Angle between points on the unit circle
	double mid_angle{M_PI * 2.0 / npts};

	// Calculate the next outer point on the unit circle
	Graph_lib::Point nxt_pt{pt_along_circle({0, 0}, r, mid_angle)};

	// Calculate midpoint between top point and next outer point
	Graph_lib::Point mid_pt{static_cast<int>(round((nxt_pt.x) * 0.5)),
	                        static_cast<int>(round((nxt_pt.y - r) * 0.5))};

	int top_mid_dist{pts_distance({0, -r}, mid_pt)};

	// Angle where the 'rays' of the star intersect, split in half
	double half_x_angle = (npts == 6) ? (0.5 * ((npts - 2) * M_PI) / npts)
	                                  : half_inters_angle(npts, r, mid_angle);

	int o_mid_dist{pts_distance({0, 0}, mid_pt)};

	// Distance between origin and inner intersection points.
	int o_inx_dist{static_cast<int>(round(top_mid_dist / tan(half_x_angle)))};
	o_inx_dist *= (o_inx_dist < 0) ? -1 : 1;

	// Radius of inner ngon (And inner points)
	int in_r = o_mid_dist - o_inx_dist;

	for (int i = 0; i < (npts * 2); ++i) {
		if (i % 2 == 0) {
			add(pt_along_circle(c, r, mid_angle * i * 0.5));
		} else {
			add(pt_along_circle(c, in_r, mid_angle * i * 0.5));
		}
	}
}

// Helpers --------------------------------------------------------------------

int stella::valid_num_pts(int num)
{
	if (num < 5) {
		throw std::runtime_error("Invalid number of points");
	}
	return num;
}

Graph_lib::Point stella::pt_along_circle(Graph_lib::Point center,
                                         int radius,
                                         double angle)
{
	if (radius < 1) {
		throw std::runtime_error("Invalid radius value");
	}
	int x{static_cast<int>(round(center.x + cos(angle - M_PI * 0.5) * radius))};
	int y{static_cast<int>(round(center.y + sin(angle - M_PI * 0.5) * radius))};
	return {x, y};
}

int stella::pts_distance(Graph_lib::Point pt_0, Graph_lib::Point pt_1)
{
	int x_dist{pt_0.x - pt_1.x};
	int y_dist{pt_0.y - pt_1.y};
	return static_cast<int>(round(sqrt(x_dist * x_dist + y_dist * y_dist)));
}
double stella::half_inters_angle(int num_pts, int radius, double angle)
{
	// Calculate angle where the 'rays' of the star intersect, split in half

	// Calculate position of the outer point on the same 'path' as the first
	int path_pt_num = (num_pts % 2 == 0) ? num_pts / 2 - 1 : num_pts / 2;
	Graph_lib::Point path_pt{
	    pt_along_circle({0, 0}, radius, angle * path_pt_num)};

	// Calculate angle of half a 'ray'
	double half_ray_angle{atan2(path_pt.x, path_pt.y * 2)};

	double mid_tri_angle = M_PI * 0.5 - angle * 0.5;

	return M_PI * 0.5 - (mid_tri_angle - half_ray_angle);
}
