#ifndef TRIANGLETILER_H
#define TRIANGLETILER_H

#include <vector>
#include <memory>
#include <cmath>
#include "../../lib/Graph.h"
#include "righttriangle.h"

namespace TRITI { //------------------------------------------------------------

namespace GL = Graph_lib;

struct Bary_coords
{
	double v;
	double w;
	double u;
};

inline double dot(GL::Point a, GL::Point b)
{
	return static_cast<double>(a.x * b.x + a.y * b.y);
}

Bary_coords bary(GL::Point p, GL::Point a, GL::Point b, GL::Point c);

inline bool is_inside_tri(const Bary_coords& c)
{
	return 0 <= c.v && c.v <= 1 && 0 <= c.w && c.w <= 1;
}

enum class TriType { ZeroArea, RightTriangle, ObliqueTriangle };

struct TriCoords
{
	TriType type = TriType::ZeroArea;
	std::vector<GL::Point> points;
};

class Bbox : public GL::Shape
{
public:
	Bbox(){};
	Bbox(initializer_list<GL::Point> lst)
	    : GL::Shape{lst}
	{}
	void set_point(int i, GL::Point pt) { Shape::set_point(i, pt); }

private:
	void add(GL::Point p) { Shape::add(p); }
	void draw_lines() const;
};

class TriangleTiler : public GL::Shape
{
public:
	TriangleTiler(GL::Point o, int w, int h, int tri_side, double rotation);
	void draw_lines() const;
	void update_transform(GL::Point new_pos, int new_side_len, float new_angle);
	GL::Point point(int p) const;
	void toggle_bounding_box() { show_bbox = !show_bbox; }
	double angle() const { return a; };
	int side_length() const { return s; };
	void clear() { tris.clear(); };
	void update_bounding_box() { new_bbox(); };

private:
	bool is_oob(const GL::Point p_0, const GL::Point p_1) const;
	bool p_fits_bbox(const GL::Point p) const;
	bool show_bbox = false;
	void new_bbox();
	TriCoords get_tri(const GL::Point p_0, const GL::Point p_1) const;
	std::vector<GL::Point> get_oblique(const GL::Point p_0,
	                                   const GL::Point p_1) const;
	static constexpr int MAX_TRIS{ 500 };
	std::vector<std::unique_ptr<GL::Closed_polyline>> tris;
	GL::Rectangle bg;
	Bbox bbox;
	GL::Point bg_min;
	GL::Point bg_max;
	int s;
	double a;
};

} // namespace TRITI -----------------------------------------------------------
#endif // TRIANGLETILER_H
