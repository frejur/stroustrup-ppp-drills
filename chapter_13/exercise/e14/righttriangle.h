#ifndef RIGHTTRIANGLE_H
#define RIGHTTRIANGLE_H
#include <cmath>
#include "../../lib/Graph.h"
#include "isoscelestriangle.h"
#define _USE_MATH_DEFINES
#include <math.h>

namespace RTRI { //-------------------------------------------------------------

namespace GL = Graph_lib;

class RightTriangle : public ITRI::IsoscelesTriangle {
public:
	RightTriangle(GL::Point origin, GL::Point end_opposite)
	: ITRI::IsoscelesTriangle(origin, end_opposite, M_PI * 0.5) {};
};


} // namespace TRI -------------------------------------------------------------



#endif // RIGHTTRIANGLE_H
