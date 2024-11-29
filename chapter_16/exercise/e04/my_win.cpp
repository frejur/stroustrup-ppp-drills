#include "my_win.h"
#include <random>

namespace {
constexpr int window_top_margin{4};
constexpr int top_panel_horizontal_padding{4};
constexpr int top_panel_button_height{20};
constexpr int coordinate_box_width{40};
constexpr int select_button_width{64};
constexpr int random_button_width{64};
constexpr int shape_button_width{32};
constexpr int shape_radius{64};

const std::string& icons_file_path()
{
	static const std::string p{"img_e04/icons.png"};
	return p;
}

const Graph_lib::Color& default_color()
{
	static const Graph_lib::Color c{
	    Graph_lib::Color(fl_rgb_color(100, 100, 100))};
	return c;
}

inline int rand_int(int min, int max)
{
	static default_random_engine ran;
	return uniform_int_distribution<>{min, max}(ran);
}

} // namespace

const char My_window::max_num_shp = 16;

//------------------------------------------------------------------------------

void position_top_panel(int& w,
                        Graph_lib::Button& sel,
                        Graph_lib::Button& rnd,
                        Graph_lib::In_box& inx,
                        Graph_lib::In_box& iny)
{
	// Place Input fields and buttons at the top center
	// (Assumes an initial position of (0,window_top_margin))
	const int mid_x{static_cast<int>(std::round(w * 0.5))};
	const int est_lb_w = 8;
	const int total_box_w = est_lb_w + coordinate_box_width;
	const int top_panel_w{total_box_w * 2 + top_panel_horizontal_padding * 2
	                      + select_button_width + top_panel_horizontal_padding
	                      + random_button_width};
	const int half_w = static_cast<int>(std::round(top_panel_w * 0.5));
	int offs_x = (mid_x - half_w);
	inx.move(offs_x, 0);
	offs_x += total_box_w + top_panel_horizontal_padding + est_lb_w;
	iny.move(offs_x, 0);
	offs_x += total_box_w + top_panel_horizontal_padding;
	sel.move(offs_x, 0);
	offs_x += select_button_width + top_panel_horizontal_padding;
	rnd.move(offs_x, 0);
}

//------------------------------------------------------------------------------

My_window::My_window(Graph_lib::Point xy, int w, int h, const string& title)
    : Window(xy, w, h, title)
    , num_shp(0)
    , shp_r(shape_radius)
    , in_x({0, window_top_margin},
           coordinate_box_width,
           top_panel_button_height,
           "X:")
    , in_y({0, window_top_margin},
           coordinate_box_width,
           top_panel_button_height,
           "Y:")
    , btn_sel({0, window_top_margin},
              select_button_width,
              top_panel_button_height,
              "Select",
              cb_select)
    , btn_rnd({0, window_top_margin},
              select_button_width,
              top_panel_button_height,
              "Random",
              cb_random)
    , arrow({0, 0}, {0, 0})
    , menu({0, 0},
           shape_button_width,
           cb_create_o,
           cb_create_tri,
           cb_create_sq,
           cb_create_hex,
           icons_file_path())
{
	size_range(w, h, w, h); // Lock window size

	// Top panel
	attach(in_x);
	attach(in_y);
	attach(btn_sel);
	attach(btn_rnd);
	position_top_panel(w, btn_sel, btn_rnd, in_x, in_y);

	// Popup Menu
	attach(arrow);
	arrow.hide();
	menu.attach(*this);
	menu.set_color(default_color());
	menu.hide();
}

void My_window::clear_shapes()
{
	for (int i = 0; i < shp_v.size(); ++i) {
		detach(shp_v[i]);
	}
	shp_v = {}; // TODO: Not sure if this is safe, but I'm assuming the
	            // Vector_ref takes care of memory safety
}

//------------------------------------------------------------------------------

void My_window::select()
{
	int x = in_x.get_int();
	int y = in_y.get_int();
	if (valid_coords(x, y)) {
		put_on_top(arrow);
		menu.bring_to_front(*this);
		Graph_lib::Point menu_c{new_menu_xy({x, y})};
		arrow.show();
		arrow.new_start_and_end_points(menu_c, {x, y});
		menu.show();
		menu.move_to(menu_c.x, menu_c.y);
		new_shp_c = {x, y};
	} else {
		menu.hide();
		arrow.hide();
	}
}

void My_window::random()
{
	int rand_x = rand_int(shp_r + 1, x_max() - shp_r - 1);
	int rand_y = rand_int(window_top_margin + top_panel_button_height + shp_r
	                          + 1,
	                      y_max() - shp_r - 1);
	in_x.set_value(std::to_string(rand_x));
	in_y.set_value(std::to_string(rand_y));
	select();
}

//------------------------------------------------------------------------------

bool My_window::valid_coords(int x, int y) const
{
	return (x > shp_r && x < x_max() - shp_r
	        && y > window_top_margin + top_panel_button_height + shp_r
	        && y < y_max() - shp_r);
}

Graph_lib::Point My_window::new_menu_xy(Graph_lib::Point shape_xy) const
{
	int x = shape_xy.x;
	x += (shape_xy.x > x_max() / 2) ? -shp_r : shp_r;
	int y = shape_xy.y;
	y += (shape_xy.y > y_max() / 2) ? -shp_r : shp_r;
	return {x, y};
}
