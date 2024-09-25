#include "../../lib/Graph.h"
#include "../../lib/Window.h"
#include <cmath>

// Chapter 15, Drill A: Function graphing
//     1.  Create a 600x600 Window labeled "Function graphs".
//     2.  Add an X and a Y axis, Length: 400, Label: "1 == 20 px".
//     3.  Add notches every 20px.
//     4.  Have the axes cross at {300, 300}.
//     5.  Color them red.
//     6.  Plot 'double one(double x) { return 1; }'
//             - Range: [-10:11]
//             - Origin: {300, 300}
//             - Number of points: 400
//             - Scaling factor: 1.0 (None)
//     7.  Change the scaling factor to 20 on both axes.
//             (Use the above scaling factor for all graphs)
//     8.  Plot 'double slope(double x) { return x / 2; }'
//     9.  Create a Text object to label the 'slope' graph:
//             Text: "x / 2".
//             Position: Just above the first plotted point.
//     10. Plot 'double square(double x) { return x * x; }'.
//     11. Plot std::cin(), color it blue.
//     12. Plot 'sloping_cos()' by composing 'slope()' and 'std::cos()'
//------------------------------------------------------------------------------

inline const Graph_lib::Color& default_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::black};
	return c;
};

//------------------------------------------------------------------------------

double one(double x)
{
	return 1;
};

double slope(double x)
{
	return x * 0.5;
};

double square(double x)
{
	return x * x;
};

double sloping_cos(double x)
{
	return slope(x) + std::cos(x);
}

//------------------------------------------------------------------------------

void drill()
{
	constexpr int win_w{600};
	constexpr int win_h{600};
	const std::string win_lb{"Function graphs"};
	Graph_lib::Window win{{0, 0}, win_w, win_h, win_lb};

	constexpr int origin_x{static_cast<int>(win_w * .5 + .5)};
	constexpr int origin_y{static_cast<int>(win_h * .5 + .5)};
	constexpr int notch_sz{20};
	constexpr int axis_target_len{400};
	constexpr int axis_target_half_len{
	    static_cast<int>(axis_target_len * .5 + .5)};
	constexpr int notch_count_neg{axis_target_half_len / notch_sz};
	constexpr int notch_count_pos{notch_count_neg};
	constexpr int axis_len{(notch_count_neg + notch_count_pos) * notch_sz};
	constexpr int x_axis_start_x{origin_x - notch_sz * notch_count_neg};
	constexpr int y_axis_start_y{origin_y + notch_sz * notch_count_pos};
	const std::string axis_lb{"1 == " + std::to_string(notch_sz) + "px"};
	const Graph_lib::Color axis_col{Graph_lib::Color::red};

	// A. Function graphing drill:
	Graph_lib::Axis x_axis{Graph_lib::Axis::x,
	                       {x_axis_start_x, origin_y},
	                       axis_len,
	                       notch_count_neg + notch_count_pos,
	                       axis_lb};
	Graph_lib::Axis y_axis{Graph_lib::Axis::y,
	                       {origin_x, y_axis_start_y},
	                       axis_len,
	                       notch_count_neg + notch_count_pos,
	                       axis_lb};
	x_axis.set_color(axis_col);
	y_axis.set_color(axis_col);
	win.attach(x_axis);
	win.attach(y_axis);

	constexpr int label_font_sz{10};
	constexpr int label_v_offs{static_cast<int>(label_font_sz * 1.5 + .5)};
	constexpr int range_start{-10};
	constexpr int range_end{11};
	constexpr int num_pts{400};
	constexpr int scale_x{20};
	constexpr int scale_y{20};

	Graph_lib::Function fn_one{one,
	                           range_start,
	                           range_end,
	                           {origin_x, origin_y},
	                           num_pts,
	                           scale_x,
	                           scale_y};
	fn_one.set_color(default_color());
	win.attach(fn_one);

	Graph_lib::Function fn_slope{slope,
	                             range_start,
	                             range_end,
	                             {origin_x, origin_y},
	                             num_pts,
	                             scale_x,
	                             scale_y};
	fn_slope.set_color(default_color());
	win.attach(fn_slope);
	Graph_lib::Text lb_slope{{fn_slope.point(0).x,
	                          fn_slope.point(0).y - label_v_offs},
	                         "x / 2"};
	lb_slope.set_font_size(label_font_sz);
	lb_slope.set_color(default_color());
	win.attach(lb_slope);

	Graph_lib::Function fn_square{square,
	                              range_start,
	                              range_end,
	                              {origin_x, origin_y},
	                              num_pts,
	                              scale_x,
	                              scale_y};
	fn_square.set_color(default_color());
	win.attach(fn_square);

	const Graph_lib::Color fn_cos_col{Graph_lib::Color::blue};
	Graph_lib::Function fn_cos{std::cos,
	                           range_start,
	                           range_end,
	                           {origin_x, origin_y},
	                           num_pts,
	                           scale_x,
	                           scale_y};
	fn_cos.set_color(fn_cos_col);
	win.attach(fn_cos);

	Graph_lib::Function fn_sl_cos{sloping_cos,
	                              range_start,
	                              range_end,
	                              {origin_x, origin_y},
	                              num_pts,
	                              scale_x,
	                              scale_y};
	fn_sl_cos.set_color(default_color());
	win.attach(fn_sl_cos);

	Graph_lib::gui_main();
}

int main()
try {
	drill();
} catch (const std::exception& e) {
	std::cerr << "Error: " << e.what() << '\n';
	std::cin.get();
} catch (...) {
	std::cerr << "Unknown error" << '\n';
	std::cin.get();
}
