#ifndef TRIANGLETILER_H
#define TRIANGLETILER_H

#include "../../lib/Graph.h"
#include "../share/geo/righttriangle.h"
#include "../share/help/coordinate_system.h"
#include <cmath>
#include <memory>
#include <vector>

namespace TRITI { //------------------------------------------------------------

constexpr int bounds_lower_limit{-9999};
constexpr int bounds_upper_limit{9999};

//------------------------------------------------------------------------------

inline Graph_lib::Point triangle_end_point(Graph_lib::Point pt,
                                           float angle,
                                           int side_len)
{
	return {static_cast<int>(std::round(pt.x + cos(angle) * side_len)),
	        static_cast<int>(std::round(pt.y + sin(angle) * side_len))};
}

//------------------------------------------------------------------------------

class Bbox : public Graph_lib::Shape
{
public:
	Bbox(Graph_lib::Point origin, int width, int height, float angle = 0);
	void reset_transform();
	void rotate(float angle) { update(angle); };
	Coord_sys::Bounds bounds() const;
	void new_from_bounds();
	int horizontal_distance_to_min() const { return half_w_neg; };
	int horizontal_distance_to_max() const { return half_w_pos; };
	int vertical_distance_to_min() const { return half_h_neg; };
	int vertical_distance_to_max() const { return half_h_pos; };

private:
	bool init;
	int init_w;
	int init_h;
	float init_a;

	int half_w_neg;
	int half_w_pos;
	int half_h_neg;
	int half_h_pos;

	float a;

	Graph_lib::Point o;
	Graph_lib::Point c;

	void set_point(int i, Graph_lib::Point pt) { Shape::set_point(i, pt); }
	void add(Graph_lib::Point p) { Shape::add(p); }
	void draw_lines() const;
	void update(float angle);
	void update(int width, int height, float angle);
	void upd_width(int w);
	void upd_height(int h);
	void set_center(Graph_lib::Point origin);
	void upd_pts();
	void rot_coords(
	    int& x1, int& x2, int& x3, int& x4, int& y1, int& y2, int& y3, int& y4);
};

Coord_sys::Bounds rotated_bounds(const Bbox& bb,
                                 const Coord_sys::Coordinate_system& cs);

class TriangleTiler : public Graph_lib::Shape
{
public:
	TriangleTiler(
	    Graph_lib::Point o, int w, int h, int tri_side, double rotation);
	void pause_drawing() { draw_active = false; };
	void resume_drawing() { draw_active = true; };
	void draw_lines() const;

	void update_transform(Graph_lib::Point new_pos,
	                      int new_side_len,
	                      float new_angle);
	Graph_lib::Point point(int p) const;
	void toggle_bounding_box() { show_bbox = !show_bbox; }
	double angle() const { return a; };
	int side_length() const { return s; };
	void clear() { tris.clear(); };
	void update_bounding_box() { new_bbox(); };
	Graph_lib::Point top_left_tile() const { return tl; };
	int debug_bbox_width() const
	{
		return tiles_bbox.horizontal_distance_to_max()
		       + tiles_bbox.horizontal_distance_to_min();
	};
	int debug_bbox_height() const
	{
		return tiles_bbox.vertical_distance_to_max()
		       + tiles_bbox.vertical_distance_to_min();
	};
	Coord_sys::Bounds debug_rotates_bounds() const
	{
		return rotated_bounds(tiles_bbox, tiles_cs);
	}
	std::vector<Graph_lib::Point> debug_draw_tiles_bbox_grid();

private:
	bool draw_active;

	bool pt_inside_bbox(Graph_lib::Point pt, const Bbox& bbox) const;
	bool is_oob(const Graph_lib::Point p_0, const Graph_lib::Point p_1) const;
	bool p_fits_bbox(const Graph_lib::Point p) const;
	bool show_bbox = false;
	void new_bbox();
	int count_tris_until_oob(Graph_lib::Point point,
	                         Graph_lib::Point offset,
	                         const int max_count = 250);
	void add_tiles(const Graph_lib::Point point_0,
	               const Graph_lib::Point point_1,
	               const int count_a,
	               const Graph_lib::Point offset_a,
	               const int count_b,
	               const Graph_lib::Point offset_b,
	               const bool invert_first = false);

	std::vector<Graph_lib::Point> get_oblique(const Graph_lib::Point p_0,
	                                          const Graph_lib::Point p_1) const;
	static constexpr int MAX_TRIS{ 500 };
	std::vector<std::unique_ptr<Graph_lib::Closed_polyline>> tris;
	Graph_lib::Point c;
	Coord_sys::Bounds bg_bnds;
	Graph_lib::Rectangle bg;
	Coord_sys::Coordinate_system tiles_cs;
	Coord_sys::Bounds tiles_bnds;
	Bbox tiles_bbox;
	Graph_lib::Point tl;
	int s;
	double a;
};

struct Top_left_tile
{
	bool inv_tile;
	bool inv_dir;
	int sign_a;
	int sign_b;
	Graph_lib::Point pos;
};

Top_left_tile top_left_tile_attributes(float angle,
                                       Graph_lib::Point init_pt,
                                       int count_a,
                                       int inv_count_a,
                                       Graph_lib::Point offs_a,
                                       int count_b,
                                       int inv_count_b,
                                       Graph_lib::Point offs_b);

Coord_sys::Bounds bounds(const RTRI::RightTriangle& tri);

bool tri_is_inside(Graph_lib::Closed_polyline& p, Coord_sys::Bounds bnds);

inline std::vector<Graph_lib::Point> points_v(
    const Graph_lib::Closed_polyline& poly)
{
	std::vector<Graph_lib::Point> pts;
	for (int i = 0; i < poly.number_of_points(); ++i) {
		pts.push_back(poly.point(i));
	}
	return pts;
}

inline std::vector<Graph_lib::Point> points_v(const Graph_lib::Rectangle& rec)
{
	return {rec.point(0),
	        {rec.point(0).x + rec.width(), rec.point(0).y},
	        {rec.point(0).x + rec.width(), rec.point(0).y + rec.height()},
	        {rec.point(0).x, rec.point(0).y + rec.height()}};
}

inline std::vector<Graph_lib::Point> points_v(const Coord_sys::Bounds& bnds)
{
	return {bnds.min,
	        {bnds.max.x, bnds.min.y},
	        {bnds.max.x, bnds.max.y},
	        bnds.max};
}

// Returns -1 if equal, 0 if X is greater, 1 if Y is greater.
inline int axis_w_gr_magnitude(Graph_lib::Point pt)
{
	int abs_x = pt.x < 0 ? pt.x * -1 : pt.x;
	int abs_y = pt.y < 0 ? pt.y * -1 : pt.y;
	if (abs_x == abs_y) {
		return -1;
	}
	if (abs_x > abs_y) {
		return 0;
	}
	return 1;
}

} // namespace TRITI -----------------------------------------------------------
#endif // TRIANGLETILER_H
