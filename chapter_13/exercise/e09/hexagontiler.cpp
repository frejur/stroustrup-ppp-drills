#include <iostream>
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
	: t_num(num_tiles), t_count(0), r(radius), c(center)
{
	tiles.push_back(std::make_unique<RegularHexagon>(c, r));
	++t_count;
	in_r = calculate_inradius();
	offset = std::make_unique<TileOffset>(r, in_r);

	act_t = 0;
	act_s = 0;
	int t_in_ring{ 0 };
	int max_t_in_ring{ 6 };
	while (t_count < t_num) {
		add_tiles(*tiles[act_t]);
		++act_t;
		t_in_ring = t_count - act_t + 1;
		if (t_in_ring > max_t_in_ring) {
			t_in_ring = 0;
			act_s = 0;
			max_t_in_ring += 6;
		}
	};
}

void HXT::HexagonTiler::add_tiles(RegularHexagon& hex)
{
	while (hex.side_is_open(act_s) && t_count < t_num) {
		Graph_lib::Point p{
			hex.center().x + offset->get(act_s).first,
			hex.center().y + offset->get(act_s).second
		};
		tiles.push_back(std::make_unique<RegularHexagon>(p, r));
		t_count++;
		hex.close_side(act_s);
		tiles.back()->close_side((act_s+3)%6);
		close_adjacent(t_count - 1, act_s);
		++act_s;
	};
	act_s = (act_s + 5)%6;

}

int HXT::HexagonTiler::tile_ring_number(int t) const
{
    if (t <= 0) {
        return 0;
    }

    // After the initial center tile, each ring of tiles increases
    // the total by a number divisible by 6.
    t = static_cast<int>(std::ceil(t / 6.0));

	// Values of t that mark a new level are triangular numbers (1, 3, 6, 10...)
	// Calculate the triangular root(level) and sum:
    int root = static_cast<int>(((sqrt(8 * t + 1) - 1) * 0.5));
    int sum = root * (root + 1) / 2;

	return (sum < t) ? root + 1 : root; // 2 to 3 -> 2, 4 to 6 -> 3, etc.
}

float HXT::HexagonTiler::tile_ring_position(int t) const {
	return tile_ring_position(t, tile_ring_number(t));
}

float HXT::HexagonTiler::tile_ring_position(int t, int ring) const
{
	// Returns a floating point number representing the position of
	// the given tile in relation to the centermost tile.
	// 0 to 6 for each side of the centre tile starting with 'up' and moving CW.
	// <side>.5 for anything inbetween.
	if (t <= 6) {
		return t - 1;
	}
	int sum{ 6 * (ring * (ring + 1) / 2) };
	int tiles_in_ring{ ring * 6 };
	int tile_idx{ t - (sum - tiles_in_ring) - 1};

	return (std::floor)((float)tile_idx / ring) + (tile_idx%ring > 0) * 0.5;
}

void HXT::HexagonTiler::close_adjacent(int t, int side)
{
	if (t > t_count - 1) {
		return;
	}
	for (int s=0; s < 6; ++s) {
		if (s == side || s == (side+3)%6) {
			continue;
		}
		int adj_t{ adjacent_tile(t, s) };
		if (adj_t > t_count -1) {
			continue;
		}
		if (tiles[adj_t]->side_is_open((s + 3)%6)) {
			tiles[adj_t]->close_side((s + 3)%6);
		}
		if (tiles[t]->side_is_open(s)) {
			tiles[t]->close_side(s);
		}
	}
}

int HXT::HexagonTiler::adjacent_tile(int t, int side)
{
	// Returns the tile number of an adjacent tile, given a tile and
	// the connecting side(0 to 6, starting with 'up' and moving CW).
	if (t == 0) {
		return side + 1;
	}
	int ring{ tile_ring_number(t) };
	float ring_pos{ tile_ring_position(t, ring) };
	switch (side) {
	case 0:
		return get_adj_0(t, ring_pos, ring);
		break;
	case 1:
		return get_adj_1(t, ring_pos, ring);
		break;
	case 2:
		return get_adj_2(t, ring_pos, ring);
		break;
	case 3:
		return get_adj_3(t, ring_pos, ring);
		break;
	case 4:
		return get_adj_4(t, ring_pos, ring);
		break;
	case 5:
		return get_adj_5(t, ring_pos, ring);
		break;
	default:
		throw std::runtime_error("Invalid side: " + std::to_string(side));
		break;
	}
}

int HXT::HexagonTiler::calculate_inradius() const
{
	return tiles.front()->center().y - tiles.front()->point(1).y;
}

void HXT::HexagonTiler::draw_lines() const
{
//	int i{ 0 };
	for (std::unique_ptr<RegularHexagon> const& t : tiles) {
		t->draw();
//		fl_color(FL_BLACK);
//		fl_draw(std::to_string(i).c_str(), t->center().x, t->center().y);
//		++i;
	}
}

int HXT::HexagonTiler::get_adj_0(
	int t, float ring_pos, int ring) const
{
	if (t == 4) {
		return 0;
	}
	if (1 < ring_pos && ring_pos <= 2) {
		return t - 1;
	}
	if (4 <= ring_pos && ring_pos < 5) {
		return t + 1;
	}
	if (ring_pos <= 1) {
		return t + ring * 6;
	}
	if (ring_pos >= 5) {
		return t + (ring + 1) * 6;
	}
	return t - 3 - (ring - 1) * 6;
}

int HXT::HexagonTiler::get_adj_1(
	int t, float ring_pos, int ring) const
{
	if (t == 5) {
		return 0;
	}
	if (2 < ring_pos && ring_pos <= 3) {
		return t - 1;
	}
	if (ring_pos >= 5) {
		int sum_ring{ (ring * (ring + 1) / 2) * 6 };
		if (t == sum_ring) {
			return sum_ring - ring * 6 + 1;
		}
		return t + 1;
	}
	if (0 <= ring_pos && ring_pos <= 2) {
		return t + ring * 6 + 1;
	}
	return t - 4 - (ring - 1) * 6;
}

int HXT::HexagonTiler::get_adj_2(
	int t, float ring_pos, int ring) const
{
	if (t == 6) {
		return 0;
	}
	if (ring_pos < 1) {
		return t + 1;
	}
	if (1 <= ring_pos && ring_pos <= 3) {
		return t + ring * 6 + 2;
	}
	if (3 < ring_pos && ring_pos <= 4) {
		return t - 1;
	}
	int sum_ring{ (ring * (ring + 1) / 2) * 6 };
	if (t == sum_ring) {
		return (ring - 2) * 6 + 1;
	}
	return t - ring * 6 + 1;
}

int HXT::HexagonTiler::get_adj_3(
	int t, float ring_pos, int ring) const
{
	if (t == 1) {
		return 0;
	}
	if (1 <= ring_pos && ring_pos < 2) {
		return t + 1;
	}
	if (4 < ring_pos && ring_pos <= 5) {
		return t - 1;
	}
	if (ring_pos < 1) {
		return t - (ring - 1) * 6;
	}
	if (ring_pos > 5) {
		return t - ring * 6;
	}
	return t - 3 + (ring + 1) * 6;
}

int HXT::HexagonTiler::get_adj_4(
	int t, float ring_pos, int ring) const
{
	if (t == 2) {
		return 0;
	}
	if (2 <= ring_pos && ring_pos < 3) {
		return t + 1;
	}
	if (ring_pos > 5) {
		return t - 1;
	}
	if (ring_pos == 0) {
		return t + ring * 6 - 1;
	}
	if (0 < ring_pos && ring_pos < 2) {
		return t - (ring - 1) * 6 - 1;
	}
	return t + ring * 6 + 4;
}

int HXT::HexagonTiler::get_adj_5(
	int t, float ring_pos, int ring) const
{
	if (t == 3) {
		return 0;
	}
	if (ring_pos == 0) {
		return ((ring + 1) * (ring + 2) / 2) * 6;
	}
	if (0 < ring_pos && ring_pos <= 1) {
		return t - 1;
	}
	if (1 < ring_pos && ring_pos < 3) {
		return t - (ring - 1) * 6 - 2;
	}
	if (3 <= ring_pos && ring_pos < 4) {
		return t + 1;
	}
	return t + ring * 6 + 5;
}

