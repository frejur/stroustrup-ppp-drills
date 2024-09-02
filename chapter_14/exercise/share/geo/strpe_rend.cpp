#include "strpe_rend.h"
#include "../help/helpers.h"
#include "strpe_rec.h"

strpe_geo::Striped_shape_renderer::Striped_shape_renderer(
    int stripe_height,
    int gap_height,
    Graph_lib::Shape& shape,
    Graph_lib::Color color)
    : strpe_h(valid_strpe_h(stripe_height, "stripe"))
    , gap_h(valid_strpe_h(gap_height, "stripe"))
    , col(color)
    , shp(shape)
{}

void strpe_geo::Striped_shape_renderer::draw_stripes() const
{
	if (col.visibility()) {
		fl_color(col.as_int());

		for (int row = 0; row < (height()); ++row) {
			int cycle_pos = row % (strpe_h + gap_h);

			if (cycle_pos < strpe_h) {
				draw_single_stripe(row);
			}
		}
		fl_color(shp.color().as_int()); // reset color
	}
}

int strpe_geo::Striped_shape_renderer::valid_strpe_h(int height,
                                                     const std::string& name)
{
	if (height < 1) {
		throw std::runtime_error("Invalid " + name + " height, must be > 0");
	}
	return height;
}

void strpe_geo::Striped_shape_renderer::set_stripe_height(int height)
{
	strpe_h = valid_strpe_h(height, "stripe");
}

void strpe_geo::Striped_shape_renderer::set_gap_height(int height)
{
	gap_h = valid_strpe_h(height, "gap");
}

//------------------------------------------------------------------------------

void strpe_geo::Striped_rectangle_renderer::draw_single_stripe(int row) const
{
	Graph_lib::Point min_xy = shp.point(0);
	fl_line(min_xy.x, min_xy.y + row, min_xy.x + width(), min_xy.y + row);
}

int strpe_geo::Striped_rectangle_renderer::width() const
{
	// TODO: This seems a bit unsafe
	return static_cast<Striped_rectangle&>(shp).width();
}

int strpe_geo::Striped_rectangle_renderer::height() const
{
	// TODO: This seems a bit unsafe
	return static_cast<Striped_rectangle&>(shp).height();
}
