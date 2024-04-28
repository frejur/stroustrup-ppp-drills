#ifndef TRIANGLETILER_H
#define TRIANGLETILER_H

#include "../../lib/Graph.h"
#include "coordinate_system.h"
#include "righttriangle.h"
#include <cmath>
#include <memory>
#include <vector>

namespace TRITI { //------------------------------------------------------------

struct Bary_coords
{
	double v;
	double w;
	double u;
};

Bary_coords bary(Graph_lib::Point p,
                 Graph_lib::Point a,
                 Graph_lib::Point b,
                 Graph_lib::Point c);

inline bool is_inside_tri(const Bary_coords& c)
{
	return 0 <= c.v && c.v <= 1 && 0 <= c.w && c.w <= 1;
}

//------------------------------------------------------------------------------

inline double dot(Graph_lib::Point a, Graph_lib::Point b)
{
	return static_cast<double>(a.x * b.x + a.y * b.y);
}

inline float pt_dist(Graph_lib::Point p0, Graph_lib::Point p1)
{
	float dx = p1.x - p0.x;
	float dy = p1.y - p0.y;
	return sqrt(dx * dx + dy * dy);
}

inline float tri_area(Graph_lib::Point p0,
                      Graph_lib::Point p1,
                      Graph_lib::Point p2)
{
	float a = ((p1.x * p0.y - p0.x * p1.y) + (p2.x * p1.y - p1.x * p2.y)
	           + (p0.x * p2.y - p2.x * p0.y))
	          * 0.5;
	if (a < 0) {
		a *= -1;
	}
	return a;
}

inline bool bbox_encompasses_bbox(Graph_lib::Point min_a);

enum class TriType { ZeroArea, RightTriangle, ObliqueTriangle };

struct TriCoords
{
	TriType type = TriType::ZeroArea;
	std::vector<Graph_lib::Point> points;
};

//------------------------------------------------------------------------------

class Bbox : public Graph_lib::Shape
{
public:
	Bbox(Graph_lib::Point origin, int width, int height, float angle = 0);
	void rotate(float angle) { update(angle); };
	Coord_sys::Bounds bounds() const;
	void new_from_bounds();

private:
	bool init;
	int half_w_neg;
	int half_w_pos;
	int half_h_neg;
	int half_h_pos;
	float a;
	Graph_lib::Point c;
	void set_point(int i, Graph_lib::Point pt) { Shape::set_point(i, pt); }
	void add(Graph_lib::Point p) { Shape::add(p); }
	void draw_lines() const;
	void update(float angle);
	void update(int width, int height, float angle);
	void upd_width(int w);
	void upd_height(int h);
	void upd_pts();
	void rot_coords(
	    int& x1, int& x2, int& x3, int& x4, int& y1, int& y2, int& y3, int& y4);
};

class TriangleTiler : public Graph_lib::Shape
{
public:
	TriangleTiler(
	    Graph_lib::Point o, int w, int h, int tri_side, double rotation);
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

private:
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
	TriCoords get_tri(const Graph_lib::Point p_0,
	                  const Graph_lib::Point p_1) const;
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

} // namespace TRITI -----------------------------------------------------------
#endif // TRIANGLETILER_H
