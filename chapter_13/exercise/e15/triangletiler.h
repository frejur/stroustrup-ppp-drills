#ifndef TRIANGLETILER_H
#define TRIANGLETILER_H

#include <vector>
#include <memory>
#include <cmath>
#include "../../lib/Graph.h"
#include "righttriangle.h"

namespace TRITI { //------------------------------------------------------------

namespace GL = Graph_lib;

enum class TriType { ZeroArea, RightTriangle, ObliqueTriangle };

struct TriCoords
{
	TriType type = TriType::ZeroArea;
	std::vector<GL::Point> points;
};

class TriangleTiler : public GL::Shape
{
public:
	TriangleTiler(GL::Point o, int w, int h, int tri_side, double rotation);
	void draw_lines() const;
	void move_to(GL::Point new_pos);
	GL::Point point(int p) const;

private:
	bool is_oob(const GL::Point p_0, const GL::Point p_1) const;
	bool p_fits_bbox(const GL::Point p) const;
	TriCoords get_tri(const GL::Point p_0, const GL::Point p_1) const;
	std::vector<GL::Point> get_oblique(const GL::Point p_0,
	                                   const GL::Point p_1) const;
	static constexpr int MAX_TRIS{ 500 };
	std::vector<std::unique_ptr<GL::Closed_polyline>> tris;
	GL::Rectangle bg;
	GL::Point bbox_min;
	GL::Point bbox_max;
	int s;
	double r;
};

} // namespace TRITI -----------------------------------------------------------
#endif // TRIANGLETILER_H
