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
                                       float angle,
                                       bool stop)
{
	tiles.push_back(
	    std::make_unique<RHEX::RegularHexagon>(pos, side_len, angle, stop));
}

Tile_lib::Offset_pair Tile_lib::Hexagon_tiler::offset_pair()
{
	// Returns the offset in pixels on:
	// a. The lateral axis
	// b. The vertical axis
	//  - represented as Point objects.
	int lat_0, lat_1, vert_0, vert_1;
	bool flip_lat, flip_vert;
	switch (dodecant(a)) {
	case 11:
	case 0:
		lat_0 = 0;
		lat_1 = 3;
		vert_0 = 1;
		vert_1 = 5;
		flip_lat = false;
		flip_vert = false;
		break;
	case 1:
	case 2:
		lat_0 = 5;
		lat_1 = 2;
		vert_0 = 4;
		vert_1 = 0;
		flip_lat = false;
		flip_vert = false;
		break;
	case 3:
	case 4:
		lat_0 = 4;
		lat_1 = 1;
		vert_0 = 3;
		vert_1 = 5;
		flip_lat = false;
		flip_vert = false;
		break;
	case 5:
	case 6:
		lat_0 = 3;
		lat_1 = 0;
		vert_0 = 2;
		vert_1 = 4;
		flip_lat = false;
		flip_vert = false;
		break;
	case 7:
	case 8:
		lat_0 = 2;
		lat_1 = 5;
		vert_0 = 1;
		vert_1 = 3;
		flip_lat = false;
		flip_vert = false;
		break;
	case 9:
	case 10:
		lat_0 = 1;
		lat_1 = 4;
		vert_0 = 0;
		vert_1 = 2;
		flip_lat = false;
		flip_vert = false;
		break;
	default:
		throw std::runtime_error("Invalid angle");
	}

	int lat_x{tiles.back()->point(lat_0).x - tiles.back()->point(lat_1).x};
	int lat_y{tiles.back()->point(lat_0).y - tiles.back()->point(lat_1).y};
	int vert_x{tiles.back()->point(vert_0).x - tiles.back()->point(vert_1).x};
	int vert_y{tiles.back()->point(vert_0).y - tiles.back()->point(vert_1).y};
	lat_x *= (flip_lat) ? -1 : 1;
	lat_y *= (flip_lat) ? -1 : 1;
	vert_x *= (flip_vert) ? -1 : 1;
	vert_y *= (flip_vert) ? -1 : 1;

	return {{lat_x, lat_y}, {vert_x, vert_y}};
}

Graph_lib::Point Tile_lib::top_left_hex_position(Graph_lib::Point init_pt,
                                                 Tile_count ca,
                                                 Tile_count cb,
                                                 Graph_lib::Point offs_a,
                                                 Graph_lib::Point offs_b)
{
	return {init_pt.x + ca.inv_count * offs_a.x - cb.inv_count * offs_b.x,
	        init_pt.y + ca.inv_count * offs_a.y - cb.inv_count * offs_b.y};
}

Coord_sys::Bounds Tile_lib::bounds(const RHEX::RegularHexagon& hex)
{
	if (hex.number_of_points() == 0) {
		throw std::runtime_error(
		    "Cannot calculate bounds for a hexagon containing no points");
	}
	std::vector<Graph_lib::Point> pts;
	for (int i = 0; i < hex.number_of_points(); ++i) {
		pts.push_back(hex.point(i));
	}
	return Coord_sys::bounds_from_points(pts);
}

void Tile_lib::Hexagon_tiler::add_tiles(const Graph_lib::Point pos,
                                        const int side_len,
                                        const float angle,
                                        const Tile_count count_a,
                                        const Tile_count count_b,
                                        const Graph_lib::Point offs_a,
                                        const Graph_lib::Point offs_b)
{
	Graph_lib::Point top_l_hex_pos{
	    top_left_hex_position(pos, count_a, count_b, offs_a, offs_b)};

	// DEBUG: Draw point numbers
	for (int i = 0; i < tiles.back()->number_of_points(); ++i) {
		if (i != 3) {
			continue;
		}
		Graph_lib::Point pt0{tiles.back()->point(i)};
		tiles.push_back(std::make_unique<Graph_lib::Closed_polyline>());
		tiles.back()->add(pt0);
		tiles.back()->add({pt0.x + 10, pt0.y});
		tiles.back()->add({pt0.x + 10, pt0.y + 10});
		tiles.back()->add({pt0.x, pt0.y + 10});
		tiles.back()->set_color(Graph_lib::Color::black);
	}
	// END DEBUG: Draw point numbers

	// DEBUG:: Draw "top-left" triangle
	tiles.push_back(
	    std::make_unique<RHEX::RegularHexagon>(top_l_hex_pos, side_len, angle));
	tiles.back()->set_color(Graph_lib::Color::dark_yellow);
	tiles.back()->set_style({Graph_lib::Line_style::solid, 2});
	// DEBUG:: Draw "top-left" triangle

	// DEBUG: Draw offset
	tiles.push_back(std::make_unique<Graph_lib::Closed_polyline>());
	tiles.back()->add(pos);
	tiles.back()->add({pos.x + offs_a.x, pos.y + offs_a.y});
	tiles.back()->set_color(Graph_lib::Color::dark_green);
	tiles.push_back(std::make_unique<Graph_lib::Closed_polyline>());
	tiles.back()->add(pos);
	tiles.back()->add({pos.x + offs_b.x, pos.y + offs_b.y});
	tiles.back()->set_color(Graph_lib::Color::yellow);
	// DEBUG: Draw offset

	RHEX::RegularHexagon hex_cursor{top_l_hex_pos, side_len, angle};
	Coord_sys::Bounds hex_bbox{bounds(hex_cursor)};

	for (int col = 0; col < count_a.total(); ++col) {
		if (col > 0) {
			// reset for each 'column'
			int offs_x = top_l_hex_pos.x - hex_cursor.point(0).x;
			int offs_y = top_l_hex_pos.y - hex_cursor.point(0).y;
			hex_cursor.move(offs_x, offs_y);
			hex_cursor.move(offs_a.x * col, offs_a.y * col);
		}
		for (int row = 0; row < count_b.total(); ++row) {
			if (row > 0) {
				hex_cursor.move(offs_b.x, offs_b.y);
			}
			hex_bbox = bounds(hex_cursor);

			// DEBUG: Draw triangles bbox
			// tiles.push_back(std::make_unique<Graph_lib::Closed_polyline>(
			//     initializer_list<Graph_lib::Point>{hex_bbox.min,
			//                                        {hex_bbox.max.x,
			//                                         hex_bbox.min.y},
			//                                        hex_bbox.max,
			//                                        {hex_bbox.min.x,
			//                                         hex_bbox.max.y}}));
			// tiles.back()->set_color(Graph_lib::Color::cyan);
			// END DEBUG: Draw triangles bbox

			if (!Coord_sys::are_overlapping(hex_bbox, bg_bnds)) {
				continue;
			}

			// if (hex_is_inside(hex_cursor, bg_bnds)) {
			// 	add_tile(hex_cursor.point(0), side_len, angle);
			// 	tiles.back()->set_fill_color(Graph_lib::Color(25));
			// }
		}
	}
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
