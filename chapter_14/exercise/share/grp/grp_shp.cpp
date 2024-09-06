#include "grp_shp.h"

void grp_shp::Shape_group::move(int offset_x, int offset_y)
{
	o.x += offset_x;
	o.y += offset_y;
	for (int i = 0; i < elem.size(); ++i) {
		move(offset_x, offset_y, i);
	}
}

void grp_shp::Shape_group::set_color(Graph_lib::Color col)
{
	Graph_lib::Shape::set_color(col);
	for (int i = 0; i < elem.size(); ++i) {
		set_color(col, i);
	}
}

void grp_shp::Shape_group::set_style(Graph_lib::Line_style sty)
{
	Graph_lib::Shape::set_style(sty);
	for (int i = 0; i < elem.size(); ++i) {
		set_style(sty, i);
	}
}

void grp_shp::Shape_group::set_fill_color(Graph_lib::Color col)
{
	Graph_lib::Shape::set_fill_color(col);
	for (int i = 0; i < elem.size(); ++i) {
		set_fill_color(col, i);
	}
}

//------------------------------------------------------------------------------

void grp_shp::Shape_group::move(int offset_x, int offset_y, int elem_index)
{
	elem[valid_index(elem_index)].move(offset_x, offset_y);
}

void grp_shp::Shape_group::set_color(Graph_lib::Color col, int elem_index)
{
	elem[valid_index(elem_index)].set_color(col);
}

void grp_shp::Shape_group::set_style(Graph_lib::Line_style sty, int elem_index)
{
	elem[valid_index(elem_index)].set_style(sty);
}

void grp_shp::Shape_group::set_fill_color(Graph_lib::Color col, int elem_index)
{
	elem[valid_index(elem_index)].set_fill_color(col);
}

//------------------------------------------------------------------------------

void grp_shp::Shape_group::draw_lines() const
{
	for (int i = 0; i < elem.size(); ++i) {
		elem[valid_index(i)].draw();
	}
}

//------------------------------------------------------------------------------

int grp_shp::Shape_group::valid_index(int idx) const
{
	if (elem.size() == 0) {
		throw std::runtime_error("Group is empty");
	}
	if (idx < 0 || idx > elem.size() - 1) {
		throw std::runtime_error("Invalid group element index");
	};
	return idx;
}
