#define _USE_MATH_DEFINES
#include "box_helpers.h"
#include <cmath>
#include <map>
#include <utility>

using HLP = BOX::ConnectionPointHelper;

enum class HLP::PtID {
	NW, N, NE,
	W, C, E,
	SW, S, SE
};

const std::map<HLP::PtID, std::pair<float, float>> HLP::dir_XY {
	{HLP::PtID::NW, {0.0, 0.0}},
	{HLP::PtID::N,  {0.5, 0.0}},
	{HLP::PtID::NE, {1.0, 0.0}},
	{HLP::PtID::W,  {0.0, 0.5}},
	{HLP::PtID::C,  {0.5, 0.5}},
	{HLP::PtID::E,  {1.0, 0.5}},
	{HLP::PtID::SW, {0.0, 1.0}},
	{HLP::PtID::S,  {0.5, 1.0}},
	{HLP::PtID::SE, {1.0, 1.0}},
};

Graph_lib::Point HLP::get_verbose(
	const GL::Point& o, const int w, const int h, const int rad,
	const HLP::PtID id)
{
	auto dir = dir_XY.find(id)->second;
	int x { static_cast<int>(o.x + w * dir.first) };
	int y { static_cast<int>(o.y + h * dir.second) };
	if (rad != 0 && (dir.first != 0.5 && dir.second != 0.5)) {
		int dist{
			static_cast<int>(rad - std::cos(M_PI*0.25) * rad) };
		x -= dist * (dir.first * 2 - 1);
		y -= dist * (dir.second * 2 - 1);
	}

	return GL::Point{x, y};
}

Graph_lib::Point HLP::get(const Box& r, const HLP::PtID id)
{
	return get_verbose(
		r.bbox_origin(), r.width(), r.height(), r.corner_radius(), id
	);
}

HLP::ConnectionPointHelper() {}; // No initialization

Graph_lib::Point BOX::nw(const Box& r)
{
	return HLP::get(r, HLP::PtID::NW);
}
Graph_lib::Point BOX::n(const Box& r)
{
	return HLP::get(r, HLP::PtID::N);
}
Graph_lib::Point BOX::ne(const Box& r)
{
	return HLP::get(r, HLP::PtID::NE);
}
Graph_lib::Point BOX::w(const Box& r) {
	return HLP::get(r, HLP::PtID::W);
}
Graph_lib::Point BOX::center(const Box& r)
{
	return HLP::get(r, HLP::PtID::C);
}
Graph_lib::Point BOX::e(const Box& r)
{
	return HLP::get(r, HLP::PtID::E);
}
Graph_lib::Point BOX::sw(const Box& r)
{
	return HLP::get(r, HLP::PtID::SW);
}
Graph_lib::Point BOX::s(const Box& r)
{
	return HLP::get(r, HLP::PtID::S);
}
Graph_lib::Point BOX::se(const Box& r)
{
	return HLP::get(r, HLP::PtID::SE);
}
