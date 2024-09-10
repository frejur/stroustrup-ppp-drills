#ifndef TEXT_BOX_HELPERS_H
#define TEXT_BOX_HELPERS_H

#include <map>
#include <utility>
#include "text_box.h"

namespace TBX {

namespace GL = Graph_lib;

struct ConnectionPointHelper
{
	enum class PtID;
	static GL::Point get(const Text_box& r, const PtID id);
private:
	static GL::Point get_for_bg_type(
		const Text_box& box, const TBX::Text_box::BG_shape bg, const PtID id);
	ConnectionPointHelper();

	// XY direction and magnitude in relation to Box origin (NW)
	const static std::map<PtID, std::pair<float, float>> dir_XY;
};
GL::Point nw(const TBX::Text_box& r);
GL::Point n(const TBX::Text_box& r);
GL::Point ne(const TBX::Text_box& r);
GL::Point w(const TBX::Text_box& r);
GL::Point center(const TBX::Text_box& r);
GL::Point e(const TBX::Text_box& r);
GL::Point sw(const TBX::Text_box& r);
GL::Point s(const TBX::Text_box& r);
GL::Point se(const TBX::Text_box& r);

} // namespace TBX

#endif // TEXT_BOX_HELPERS_H
