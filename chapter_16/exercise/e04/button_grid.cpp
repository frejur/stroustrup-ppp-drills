#include "button_grid.h"

btn_grd::Button_grid::Button_grid(Graph_lib::Point top_left,
                                  int button_size,
                                  Graph_lib::Callback cb_top_left,
                                  Graph_lib::Callback cb_top_right,
                                  Graph_lib::Callback cb_btm_left,
                                  Graph_lib::Callback cb_btm_right,
                                  const string& image_path)
    : is_hidden(false)
{
	btn.push_back(new shp_btn::Image_button{top_left,
	                                        button_size,
	                                        button_size,
	                                        "",
	                                        cb_top_left,
	                                        image_path});
	btn.push_back(
	    new shp_btn::Image_button{{top_left.x + button_size, top_left.y},
	                              button_size,
	                              button_size,
	                              "",
	                              cb_top_right,
	                              image_path});
	btn.push_back(
	    new shp_btn::Image_button{{top_left.x, top_left.y + button_size},
	                              button_size,
	                              button_size,
	                              "",
	                              cb_btm_left,
	                              image_path});
	btn.push_back(new shp_btn::Image_button{{top_left.x + button_size,
	                                         top_left.y + button_size},
	                                        button_size,
	                                        button_size,
	                                        "",
	                                        cb_btm_right,
	                                        image_path});
	offset_image(button_size, 0, Button_grid_ID::Top_right);
	offset_image(0, button_size, Button_grid_ID::Bottom_left);
	offset_image(button_size, button_size, Button_grid_ID::Bottom_right);
}

//------------------------------------------------------------------------------

void btn_grd::Button_grid::move_to(int new_x, int new_y)
{
	int offs_x = new_x - btn[1].loc.x;
	int offs_y = new_y - btn[2].loc.y;
	for (int i = 0; i < btn.size(); ++i) {
		btn[i].move(offs_x, offs_y);
	}
}

//------------------------------------------------------------------------------

void btn_grd::Button_grid::hide()
{
	for (int i = 0; i < btn.size(); ++i) {
		btn[i].hide();
	}
	is_hidden = true;
}

void btn_grd::Button_grid::show()
{
	for (int i = 0; i < btn.size(); ++i) {
		btn[i].show();
	}
	is_hidden = false;
}

//------------------------------------------------------------------------------

void btn_grd::Button_grid::attach(Graph_lib::Window& win)
{
	for (int i = 0; i < btn.size(); ++i) {
		win.attach(btn[i]);
	}
}

void btn_grd::Button_grid::bring_to_front(Graph_lib::Window& win)
{
	for (int i = 0; i < btn.size(); ++i) {
		btn[i].put_on_top();
	}
}
//------------------------------------------------------------------------------

void btn_grd::Button_grid::set_color(Graph_lib::Color col)
{
	for (int i = 0; i < btn.size(); ++i) {
		btn[i].set_color(col);
	}
}

void btn_grd::Button_grid::offset_image(int offs_x,
                                        int offs_y,
                                        Button_grid_ID id)
{
	int sz = (std::max)(std::abs(offs_x), std::abs(offs_y));
	btn[static_cast<int>(id)].set_mask(offs_x, offs_y, sz, sz);
}
