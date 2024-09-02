#include "strpe_rec.h"

strpe_geo::Striped_rectangle::Striped_rectangle(Graph_lib::Point corner_0,
                                                Graph_lib::Point corner_1,
                                                int stripe_height,
                                                int gap_height)
    : Graph_lib::Rectangle(corner_0, corner_1)
    , rend(stripe_height, gap_height, *this)
{}

void strpe_geo::Striped_rectangle::draw_lines() const
{
	rend.draw_stripes();
	Graph_lib::Rectangle::draw_lines();
}
