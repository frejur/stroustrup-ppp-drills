#include "hexagontiler.h"
#include <memory>
#include "regularhexagon.h"
#include <cmath>
#include <algorithm>
#include <string>

HXT::TileOffset::TileOffset(int radius, int inradius)
	: offs{{
		{0, inradius * -2},
		{static_cast<int>(radius * 1.5), -inradius},
		{static_cast<int>(radius * 1.5), inradius},
		{0, inradius * 2},
		{static_cast<int>(radius * -1.5), inradius},
		{static_cast<int>(radius * -1.5), -inradius},
	}}
{
}

HXT::HexagonTiler::HexagonTiler(
	Graph_lib::Point center, int num_tiles, int radius)
	: c(center), r(radius), in_r(0), t_count(0)
{
}

int HXT::HexagonTiler::calculate_inradius() const
{
	return tiles.front()->center().y - tiles.front()->point(1).y;
}

void HXT::HexagonTiler::add_tile(const RegularHexagon& hex, const int con)
{
}

void HXT::HexagonTiler::draw_lines() const
{
	int i{ 0 };
	for (std::unique_ptr<RegularHexagon> const& t : tiles) {
		t->draw();
		fl_color(FL_BLACK);
		fl_draw(std::to_string(i).c_str(), t->center().x, t->center().y);
		++i;
	}
}

