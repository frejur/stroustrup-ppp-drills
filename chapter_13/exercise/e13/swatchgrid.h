#ifndef SWATCHGRID_H
#define SWATCHGRID_H

#include "../../lib/Graph.h"
#include <vector>
#include <memory>

namespace SWGR { //-------------------------------------------------------------

struct HSV { double h, s, v; };
struct RGB { double r, g, b; };

class SwatchGrid : public Graph_lib::Shape
{
public:
	SwatchGrid(Graph_lib::Point xy, int w, int h, int num_x, int num_y, int pad_sz=2);
	void draw_lines() const;
private:
	Graph_lib::Point xy;
	int w, h;
	int sw_num_x, sw_num_y;
	int sw_sz_x, sw_sz_y, pad_sz;
	std::vector<std::unique_ptr<Graph_lib::Rectangle>> swatches;
	HSV HSV_from_RGB(RGB rgb);
	RGB RGB_from_HSV(HSV hsv);
};

} // end namespace SWGR --------------------------------------------------------
#endif // SWATCHGRID_H
