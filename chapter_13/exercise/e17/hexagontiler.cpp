#include "hexagontiler.h"
#include "../share/geo/regularhexagon.h"
#include "../share/help/inters.h"

Tile_lib::Hexagon_tiler::Hexagon_tiler(
    Graph_lib::Point o, int w, int h, int tri_side, double angle)
    : Tiler(o, w, h, tri_side, angle)
{
	// Add first tile
	add_tile(o, s, a);
	tiles.back()->set_color(Graph_lib::Color::blue);
}

void Tile_lib::Hexagon_tiler::add_tile(Graph_lib::Point pos,
                                       int side_len,
                                       float angle)
{
	tiles.push_back(
	    std::make_unique<RHEX::RegularHexagon>(pos, side_len, angle));
}

Tile_lib::Offset_pair Tile_lib::Hexagon_tiler::offset_pair()
{
	return {{tiles.back()->point(0).x - tiles.back()->point(4).x,
	         tiles.back()->point(0).y - tiles.back()->point(4).y},
	        {tiles.back()->point(2).x - tiles.back()->point(5).x,
	         tiles.back()->point(2).y - tiles.back()->point(5).y}};
}

void Tile_lib::Hexagon_tiler::add_tiles(const Graph_lib::Point pos,
                                        const int side_len,
                                        const float angle,
                                        const Tile_count count_a,
                                        const Tile_count count_b,
                                        const Graph_lib::Point offs_a,
                                        const Graph_lib::Point offs_b)
{
	Top_left_tile top_l_tri{
	    top_left_tile_attributes(angle, pos, count_a, count_b, offs_a, offs_b)};

	const Tile_count& count_col = (top_l_tri.inv_dir) ? count_b : count_a;
	const Tile_count& count_row = (top_l_tri.inv_dir) ? count_a : count_b;
	const Graph_lib::Point offs_col
	    = (top_l_tri.inv_dir) ? Graph_lib::Point{offs_b.x * top_l_tri.sign_b,
	                                             offs_b.y * top_l_tri.sign_b}
	                          : Graph_lib::Point{offs_a.x * top_l_tri.sign_a,
	                                             offs_a.y * top_l_tri.sign_a};
	const Graph_lib::Point offs_row
	    = (top_l_tri.inv_dir) ? Graph_lib::Point{offs_a.x * top_l_tri.sign_a,
	                                             offs_a.y * top_l_tri.sign_a}
	                          : Graph_lib::Point{offs_b.x * top_l_tri.sign_b,
	                                             offs_b.y * top_l_tri.sign_b};

	// DEBUG:: Draw "top-left" triangle
	tiles.push_back(
	    std::make_unique<RHEX::RegularHexagon>(top_l_tri.pos, side_len, angle));
	tiles.back()->set_color(Graph_lib::Color::dark_yellow);
	tiles.back()->set_style({Graph_lib::Line_style::solid, 2});
	// DEBUG:: Draw "top-left" triangle

	// DEBUG: Draw offset
	tiles.push_back(std::make_unique<Graph_lib::Closed_polyline>());
	tiles.back()->add(pos);
	tiles.back()->add({pos.x + offs_a.x, pos.y + offs_a.y});
	tiles.back()->set_color(Graph_lib::Color::yellow);
	tiles.push_back(std::make_unique<Graph_lib::Closed_polyline>());
	tiles.back()->add(pos);
	tiles.back()->add({pos.x + offs_b.x, pos.y + offs_b.y});
	tiles.back()->set_color(Graph_lib::Color::blue);
	// DEBUG: Draw offset
}

bool Tile_lib::Hexagon_tiler::tile_is_inside(int idx)
{
	if (idx < 0 || idx > tiles.size() - 1) {
		throw std::runtime_error("Invalid index");
	}

	return Tile_lib::hex_is_inside(reinterpret_cast<RHEX::RegularHexagon&>(
	                                   *tiles[idx]),
	                               bg_bnds);
}

bool Tile_lib::hex_is_inside(RHEX::RegularHexagon& hex, Coord_sys::Bounds bnds)
{
	if (hex.number_of_points() != 6) {
		throw std::runtime_error("Not a hexagon");
	}
	for (int i = 0; i < hex.number_of_points(); ++i) {
		if (Coord_sys::is_inside(hex.point(i), bnds)) {
			hex.set_fill_color(Graph_lib::Color::red);
			return true;
		}
	}

	std::vector<Graph_lib::Point> tri_pts{hex.center(),
	                                      hex.point(0),
	                                      hex.point(1)};
	for (int i = 0; i < 6; ++i) {
		if (i > 0) {
			tri_pts[1] = hex.point(i);
			tri_pts[2] = hex.point(i + 1);
		}
		if (inters::any_inside_tri(points_v(bnds), tri_pts)) {
			hex.set_fill_color(Graph_lib::Color::green);
			return true;
		}
	}

	if (inters::lines_intersect(points_v(hex), points_v(bnds))) {
		hex.set_fill_color(Graph_lib::Color::magenta);
		return true;
	}
	return false;
}
