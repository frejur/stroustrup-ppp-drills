#ifndef ISOSCELESTRIANGLE_H
#define ISOSCELESTRIANGLE_H
#include "../../../lib/Graph.h"
#include <cmath>
namespace itri { //-------------------------------------------------------------

namespace GL = Graph_lib;

class IsoscelesTriangle : public GL::Closed_polyline {
public:
	IsoscelesTriangle(GL::Point origin,
	                  GL::Point end_opposite,
	                  double angle,
	                  bool invert = false);
	IsoscelesTriangle(GL::Point origin,
	                  int width,
	                  int height,
	                  double rotation = 0);
};

} // namespace itri

#endif // ISOSCELESTRIANGLE_H
