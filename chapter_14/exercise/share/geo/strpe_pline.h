#ifndef STRIPED_CIRCLE_H
#define STRIPED_CIRCLE_H
#include "../../../lib/Graph.h"
#include "strpe_rend.h"

namespace strpe_geo {

class Striped_polyline : public Graph_lib::Closed_polyline
{
public:
	Striped_polyline(int stripe_height = default_stripe_height,
	                 int gap_height = default_gap_height);
	void draw_lines() const override;

	// Hide base class method
	void set_fill_color(Graph_lib::Color color) { rend.set_color(color); };

private:
	Striped_polyline_renderer rend;
};

} // namespace strpe_geo

#endif // STRIPED_CIRCLE_H
