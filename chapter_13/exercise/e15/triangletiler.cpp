#include "triangletiler.h"

TRITI::TriangleTiler::TriangleTiler(
	Graph_lib::Point o, int w, int h, int tri_side, double rotation)
 : GL::Shape(), bg(o, w, h), bbox_min(o), bbox_max({w, h}), s(tri_side),
   r(rotation)
{
	// Add first tile
	GL::Point in_end{
		static_cast<int>(std::round(o.x + cos(r) * s)),
		static_cast<int>(std::round(o.y + sin(r) * s))
	};
	tris.push_back(std::make_unique<RTRI::RightTriangle>(o, in_end));
}

void TRITI::TriangleTiler::draw_lines() const {
	bg.draw_lines();
	for (const auto& t : tris) {
		t->draw_lines();
	}
}

void TRITI::TriangleTiler::move_to(Graph_lib::Point new_pos)
{
	for (auto& t : tris) {
		t->move(new_pos.x - t->point(0).x, new_pos.y - t->point(0).y);
	}
}

Graph_lib::Point TRITI::TriangleTiler::point(int p) const
{
	int count = 0;
	for (const auto& t : tris) {
		for (int i = 0; i < t->number_of_points(); ++i) {
			if (count == p) {
				return t->point(i);
			}
			++count;
		}
	}
}

// bool TRITI::TriangleTiler::is_oob(const Graph_lib::Point p_0,
//                                   const Graph_lib::Point p_1) const
// {
// 	/*
// 	 * Returns true if out of bounds
// 	 */
// 	if (p_0.x <= bbox_min.x) {
// 		return (p_1.x <= bbox_min.x) || (p_1.x == p_0.x && p_1.y < p_0.y);
// 	}
// 	// bool check_b = ((p_0.x == bbox_max.x && p_1.x > p_0.x)
// 	//     || (p_0.y == bbox_min.y && p_1.y < p_0.y)
// 	//     || (p_0.y == bbox_max.y && p_1.y > p_0.y)) {
// 	// 	return true;
// 	// }
// }

// bool TRITI::TriangleTiler::p_fits_bbox(const Graph_lib::Point p) const
// {
// 	return (p.x >= bbox_min.x && p.x <= bbox_max.x)
// 	       && (p.y >= bbox_min.y && p.y <= bbox_max.y);
// }

// TRITI::TriCoords TRITI::TriangleTiler::get_tri(const Graph_lib::Point p_0,
//                                                const Graph_lib::Point p_1) const
// {
// 	if (!p_fits_bbox(p_0) || !p_fits_bbox(p_1)) {
// 		return {TriType::ObliqueTriangle, get_oblique(p_0, p_1)};
// 	}
// }
