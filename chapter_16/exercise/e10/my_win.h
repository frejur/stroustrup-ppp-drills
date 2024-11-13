#ifndef MY_WIN_H
#define MY_WIN_H

#include "../../lib/Graph.h"
#include "../../lib/Window.h"
#include "valid_int_mm.h"

class My_window : public Graph_lib::Window
{
public:
	My_window(Graph_lib::Point xy, int w, int h, const string& title);
	void validate_test();

private:
	Validated_int_min_max_in_box test;
	Graph_lib::In_box in;
};

#endif // MY_WIN_H
