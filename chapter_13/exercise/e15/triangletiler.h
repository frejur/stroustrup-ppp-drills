#ifndef TRIANGLETILER_H
#define TRIANGLETILER_H

#include <vector>
#include <memory>
#include <cmath>
#include "../../lib/Graph.h"
#include "righttriangle.h"

namespace TRITI { //------------------------------------------------------------

namespace GL = Graph_lib;

class TriangleTiler
{
public:
	TriangleTiler();
private:
	std::vector<std::unique_ptr<RTRI::RightTriangle>> tris;
	GL::Point bbox_min;
	GL::Point bbox_max;
};

} // namespace TRITI -----------------------------------------------------------
#endif // TRIANGLETILER_H
