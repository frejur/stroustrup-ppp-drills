#ifndef MY_WIN_H
#define MY_WIN_H

#include "../../lib/Graph.h"
#include "../../lib/Window.h"
#include "../share/canvas/canvas.h"
#include "../share/fct.h"
#include "step_in_dbl.h"
#include "step_in_int.h"
#include "tgl.h"

class My_window : public Graph_lib::Window
{
public:
	My_window(Graph_lib::Point xy, int w, int h, const string& title);
	void update_logarithmic_base();

private:
	const int marg_top;
	const int marg_btm;
	const int marg_sde;
	const int fn_ctrl_h;
	const int pblock_w;
	const int plabel_w;
	const int content_w;
	const int toggle_w;

	chart::Canvas canvas;

	// Functions
	fct::Fct fn_log;

	// Toggles
	Toggle tgl_fn_log;
	Toggle tgl_fn_sin;
	Toggle tgl_fn_sup;
	Toggle tgl_fn_prl;

	// Function labels
	Graph_lib::Text txt_fn_log;
	Graph_lib::Text txt_fn_sin;
	Graph_lib::Text txt_fn_sup;
	Graph_lib::Text txt_fn_prl;

	// Function parameters
	Step_double_in_box inb_fn_log_b;

	Graph_lib::Rectangle fn_0_placeholder;
	Graph_lib::Rectangle fn_1_placeholder;
	Graph_lib::Rectangle fn_2_placeholder;
	Graph_lib::Rectangle fn_3_placeholder;

	void toggle_log();
	void toggle_sin();
	void toggle_sup();
	void toggle_prl();
};

#endif // MY_WIN_H
