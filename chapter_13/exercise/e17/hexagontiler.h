#ifndef HEXAGONTILER_H
#define HEXAGONTILER_H

#include "../share/geo/regularhexagon.h"
#include "../share/tiler/tiler.h"

namespace Tile_lib { //--------------------------------------------------------

class Hexagon_tiler : public Tiler
{
public:
	Hexagon_tiler(
	    Graph_lib::Point o, int w, int h, int hex_side, double rotation);

private:
	void add_tiles(const Graph_lib::Point pos,
	               const int side_len,
	               const float angle,
	               const Tile_count count_a,
	               const Tile_count count_b,
	               const Graph_lib::Point offset_a,
	               const Graph_lib::Point offset_b);
	void add_tile(Graph_lib::Point pos, int side_len, float angle);

	bool tile_is_inside(int idx);
	Offset_pair offset_pair();
};

Coord_sys::Bounds bounds(const RHEX::RegularHexagon& hex);

bool hex_is_inside(RHEX::RegularHexagon& p, Coord_sys::Bounds bnds);
//------------------------------------------------------------------------------

Graph_lib::Point top_left_hex_position(Graph_lib::Point init_pt,
                                       Tile_count count_a,
                                       Tile_count count_b,
                                       Graph_lib::Point offs_a,
                                       Graph_lib::Point offs_b);

inline int sextant(const float angle)
{
	return static_cast<int>(angle / M_PI / 3);
};

inline int dodecant(const float angle)
{
	return static_cast<int>(angle / M_PI / 6);
};

//------------------------------------------------------------------------------

} // namespace Tile_lib

#endif // HEXAGONTILER_H
