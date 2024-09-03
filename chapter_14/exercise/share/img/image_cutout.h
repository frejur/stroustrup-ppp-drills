#ifndef IMAGE_CUTOUT_H
#define IMAGE_CUTOUT_H
#include "../../../lib/Graph.h"
#include <string>
#include <vector>

namespace imgcut {

class Image_cutout : public Graph_lib::Image
{
public:
	Image_cutout(Graph_lib::Point xy,
	             std::string s,
	             Graph_lib::Suffix e = Graph_lib::Suffix::none);
	void set_mask(Graph_lib::Point xy, int ww, int hh) = delete;
	void set_poly_mask(const Graph_lib::Closed_polyline& pm,
	                   int offset_x = 0,
	                   int offset_y = 0);
	void draw_lines() const override;

private:
	std::vector<Graph_lib::Point> mask;
	Fl_RGB_Image* p_masked;
	int offs_x;
	int offs_y;
};
} // namespace imgcut

#endif // IMAGE_CUTOUT_H
