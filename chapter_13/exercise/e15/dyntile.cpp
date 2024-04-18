#include "dyntile.h"
#include "righttriangle.h"

dyntile::Dynamic_tile::Dynamic_tile(dyntile::Tile_type type,
                                    Graph_lib::Point origin,
                                    int side_len,
                                    float angle,
                                    int min_side_len,
                                    int max_side_len)
    : is_xform(false)
    , min_s(min_side_len)
    , max_s(max_side_len)
    , s(side_len)
    , a(angle)
    , o(origin)
    , new_s(side_len)
    , new_a(angle)
    , new_o(origin)
    , t(type)
{
	if (!valid_min_max(min_side_len, max_side_len)) {
		throw std::runtime_error("Invalid parameters");
	}
	cap_parms(side_len, angle);
	tile = new_tile(type);
	tile->set_color(Graph_lib::Color::black);
}

//------------------------------------------------------------------------------

std::unique_ptr<Graph_lib::Closed_polyline> dyntile::Dynamic_tile::new_tile(
    Tile_type type)
{
	if (type == Tile_type::Right_triangle) {
		Graph_lib::Point in_end{static_cast<int>(std::round(o.x + cos(a) * s)),
		                        static_cast<int>(std::round(o.y + sin(a) * s))};
		return std::make_unique<RTRI::RightTriangle>(o, in_end);
	} else {
		throw std::runtime_error("Not implemented yet");
	}
};

//------------------------------------------------------------------------------
// Transformation

void dyntile::Dynamic_tile::cue_transform(Graph_lib::Point new_origin,
                                          int new_side_len,
                                          float new_angle)
// Register new transform values
{
	if (!is_transforming()) {
		return;
	}
	if (new_origin != o) {
		o = new_origin;
	}
	cap_parms(new_s, new_a);
	s = new_s;
	a = new_a;
}

void dyntile::Dynamic_tile::apply_transform()
// Replace current tile with a newly transformed tile
{
	if (s == new_s && a == new_a && o == new_o) {
		return;
	}
	tile = new_tile(t);
}

//------------------------------------------------------------------------------

void dyntile::Dynamic_tile::cap_parms(int side_len, float angle)
{
	if (side_len < min_s) {
		s = min_s;
	} else if (side_len > max_s) {
		s = max_s;
	}
	// TODO: Implement wrap-around
	if (angle < 0) {
		a = 0;
	} else if (angle > 360) {
		a = 360;
	}
}
