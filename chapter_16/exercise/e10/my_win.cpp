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

constexpr int number_of_function_points{100};
constexpr int function_stroke_thickness{2};

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
	static const Graph_lib::Line_style s{Graph_lib::Line_style::solid,
	                                     function_stroke_thickness};
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

double Plot::fn_log_base = 2.0;
double Plot::fn_sin_freq = 9.5;
double Plot::fn_sup_exp_n = 2.0;
double Plot::fn_sup_exp_m = 2.0;
std::vector<int> Plot::permutation_table = Plot::gen_seq(
    number_of_function_points);
std::vector<double> Plot::gradients = Plot::gen_gradients(
    number_of_function_points);
int Plot::fn_prl_octaves = 8;
double Plot::fn_prl_persistence = .5;

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
    , fn_log(Plot::fn_log, 0, 1, {0, 0}, number_of_function_points, 1, 1)
    , fn_sin(Plot::fn_sin, 0, 1, {0, 0}, number_of_function_points, 1, 1)
    , fn_sup_upr(Plot::fn_sup_upr, 0, 1, {0, 0}, number_of_function_points, 1, 1)
    , fn_sup_lwr(Plot::fn_sup_lwr, 0, 1, {0, 0}, number_of_function_points, 1, 1)
    , fn_prl(Plot::fn_prl, 0, 1, {0, 0}, number_of_function_points, 1, 1)
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
                 "sin(x * f) / 2 + 0.5")
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
                   Plot::fn_log_base,
                   2,
                   10,
                   0.5,
                   [](void*, void* pw) {
	                   (*static_cast<My_window*>(pw)).update_logarithmic_base();
                   })
    , inb_fn_sin_f({x_max() - marg_sde - pblock_w + plabel_w,
                    tgl_fn_sin.position().y},
                   fn_ctrl_h * 1.6,
                   fn_ctrl_h,
                   "f:",
                   Plot::fn_sin_freq,
                   5,
                   16,
                   1,
                   [](void*, void* pw) {
	                   (*static_cast<My_window*>(pw)).update_sine_frequency();
                   })
    , inb_fn_sup_exp_n({x_max() - marg_sde - pblock_w + plabel_w,
                        tgl_fn_sup.position().y},
                       fn_ctrl_h * 1.6,
                       fn_ctrl_h,
                       "n:",
                       Plot::fn_sup_exp_n,
                       0.25,
                       5,
                       1,
                       [](void*, void* pw) {
	                       (*static_cast<My_window*>(pw))
	                           .update_superellipse_exponent_n();
                       })
    , inb_fn_sup_exp_m({x_max() - marg_sde - pblock_w * 2 + plabel_w,
                        tgl_fn_sup.position().y},
                       fn_ctrl_h * 1.6,
                       fn_ctrl_h,
                       "m:",
                       Plot::fn_sup_exp_m,
                       0.25,
                       5,
                       1,
                       [](void*, void* pw) {
	                       (*static_cast<My_window*>(pw))
	                           .update_superellipse_exponent_m();
                       })
    , inb_fn_prl_o({x_max() - marg_sde - pblock_w + plabel_w,
                    tgl_fn_prl.position().y},
                   fn_ctrl_h * 1.6,
                   fn_ctrl_h,
                   "o:",
                   Plot::fn_prl_octaves,
                   1,
                   16,
                   1,
                   [](void*, void* pw) {
	                   (*static_cast<My_window*>(pw))
	                       .update_perlin_noise_number_of_octaves();
                   })
    , inb_fn_prl_p({x_max() - marg_sde - pblock_w * 2 + plabel_w,
                    tgl_fn_prl.position().y},
                   fn_ctrl_h * 1.6,
                   fn_ctrl_h,
                   "p:",
                   Plot::fn_prl_persistence,
                   0.1,
                   2,
                   0.1,
                   [](void*, void* pw) {
	                   (*static_cast<My_window*>(pw))
	                       .update_perlin_noise_persistence();
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

	// Logarithmic function
	fn_log.set_origin(canvas.position_from_value(0, 0));
	fn_log.set_x_scale(canvas.x_scale_factor());
	fn_log.set_y_scale(canvas.y_scale_factor());
	attach(fn_log);
	fn_log.set_color(function_log_color());
	fn_log.set_style(function_style());

	// Sine function
	fn_sin.set_origin(canvas.position_from_value(0, 0));
	fn_sin.set_x_scale(canvas.x_scale_factor());
	fn_sin.set_y_scale(canvas.y_scale_factor());
	attach(fn_sin);
	fn_sin.set_color(function_sin_color());
	fn_sin.set_style(function_style());

	// Superellipse function
	const int sup_offs = function_stroke_thickness; // Offset and shrink curves
	                                                // slightly to avoid canvas
	                                                // axes overlap
	fn_sup_upr.set_origin(
	    {canvas.origin().x + sup_offs, canvas.origin().y - sup_offs});
	fn_sup_upr.set_x_scale(canvas.x_scale_factor() - sup_offs / 2);
	fn_sup_upr.set_y_scale(canvas.y_scale_factor() - sup_offs);
	attach(fn_sup_upr);
	fn_sup_upr.set_color(function_superellipse_color());
	fn_sup_upr.set_style(function_style());

	fn_sup_lwr.set_origin(
	    {canvas.origin().x + sup_offs, canvas.origin().y - sup_offs});
	fn_sup_lwr.set_x_scale(canvas.x_scale_factor() - sup_offs / 2);
	fn_sup_lwr.set_y_scale(canvas.y_scale_factor() - sup_offs);
	attach(fn_sup_lwr);
	fn_sup_lwr.set_color(function_superellipse_color());
	fn_sup_lwr.set_style(function_style());

	// Perlin noise function
	Plot::shuffle_permutations(Plot::permutation_table, 3);
	fn_prl.set_origin(
	    {canvas.origin().x + sup_offs, canvas.origin().y - sup_offs});
	fn_prl.set_x_scale(canvas.x_scale_factor() - sup_offs / 2);
	fn_prl.set_y_scale(canvas.y_scale_factor() - sup_offs);
	attach(fn_prl);
	fn_prl.set_color(function_perlin_noise_color());
	fn_prl.set_style(function_style());

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
	attach(inb_fn_sin_f);
	attach(inb_fn_sup_exp_m);
	attach(inb_fn_sup_exp_n);
	attach(inb_fn_prl_o);
	attach(inb_fn_prl_p);
}
//------------------------------------------------------------------------------

void My_window::update_logarithmic_base()
{
	double b = inb_fn_log_b.value();
	Plot::fn_log_base = b;
	fn_log.refresh();
}

void My_window::update_sine_frequency()
{
	double f = inb_fn_sin_f.value();
	Plot::fn_sin_freq = f;
	fn_sin.refresh();
}

void My_window::update_superellipse_exponent_m()
{
	double m = inb_fn_sup_exp_m.value();
	Plot::fn_sup_exp_m = m;
	fn_sup_lwr.refresh();
	fn_sup_upr.refresh();
	redraw();
}

void My_window::update_superellipse_exponent_n()
{
	double n = inb_fn_sup_exp_n.value();
	Plot::fn_sup_exp_n = n;
	fn_sup_upr.refresh();
	fn_sup_lwr.refresh();
	redraw();
}

void My_window::update_perlin_noise_number_of_octaves()
{
	int o = inb_fn_prl_o.value();
	Plot::fn_prl_octaves = o;
	fn_prl.refresh();
	redraw();
}

void My_window::update_perlin_noise_persistence()
{
	double p = inb_fn_prl_p.value();
	Plot::fn_prl_persistence = p;
	fn_prl.refresh();
	redraw();
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
	if (fn_sin.is_visible()) {
		fn_sin.hide();
	} else {
		fn_sin.show();
	}
}

void My_window::toggle_sup()
{
	tgl_fn_sup.toggle();
	if (fn_sup_upr.is_visible()) {
		fn_sup_upr.hide();
		fn_sup_lwr.hide();
	} else {
		fn_sup_upr.show();
		fn_sup_lwr.show();
	}
}

void My_window::toggle_prl()
{
	tgl_fn_prl.toggle();
	if (fn_prl.is_visible()) {
		fn_prl.hide();
		fn_prl.hide();
	} else {
		fn_prl.show();
		fn_prl.show();
	}
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
