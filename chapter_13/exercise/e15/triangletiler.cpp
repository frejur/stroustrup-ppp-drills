#include "triangletiler.h"

Tile_lib::Triangle_tiler::Triangle_tiler(
    Graph_lib::Point o, int w, int h, int tri_side, double angle)
    : Tiler(o, w, h, tri_side, angle)
{
	// Add first tile
	add_tile(o, tri_side, angle);
	tiles.back()->set_color(Graph_lib::Color::blue);
}

void Tile_lib::Triangle_tiler::add_tile(Graph_lib::Point pos,
                                        int side_len,
                                        float angle)
{
	tiles.push_back(
	    std::make_unique<RTRI::RightTriangle>(pos,
	                                          Tile_lib::triangle_end_point(pos,
	                                                                       a,
	                                                                       s)));
}

void Tile_lib::Triangle_tiler::add_tiles(const Graph_lib::Point pos,
                                         const int side_len,
                                         const float angle,
                                         const Tile_count count_a,
                                         const Tile_count count_b,
                                         const Graph_lib::Point offs_a,
                                         const Graph_lib::Point offs_b)
{
	Top_left_tile top_l_tri{
	    top_left_tile_attributes(angle, pos, count_a, count_b, offs_a, offs_b)};
	Graph_lib::Point top_l_tri_end_pt{
	    Tile_lib::triangle_end_point(top_l_tri.pos, angle, side_len)};

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
	    std::make_unique<RTRI::RightTriangle>(top_l_tri.pos, top_l_tri_end_pt));
	tiles.back()->set_color(Graph_lib::Color::dark_yellow);
	tiles.back()->set_style({Graph_lib::Line_style::solid, 2});
	// DEBUG:: Draw "top-left" triangle

	RTRI::RightTriangle tri_cursor{top_l_tri.pos,
	                               top_l_tri_end_pt,
	                               top_l_tri.inv_tile};
	RTRI::RightTriangle tri_cursor_inv{top_l_tri.pos,
	                                   top_l_tri_end_pt,
	                                   !top_l_tri.inv_tile};
	Coord_sys::Bounds tri_bbox{bounds(tri_cursor)};
	Coord_sys::Bounds tri_bbox_inv{bounds(tri_cursor_inv)};
	Coord_sys::Bounds tri_bbox_combo{
	    Coord_sys::merged_bounds(tri_bbox, tri_bbox_inv)};

	for (int col = 0; col < count_col.total(); ++col) {
		if (col > 0) {
			// reset for each 'column'
			int offs_x = top_l_tri.pos.x
			             - (top_l_tri.inv_tile ? tri_cursor_inv.point(0).x
			                                   : tri_cursor.point(0).x);
			int offs_y = top_l_tri.pos.y
			             - (top_l_tri.inv_tile ? tri_cursor_inv.point(0).y
			                                   : tri_cursor.point(0).y);
			tri_cursor.move(offs_x, offs_y);
			tri_cursor_inv.move(offs_x, offs_y);

			tri_cursor.move(offs_col.x * col, offs_col.y * col);
			tri_cursor_inv.move(offs_col.x * col, offs_col.y * col);
		}
		for (int row = 0; row < count_row.total(); ++row) {
			if (row > 0) {
				tri_cursor.move(offs_row.x, offs_row.y);
				tri_cursor_inv.move(offs_row.x, offs_row.y);
			}
			tri_bbox = bounds(tri_cursor);
			tri_bbox_inv = bounds(tri_cursor_inv);
			tri_bbox_combo = Coord_sys::merged_bounds(tri_bbox, tri_bbox_inv);

			// DEBUG: Draw triangles bbox
			tiles.push_back(std::make_unique<Graph_lib::Closed_polyline>(
			    initializer_list<Graph_lib::Point>{tri_bbox_combo.min,
			                                       {tri_bbox_combo.max.x,
			                                        tri_bbox_combo.min.y},
			                                       tri_bbox_combo.max,
			                                       {tri_bbox_combo.min.x,
			                                        tri_bbox_combo.max.y}}));
			tiles.back()->set_color(Graph_lib::Color::cyan);
			// END DEBUG: Draw triangles bbox

			if (!Coord_sys::are_overlapping(tri_bbox_combo, bg_bnds)) {
				continue;
			}

			if (tri_is_inside(tri_cursor, bg_bnds)) {
				tiles.push_back(std::make_unique<Graph_lib::Closed_polyline>(
				    initializer_list<Graph_lib::Point>{tri_cursor.point(0),
				                                       tri_cursor.point(1),
				                                       tri_cursor.point(2)}));
				tiles.back()->set_fill_color(Graph_lib::Color(25));
			}
			if (tri_is_inside(tri_cursor_inv, bg_bnds)) {
				tiles.push_back(std::make_unique<Graph_lib::Closed_polyline>(
				    initializer_list<Graph_lib::Point>{tri_cursor_inv.point(0),
				                                       tri_cursor_inv.point(1),
				                                       tri_cursor_inv.point(
				                                           2)}));
				tiles.back()->set_fill_color(Graph_lib::Color(20));
			}
		}
	}
}
