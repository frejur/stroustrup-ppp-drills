#ifndef TRIANGLETILER_H
#define TRIANGLETILER_H

#include <vector>
#include <memory>
#include <cmath>
#include "../../lib/Graph.h"
#include "righttriangle.h"

namespace TRITI { //------------------------------------------------------------

namespace GL = Graph_lib;

class TriangleTiler : public GL::Shape
{
public:
	TriangleTiler(GL::Point o, int w, int h, int tri_side, double rotation);
	void draw_lines() const;
private:
	static constexpr int MAX_TRIS{ 500 };
	std::vector<std::unique_ptr<RTRI::RightTriangle>> tris;
	GL::Rectangle bg;
	GL::Point bbox_min;
	GL::Point bbox_max;
	int s;
	double r;
};

} // namespace TRITI -----------------------------------------------------------
#endif // TRIANGLETILER_H
