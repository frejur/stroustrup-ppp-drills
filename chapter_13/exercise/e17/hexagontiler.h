#ifndef TRIANGLETILER_H
#define TRIANGLETILER_H

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

struct TL_hex_attr
{
	bool inv_tile;
	bool inv_dir;
	int sign_a;
	int sign_b;
	Graph_lib::Point pos;
};

TL_hex_attr top_left_hex_attributes(float angle,
                                    Graph_lib::Point init_pt,
                                    Tile_count count_a,
                                    Tile_count count_b,
                                    Graph_lib::Point offs_a,
                                    Graph_lib::Point offs_b);

//------------------------------------------------------------------------------

} // namespace Tile_lib

#endif // TRIANGLETILER_H
