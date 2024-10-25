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

private:
	Graph_lib::Image bg;
};

#endif // MY_WIN_H
