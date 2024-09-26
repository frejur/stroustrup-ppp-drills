#include "e02.h"
#include "../../lib/GUI.h"
#include "../../lib/Graph.h"
#include "../../lib/Window.h"
#include "fct.h"
#include <cmath>
#include <exception>
#include <iostream>

// Chapter 15, exercise 2: Define a new Graph_lib::Function
// - Copy & paste the code for Graph_lib::Function, call it 'Fct;.
// - Have this version store the parameters passed to its constructor(s)
// - Add setter functions.

inline const std::function<double(double)>& functions(int i)
{
	static const std::vector<std::function<double(double)>>
	    f{[](double x) { return 0.5 * x; },
	      [](double x) { return x * x; },
	      [](double x) { return cos(x); },
	      [](double x) { return cos(x) + 0.5 * x; }};
	return f[i % f.size()];
};

void stuff(fct::Fct& f)
{
	int f_idx = ch15_e02::random_int(0, 255);
	f.set_function(functions(f_idx));

	double r_start = ch15_e02::random_int(0, 20) * -1;
	double r_end = r_start * -1 + ch15_e02::random_int(5, 20);
	f.set_range(r_start, r_end);

	double scale = ch15_e02::random_double(15, 50);
	f.set_x_scale(scale);
	f.set_y_scale(scale);

	int count = ch15_e02::random_int(1, 50) * 8;
	f.set_count(count);
}

void ch15_e02::e02()
{
	constexpr int win_w{ 640 };
	constexpr int win_h{ 480 };
	Graph_lib::Point c{static_cast<int>(win_w * 0.5),
	                   static_cast<int>(win_h * 0.5)};
	Btn_win win{{10, 10}, win_w, win_h, "Fun fcts"};
	fl_color(0);

	fct::Fct fn_test{cos, -10, 10, c};
	win.attach(fn_test);

	constexpr int btn_w{128};
	constexpr int btn_h{32};
	Graph_lib::Button btn{{c.x - btn_w / 2, win_h - btn_h * 2},
	                      128,
	                      32,
	                      "I'm feeling lucky!",
	                      cb};
	win.attach(btn);

	repeat_on_click(win, stuff, fn_test);
}

int main() {
	try {
		ch15_e02::e02();
		return 0;
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	} catch (...) {
		std::cerr << "Unknown error\n";
		return 2;
	}
	return 0;
}
