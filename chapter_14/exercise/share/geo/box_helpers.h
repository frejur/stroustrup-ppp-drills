#ifndef BOX_HELPERS_H
#define BOX_HELPERS_H

#include <map>
#include <utility>
#include "box.h"

namespace BOX {

namespace GL = Graph_lib;

struct ConnectionPointHelper
{
	enum class PtID;
	static GL::Point get(const Box& r, const PtID id);
	static Graph_lib::Point get_verbose(
		const GL::Point& o, const int w, const int h, const int rad,
		const PtID id
	);
private:
	ConnectionPointHelper();

	// XY direction and magnitude in relation to Box origin (NW)
	const static std::map<PtID, std::pair<float, float>> dir_XY;
};

enum class ConnectionPointHelper::PtID { NW, N, NE, W, C, E, SW, S, SE };

GL::Point nw(const Box& r);
GL::Point n(const Box& r);
GL::Point ne(const Box& r);
GL::Point w(const Box& r);
GL::Point center(const Box& r);
GL::Point e(const Box& r);
GL::Point sw(const Box& r);
GL::Point s(const Box& r);
GL::Point se(const Box& r);

} // namespace BOX

#endif // BOX_HELPERS_H
