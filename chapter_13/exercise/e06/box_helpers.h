#ifndef BOX_HELPERS_H
#define BOX_HELPERS_H

#include "../../lib/Graph.h"
#include <map>
#include <utility>

namespace BOX {

namespace GL = Graph_lib;

struct ConnectionPointHelper
{
	enum class PtID;
	static GL::Point get(const GL::Rectangle& r, PtID id);
private:
	ConnectionPointHelper();

	// XY direction and magnitude in relation to Rectangle origin (NW)
	const static std::map<PtID, std::pair<float, float>> dir_XY;
};

GL::Point nw(const Graph_lib::Rectangle& r);
GL::Point n(const Graph_lib::Rectangle& r);
GL::Point ne(const Graph_lib::Rectangle& r);
GL::Point w(const Graph_lib::Rectangle& r);
GL::Point center(const GL::Rectangle& r);
GL::Point e(const Graph_lib::Rectangle& r);
GL::Point sw(const Graph_lib::Rectangle& r);
GL::Point s(const Graph_lib::Rectangle& r);
GL::Point se(const Graph_lib::Rectangle& r);

} // namespace BOX

#endif // BOX_HELPERS_H
