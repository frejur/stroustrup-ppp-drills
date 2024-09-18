#ifndef MAZE_H
#define MAZE_H
#include "../../lib/Graph.h"
#include "../share/geo/pac.h"
#include "../share/grp/grp_shp.h"
#include <string>

namespace ch14_e16 {

enum class Pill_dir { None = -1, Up, Right, Down, Left };

class Pill : public Graph_lib::Circle
{
public:
	Pill(Graph_lib::Point center, int radius, Pill_dir direction);
	bool has_been_eaten() const { return is_gone; }
	void consume();
	void regurgitate();
	Pill_dir direction() const { return dir; };

private:
	bool is_gone;
	Pill_dir dir;
};

//------------------------------------------------------------------------------

class Pill_group : public grp_shp::Shape_group
{
public:
	using Shape_group::move;
	using Shape_group::Shape_group;
	Graph_lib::Point center(int element_index) const;
	Pill_dir direction(int element_index) const;
	bool has_been_eaten(int element_index) const;
	void consume(int element_index);
	void regurgitate(int element_index);
};

//------------------------------------------------------------------------------

class Maze : public Graph_lib::Shape
{
public:
	Maze(Graph_lib::Point origin,
	     int tile_count_x,
	     int tile_count_y,
	     int tile_size);
	;
	Graph_lib::Point origin() const { return point(0); };
	int width() const { return count_x * tile_sz; };
	int height() const { return count_y * tile_sz; };
	int horizontal_tiles_count() const { return count_x; }
	int vertical_tiles_count() const { return count_y; }
	bool is_ready() const { return has_loaded; };
	void load_level(const std::vector<std::string>& level_chars);

	void draw_lines() const override;
	void move(int offset_x, int offset_y) override;

	void show() { is_hid = false; };
	void hide() { is_hid = true; };
	bool is_hidden() const { return is_hid; };

	void reset();

	// Pacman
	Graph_lib::Point pacman_position() const { return pac.center(); };
	float jaw_state() const { return pac.jaw_state(); };
	Graph_lib::Point direction_vector() const;
	;
	void move_pacman(int offs_x, int offs_y) { pac.move(offs_x, offs_y); };
	void set_jaw_state(float j) { pac.set_jaw_state(j); };
	void set_direction(pac::Pacman_dir d) { pac.set_direction(d); };

	// Pills
	int number_of_pills() const { return pills.number_of_elements(); };
	Graph_lib::Point pill_position(int idx) const { return pills.center(idx); };
	Pill_dir pill_direction(int idx) const { return pills.direction(idx); };
	bool pill_has_been_eaten(int i) const { return pills.has_been_eaten(i); };
	void consume_pill(int idx) { pills.consume(idx); };
	void regurgitate_pill(int idx) { pills.regurgitate(idx); };

private:
	const int count_x;
	const int count_y;
	const int tile_sz;
	const int pill_r;
	bool has_loaded;
	bool is_hid;
	Graph_lib::Point pac_start_pos;
	pac::Pacman_dir pac_start_dir;
	pac::Pacman pac;
	grp_shp::Shape_group walls;
	Pill_group pills;

	void add_wall(const int col, const int row);
	void add_pill(const int col, const int row, const char c);

	void reset_pac();

	Graph_lib::Point tile_pos(const int col, const int row) const;
	Graph_lib::Point pac_pos(const int col, const int row) const;
	pac::Pacman_dir dir_from_c(const char c) const;

	// Validate, will throw exceptions
	int valid_t_count(const int c) const;
	int valid_t_sz(const int sz, const int t_count_x, const int t_count_y) const;
	int valid_pill_idx(const int i) const;
};

//------------------------------------------------------------------------------

std::vector<std::string> read_maze_from_file(const std::string& filename);

} // namespace ch14_e16

#endif // MAZE_H
