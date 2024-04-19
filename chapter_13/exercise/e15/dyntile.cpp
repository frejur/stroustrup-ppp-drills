#include "dyntile.h"
#include "righttriangle.h"

dyntile::Dynamic_tile::Dynamic_tile(dyntile::Tile_type type,
                                    Graph_lib::Point origin,
                                    int side_len,
                                    float angle,
                                    int min_side_len,
                                    int max_side_len)
    : init_pos(false)
    , is_xform(false)
    , min_s(min_side_len)
    , max_s(max_side_len)
    , s(side_len)
    , a(angle)
    , o(origin)
    , preview_s(side_len)
    , preview_a(angle)
    , preview_o(origin)
    , t(type)
{
	if (!valid_min_max(min_side_len, max_side_len)) {
		throw std::runtime_error("Invalid parameters");
	}
	init_pos = true;
	cap_parms(side_len, angle);
	tile = new_tile(type);
	tile->set_color(Graph_lib::Color::black);
}

//------------------------------------------------------------------------------

std::unique_ptr<Graph_lib::Closed_polyline> dyntile::Dynamic_tile::new_tile(
    Tile_type type)
{
	if (type == Tile_type::Right_triangle) {
		Graph_lib::Point in_end{static_cast<int>(std::round(
		                            preview_o.x + cos(preview_a) * preview_s)),
		                        static_cast<int>(std::round(
		                            preview_o.y + sin(preview_a) * preview_s))};
		return std::make_unique<RTRI::RightTriangle>(preview_o, in_end);
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
	if (!is_transforming() || !init_pos) {
		return;
	}
	if (new_origin != preview_o) {
		preview_o = new_origin;
	}
	cap_parms(new_side_len, new_angle);
	preview_s = new_side_len;
	preview_a = new_angle;
}

void dyntile::Dynamic_tile::apply_transform(bool preview)
// Replace current tile with a newly transformed tile
{
	if (preview && s == preview_s && a == preview_a && o == preview_o) {
		tile->set_color(Graph_lib::Color::red);
		return;
	}
	tile = new_tile(t);
	if (preview) {
		tile->set_color(Graph_lib::Color::red);
	} else {
		tile->set_color(Graph_lib::Color::black);
		o = preview_o;
		s = preview_s;
		a = preview_a;
	}
}

//------------------------------------------------------------------------------

void dyntile::Dynamic_tile::cap_parms(int& side_len, float& angle)
{
	if (side_len < min_s) {
		side_len = min_s;
	} else if (side_len > max_s) {
		side_len = max_s;
	}
	// TODO: Implement wrap-around
	if (angle < 0) {
		angle = 0;
	} else if (angle > 360) {
		angle = 360;
	}
}
