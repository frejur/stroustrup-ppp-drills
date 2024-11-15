#ifndef MY_WIN_H
#define MY_WIN_H

#include "../../lib/Graph.h"
#include "../../lib/Window.h"
#include "step_in_dbl.h"
#include "step_in_int.h"
#include "tgl.h"

class My_window : public Graph_lib::Window
{
public:
	My_window(Graph_lib::Point xy, int w, int h, const string& title);
	void validate_test();
	void validate_test2();
	void toggle_test();

private:
	Step_int_in_box test;
	Step_double_in_box test2;
	Toggle tgl_test;
	Graph_lib::Out_box out;
	Graph_lib::Out_box out2;
	Graph_lib::Out_box out3;
};

#endif // MY_WIN_H
