#define _USE_MATH_DEFINES
#include "grp_rpoly.h"
#include "../geo/regularpoly.h"
#include "../help/helpers.h"
#include <cmath>

void grp_shp::R_poly_group::scale(double scale_factor)
{
	for (int i = 0; i < elem.size(); ++i) {
		scale(scale_factor, i);
	}
}

void grp_shp::R_poly_group::rotate(double offset_degrees)
{
	for (int i = 0; i < elem.size(); ++i) {
		rotate(offset_degrees, i);
	}
}

void grp_shp::R_poly_group::rotate_around_origin(double offset_degrees)
{
	if (ch14_hlp::wrap_angle(offset_degrees * M_PI / 180) == 0) {
		return;
	}
	for (int i = 0; i < elem.size(); ++i) {
		if (i > 1) {
			return;
		}
		move_elem_to_rot_pos(offset_degrees, i);
		rotate(offset_degrees, i);
	}
}

//------------------------------------------------------------------------------

void grp_shp::R_poly_group::scale(double scale_factor, int element_index)
{
	Relative_r_poly& p{
	    dynamic_cast<Relative_r_poly&>(elem[valid_index(element_index)])};
	p.scale(scale_factor);
}

void grp_shp::R_poly_group::rotate(double offset_degrees, int element_index)
{
	Relative_r_poly& p{
	    dynamic_cast<Relative_r_poly&>(elem[valid_index(element_index)])};
	p.rotate(offset_degrees);
}

int grp_shp::R_poly_group::radius(int element_index) const
{
	const Relative_r_poly& p{
	    dynamic_cast<const Relative_r_poly&>(elem[valid_index(element_index)])};
	return p.radius();
}

Graph_lib::Point grp_shp::R_poly_group::center(int element_index) const
{
	const Relative_r_poly& p{
	    dynamic_cast<const Relative_r_poly&>(elem[valid_index(element_index)])};
	return p.center();
}

//------------------------------------------------------------------------------

void grp_shp::R_poly_group::add(Graph_lib::Point center,
                                int radius,
                                int number_of_sides,
                                double angle_degrees)
{
	elem.push_back(
	    new Relative_r_poly{o, center, radius, number_of_sides, angle_degrees});
}
//------------------------------------------------------------------------------

double grp_shp::R_poly_group::relative_distance(int element_index) const
{
	const Relative_r_poly& p{
	    dynamic_cast<const Relative_r_poly&>(elem[valid_index(element_index)])};
	return p.relative_distance();
}

double grp_shp::R_poly_group::relative_angle(int element_index) const
{
	const Relative_r_poly& p{
	    dynamic_cast<const Relative_r_poly&>(elem[valid_index(element_index)])};
	return p.relative_angle();
}

void grp_shp::R_poly_group::update_relative_distance(int element_index)
{
	Relative_r_poly& p{
	    dynamic_cast<Relative_r_poly&>(elem[valid_index(element_index)])};
	p.update_relative_distance(o);
}

void grp_shp::R_poly_group::update_relative_angle(int element_index)
{
	Relative_r_poly& p{
	    dynamic_cast<Relative_r_poly&>(elem[valid_index(element_index)])};
	p.update_relative_angle(o);
}

void grp_shp::R_poly_group::set_relative_distance(int element_index,
                                                  double new_distance)
{
	Relative_r_poly& p{
	    dynamic_cast<Relative_r_poly&>(elem[valid_index(element_index)])};
	p.set_relative_distance(new_distance);
}

void grp_shp::R_poly_group::set_relative_angle(int element_index,
                                               double new_angle)
{
	Relative_r_poly& p{
	    dynamic_cast<Relative_r_poly&>(elem[valid_index(element_index)])};
	p.set_relative_angle(new_angle);
}

//------------------------------------------------------------------------------

void grp_shp::R_poly_group::set_position(int x, int y, int element_index)
{
	Relative_r_poly& p{
	    dynamic_cast<Relative_r_poly&>(elem[valid_index(element_index)])};
	p.move(x - p.center().x, y - p.center().y);
}

void grp_shp::R_poly_group::move_elem_to_rot_pos(double offset_degrees,
                                                 int element_index)
{
	Graph_lib::Point old_pos = center(element_index);
	double old_a{relative_angle(element_index)};
	double new_a{old_a + offset_degrees};
	double new_a_rad{new_a * M_PI / 180};
	double dist{relative_distance(element_index)};
	double new_x{o.x - cos(new_a_rad) * dist};
	double new_y{o.y - sin(new_a_rad) * dist};
	int rnd_x = (new_x >= 0) ? static_cast<int>(new_x + 0.5)
	                         : static_cast<int>(new_x - 0.5);
	int rnd_y = (new_y >= 0) ? static_cast<int>(new_y + 0.5)
	                         : static_cast<int>(new_y - 0.5);
	set_position(rnd_x, rnd_y, element_index);
	set_relative_angle(element_index, new_a);
}
