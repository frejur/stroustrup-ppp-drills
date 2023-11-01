#ifndef RIGHTTRIANGLE_H
#define RIGHTTRIANGLE_H
#include <cmath>
#include "../../lib/Graph.h"
namespace RTRI { //-------------------------------------------------------------

namespace GL = Graph_lib;

class RightTriangle : public GL::Closed_polyline {
public:
	RightTriangle(GL::Point origin, GL::Point end_opposite, int len_adjacent);
	RightTriangle(GL::Point origin, GL::Point end_opposite)
	: RightTriangle(origin, end_opposite,
		sqrt(
			pow(std::abs(end_opposite.y - origin.y), 2) +
			pow(std::abs(end_opposite.x - origin.x), 2)
		)
	) {};
};


} // namespace TRI -------------------------------------------------------------



#endif // RIGHTTRIANGLE_H
