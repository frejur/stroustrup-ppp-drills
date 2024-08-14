#ifndef TRIANGLETILER_H
#define TRIANGLETILER_H

#include "../share/tiler/tiler.h"

namespace Tile_lib { //--------------------------------------------------------

class Triangle_tiler : public Tiler
{
public:
	Triangle_tiler(
	    Graph_lib::Point o, int w, int h, int tri_side, double rotation);

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
	Offset_pair offset_pair(const double angle);
};

//------------------------------------------------------------------------------

struct TL_tri_attr
{
	bool inv_tile;
	bool inv_dir;
	int sign_a;
	int sign_b;
	Graph_lib::Point pos;
};

TL_tri_attr top_left_tri_attributes(float angle,
                                    Graph_lib::Point init_pt,
                                    Tile_count count_a,
                                    Tile_count count_b,
                                    Graph_lib::Point offs_a,
                                    Graph_lib::Point offs_b);

//------------------------------------------------------------------------------

inline Graph_lib::Point triangle_end_point(Graph_lib::Point pt,
                                           float angle,
                                           int side_len)
{
	return {static_cast<int>(std::round(pt.x + cos(angle) * side_len)),
	        static_cast<int>(std::round(pt.y + sin(angle) * side_len))};
}

} // namespace Tile_lib

#endif // TRIANGLETILER_H
