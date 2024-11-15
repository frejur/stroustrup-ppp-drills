#include "my_win.h"

namespace {
constexpr float margin_top_factor{0.1};
constexpr float margin_bottom_factor{0.05};
constexpr float margin_side_factor{0.1};
constexpr float function_controls_height_factor{0.05};
constexpr int number_of_functions{4};
constexpr int function_controls_inbetween_padding{5};
constexpr int canvas_lower_padding{10};
const int calculate_canvas_height(int window_h,
                                  int top_margin,
                                  int btm_margin,
                                  int control_h);
void setup_canvas(chart::Canvas& canvas);
const Graph_lib::Color& grid_color()
{
	static const Graph_lib::Color c{
	    Graph_lib::Color(fl_rgb_color(155, 155, 155))};
	return c;
}
const Graph_lib::Line_style& grid_style()
{
	static const Graph_lib::Line_style s{Graph_lib::Line_style::dot, 1};
	return s;
}
} // namespace
//------------------------------------------------------------------------------

My_window::My_window(Graph_lib::Point xy, int w, int h, const string& title)
    : Window(xy, w, h, title)
    , marg_top(y_max() * margin_top_factor)
    , marg_btm(y_max() * margin_bottom_factor)
    , marg_sde(x_max() * margin_side_factor)
    , fn_ctrl_h(y_max() * function_controls_height_factor)
    , content_w(x_max() - marg_sde * 2)
    , canvas({marg_sde, marg_top},
             content_w,
             calculate_canvas_height(y_max(), marg_top, marg_btm, fn_ctrl_h))
    , fn_0_placeholder({marg_sde,
                        marg_top + canvas.height() + canvas_lower_padding},
                       content_w,
                       fn_ctrl_h)
    , fn_1_placeholder({marg_sde,
                        fn_0_placeholder.point(0).y + fn_ctrl_h
                            + function_controls_inbetween_padding},
                       content_w,
                       fn_ctrl_h)
    , fn_2_placeholder({marg_sde,
                        fn_1_placeholder.point(0).y + fn_ctrl_h
                            + function_controls_inbetween_padding},
                       content_w,
                       fn_ctrl_h)
    , fn_3_placeholder({marg_sde,
                        fn_2_placeholder.point(0).y + fn_ctrl_h
                            + function_controls_inbetween_padding},
                       content_w,
                       fn_ctrl_h)
{
	attach(fn_0_placeholder);
	attach(fn_1_placeholder);
	attach(fn_2_placeholder);
	attach(fn_3_placeholder);
	attach(canvas);
	setup_canvas(canvas);
}

//------------------------------------------------------------------------------

namespace {
const int calculate_canvas_height(int window_h,
                                  int top_margin,
                                  int btm_margin,
                                  int control_h)
{
	int pad_count = (number_of_functions > 0)
	                    ? (function_controls_inbetween_padding - 1)
	                    : 0;
	return window_h - top_margin - number_of_functions * control_h
	       - pad_count * function_controls_inbetween_padding
	       - canvas_lower_padding - btm_margin;
}
void setup_canvas(chart::Canvas& canvas)
{
	canvas.set_x_min_value(0);
	canvas.set_x_max_value(1);
	canvas.set_y_min_value(0);
	canvas.set_y_max_value(1);
	canvas.set_x_unit(0.5);
	canvas.set_y_unit(0.5);
	canvas.set_grid_color(grid_color());
	canvas.set_grid_style(grid_style());
	canvas.show_horizontal_grid_lines();
	canvas.show_vertical_grid_lines();
}
} // namespace
