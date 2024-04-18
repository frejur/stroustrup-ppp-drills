#ifndef DYNTILE_H
#define DYNTILE_H
#include "../../lib/Graph.h"
#include <memory>

namespace dyntile {

constexpr float refresh_rate{0.01};
constexpr float refresh_time_out{1};

constexpr int default_min_side_len{10};
constexpr int default_max_side_len{200};

enum class Tile_type { Right_triangle, Regular_hexagon };

class Dynamic_tile : public Graph_lib::Shape
{
public:
	Dynamic_tile(Tile_type type,
	             Graph_lib::Point origin,
	             int side_len,
	             float angle,
	             int min_side_len = default_min_side_len,
	             int max_side_len = default_max_side_len);

	void draw_lines() const { tile->draw(); };
	bool is_transforming() const { return is_xform; };
	void cue_transform(Graph_lib::Point new_origin,
	                   int new_side_len,
	                   float new_angle);
	void apply_transform();
	void enable_transform() { is_xform = true; };
	void disable_transform() { is_xform = false; };
	Graph_lib::Point origin() const { return o; };
	int side_length() const { return s; };
	float angle() const { return a; };

private:
	bool is_xform;
	const int min_s;
	const int max_s;
	int s;
	float a;
	Graph_lib::Point o;
	int new_s;
	float new_a;
	Graph_lib::Point new_o;
	Tile_type t;
	bool valid_min_max(int min_side_len, int max_side_len) const
	{
		return !(min_side_len >= max_side_len || s < min_side_len
		         || s > max_side_len);
	}
	void cap_parms(int side_len, float angle);
	std::unique_ptr<Graph_lib::Closed_polyline> tile;
	std::unique_ptr<Graph_lib::Closed_polyline> new_tile(Tile_type type);
	;
};

} // namespace dyntile

#endif // DYNTILE_H
