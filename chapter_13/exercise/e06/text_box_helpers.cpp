#include "text_box.h"
#include "text_box_helpers.h"
#include "box_helpers.h"
#include "ellipse_helpers.h"

using HLPELL = ELL::ConnectionPointHelper;
using HLPBOX = BOX::ConnectionPointHelper;
using HLP = TBX::ConnectionPointHelper;

enum class HLP::PtID {
	NW, N, NE,
	W, C, E,
	SW, S, SE
};

Graph_lib::Point HLP::get_for_bg_type(
	const Text_box& box, TBX::Text_box::BG_shape bg, HLP::PtID id)
{
	if(bg == TBX::Text_box::BG_NONE) {
		return box.center();
	}
	if(bg == TBX::Text_box::BG_BOX) {
		return HLPBOX::get_verbose(
			box.bbox_origin(), box.width(), box.height(), box.corner_radius(),
			static_cast<HLPBOX::PtID>(id)
		);
	} else {
		return HLPELL::get_verbose(
			box.center(), box.width(), box.height(),
			static_cast<HLPELL::PtID>(id)
		);
	}
}

Graph_lib::Point HLP::get(const Text_box& box, const HLP::PtID id)
{
	return get_for_bg_type(box, box.shape_type(), id);
}


HLP::ConnectionPointHelper() {}; // No initialization

Graph_lib::Point TBX::nw(const Text_box& box)
{
	return HLP::get(box, HLP::PtID::NW);
}
Graph_lib::Point TBX::n(const Text_box& box)
{
	return HLP::get(box, HLP::PtID::N);
}
Graph_lib::Point TBX::ne(const Text_box& box)
{
	return HLP::get(box, HLP::PtID::NE);
}
Graph_lib::Point TBX::w(const Text_box& box) {
	return HLP::get(box, HLP::PtID::W);
}
Graph_lib::Point TBX::center(const Text_box& box)
{
	return HLP::get(box, HLP::PtID::C);
}
Graph_lib::Point TBX::e(const Text_box& box)
{
	return HLP::get(box, HLP::PtID::E);
}
Graph_lib::Point TBX::sw(const Text_box& box)
{
	return HLP::get(box, HLP::PtID::SW);
}
Graph_lib::Point TBX::s(const Text_box& box)
{
	return HLP::get(box, HLP::PtID::S);
}
Graph_lib::Point TBX::se(const Text_box& box)
{
	return HLP::get(box, HLP::PtID::SE);
}
