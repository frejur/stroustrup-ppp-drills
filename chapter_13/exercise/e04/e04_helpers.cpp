#include "e04_helpers.h"
#include <map>
#include <utility>

using HLP = E04::ConnectionPointHelper;

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

Graph_lib::Point HLP::get(const Graph_lib::Rectangle& r, HLP::PtID id)
{
	auto dir = dir_XY.find(id)->second;
	return(
		GL::Point{
			static_cast<int>(r.point(0).x + r.width() * dir.first),
			static_cast<int>(r.point(0).y + r.height() * dir.second)
		}
	);
}

HLP::ConnectionPointHelper() {}; // No initialization

Graph_lib::Point E04::nw(const Graph_lib::Rectangle& r)
{
	return HLP::get(r, HLP::PtID::NW);
}
Graph_lib::Point E04::n(const Graph_lib::Rectangle& r)
{
	return HLP::get(r, HLP::PtID::N);
}
Graph_lib::Point E04::ne(const Graph_lib::Rectangle& r)
{
	return HLP::get(r, HLP::PtID::NE);
}
Graph_lib::Point E04::w(const Graph_lib::Rectangle& r) {
	return HLP::get(r, HLP::PtID::W);
}
Graph_lib::Point E04::center(const Graph_lib::Rectangle& r)
{
	return HLP::get(r, HLP::PtID::C);
}
Graph_lib::Point E04::e(const Graph_lib::Rectangle& r)
{
	return HLP::get(r, HLP::PtID::E);
}
Graph_lib::Point E04::sw(const Graph_lib::Rectangle& r)
{
	return HLP::get(r, HLP::PtID::SW);
}
Graph_lib::Point E04::s(const Graph_lib::Rectangle& r)
{
	return HLP::get(r, HLP::PtID::S);
}
Graph_lib::Point E04::se(const Graph_lib::Rectangle& r)
{
	return HLP::get(r, HLP::PtID::SE);
}
