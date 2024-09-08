#include "e09_board.h"
#include <cmath>

//------------------------------------------------------------------------------

ch14_e09::Board::Board(Graph_lib::Point origin, int tile_size)
    : o(origin)
    , tile_sz(tile_size)
    , frame(o)
    , light_tiles(o)
    , dark_tiles(o)
    , light_pieces(o)
    , dark_pieces(o)
{
	frame.add(o, calc_frame_radius(tile_sz), 4, 45);

	int tile_sz_half{tile_sz / 2};
	int tile_top_l_x{o.x - tile_sz * 4 - tile_sz_half};
	int tile_top_l_y{o.y - tile_sz * 4 - tile_sz_half};
	int tile_rad{static_cast<int>(std::round(sqrt(2) * tile_sz / 2))};
	int piece_rad{static_cast<int>(std::round(tile_rad * 0.55))};
	int count = 0;
	for (int row = 0; row < 10; ++row) {
		for (int col = 0; col < 10; ++col) {
			if ((row + col) % 2) {
				dark_tiles.add({tile_top_l_x + tile_sz * col,
				                tile_top_l_y + tile_sz * row},
				               tile_rad,
				               4,
				               45);
			} else {
				light_tiles.add({tile_top_l_x + tile_sz * col,
				                 tile_top_l_y + tile_sz * row},
				                tile_rad,
				                4,
				                45);
			}
			if (count < 40 && ((count + (row % 2)) % 2 == 1)) {
				dark_pieces.add({tile_top_l_x + tile_sz * col,
				                 tile_top_l_y + tile_sz * row},
				                piece_rad,
				                8);
			}
			if (count > 60 && ((count + (row % 2)) % 2 == 1)) {
				light_pieces.add({tile_top_l_x + tile_sz * col,
				                  tile_top_l_y + tile_sz * row},
				                 piece_rad,
				                 8);
			}
			++count;
		}
	}
	frame.set_color(Graph_lib::Color::invisible);
	light_tiles.set_color(Graph_lib::Color::invisible);
	dark_tiles.set_color(Graph_lib::Color::invisible);
	light_pieces.set_color(Graph_lib::Color::invisible);
	dark_pieces.set_color(Graph_lib::Color::invisible);

	frame.set_fill_color(Graph_lib::Color::dark_blue);
	light_tiles.set_fill_color(Graph_lib::Color::white);
	dark_tiles.set_fill_color(Graph_lib::Color::blue);
	light_pieces.set_fill_color(Graph_lib::Color::yellow);
	dark_pieces.set_fill_color(Graph_lib::Color::black);
}

void ch14_e09::Board::move(int x, int y)
{
	frame.move(x, y);
	light_tiles.move(x, y);
	dark_tiles.move(x, y);
	light_pieces.move(x, y);
	dark_pieces.move(x, y);
}

void ch14_e09::Board::scale(double scale_factor)
{
	frame.scale_uniformly(scale_factor);
	light_tiles.scale_uniformly(scale_factor);
	dark_tiles.scale_uniformly(scale_factor);
	light_pieces.scale_uniformly(scale_factor);
	dark_pieces.scale_uniformly(scale_factor);
}

void ch14_e09::Board::rotate(double offset_degrees)
{
	frame.rotate_around_origin(offset_degrees);
	light_tiles.rotate_around_origin(offset_degrees);
	dark_tiles.rotate_around_origin(offset_degrees);
	light_pieces.rotate_around_origin(offset_degrees);
	dark_pieces.rotate_around_origin(offset_degrees);
}

int ch14_e09::Board::calc_frame_radius(int tile_size)
{
	return sqrt(2.0) * tile_size * 5 + 2 * tile_size;
}

//------------------------------------------------------------------------------

void ch14_e09::Board::draw_lines() const
{
	frame.draw();
	light_tiles.draw();
	dark_tiles.draw();
	light_pieces.draw();
	dark_pieces.draw();
}
