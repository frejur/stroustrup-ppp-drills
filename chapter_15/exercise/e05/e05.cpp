#define _USE_MATH_DEFINES
#include "e05.h"
#include "../../lib/Simple_window.h"
#include <cmath>
#include <sstream>

// Chapter 15, exercise 5: The Leibniz series
// - "Animate" the Leibniz series, a.k.a. the Leinbiz formula for PI:
//     PI / 4 = 1 - 1/3 + 1/5 - 1/7 + 1/9 - 1 /11 ...

inline const Graph_lib::Color& default_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::black};
	return c;
};

inline const Graph_lib::Font& default_font()
{
	static const Graph_lib::Font f{Graph_lib::Font::helvetica};
	return f;
};

//------------------------------------------------------------------------------

double leibniz(const int n)
{
	double x{};
	for (int i = 0; i <= n; ++i) {
		x += ((i % 2 == 0) ? 1 : -1) / (2 * i + 1.0);
	}
	return x;
}

//------------------------------------------------------------------------------

void ch15_e05::e05()
{
	using Align = Text_alignment;
	fl_color(default_color().as_int());

	constexpr int win_w{640};
	constexpr int win_h{320};
	const std::string win_lb{"Serious series"};
	Simple_window win{{0, 0}, win_w, win_h, win_lb};

	constexpr int pad{static_cast<int>(win_w * .1 + .5)};
	Graph_canvas gc{{pad, pad},
	                win_w - pad * 2,
	                win_h - pad * 2,
	                {pad, win_h - pad},
	                16,
	                static_cast<int>(win_h * 0.3 + 0.5)};

	Graph_lib::Text clk_anim{{win_w - 200, 20}, "Click to animate - >"};
	win.attach(clk_anim);

	// Axes
	const std::string axis_lb_x{"Leibniz series"};
	const std::string axis_lb_y{""};
	const Graph_lib::Color axis_col{Graph_lib::Color::black};
	Graph_lib::Axis x_axis{Graph_lib::Axis::x,
	                       gc.x_axis_start(),
	                       gc.x_axis_length(),
	                       gc.number_of_x_notches(),
	                       axis_lb_x};
	Graph_lib::Axis y_axis{Graph_lib::Axis::y,
	                       gc.y_axis_start(),
	                       gc.y_axis_length(),
	                       gc.number_of_y_notches(),
	                       axis_lb_y};
	win.attach(x_axis);
	win.attach(y_axis);

	// Reference value function (PI / 4)
	const double range_start{(double) -gc.number_of_neg_x_notches()};
	const double range_end{(double) gc.number_of_pos_x_notches()};
	const int num_pts{gc.number_of_pos_x_notches() * 10};
	const double scale_x{(double) gc.x_notch_size()};
	const double scale_y{(double) gc.y_notch_size() * 2};

	Graph_lib::Color fn_qr_pi_col{Graph_lib::Color::dark_green};
	Graph_lib::Function fn_qr_pi{[](double x) { return M_PI / 4; },
	                             range_start,
	                             range_end,
	                             gc.graph_origin(),
	                             num_pts,
	                             scale_x,
	                             scale_y};
	fn_qr_pi.set_color(fn_qr_pi_col);
	win.attach(fn_qr_pi);

	// Label
	Label_style ref_style{default_font(), 10, fn_qr_pi_col, Align::Mid_left};
	Graph_lib::Text lb_qr_pi{fn_qr_pi.point(0), "PI / 4"};
	Graph_lib::Text lb_qr_pi_val{fn_qr_pi.point(0), std::to_string(M_PI / 4)};
	ref_style.apply_to(lb_qr_pi);
	ref_style.apply_to(lb_qr_pi_val);
	lb_qr_pi_val.move(0, ref_style.font_size);
	win.attach(lb_qr_pi);
	win.attach(lb_qr_pi_val);

	// Animate Leibniz series (Approximation of PI / 4)
	Label_style pt_style{default_font(), 10, default_color()};
	Graph_lib::Vector_ref<Graph_lib::Circle> leibniz_pts{};
	for (int n = 0; n <= gc.number_of_pos_x_notches(); ++n) {
		Graph_lib::Function fn_leibniz{leibniz,
		                               0,
		                               (double) n + 1,
		                               gc.graph_origin(),
		                               n + 1,
		                               scale_x,
		                               scale_y};

		// Add graphed point
		leibniz_pts.push_back(
		    new Graph_lib::Circle{fn_leibniz.point(n), gc.x_notch_size() / 6});
		Graph_lib::Circle& pt = leibniz_pts[leibniz_pts.size() - 1];
		pt.set_fill_color(default_color());
		win.attach(pt);

		// Label
		ostringstream oss;
		oss << "n = " << n;
		Graph_lib::Text lb_pt_top{pt.center(), oss.str()};
		oss.str({});
		oss << '(' << leibniz(n) << ')';
		Graph_lib::Text lb_pt_btm{pt.center(), oss.str()};
		pt_style.apply_to(lb_pt_top);
		pt_style.apply_to(lb_pt_btm);
		lb_pt_top.move(0, -pt_style.font_size);
		win.attach(lb_pt_top);
		win.attach(lb_pt_btm);

		win.put_on_top(fn_qr_pi);
		win.wait_for_button(); // Click button to animate ----------------------

		win.detach(lb_pt_top);
		win.detach(lb_pt_btm);
	}
}

int main()
try {
	ch15_e05::e05();
	return 0;
} catch (const std::exception& e) {
	std::cerr << "Error: " << e.what() << '\n';
	std::cin.get();
	return 1;
} catch (...) {
	std::cerr << "Unknown error" << '\n';
	std::cin.get();
	return 2;
}
