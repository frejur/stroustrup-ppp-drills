#ifndef MY_WIN_H
#define MY_WIN_H

#include "../../lib/Graph.h"
#include "../../lib/Window.h"
#include "../share/image_button.h"

class My_window : public Graph_lib::Window
{
public:
	My_window(Graph_lib::Point xy, int w, int h, const string& title);
	void scurry();
	int number_of_clicks() const { return num_clk; }

private:
	static char num_clk;
	shp_btn::Image_button btn_img;
	static void cb(void*, void* pw)
	{
		if (++num_clk > 10) {
			(*static_cast<My_window*>(pw)).hide();
		}
		(*static_cast<My_window*>(pw)).scurry();
	}
};

#endif // MY_WIN_H
