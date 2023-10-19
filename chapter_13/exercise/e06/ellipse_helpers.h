#ifndef ELLIPSE_HELPERS_H
#define ELLIPSE_HELPERS_H

#include "../../lib/Graph.h"
#include <map>
#include <utility>

namespace ELL {

namespace GL = Graph_lib;

struct ConnectionPointHelper
{
	enum class PtID;
	static GL::Point get(const GL::Circle& r, PtID id);
	static GL::Point get(const GL::Ellipse& r, PtID id);
private:
	ConnectionPointHelper();
	const static GL::Point getPerimeterPoint(
		const GL::Ellipse&,	double radius_x, double radius_y, double angle);

	// Direction in relation to center of Circle/Ellipse
	const static std::map<PtID, double> dir_angle;
};

GL::Point nw(const Graph_lib::Ellipse& r);
GL::Point n(const Graph_lib::Ellipse& r);
GL::Point ne(const Graph_lib::Ellipse& r);
GL::Point w(const Graph_lib::Ellipse& r);
GL::Point center(const GL::Ellipse& r);
GL::Point e(const Graph_lib::Ellipse& r);
GL::Point sw(const Graph_lib::Ellipse& r);
GL::Point s(const Graph_lib::Ellipse& r);
GL::Point se(const Graph_lib::Ellipse& r);

GL::Point nw(const Graph_lib::Circle& r);
GL::Point n(const Graph_lib::Circle& r);
GL::Point ne(const Graph_lib::Circle& r);
GL::Point w(const Graph_lib::Circle& r);
GL::Point center(const GL::Circle& r);
GL::Point e(const Graph_lib::Circle& r);
GL::Point sw(const Graph_lib::Circle& r);
GL::Point s(const Graph_lib::Circle& r);
GL::Point se(const Graph_lib::Circle& r);
} // namespace ELL

#endif // ELL_HELPERS_H
