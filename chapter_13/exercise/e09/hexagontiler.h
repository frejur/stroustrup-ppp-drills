#ifndef HEXAGONTILER_H
#define HEXAGONTILER_H
#include "../../lib/Graph.h"
#include "regularhexagon.h"
#include <memory>
#include <vector>
#include <map>
#include <utility>
#include <array>

namespace HXT { //--------------------------------------------------------------

struct TileOffset
{
	TileOffset(int radius, int inradius);
	std::pair<int, int> get(int i) const { return offs[i%6]; };
private:
	const std::array<std::pair<int, int>, 6> offs;
};

class HexagonTiler : public Graph_lib::Shape
{
public:
	HexagonTiler(Graph_lib::Point center, int num_tiles, int radius);
	Graph_lib::Point center() const { return c; };
	Graph_lib::Point tile_center() const { return tc; };
	int num_tiles() const { return tile_count; };
	int radius() const { return r; };
	int inradius() const { return ir; };
private:
	Graph_lib::Point c, tc; // center and last tile center
	int r, ir; // radius and inradius
	int tile_count;
	int active_edge;
	int active_tile;
	int calculate_inradius() const;
	void add_tile(const Graph_lib::Point& o, const int connecting_side);
	std::vector<std::unique_ptr<RegularHexagon>> tiles;
	std::unique_ptr<TileOffset> offs;
	void draw_lines() const;
};

} // namespace HXT -------------------------------------------------------------

#endif // HEXAGONTILER_H
