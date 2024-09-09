#ifndef BOARD_H
#define BOARD_H
#include "../../lib/Graph.h"
#include "../share/grp/grp_rpoly.h"

namespace ch14_e09 {

static constexpr int tile_size_min{8};
static constexpr int tile_size_max{128};
static constexpr int piece_sides{9};

static const Graph_lib::Color default_frame_color()
{
	static const Graph_lib::Color& c{
	    static_cast<int>(fl_rgb_color(160, 120, 100))};
	return c;
}

static const Graph_lib::Color default_light_piece_color()
{
	static const Graph_lib::Color& c{
	    static_cast<int>(fl_rgb_color(230, 220, 190))};
	return c;
}

static const Graph_lib::Color default_dark_tile_color()
{
	static const Graph_lib::Color& c{
	    static_cast<int>(fl_rgb_color(160, 120, 100))};
	return c;
}

static const Graph_lib::Color default_light_tile_color()
{
	static const Graph_lib::Color& c{
	    static_cast<int>(fl_rgb_color(195, 165, 135))};
	return c;
}

static const Graph_lib::Color default_dark_piece_color()
{
	static const Graph_lib::Color& c{static_cast<int>(fl_rgb_color(40, 35, 30))};
	return c;
}

//------------------------------------------------------------------------------

class Board : public Graph_lib::Shape
{
public:
	void extracted();
	Board(Graph_lib::Point origin, int tile_size);

	void move_piece(int start_tile, int end_tile);
	void move(int x, int y) override;
	void scale(double scale_factor);
	void rotate(double offset_degrees);
	Graph_lib::Point tile_position(int tile_index)
	{
		return dark_tiles.center(valid_tile_index(tile_index));
	}
	void set_outer_frame_color(Graph_lib::Color col)
	{
		frame.set_fill_color(col, 0);
	};
	void set_inner_frame_color(Graph_lib::Color col)
	{
		frame.set_fill_color(col, 1);
	};
	void set_light_tiles_color(Graph_lib::Color col)
	{
		light_tiles.set_fill_color(col);
	};
	void set_dark_tiles_color(Graph_lib::Color col)
	{
		dark_tiles.set_fill_color(col);
	};
	void set_light_pieces_color(Graph_lib::Color col)
	{
		light_pieces.set_fill_color(col);
	};
	void set_dark_pieces_color(Graph_lib::Color col)
	{
		dark_pieces.set_fill_color(col);
	};
	void reset()
	{
		frame.reset();
		light_tiles.reset();
		dark_tiles.reset();
		light_pieces.reset();
		dark_pieces.reset();
		init_tile_status_v(true);
		set_colors();
	}

private:
	Graph_lib::Point o;
	int tile_sz;

	grp_shp::R_poly_group frame;
	grp_shp::R_poly_group light_tiles;
	grp_shp::R_poly_group dark_tiles;
	grp_shp::R_poly_group light_pieces;
	grp_shp::R_poly_group dark_pieces;

	// tie tile indices to piece indices
	std::vector<int> tile_status{std::vector<int>(50, -1)};

	int valid_tile_size(int tile_size)
	{
		if (tile_size < tile_size_min || tile_size > tile_size_max) {
			throw std::runtime_error("Invalid tile size");
		}
		return tile_size;
	}

	int valid_tile_index(int tile_index)
	{
		if (tile_index < 0 || tile_index > 49) {
			throw std::runtime_error("Invalid tile index");
		}
		return tile_index;
	}

	int calc_square_diagonal(int side);
	void add_frame();

	Graph_lib::Point point(int i) const override { return {0, 0}; };

	void draw_lines() const override;
	void add_tiles_and_pieces();
	void init_tile_status_v(bool full_reset = false);
	void set_colors();
};
} // namespace ch14_e09

#endif // BOARD_H
