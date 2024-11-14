#ifndef MY_WIN_H
#define MY_WIN_H

#include "../../lib/Graph.h"
#include "../../lib/Window.h"
#include "step_in.h"
#include "valid_dbl_mm.h"

class My_window : public Graph_lib::Window
{
public:
	My_window(Graph_lib::Point xy, int w, int h, const string& title);
	void validate_test();
	void validate_test2();

private:
	Step_int_in_box test;
	Validated_double_min_max_in_box test2;
	Graph_lib::Out_box out;
	Graph_lib::Out_box out2;
};

#endif // MY_WIN_H
