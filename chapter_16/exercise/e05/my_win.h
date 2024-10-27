#ifndef MY_WIN_H
#define MY_WIN_H

#include "../../lib/GUI.h"
#include "../../lib/Graph.h"
#include "../../lib/Window.h"
#include "../share/outlined_text.h"
#include "../share/shape_button.h"

//------------------------------------------------------------------------------
// Used to store info about the different Ouija board 'Ghosts'
struct Ghost_writer
{
	const std::string name;
	const std::string aka;
	const std::string file_path;
};

// An In_box that triggers its callback function when editted
class In_box_control : public Graph_lib::Widget
{
public:
	In_box_control(Graph_lib::Point xy,
	               int w,
	               int h,
	               const string& s,
	               Graph_lib::Callback callback_fn)
	    : Graph_lib::Widget(xy, w, h, s, callback_fn)
	{}

	int get_int();
	string get_string();
	void clear();

	void attach(Graph_lib::Window& win);
};

// Single character shape
// - Black background
// - Can be marked as mapped or unmapped
// - Stores a mapped coordinate pair as a Point
class Map_char : public Graph_lib::Text
{
public:
	Map_char(Graph_lib::Point xy, char c)
	    : Graph_lib::Text::Text(xy, std::string{c})
	    , is_map(false)   // unmapped by default
	    , is_hidden(true) // hidden by default
	    , map_xy{0, 0}
	{
		set_font(Graph_lib::Font::courier_bold);
		set_color(Graph_lib::Color::white);
		set_font_size(11);
	}

	virtual void draw_lines() const
	{
		if (is_hidden) {
			return;
		}
		// Draws black background
		Graph_lib::Color ocol = fl_color();
		fl_color(Graph_lib::Color::black);
		fl_rectf(point(0).x - 2,
		         point(0).y - fsz - 1 + fl_descent(),
		         fsz + 1,
		         fsz + 1);
		fl_color(ocol.as_int());
		Graph_lib::Text::draw_lines();
		if (is_map) {
			// Draw 'X'
			fl_line(point(0).x + 1,
			        point(0).y - fsz + 2,
			        point(0).x + fsz - 1,
			        point(0).y);
			fl_line(point(0).x + fsz - 1,
			        point(0).y - fsz + 2,
			        point(0).x + 1,
			        point(0).y);
		}
	}

	void mark_as_mapped() { is_map = true; };
	void mark_as_unmapped() { is_map = false; };
	bool is_mapped() const { return is_map; };

	void show() { is_hidden = false; };
	void hide() { is_hidden = true; };

	void set_mapped_position(Graph_lib::Point xy) { map_xy = xy; };

	Graph_lib::Point mapped_position() const { return map_xy; };

private:
	bool is_map;
	bool is_hidden;
	Graph_lib::Point map_xy;
	static const int fsz = 11;
};

// Like Shape_button but with some default formatting
class My_button : public shp_btn::Shape_button
{
public:
	My_button(Graph_lib::Point top_left,
	          const string& label,
	          Graph_lib::Callback callback_fn,
	          Graph_lib::Color bg_color = Graph_lib::Color::black);
	static constexpr int font_size{10};
	static constexpr int width{36};
	static constexpr int height{16};
};

//------------------------------------------------------------------------------

class My_window : public Graph_lib::Window
{
private:
	enum class Grid_element_action { Hide, Show };
	enum class Char_action { Hide, Show, Mark_mapped, Mark_unmapped };
	enum class Window_state { None, Normal, Ouija, Remapping };

public:
	My_window(Graph_lib::Point xy, int w, int h, const string& title);

	// Callback actions
	void get_and_remap_char();
	void show_speak_to_menu();
	void speak_to_poe();
	void speak_to_frank();
	void speak_to_doc();
	void move_planchette();
	void abort_seance();
	void show_remapping_screen();
	void abort_remapping();
	void clear_remappings();
	void save_remappings();

	static bool is_valid_ch(char c)
	{
		return ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
	};

private:
	const static int left_m;
	const static int right_m;
	const static int top_m;
	const static int btm_m;
	const static int btn_pad;
	const static int unit_sz;
	const static int info_fsz;
	const static int status_fsz;
	const static int status_l_pad;
	const static int speak_r_pad;
	const static int speak_top_pad;
	const static int map_btn_r_pad;
	const static int map_btn_btm_pad;

	bool should_reload;
	Window_state st;
	const Graph_lib::Point gdbye_xy;

	Outlined_text txt_info;
	Outlined_text txt_status;
	Graph_lib::Image bg;
	My_button speak_btn;
	Graph_lib::Menu speak_menu;
	My_button next_btn;
	My_button quit_btn;
	Graph_lib::Vector_ref<In_box_control> map_grid_inp;
	Graph_lib::Vector_ref<Graph_lib::Rectangle> map_grid_rct;
	Graph_lib::Vector_ref<Map_char> map_chars;
	My_button map_btn;
	Graph_lib::Menu map_menu;
	Graph_lib::Circle planch; // Planchette / Cursor

	// Stream used for reading in characters when 'Next' is pressed
	std::istringstream ch_stream;
	void read_file_into_stream(const std::string& file_path);

	// Callbacks
	static void cb_speak(void*, void* pw);
	static void cb_next(void*, void* pw);
	static void cb_quit(void*, void* pw);
	static void cb_map(void*, void* pw);
	static void cb_map_abort(void*, void* pw);
	static void cb_map_clear(void*, void* pw);
	static void cb_map_save(void*, void* pw);

	// State
	void prep_for_normal();
	void prep_for_ouija(const Ghost_writer& w);
	void prep_for_remap();

	// Create, place and attach widgets
	void create_speak_buttons();
	void create_mapping_screen();

	// Text
	void upd_txt_info(const std::string& new_text);
	void upd_txt_status(const std::string& new_text);

	// Modify grid
	void mod_all_map_grid_elem(Grid_element_action a);
	void mod_map_grid_elem(int idx,
	                       Grid_element_action a,
	                       bool skip_check = false);

	// Modify chars
	int num_unmap() const;
	void map_ch(char c, Graph_lib::Point new_xy);
	void mod_all_map_chars(Char_action a);

	// Save / load mappings
	void save_map(const std::string& file_path);
	void load_map(const std::string& file_path);

	int valid_map_char_idx(int idx);
	int valid_map_elem_idx(int idx);

	static constexpr int map_num_chars{'Z' - 'A' + 1 + 10};
	int valid_map_num_chars() const;
	int valid_map_num_grid_elem() const;
};

#endif // MY_WIN_H
