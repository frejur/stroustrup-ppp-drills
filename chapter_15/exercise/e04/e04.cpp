#include "../../lib/Graph.h"
#include "../../lib/Window.h"
#include <cmath>

// Chapter 15, exercise 4: More graphs
// - Plot the following functions on a single canvas:
//     1. sin(x)
//     2. cos(x)
//     3. (sin(x) + cos(x))
//     4. (sin(x) * sin(x) + cos(x) * cos(c))
// - Provide axes and labels

inline const Graph_lib::Color& default_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::black};
	return c;
};

//------------------------------------------------------------------------------

int calc_lb_w(const std::string& txt, Graph_lib::Font f, int f_sz)
{
	int dummy; // not needed
	int w;
	int font_backup = fl_font();
	int size_backup = fl_size();
	fl_font(f.as_int(), f_sz);
	fl_text_extents(txt.c_str(), dummy, dummy, w, dummy);
	fl_font(font_backup, size_backup);
	return w;
}

//------------------------------------------------------------------------------

double sum_sin_cos(double x)
{
	return std::sin(x) + std::cos(x);
}

double pyth_id(double x)
{
	return std::sin(x) * std::sin(x) + std::cos(x) * std::cos(x);
}

//------------------------------------------------------------------------------

void e04()
{
	constexpr int win_w{640};
	constexpr int win_h{320};
	const std::string win_lb{"Brosine before hosine"};
	Graph_lib::Window win{{0, 0}, win_w, win_h, win_lb};

	constexpr int origin_x{static_cast<int>(win_w * .35 + .5)};
	constexpr int origin_y{static_cast<int>(win_h * .5 + .5)};
	constexpr int notch_sz{24};
	constexpr int x_axis_target_len{static_cast<int>(win_w * 0.65 + 0.5)};
	constexpr int x_axis_target_pos_len{
	    static_cast<int>(x_axis_target_len * 0.8 + 0.5)};
	constexpr int x_notch_count_neg{(x_axis_target_len - x_axis_target_pos_len)
	                                / notch_sz};
	constexpr int x_notch_count_pos{x_axis_target_pos_len / notch_sz};
	constexpr int x_axis_len{(x_notch_count_neg + x_notch_count_pos) * notch_sz};
	constexpr int y_axis_target_len{static_cast<int>(win_h * 0.8 + 0.5)};
	constexpr int y_axis_target_pos_len{
	    static_cast<int>(y_axis_target_len * 0.5 + 0.5)};
	constexpr int y_notch_count_neg{(y_axis_target_len - y_axis_target_pos_len)
	                                / notch_sz};
	constexpr int y_notch_count_pos{y_axis_target_pos_len / notch_sz};
	constexpr int y_axis_len{(y_notch_count_neg + y_notch_count_pos) * notch_sz};
	constexpr int x_axis_start_x{origin_x - notch_sz * x_notch_count_neg};
	constexpr int y_axis_start_y{origin_y + notch_sz * y_notch_count_pos};
	const std::string axis_lb{"1 notch == 0.5"};
	const Graph_lib::Color axis_col{Graph_lib::Color::black};

	Graph_lib::Axis x_axis{Graph_lib::Axis::x,
	                       {x_axis_start_x, origin_y},
	                       x_axis_len,
	                       x_notch_count_neg + x_notch_count_pos,
	                       axis_lb};
	Graph_lib::Axis y_axis{Graph_lib::Axis::y,
	                       {origin_x, y_axis_start_y},
	                       y_axis_len,
	                       y_notch_count_neg + y_notch_count_pos,
	                       axis_lb};
	x_axis.set_color(axis_col);
	y_axis.set_color(axis_col);
	win.attach(x_axis);
	win.attach(y_axis);

	const Graph_lib::Font label_font{Graph_lib::Font::helvetica};
	constexpr int label_font_sz{10};
	constexpr int label_h_offs{static_cast<int>(label_font_sz * 0.5 + .5)};
	constexpr int label_v_offs{static_cast<int>(label_font_sz * 1.5 + .5)};
	constexpr int range_start{-x_notch_count_neg / 2};
	constexpr int range_end{x_notch_count_pos / 2 + 1};
	constexpr int num_pts{400};
	constexpr int scale_x{notch_sz * 2};
	constexpr int scale_y{notch_sz * 2};

	Graph_lib::Color fn_sin_col{Graph_lib::Color::dark_green};
	Graph_lib::Function fn_sin{std::sin,
	                           range_start,
	                           range_end,
	                           {origin_x, origin_y},
	                           num_pts,
	                           scale_x,
	                           scale_y};
	fn_sin.set_color(fn_sin_col);
	win.attach(fn_sin);
	std::string lb_sin_txt{"f(x) = sin(x)"};
	Graph_lib::Text lb_sin{{fn_sin.point(0).x - label_h_offs
	                            - calc_lb_w(lb_sin_txt,
	                                        label_font,
	                                        label_font_sz),
	                        fn_sin.point(0).y},
	                       lb_sin_txt};
	lb_sin.set_font_size(label_font_sz);
	lb_sin.set_color(fn_sin_col);
	lb_sin.set_font(label_font);
	win.attach(lb_sin);

	Graph_lib::Color fn_cos_col{Graph_lib::Color::dark_red};
	Graph_lib::Function fn_cos{std::cos,
	                           range_start,
	                           range_end,
	                           {origin_x, origin_y},
	                           num_pts,
	                           scale_x,
	                           scale_y};
	fn_cos.set_color(fn_cos_col);
	win.attach(fn_cos);
	std::string lb_cos_txt{"g(x) = cos(x)"};
	Graph_lib::Text lb_cos{{fn_cos.point(0).x - label_h_offs
	                            - calc_lb_w(lb_cos_txt,
	                                        label_font,
	                                        label_font_sz),
	                        fn_cos.point(0).y},
	                       lb_cos_txt};
	lb_cos.set_font_size(label_font_sz);
	lb_cos.set_color(fn_cos_col);
	lb_cos.set_font(label_font);
	win.attach(lb_cos);

	Graph_lib::Color fn_sum_sin_cos_col{Graph_lib::Color::dark_blue};
	Graph_lib::Function fn_sum_sin_cos{sum_sin_cos,
	                                   range_start,
	                                   range_end,
	                                   {origin_x, origin_y},
	                                   num_pts,
	                                   scale_x,
	                                   scale_y};
	fn_sum_sin_cos.set_color(fn_sum_sin_cos_col);
	win.attach(fn_sum_sin_cos);
	std::string lb_sum_sin_cos_txt{"h(x) = cos(x)"};
	Graph_lib::Text lb_sum_sin_cos{{fn_sum_sin_cos.point(0).x - label_h_offs
	                                    - calc_lb_w(lb_sum_sin_cos_txt,
	                                                label_font,
	                                                label_font_sz),
	                                fn_sum_sin_cos.point(0).y},
	                               lb_sum_sin_cos_txt};
	lb_sum_sin_cos.set_font_size(label_font_sz);
	lb_sum_sin_cos.set_color(fn_sum_sin_cos_col);
	lb_sum_sin_cos.set_font(label_font);
	win.attach(lb_sum_sin_cos);

	Graph_lib::Color fn_sum_sq_sin_cos_col{Graph_lib::Color::yellow};
	Graph_lib::Function fn_sum_sq_sin_cos{pyth_id,
	                                      range_start,
	                                      range_end,
	                                      {origin_x, origin_y},
	                                      num_pts,
	                                      scale_x,
	                                      scale_y};
	fn_sum_sq_sin_cos.set_color(fn_sum_sq_sin_cos_col);
	fn_sum_sq_sin_cos.set_style(
	    Graph_lib::Line_style(Graph_lib::Line_style::solid, 2));
	win.attach(fn_sum_sq_sin_cos);
	std::string lb_sum_sq_sin_cos_txt{"p(x) = sin(x) sin(x) + cos(x) cos(x)"};
	Graph_lib::Text lb_sum_sq_sin_cos{{fn_sum_sq_sin_cos.point(0).x
	                                       - label_h_offs
	                                       - calc_lb_w(lb_sum_sq_sin_cos_txt,
	                                                   label_font,
	                                                   label_font_sz),
	                                   fn_sum_sq_sin_cos.point(0).y},
	                                  lb_sum_sq_sin_cos_txt};
	lb_sum_sq_sin_cos.set_font_size(label_font_sz);
	lb_sum_sq_sin_cos.set_color(fn_sum_sq_sin_cos_col);
	lb_sum_sq_sin_cos.set_font(label_font);
	win.attach(lb_sum_sq_sin_cos);

	Graph_lib::gui_main();
}

int main()
try {
	e04();
} catch (const std::exception& e) {
	std::cerr << "Error: " << e.what() << '\n';
	std::cin.get();
} catch (...) {
	std::cerr << "Unknown error" << '\n';
	std::cin.get();
}
