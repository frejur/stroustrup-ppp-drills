#include "e09_board.h"
#include <cmath>

//------------------------------------------------------------------------------

int ch14_e09::Board::calc_square_diagonal(int side)
{
	return sqrt(2.0) * side;
}

void ch14_e09::Board::add_frame()
{
	int tiles_diag = calc_square_diagonal(tile_sz * 5);
	int outer_r{tiles_diag + tile_sz};
	int inner_r{static_cast<int>(std::round(tiles_diag + tile_sz * 0.2))};
	frame.add(o, outer_r, 4, 45);
	frame.add(o, inner_r, 4, 45);
}

void ch14_e09::Board::add_tiles_and_pieces()
{
	int tile_sz_half{tile_sz / 2};
	int tile_top_l_x{o.x - tile_sz * 4 - tile_sz_half};
	int tile_top_l_y{o.y - tile_sz * 4 - tile_sz_half};
	int tile_r{static_cast<int>(std::round(sqrt(2) * tile_sz / 2))};
	int piece_r{static_cast<int>(std::round(tile_r * 0.55))};
	int count = 0;
	for (int row = 0; row < 10; ++row) {
		for (int col = 0; col < 10; ++col) {
			int pos_x{tile_top_l_x + tile_sz * col};
			int pos_y{tile_top_l_y + tile_sz * row};
			if ((row + col) % 2) {
				dark_tiles.add({pos_x, pos_y}, tile_r, 4, 45);
			} else {
				light_tiles.add({pos_x, pos_y}, tile_r, 4, 45);
			}
			if (count < 40 && ((count + (row % 2)) % 2 == 1)) {
				dark_pieces.add({pos_x, pos_y}, piece_r, piece_sides);
			} else if (count > 60 && ((count + (row % 2)) % 2 == 1)) {
				light_pieces.add({pos_x, pos_y}, piece_r, piece_sides);
			}
			++count;
		}
	}
}

void ch14_e09::Board::init_tile_status_v(bool full_reset)
{
	for (int i = 0; i < tile_status.size(); ++i) {
		if (i < 20) {
			tile_status[i] = i;
		} else if (i > 29) {
			tile_status[i] = i - 10;
		} else if (full_reset) {
			tile_status[i] = -1;
		}
	}
}

void ch14_e09::Board::set_colors()
{
	set_inner_frame_color(default_light_tile_color());
	set_outer_frame_color(default_frame_color());
	set_light_tiles_color(default_light_tile_color());
	set_dark_tiles_color(default_dark_tile_color());
	set_light_pieces_color(default_light_piece_color());
	set_dark_pieces_color(default_dark_piece_color());
}

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
	add_frame();
	add_tiles_and_pieces();
	init_tile_status_v();

	// No outlines
	frame.set_color(Graph_lib::Color::invisible);
	light_tiles.set_color(Graph_lib::Color::invisible);
	dark_tiles.set_color(Graph_lib::Color::invisible);
	light_pieces.set_color(Graph_lib::Color::invisible);
	dark_pieces.set_color(Graph_lib::Color::invisible);

	set_colors();
}

void ch14_e09::Board::move_piece(int start_tile, int end_tile)
{
	// Some basic movements, very rudimentary.
	// TODO: The concept of 'kings' has not been implemented, etc.

	if (start_tile == end_tile) {
		throw std::runtime_error("Illegal move: Start equals end");
	}

	// Adjust for 1-based-index entry
	start_tile -= 1;
	end_tile -= 1;

	int start_piece = tile_status[valid_tile_index(start_tile)];
	if (start_piece == -1) {
		throw std::runtime_error("Illegal move: Start tile is empty");
	}
	int end_piece = tile_status[valid_tile_index(end_tile)];

	int tiles_diff = std::abs(start_tile - end_tile);
	bool start_is_odd_row = (start_tile % 10 < 5); // For ref.: Top row is Odd
	int num_tiles = 0; // The distance in diagonal tiles
	int sign = (end_tile > start_tile) ? 1 : -1;

	if (4 <= tiles_diff && tiles_diff <= 6) {
		num_tiles = 1;
	} else if (tiles_diff == 9 || tiles_diff == 11) {
		num_tiles = 2;
	}

	// So far so good, now check for exceptions when pieces are close to the
	// side of the board.
	if (num_tiles == 2) {
		if (((start_tile % 5 == 0)
		     && (((sign > 0) && tiles_diff == 9)
		         || ((sign < 0) && tiles_diff == 11)))
		    || ((((start_tile + 1) % 5) == 0)
		        && (((sign > 0) && tiles_diff == 11)
		            || ((sign < 0) && tiles_diff == 9)))) {
			num_tiles = 0;
		}
	} else if (num_tiles == 1) {
		if ((((start_tile - 5) % 10 == 0) || ((start_tile - 4) % 10 == 0))
		    && tiles_diff != 5) {
			num_tiles = 0;
		}
	}

	if (num_tiles == 0) {
		throw std::runtime_error("Illegal move: Only diagonal moves within a "
		                         "distance of 2 tiles allowed");
	}

	if (end_piece != -1) {
		throw std::runtime_error("Illegal move: End tile is occupied");
	}

	// Single tile moves may only move forward
	bool is_dark = true;
	if (start_piece < 20) {
		// Dark
		if (num_tiles == 1 && end_tile < start_tile) {
			throw std::runtime_error(
			    "Illegal move: Dark may only move downwards");
		}
	} else {
		// Light
		if (num_tiles && end_tile > start_tile) {
			throw std::runtime_error(
			    "Illegal move: Light may only move upwards");
		}
		is_dark = false;
	}

	// Double tile moves must skip past an opponent
	int skipped_tile = -1;
	int skipped_piece = -1;
	bool skipped_is_dark = false;
	if (num_tiles == 2) {
		if (sign > 0) {
			if (start_is_odd_row) {
				skipped_tile = start_tile + (tiles_diff + 1) / 2;
			} else {
				skipped_tile = start_tile + (tiles_diff - 1) / 2;
			}
		} else {
			if (start_is_odd_row) {
				skipped_tile = start_tile - (tiles_diff - 1) / 2;
			} else {
				skipped_tile = start_tile - (tiles_diff + 1) / 2;
			}
		}

		skipped_piece = tile_status[skipped_tile];
		if (skipped_piece == -1) {
			throw std::runtime_error(
			    "Illegal move: Cannot skip over an empty tile");
		}

		skipped_is_dark = (skipped_piece < 20);
		if (is_dark + skipped_is_dark != 1) {
			throw std::runtime_error(
			    "Illegal move: Cannot skip over a tile of the same color");
		}
	}

	// Move is legal, proceed to update position, visibility and status
	Graph_lib::Point start_pos{tile_position(start_tile)};
	Graph_lib::Point end_pos{tile_position(end_tile)};
	if (is_dark) {
		dark_pieces.move(end_pos.x - start_pos.x,
		                 end_pos.y - start_pos.y,
		                 start_piece);
	} else {
		light_pieces.move(end_pos.x - start_pos.x,
		                  end_pos.y - start_pos.y,
		                  start_piece - 20);
	}

	tile_status[start_tile] = -1;

	if (num_tiles == 2) {
		tile_status[skipped_tile] = -1;
		if (skipped_is_dark) {
			dark_pieces.set_fill_color(Graph_lib::Color::invisible,
			                           skipped_piece);
		} else {
			light_pieces.set_fill_color(Graph_lib::Color::invisible,
			                            skipped_piece - 20);
		}
	}

	tile_status[end_tile] = start_piece;
}

//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------

void ch14_e09::Board::draw_lines() const
{
	frame.draw();
	light_tiles.draw();
	dark_tiles.draw();
	light_pieces.draw();
	dark_pieces.draw();
}
