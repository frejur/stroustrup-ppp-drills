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
	int a0, a1, b0, b1;
	switch (sextant(a)) {
	case 0:
		a0 = 2;
		a1 = 4;
		b0 = 0;
		b1 = 3;
		break;
	case 1:
		a0 = 1;
		a1 = 5;
		b0 = 3;
		b1 = 0;
		break;
	case 2:
		a0 = 1;
		a1 = 5;
		b0 = 3;
		b1 = 0;
		break;
	case 3:
		a0 = 1;
		a1 = 5;
		b0 = 3;
		b1 = 0;
		break;
	case 4:
		a0 = 1;
		a1 = 5;
		b0 = 3;
		b1 = 0;
		break;
	case 5:
		a0 = 1;
		a1 = 5;
		b0 = 3;
		b1 = 0;
		break;
	default:
		throw std::runtime_error("Invalid angle");
	}

	return {{tiles.back()->point(a0).x - tiles.back()->point(a1).x,
	         tiles.back()->point(a0).y - tiles.back()->point(a1).y},
	        {tiles.back()->point(b0).x - tiles.back()->point(b1).x,
	         tiles.back()->point(b0).y - tiles.back()->point(b1).y}};
}

Tile_lib::TL_hex_attr Tile_lib::top_left_hex_attributes(float angle,
                                                        Graph_lib::Point init_pt,
                                                        Tile_count ca,
                                                        Tile_count cb,
                                                        Graph_lib::Point offs_a,
                                                        Graph_lib::Point offs_b)
{
	if (angle < 0 || angle > M_PI * 2) {
		throw std::runtime_error("Invalid angle");
	}

	switch (sextant(angle)) {
	case 0:
		return {false,
		        1,
		        -1,
		        {init_pt.x - ca.inv_count * offs_a.x - cb.inv_count * offs_b.x,
		         init_pt.y - ca.inv_count * offs_a.y - cb.inv_count * offs_b.y}};
	case 1:
	case 2:
		return {true,
		        1,
		        1,
		        {init_pt.x - ca.inv_count * offs_a.x + cb.count * offs_b.x,
		         init_pt.y - ca.inv_count * offs_a.y + cb.count * offs_b.y}};
	case 3:
	case 4:
		return {false,
		        -1,
		        -1,
		        {init_pt.x - ca.count * offs_a.x - cb.count * offs_b.x,
		         init_pt.y - ca.count * offs_a.y - cb.count * offs_b.y}};
	case 5:
	case 6:
		return {false,
		        -1,
		        1,
		        {init_pt.x + ca.count * offs_a.x - cb.inv_count * offs_b.x,
		         init_pt.y + ca.count * offs_a.y - cb.inv_count * offs_b.y}};
	default:
		throw std::runtime_error("Invalid angle");
	}
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
	TL_hex_attr top_l_hex{
	    top_left_hex_attributes(angle, pos, count_a, count_b, offs_a, offs_b)};

	const Tile_count& count_col = (top_l_hex.inv_dir) ? count_b : count_a;
	const Tile_count& count_row = (top_l_hex.inv_dir) ? count_a : count_b;
	const Graph_lib::Point offs_col
	    = (top_l_hex.inv_dir) ? Graph_lib::Point{offs_b.x * top_l_hex.sign_b,
	                                             offs_b.y * top_l_hex.sign_b}
	                          : Graph_lib::Point{offs_a.x * top_l_hex.sign_a,
	                                             offs_a.y * top_l_hex.sign_a};
	const Graph_lib::Point offs_row
	    = (top_l_hex.inv_dir) ? Graph_lib::Point{offs_a.x * top_l_hex.sign_a,
	                                             offs_a.y * top_l_hex.sign_a}
	                          : Graph_lib::Point{offs_b.x * top_l_hex.sign_b,
	                                             offs_b.y * top_l_hex.sign_b};

	// DEBUG:: Draw "top-left" triangle
	tiles.push_back(
	    std::make_unique<RHEX::RegularHexagon>(top_l_hex.pos, side_len, angle));
	tiles.back()->set_color(Graph_lib::Color::dark_yellow);
	tiles.back()->set_style({Graph_lib::Line_style::solid, 2});
	// DEBUG:: Draw "top-left" triangle

	// DEBUG: Draw offset
	tiles.push_back(std::make_unique<Graph_lib::Closed_polyline>());
	tiles.back()->add(pos);
	tiles.back()->add({pos.x + offs_col.x, pos.y + offs_col.y});
	tiles.back()->set_color(Graph_lib::Color::yellow);
	tiles.push_back(std::make_unique<Graph_lib::Closed_polyline>());
	tiles.back()->add(pos);
	tiles.back()->add({pos.x + offs_row.x, pos.y + offs_row.y});
	tiles.back()->set_color(Graph_lib::Color::blue);
	// DEBUG: Draw offset

	RHEX::RegularHexagon hex_cursor{top_l_hex.pos, side_len, angle};
	Coord_sys::Bounds hex_bbox{bounds(hex_cursor)};

	for (int col = 0; col < count_col.total(); ++col) {
		if (col > 0) {
			// reset for each 'column'
			int offs_x = top_l_hex.pos.x - hex_cursor.point(0).x;
			int offs_y = top_l_hex.pos.y - hex_cursor.point(0).y;
			hex_cursor.move(offs_x, offs_y);
			hex_cursor.move(offs_col.x * col, offs_col.y * col);
		}
		for (int row = 0; row < count_row.total(); ++row) {
			if (row > 0) {
				hex_cursor.move(offs_row.x, offs_row.y);
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
