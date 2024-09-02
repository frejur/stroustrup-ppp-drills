#ifndef STRIPED_RECTANGLE_H
#define STRIPED_RECTANGLE_H
#include "../../../lib/Graph.h"
#include "strpe_rend.h"

namespace strpe_geo {

class Striped_rectangle : public Graph_lib::Rectangle
{
public:
	Striped_rectangle(Graph_lib::Point corner_0,
	                  Graph_lib::Point corner_1,
	                  int stripe_height = default_stripe_height,
	                  int gap_height = default_gap_height);
	void draw_lines() const override;

	// Hide base class method
	void set_fill_color(Graph_lib::Color color) { rend.set_color(color); };

private:
	Striped_rectangle_renderer rend;
};

} // namespace strpe_geo

#endif // STRIPED_RECTANGLE_H
