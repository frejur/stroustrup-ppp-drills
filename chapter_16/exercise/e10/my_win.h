#ifndef MY_WIN_H
#define MY_WIN_H

#include "../../lib/Graph.h"
#include "../../lib/Window.h"

class My_window : public Graph_lib::Window
{
public:
	My_window(Graph_lib::Point xy, int w, int h, const string& title);
};

#endif // MY_WIN_H
