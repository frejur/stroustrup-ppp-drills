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
	Graph_lib::Point tile_center(int t) const;
	int num_tiles() const { return t_count; };
	int radius() const { return r; };
	int inradius() const { return in_r; };
private:
	int t_count; // tile count
	int act_s;   // index of active side
	int act_t;   // index of active tile
	int r;       // radius
	Graph_lib::Point c;
	std::vector<std::unique_ptr<RegularHexagon>> tiles;
	int calculate_inradius() const;
	int in_r; // inradius
	void add_tiles(RegularHexagon& hex, const int connecting_side);
	void draw_lines() const;
};

} // namespace HXT -------------------------------------------------------------

#endif // HEXAGONTILER_H
