#include "strpe_circ.h"

strpe_geo::Striped_circle::Striped_circle(Graph_lib::Point center,
                                          int radius,
                                          int stripe_height,
                                          int gap_height)
    : Graph_lib::Circle(center, radius)
    , rend(stripe_height, gap_height, *this)
{}

void strpe_geo::Striped_circle::draw_lines() const
{
	rend.draw_stripes();
	Graph_lib::Circle::draw_lines();
}
