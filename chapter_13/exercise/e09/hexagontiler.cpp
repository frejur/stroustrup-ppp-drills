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
	: c(center), tc(center), r(radius), ir(0), tile_count(0), active_edge(0),
	active_tile(0)
{
	num_tiles = (std::max)(1, num_tiles);
	int cyc{ 0 }; // active cycle (1 is the innermost)
	int cyc_t {0};// number of the active tile in cycle
	int idx{ 0 }; // index of active tile
	std::cout << "Tile #0" << std::endl;
	do {
		add_tile(tc, active_edge);
		if (tile_count==0) {
			cyc = 1; // start first cycle
			tile_count = 1;
			ir = calculate_inradius();
			offs = make_unique<TileOffset>(r, ir);
		} else {
			tiles[idx]->close_side(active_edge);
			++cyc_t;
			++tile_count;
			++active_edge;
		}
		if (tile_count > 0 && !tiles[idx]->side_is_open(active_edge)) {
			tc = tiles[idx+1]->center();
			++idx;
			++active_tile;
			std::cout << '\t' << "Final Side status: ";
			for (int i=0; i<6; ++i) {
				std::cout << tiles[active_tile-1]->side_is_open(i) << ", ";
			}
			std::cout << std::endl;
			std::cout << "Tile #" << idx << std::endl;
			if (cyc_t%(6*cyc)==0) {
				std::cout << "NEW CYCLE" << std::endl;
				active_edge = 0;
				cyc_t = 0;
				++cyc;
				continue;
			}
			--active_edge;
			std::cout << '\t' << "Pre (" << active_tile << "): ";
			for (int i=0; i<6; ++i) {
				std::cout << tiles[active_tile]->side_is_open(i) << ", ";
			}
			tiles[active_tile]->close_side((active_edge+5)%6);
			tiles[active_tile]->close_side((active_edge+4)%6);
			tiles[active_tile]->close_side((active_edge+3)%6);
			std::cout << ", " << "Post (" << active_tile << "): ";
			for (int i=0; i<6; ++i) {
				std::cout << tiles[active_tile]->side_is_open(i) << ", ";
			}
			std::cout << std::endl;
		}
		std::cout << '\t' << "Cycle tile: " << cyc_t << " in " << cyc << std::endl;
	} while (tile_count < num_tiles);
}

int HXT::HexagonTiler::calculate_inradius() const
{
	return tiles.front()->center().y - tiles.front()->point(1).y;
}

void HXT::HexagonTiler::add_tile(const Graph_lib::Point& o, const int con)
{
	std::pair<int, int> offset =
		(tile_count > 0) ? offs->get(con) : std::make_pair(0, 0);
	if (tile_count>0) {
		std::cout << '\t' << '\t' << "Side status: ";
		for (int i=0; i<6; ++i) {
			std::cout << tiles[active_tile]->side_is_open(i) << ", ";
		}
		std::cout << std::endl;
	}
	std::cout << '\t' << '\t' << "Adding tile " << tile_count << " with a connection of: " << con << std::endl;
	Graph_lib::Point p{ o.x + offset.first, o.y + offset.second };
	tiles.push_back(
		std::make_unique<RegularHexagon>(p, r)
	);
	if (tile_count > 0) {
		tiles.back()->close_side((con+3)%6);
		tiles.back()->close_side((con+2)%6);
	}
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

