#include "strpe_pline.h"

strpe_geo::Striped_polyline::Striped_polyline(int stripe_height, int gap_height)
    : Graph_lib::Closed_polyline()
    , rend(stripe_height, gap_height, *this)
{}

void strpe_geo::Striped_polyline::draw_lines() const
{
	rend.draw_stripes();
	Graph_lib::Closed_polyline::draw_lines();
}
