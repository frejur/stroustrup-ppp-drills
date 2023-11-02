#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <cmath>
#include "../../lib/Graph.h"
namespace ITRI { //-------------------------------------------------------------

namespace GL = Graph_lib;

class IsoscelesTriangle : public GL::Closed_polyline {
public:
	IsoscelesTriangle(GL::Point origin, GL::Point end_opposite, double angle);
};

} // namespace TRI -------------------------------------------------------------



#endif // TRIANGLE_H
