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
