#ifndef STRIPED_CIRCLE_H
#define STRIPED_CIRCLE_H
#include "../../../lib/Graph.h"
#include "strpe_rend.h" // TODO: Update

namespace strpe_geo {

class Striped_circle : public Graph_lib::Circle
{
public:
	Striped_circle(Graph_lib::Point center,
	               int radius,
	               int stripe_height = default_stripe_height,
	               int gap_height = default_gap_height);
	void draw_lines() const override;

	// Hide base class method
	void set_fill_color(Graph_lib::Color color) { rend.set_color(color); };

private:
	Striped_circle_renderer rend; // TODO: Update
};

} // namespace strpe_geo

#endif // STRIPED_CIRCLE_H
