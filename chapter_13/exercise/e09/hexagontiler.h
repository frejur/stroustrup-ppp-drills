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
	int tile_ring_number(int t) const;
	float tile_ring_position(int t) const;
	int adjacent_tile(int t, int side);
private:
	int t_num;   // desired no. of tiles
	int t_count; // tile count
	int act_s;   // index of active side
	int act_t;   // index of active tile
	int r;       // radius
	Graph_lib::Point c;
	std::vector<std::unique_ptr<RegularHexagon>> tiles;
	int calculate_inradius() const;
	int in_r;    // inradius
	void add_tiles(RegularHexagon& hex);
	void draw_lines() const;
	std::unique_ptr<TileOffset> offset;
	int get_adj_0(int t, float ring_pos, int ring) const;
	int get_adj_1(int t, float ring_pos, int ring) const;
	int get_adj_2(int t, float ring_pos, int ring) const;
	int get_adj_3(int t, float ring_pos, int ring) const;
	int get_adj_4(int t, float ring_pos, int ring) const;
	int get_adj_5(int t, float ring_pos, int ring) const;
	float tile_ring_position(int t, int ring) const;
	void close_adjacent(int t, int side);
};

} // namespace HXT -------------------------------------------------------------

#endif // HEXAGONTILER_H
