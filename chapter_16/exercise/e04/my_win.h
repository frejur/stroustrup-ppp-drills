#ifndef MY_WIN_H
#define MY_WIN_H

#include "../../lib/GUI.h"
#include "../../lib/Graph.h"
#include "../../lib/Window.h"
#include "../share/geo/arrow.h"
#include "button_grid.h"
#include <FL/Fl_Input.H>

//------------------------------------------------------------------------------

// Like an In_box, only you can manually set its value
class In_control : public Graph_lib::In_box
{
public:
	using Graph_lib::In_box::In_box;
	void set_value(const std::string& s)
	{
		Fl_Input& pi = *static_cast<Fl_Input*>(pw);
		pi.value(s.c_str());
	}
};

//------------------------------------------------------------------------------

enum class Shape_type { Square, Circle, Hexagon, Triangle };

class My_window : public Graph_lib::Window
{
public:
	My_window(Graph_lib::Point xy, int w, int h, const string& title);
	int number_of_shapes() const { return num_shp; }

	void create_shape(Shape_type type);
	void clear_shapes();

	// Draws menu near (valid) coordinates, draws an arrow pointing towards the
	// center of the shape to be drawn
	void select();

	// Sets the Input fields to a random pair of valid XY coordinates
	void random();

private:
	char num_shp;
	static const char max_num_shp;
	const int shp_r;

	Graph_lib::Point new_shp_c;

	In_control in_x;
	In_control in_y;
	Graph_lib::Button btn_sel;
	Graph_lib::Button btn_rnd;

	Graph_lib::Vector_ref<Graph_lib::Shape> shp_v;

	Arrow arrow;
	btn_grd::Button_grid menu;

	// Callbacks
	static void cb_select(void*, void* pw);
	static void cb_random(void*, void* pw);
	static void cb_create_hex(void*, void* pw);
	static void cb_create_o(void*, void* pw);
	static void cb_create_tri(void*, void* pw);
	static void cb_create_sq(void*, void* pw);

	Graph_lib::Point new_menu_xy(Graph_lib::Point shape_xy) const;
	bool valid_coords(int x, int y) const;
};

//------------------------------------------------------------------------------

inline void My_window::cb_select(void*, void* pw)
{
	(*static_cast<My_window*>(pw)).select();
}

inline void My_window::cb_random(void*, void* pw)
{
	(*static_cast<My_window*>(pw)).random();
}

inline void My_window::cb_create_hex(void*, void* pw)
{
	(*static_cast<My_window*>(pw)).create_shape(Shape_type::Hexagon);
}

inline void My_window::cb_create_o(void*, void* pw)
{
	(*static_cast<My_window*>(pw)).create_shape(Shape_type::Circle);
}

inline void My_window::cb_create_tri(void*, void* pw)
{
	(*static_cast<My_window*>(pw)).create_shape(Shape_type::Triangle);
}

inline void My_window::cb_create_sq(void*, void* pw)
{
	(*static_cast<My_window*>(pw)).create_shape(Shape_type::Square);
}

#endif // MY_WIN_H
