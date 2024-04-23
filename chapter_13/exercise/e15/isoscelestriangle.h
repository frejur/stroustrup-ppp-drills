#ifndef ISOSCELESTRIANGLE_H
#define ISOSCELESTRIANGLE_H
#include <cmath>
#include "../../lib/Graph.h"
namespace ITRI { //-------------------------------------------------------------

namespace GL = Graph_lib;

class IsoscelesTriangle : public GL::Closed_polyline {
public:
	IsoscelesTriangle(GL::Point origin,
	                  GL::Point end_opposite,
	                  double angle,
	                  bool invert = false);
};

} // namespace TRI -------------------------------------------------------------



#endif // ISOSCELESTRIANGLE_H
