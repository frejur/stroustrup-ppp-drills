#include "my_win.h"
#include "plot_fn.h"

namespace {
constexpr float margin_side_factor{0.1}; // Multiplied by window width

// Values multiplied by window height
constexpr float margin_top_factor{0.1};
constexpr float margin_bottom_factor{0.05};
constexpr float function_controls_height_factor{0.04};

constexpr float parameter_block_width_factor{5.0}; // Multiplied by function
                                                   // control height
constexpr float parameter_label_width_factor{0.2}; // Multiplied by parameter
                                                   // block width
constexpr int number_of_functions{4};
constexpr int function_controls_inbetween_padding{10};
constexpr int label_padding{6};
constexpr int canvas_lower_padding{32};
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

const Graph_lib::Line_style& function_style()
{
	static const Graph_lib::Line_style s{Graph_lib::Line_style::solid, 2};
	return s;
}
const Graph_lib::Color& function_log_color()
{
	static const Graph_lib::Color c{
	    Graph_lib::Color(fl_rgb_color(80, 160, 230))};
	return c;
}
const Graph_lib::Color& function_sin_color()
{
	static const Graph_lib::Color c{Graph_lib::Color(fl_rgb_color(230, 90, 45))};
	return c;
}
const Graph_lib::Color& function_superellipse_color()
{
	static const Graph_lib::Color c{
	    Graph_lib::Color(fl_rgb_color(245, 200, 50))};
	return c;
}
const Graph_lib::Color& function_perlin_noise_color()
{
	static const Graph_lib::Color c{
	    Graph_lib::Color(fl_rgb_color(120, 235, 120))};
	return c;
}

constexpr float label_font_size_factor{0.6};
const Graph_lib::Font& label_font()
{
	static const Graph_lib::Font f{Graph_lib::Font::helvetica};
	return f;
}

} // namespace
//------------------------------------------------------------------------------

double Plot::fn_log_base = 2;

//------------------------------------------------------------------------------

My_window::My_window(Graph_lib::Point xy, int w, int h, const string& title)
    : Window(xy, w, h, title)
    , marg_top(y_max() * margin_top_factor)
    , marg_btm(y_max() * margin_bottom_factor)
    , marg_sde(x_max() * margin_side_factor)
    , fn_ctrl_h(y_max() * function_controls_height_factor)
    , pblock_w(fn_ctrl_h * parameter_block_width_factor)
    , plabel_w(pblock_w * parameter_label_width_factor)
    , content_w(x_max() - marg_sde * 2)
    , toggle_w(fn_ctrl_h * 1.6)
    , canvas({marg_sde, marg_top},
             content_w,
             calculate_canvas_height(y_max(), marg_top, marg_btm, fn_ctrl_h))
    , fn_log(Plot::fn_log, 0, 1, {0, 0}, 20, 1, 1)

    , tgl_fn_log({marg_sde, marg_top + canvas.height() + canvas_lower_padding},
                 toggle_w,
                 fn_ctrl_h,
                 function_log_color(),
                 [](void*, void* pw) {
	                 (*static_cast<My_window*>(pw)).toggle_log();
                 })
    , tgl_fn_sin({marg_sde,
                  tgl_fn_log.position().y + fn_ctrl_h
                      + function_controls_inbetween_padding},
                 toggle_w,
                 fn_ctrl_h,
                 function_sin_color(),
                 [](void*, void* pw) {
	                 (*static_cast<My_window*>(pw)).toggle_sin();
                 })
    , tgl_fn_sup({marg_sde,
                  tgl_fn_sin.position().y + fn_ctrl_h
                      + function_controls_inbetween_padding},
                 toggle_w,
                 fn_ctrl_h,
                 function_superellipse_color(),
                 [](void*, void* pw) {
	                 (*static_cast<My_window*>(pw)).toggle_sup();
                 })
    , tgl_fn_prl({marg_sde,
                  tgl_fn_sup.position().y + fn_ctrl_h
                      + function_controls_inbetween_padding},
                 toggle_w,
                 fn_ctrl_h,
                 function_perlin_noise_color(),
                 [](void*, void* pw) {
	                 (*static_cast<My_window*>(pw)).toggle_prl();
                 })
    , txt_fn_log({marg_sde + toggle_w + label_padding,
                  tgl_fn_log.position().y + fn_ctrl_h / 2},
                 "log(b, x + 1)")
    , txt_fn_sin({marg_sde + toggle_w + label_padding,
                  tgl_fn_sin.position().y + fn_ctrl_h / 2},
                 "sin(x * f) + 1")
    , txt_fn_sup({marg_sde + toggle_w + label_padding,
                  tgl_fn_sup.position().y + fn_ctrl_h / 2},
                 "0.5 * (1 + superellipse(x, n, m))")
    , txt_fn_prl({marg_sde + toggle_w + label_padding,
                  tgl_fn_prl.position().y + fn_ctrl_h / 2},
                 "perlin_noise(x, o, p)")
    , inb_fn_log_b({x_max() - marg_sde - pblock_w + plabel_w,
                    tgl_fn_log.position().y},
                   fn_ctrl_h * 1.6,
                   fn_ctrl_h,
                   "b:",
                   2,
                   2,
                   10,
                   0.5,
                   [](void*, void* pw) {
	                   (*static_cast<My_window*>(pw)).update_logarithmic_base();
                   })
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

	// Canvas
	attach(canvas);
	setup_canvas(canvas);

	// Functions
	fn_log.set_origin(canvas.position_from_value(0, 0));
	fn_log.set_x_scale(canvas.x_scale_factor());
	fn_log.set_y_scale(canvas.y_scale_factor());
	attach(fn_log);
	fn_log.set_color(function_log_color());
	fn_log.set_style(function_style());

	// Toggles
	attach(tgl_fn_log);
	tgl_fn_log.turn_on();
	attach(tgl_fn_sin);
	tgl_fn_sin.turn_on();
	attach(tgl_fn_sup);
	tgl_fn_sup.turn_on();
	attach(tgl_fn_prl);
	tgl_fn_prl.turn_on();

	// Function labels
	attach(txt_fn_log);
	attach(txt_fn_sin);
	attach(txt_fn_sup);
	attach(txt_fn_prl);
	txt_fn_log.set_font(label_font());
	txt_fn_sin.set_font(label_font());
	txt_fn_sup.set_font(label_font());
	txt_fn_prl.set_font(label_font());
	int new_sz{static_cast<int>(fn_ctrl_h * label_font_size_factor)};
	txt_fn_log.set_font_size(new_sz);
	txt_fn_sin.set_font_size(new_sz);
	txt_fn_sup.set_font_size(new_sz);
	txt_fn_prl.set_font_size(new_sz);

	// Adjust vertical placement of labels
	Graph_lib::Font old_f{fl_font()};
	int old_sz{fl_size()};
	fl_font(label_font().as_int(), new_sz);
	txt_fn_log.move(0, new_sz / 2 - fl_descent() / 2);
	txt_fn_sin.move(0, new_sz / 2 - fl_descent() / 2);
	txt_fn_sup.move(0, new_sz / 2 - fl_descent() / 2);
	txt_fn_prl.move(0, new_sz / 2 - fl_descent() / 2);
	fl_font(old_f.as_int(), old_sz);

	// Parameters
	attach(inb_fn_log_b);
}
//------------------------------------------------------------------------------

void My_window::update_logarithmic_base()
{
	double d = inb_fn_log_b.value();
	Plot::fn_log_base = d;
	fn_log.refresh();
}
//------------------------------------------------------------------------------

void My_window::toggle_log()
{
	tgl_fn_log.toggle();
	if (fn_log.is_visible()) {
		fn_log.hide();
	} else {
		fn_log.show();
	}
}

void My_window::toggle_sin()
{
	tgl_fn_sin.toggle();
}

void My_window::toggle_sup()
{
	tgl_fn_sup.toggle();
}

void My_window::toggle_prl()
{
	tgl_fn_prl.toggle();
}

//------------------------------------------------------------------------------

namespace {
const int calculate_canvas_height(int window_h,
                                  int top_margin,
                                  int btm_margin,
                                  int control_h)
{
	int pad_count = (number_of_functions > 0) ? (number_of_functions - 1) : 0;
	return window_h - top_margin - canvas_lower_padding
	       - number_of_functions * control_h
	       - pad_count * function_controls_inbetween_padding - btm_margin;
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
