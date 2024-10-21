#ifndef LN_WIN_H
#define LN_WIN_H

#include "../../lib/GUI.h"
#include "../../lib/Graph.h"
#include "../../lib/Window.h"

struct Lines_window : Graph_lib::Window
{
	Lines_window(Graph_lib::Point xy, int w, int h, const string& title);
	Graph_lib::Open_polyline lines;

private:
	Graph_lib::Button next_button; // Adds Point(next_x, next_y) to 'lines'
	Graph_lib::Button quit_button;
	Graph_lib::In_box next_x;
	Graph_lib::In_box next_y;
	Graph_lib::Out_box xy_out;

	void next();
	void quit();
};

#endif // LN_WIN_H
