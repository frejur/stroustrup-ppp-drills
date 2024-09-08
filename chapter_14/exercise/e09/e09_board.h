#ifndef BOARD_H
#define BOARD_H
#include "../../lib/Graph.h"
#include "../share/grp/grp_rpoly.h"

namespace ch14_e09 {

static constexpr int tile_size_min{8};
static constexpr int tile_size_max{128};

class Board : public Graph_lib::Shape
{
public:
	Board(Graph_lib::Point origin, int tile_size);
	;
	void move(int x, int y) override;
	void scale(double scale_factor);
	void rotate(double offset_degrees);
	void set_frame_color(Graph_lib::Color col) { frame.set_fill_color(col); };
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
	}

private:
	Graph_lib::Point o;
	int tile_sz;

	grp_shp::R_poly_group frame;
	grp_shp::R_poly_group light_tiles;
	grp_shp::R_poly_group dark_tiles;
	grp_shp::R_poly_group light_pieces;
	grp_shp::R_poly_group dark_pieces;

	int valid_tile_size(int tile_size)
	{
		if (tile_size < tile_size_min || tile_size > tile_size_max) {
			throw std::runtime_error("Invalid tile size");
		}
		return tile_size;
	}

	int calc_frame_radius(int tile_size);

	Graph_lib::Point point(int i) const override { return {0, 0}; };

	void draw_lines() const override;
};
} // namespace ch14_e09

#endif // BOARD_H
