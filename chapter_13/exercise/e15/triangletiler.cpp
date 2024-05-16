#include "triangletiler.h"

Tile_lib::Triangle_tiler::Triangle_tiler(
    Graph_lib::Point o, int w, int h, int tri_side, double angle)
    : Tiler(o, w, h, tri_side, angle)
{
	// Add first tile
	tris.push_back(
	    std::make_unique<RTRI::RightTriangle>(o,
	                                          Tile_lib::triangle_end_point(o,
	                                                                       a,
	                                                                       s)));
	tris.back()->set_color(Graph_lib::Color::blue);
}
