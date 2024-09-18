#include "maze.h"
#include <fstream>

namespace {
constexpr int minimum_tile_count{16};
constexpr int maximum_tile_count{128};
constexpr int minimum_width{minimum_tile_count * 4};
constexpr int minimum_height{minimum_width};
constexpr int maximum_width{1024};
constexpr int maximum_height{maximum_width};
inline const Graph_lib::Color& wall_color()
{
	static const Graph_lib::Color c{
	    static_cast<int>(fl_rgb_color(145, 145, 145))};
	return c;
}
inline const Graph_lib::Color& pill_color()
{
	static const Graph_lib::Color c{
	    static_cast<int>(fl_rgb_color(245, 245, 245))};
	return c;
}
inline const Graph_lib::Color& pacman_color()
{
	static const Graph_lib::Color c{
	    static_cast<int>(fl_rgb_color(255, 205, 50))};
	return c;
}
} // namespace

//------------------------------------------------------------------------------

ch14_e16::Pill::Pill(Graph_lib::Point center, int radius, Pill_dir direction)
    : Graph_lib::Circle::Circle(center, radius)
    , is_gone(false)
    , dir(direction)
{
	set_color(Graph_lib::Color::invisible);
	set_fill_color(pill_color());
}

void ch14_e16::Pill::consume()
{
	is_gone = true;
	set_fill_color(Graph_lib::Color::invisible);
}

void ch14_e16::Pill::regurgitate()
{
	is_gone = false;
	set_fill_color(pill_color());
}

//------------------------------------------------------------------------------

Graph_lib::Point ch14_e16::Pill_group::center(int element_index) const
{
	const Pill& p{dynamic_cast<const Pill&>(elem[valid_index(element_index)])};
	return p.center();
}

bool ch14_e16::Pill_group::has_been_eaten(int element_index) const
{
	const Pill& p{dynamic_cast<const Pill&>(elem[valid_index(element_index)])};
	return p.has_been_eaten();
}

void ch14_e16::Pill_group::consume(int element_index)
{
	Pill& p{dynamic_cast<Pill&>(elem[valid_index(element_index)])};
	p.consume();
}

void ch14_e16::Pill_group::regurgitate(int element_index)
{
	Pill& p{dynamic_cast<Pill&>(elem[valid_index(element_index)])};
	p.regurgitate();
}

ch14_e16::Pill_dir ch14_e16::Pill_group::direction(int element_index) const
{
	const Pill& p{dynamic_cast<const Pill&>(elem[valid_index(element_index)])};
	return p.direction();
}

//------------------------------------------------------------------------------

ch14_e16::Maze::Maze(Graph_lib::Point origin,
                     int tile_count_x,
                     int tile_count_y,
                     int tile_size)
    : count_x(valid_t_count(tile_count_x))
    , count_y(valid_t_count(tile_count_y))
    , tile_sz(valid_t_sz(tile_size, count_x, count_y))
    , pill_r(static_cast<int>(std::round(tile_sz * 0.125)))
    , has_loaded(false)
    , is_hid(false)
    , pac_start_pos(origin)
    , pac(origin, static_cast<int>(std::round(tile_size * 0.35)))
    , walls(origin)
    , pills(origin)
{
	add(origin);
	pac.set_color(Graph_lib::Color::invisible);
	pac.set_fill_color(pacman_color());
}

void ch14_e16::Maze::load_level(const std::vector<string>& level_chars)
{
	if (has_loaded) {
		throw std::runtime_error("Level has already been loaded");
	}
	if (level_chars.size() != count_y) {
		throw std::runtime_error("Expected " + std::to_string(count_y)
		                         + " rows but got "
		                         + std::to_string(level_chars.size()));
	}

	bool found_start{false};
	int row = 0;
	int col = 0;
	for (const std::string& s : level_chars) {
		if (s.size() != count_x) {
			throw std::runtime_error("Expected " + std::to_string(count_x)
			                         + " columns but got "
			                         + std::to_string(s.size()));
		}
		for (const char c : s) {
			switch (c) {
			case 'U':
			case 'R':
			case 'D':
			case 'L':
				if (found_start) {
					throw std::runtime_error(
					    "Found duplicate starting positions");
				}
				found_start = true;
				pac_start_pos = pac_pos(col, row);
				pac_start_dir = dir_from_c(c);
				break;
			case '#':
				add_wall(col, row);
				break;
			case '.':
			case 'u':
			case 'r':
			case 'd':
			case 'l':
				add_pill(col, row, c);
				break;
			default:
				throw std::runtime_error("Invalid character: '" + std::string{c}
				                         + "'");
			}
			++col;
		}
		col = 0;
		++row;
	}
	if (!found_start) {
		throw std::runtime_error("Could not find a start position");
	}
	reset_pac();
	has_loaded = true;
}

void ch14_e16::Maze::draw_lines() const
{
	if (is_hidden()) {
		return; // Abort if hidden ---------------------------------------------
	}

	if (!is_ready()) {
		fl_line(point(0).x,
		        point(0).y,
		        point(0).x + width(),
		        point(0).y + height());
		fl_line(point(0).x + width(),
		        point(0).y,
		        point(0).x,
		        point(0).y + height());
		return; // Abort if not ready ------------------------------------------
	}

	walls.draw();
	pills.draw();
	pac.draw();
}

void ch14_e16::Maze::move(int offset_x, int offset_y)
{
	set_point(0, {point(0).x + offset_x, point(0).y + offset_y});
	pac.move(offset_x, offset_y);
	for (int i = 0; i < walls.number_of_elements(); ++i) {
		walls.move(offset_x, offset_y, i);
	}
	for (int j = 0; j < pills.number_of_elements(); ++j) {
		pills.move(offset_x, offset_y, j);
	}
}

void ch14_e16::Maze::reset()
{
	for (int i = 0; i < pills.number_of_elements(); ++i) {
		pills.regurgitate(i);
	}
	reset_pac();
}

Graph_lib::Point ch14_e16::Maze::direction_vector() const
{
	switch (pac.direction()) {
	case pac::Pacman_dir::Up:
		return {0, -1};
	case pac::Pacman_dir::Right:
		return {1, 0};
	case pac::Pacman_dir::Down:
		return {0, 1};
	case pac::Pacman_dir::Left:
	default:
		return {-1, 0};
	}
}

void ch14_e16::Maze::add_wall(const int col, const int row)
{
	walls.add(new Graph_lib::Rectangle{tile_pos(col, row), tile_sz, tile_sz});
	walls.set_color(Graph_lib::Color::invisible, walls.number_of_elements() - 1);
	walls.set_fill_color(wall_color(), walls.number_of_elements() - 1);
}

void ch14_e16::Maze::add_pill(const int col, const int row, const char c)
{
	Pill_dir d;
	switch (c) {
	case '.':
		d = Pill_dir::None;
		break;
	case 'u':
		d = Pill_dir::Up;
		break;
	case 'r':
		d = Pill_dir::Right;
		break;
	case 'd':
		d = Pill_dir::Down;
		break;
	case 'l':
		d = Pill_dir::Left;
		break;
	default:
		throw std::runtime_error("Invalid pill char: " + std::to_string(c));
	}
	pills.add(new Pill{pac_pos(col, row), pill_r, d});
}

void ch14_e16::Maze::reset_pac()
{
	pac.move(pac_start_pos.x - pac.center().x, pac_start_pos.y - pac.center().y);
	pac.set_direction(pac_start_dir);
	pac.set_jaw_state(1);
}

Graph_lib::Point ch14_e16::Maze::tile_pos(const int col, const int row) const
{
	return {origin().x + col * tile_sz, origin().y + row * tile_sz};
}

Graph_lib::Point ch14_e16::Maze::pac_pos(const int col, const int row) const
{
	int half_t = static_cast<int>(std::round(tile_sz * 0.5));
	return {origin().x + half_t + col * tile_sz,
	        origin().y + half_t + row * tile_sz};
}

//------------------------------------------------------------------------------

pac::Pacman_dir ch14_e16::Maze::dir_from_c(const char c) const
{
	pac::Pacman_dir d;
	switch (c) {
	case 'U':
		d = pac::Pacman_dir::Up;
		break;
	case 'R':
		d = pac::Pacman_dir::Right;
		break;
	case 'D':
		d = pac::Pacman_dir::Down;
		break;
	case 'L':
		d = pac::Pacman_dir::Left;
		break;
	default:
		throw std::runtime_error("Invalid direction");
	}
	return d;
}

//------------------------------------------------------------------------------

int ch14_e16::Maze::valid_t_count(const int c) const
{
	if (minimum_tile_count > c || c > maximum_tile_count) {
		throw std::runtime_error("Invalid tile count, expected a value between "
		                         + std::to_string(minimum_tile_count) + " and "
		                         + std::to_string(maximum_tile_count));
	}
	return c;
}

int ch14_e16::Maze::valid_t_sz(const int sz,
                               const int t_count_x,
                               const int t_count_y) const
{
	int w = sz * t_count_x;
	if (w < minimum_width) {
		throw std::runtime_error("Invalid tile size, width would be below "
		                         + std::to_string(minimum_width));
	}
	if (w > maximum_width) {
		throw std::runtime_error("Invalid tile size, width would exceed "
		                         + std::to_string(maximum_width));
	}
	int h = sz * t_count_x;
	if (h < minimum_height) {
		throw std::runtime_error("Invalid tile size, height would be below "
		                         + std::to_string(minimum_height));
	}
	if (h > maximum_height) {
		throw std::runtime_error("Invalid tile size, height would exceed "
		                         + std::to_string(maximum_height));
	}
	return sz;
}

int ch14_e16::Maze::valid_pill_idx(const int i) const
{
	if (i >= pills.number_of_elements()) {
		throw std::runtime_error("Invalid pill index");
	}
	return i;
}

//------------------------------------------------------------------------------

std::vector<std::string> ch14_e16::read_maze_from_file(
    const std::string& filename)
{
	std::ifstream ifs{filename};

	if (!ifs) {
		throw std::runtime_error("Could not open file: " + filename);
	}

	std::vector<std::string> txt;
	std::string s;
	int count = 0;

	while (getline(ifs, s)) {
		txt.push_back(s);
		count += s.size();
		if (count > maximum_tile_count * maximum_tile_count) {
			throw std::runtime_error("Too many characters in file");
		}
	}
	return txt;
}
