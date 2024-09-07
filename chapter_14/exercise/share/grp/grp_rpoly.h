#define _USE_MATH_DEFINES
#ifndef R_POLY_GROUP_H
#define R_POLY_GROUP_H
#include "../geo/regularpoly.h"
#include "../help/helpers.h"
#include "grp_shp.h"
#include <cmath>

namespace grp_shp {

class Relative_r_poly : public RPOL::Regular_polygon
{
public:
	Relative_r_poly(Graph_lib::Point global_origin,
	                Graph_lib::Point local_origin,
	                int radius,
	                int number_of_sides,
	                double angle_degrees = 0)
	    : RPOL::Regular_polygon::Regular_polygon(local_origin,
	                                             radius,
	                                             number_of_sides,
	                                             angle_degrees)
	    , init_origin(local_origin)
	    , init_radius(radius)
	    , init_angle(angle_degrees)
	    , rel_dist(calc_rel_dist(global_origin))
	    , rel_angle(calc_rel_angle(global_origin)){};
	double relative_distance() const { return rel_dist; };
	double relative_angle() const { return rel_angle; };
	void update_relative_distance(Graph_lib::Point new_global_origin)
	{
		rel_dist = calc_rel_dist(new_global_origin);
	}
	void set_relative_distance(double new_distance) { rel_dist = new_distance; }
	void update_relative_angle(Graph_lib::Point new_global_origin)
	{
		rel_angle = calc_rel_angle(new_global_origin);
	}
	void set_relative_angle(double new_angle) { rel_angle = new_angle; }

private:
	// Initial values
	const Graph_lib::Point init_origin;
	const int init_radius;
	const int init_angle;
	// Values relative to the global origin
	double rel_dist;
	double rel_angle;
	// Calculate
	double calc_rel_dist(Graph_lib::Point new_global_origin)
	{
		return ch14_hlp::distance_between(center(), new_global_origin);
	};
	double calc_rel_angle(Graph_lib::Point new_global_origin)
	{
		return ch14_hlp::angle_between(center(), new_global_origin) * 180
		       / M_PI;
	};
};

class R_poly_group : public Shape_group
{
public:
	using Shape_group::Shape_group;
	// Global
	void scale(double scale_factor);
	void rotate(double offset_degrees);
	void rotate_around_origin(double offset_degrees);

	// Element-wise
	void scale(double scale_factor, int element_index);
	void rotate(double offset_degrees, int element_index);
	int radius(int elem_index) const;
	Graph_lib::Point center(int elem_index) const;

	// Container
	void add(Graph_lib::Point center,
	         int radius,
	         int number_of_sides,
	         double angle_degrees = 0);

private:
	void add(Graph_lib::Shape& shape){}; // Hide
	void add(Graph_lib::Shape* shape){}; // Hide

	// Element-wise, relative to group origin
	double relative_distance(int elem_index) const;
	double relative_angle(int elem_index) const;
	void update_relative_distance(int elem_index);
	void update_relative_angle(int elem_index);
	void set_relative_distance(int elem_index, double new_distance);
	void set_relative_angle(int elem_index, double new_angle);

	// Set local attributes without updating relative attributes
	void set_position(int x, int y, int elem_index);

	void move_elem_to_rot_pos(double offset_degrees, int element_index);
};

} // namespace grp_shp

#endif // R_POLY_GROUP_H
