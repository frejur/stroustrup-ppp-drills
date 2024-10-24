#ifndef MY_WIN_H
#define MY_WIN_H

#include "../../lib/GUI.h"
#include "../../lib/Graph.h"
#include "../../lib/Window.h"
#include "../share/shape_button.h"

class My_window : public Graph_lib::Window
{
public:
	My_window(Graph_lib::Point xy, int w, int h, const string& title);

	// Actions (Defined in 'my_win_fn.cpp')
	void act_prnt(int row, int col);
	void act_lite(int row, int col);
	void act_dots(int row, int col);
	void act_grow(int row, int col);
	void act_caps(int row, int col);
	void act_tiny(int row, int col);
	void act_dark(int row, int col);
	void act_rght(int row, int col);
	void act_dash(int row, int col);
	void act_hide(int row, int col);
	void act_wide(int row, int col);
	void act_empt(int row, int col);
	void act_down(int row, int col);
	void act_long(int row, int col);
	void act_time(int row, int col);
	void act_bgrd(int row, int col);

private:
	static constexpr int rows{4};
	static constexpr int cols{4};

	std::function<void()> active_fn;

	static std::vector<std::string> lb_v;
	static std::vector<Graph_lib::Callback> cb_v;

	Graph_lib::Out_box out;
	Graph_lib::Vector_ref<shp_btn::Shape_button> btn_grid;

	shp_btn::Shape_button& btn_from_idx(int row, int col)
	{
		int idx{row * cols + col};
		if (idx < 0 || idx >= btn_grid.size()) {
			throw std::runtime_error("Invalid button index");
		}
		return btn_grid[row * cols + col];
	};
};

#endif // MY_WIN_H
