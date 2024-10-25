#ifndef BUTTON_GRID_H
#define BUTTON_GRID_H
#include "../../lib/GUI.h"
#include "../../lib/Graph.h"
#include "../share/image_button.h"

namespace btn_grd {

enum class Button_grid_ID {
	Top_left = 0,
	Top_right,
	Bottom_left,
	Bottom_right
};

class Button_grid
{
public:
	Button_grid(Graph_lib::Point top_left,
	            int button_size,
	            Graph_lib::Callback cb_top_left,
	            Graph_lib::Callback cb_top_right,
	            Graph_lib::Callback cb_btm_left,
	            Graph_lib::Callback cb_btm_right,
	            const std::string& image_path);
	Graph_lib::Point center_position() const;
	void move_to(int new_x, int new_y);
	void hide();
	void show();
	void attach(Graph_lib::Window& win);
	void bring_to_front(Graph_lib::Window& win);
	void set_color(Graph_lib::Color col);
	void offset_image(int offs_x, int offs_y, Button_grid_ID);
	bool is_visible() const { return !is_hidden; };

private:
	bool is_hidden;
	Graph_lib::Vector_ref<shp_btn::Image_button> btn;
};
} // namespace btn_grd

#endif // BUTTON_GRID_H
