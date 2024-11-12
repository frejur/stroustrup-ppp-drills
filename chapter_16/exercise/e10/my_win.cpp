#include "my_win.h"
#include "cb_id.h"
#include <chrono>
#include <random>

namespace {

constexpr int pad_calc{32};

struct RGB
{
	int r;
	int g;
	int b;
};

struct Calc_colors
{
	Calc_colors(RGB f, RGB a, RGB n, RGB o)
	    : frame(fl_rgb_color(f.r, f.g, f.b))
	    , actions(fl_rgb_color(a.r, a.g, a.b))
	    , numbers(fl_rgb_color(n.r, n.g, n.b))
	    , operators(fl_rgb_color(o.r, o.g, o.b))
	{}
	Graph_lib::Color frame;
	Graph_lib::Color actions;
	Graph_lib::Color numbers;
	Graph_lib::Color operators;
};

const std::vector<Calc_colors>& random_colors()
{
	static const std::vector<Calc_colors> c_v{
	    {{105, 70, 175}, {80, 50, 130}, {70, 55, 105}, {135, 185, 60}},
	    {{70, 170, 105}, {50, 125, 80}, {55, 105, 70}, {160, 85, 155}},
	    {{180, 50, 70}, {130, 35, 50}, {105, 40, 50}, {60, 165, 135}},
	    {{185, 190, 40}, {130, 135, 30}, {105, 110, 35}, {50, 100, 175}},
	    {{115, 100, 105}, {80, 70, 75}, {70, 60, 70}, {155, 65, 115}},
	};
	return c_v;
}

inline int rand_int(int min, int max)
{
	static default_random_engine ran{static_cast<unsigned>(
	    std::chrono::system_clock::now().time_since_epoch().count())};
	return uniform_int_distribution<>{min, max}(ran);
}

void change_calc_style(My_calculator& c)
{
	int r_i{rand_int(0, random_colors().size() - 1)};
	c.set_frame_color(random_colors()[r_i].frame);
	c.set_color_of_action_buttons(random_colors()[r_i].actions);
	c.set_color_of_numerical_buttons(random_colors()[r_i].numbers);
	c.set_color_of_operator_buttons(random_colors()[r_i].operators);
}

} // namespace

My_window::My_window(Graph_lib::Point xy, int w, int h, const string& title)
    : Window(xy, w, h, title)
    , calc_l(*this, {0, 0}, {})
    , calc_r(*this,
             {0, 0},
             {{[](void*, void* pw) {
	               My_calculator& c = (*static_cast<My_calculator*>(pw));
	               c.press_operator(My_calculator::Operator_type::Equals);
	               if (c.current_mode() == My_calculator::Mode::Calculator) {
		               change_calc_style(c);
	               }
               },
               My_calculator::Button_ID::Equals}})
{
	size_range(w, h, w, h); // Lock window size
	const int combined_w = calc_l.width() + pad_calc + calc_r.width();
	calc_l.move(w / 2 - combined_w / 2, h / 2 - calc_l.height() / 2);
	calc_r.move(calc_l.position().x + calc_l.width() + pad_calc,
	            calc_l.position().y);
	change_calc_style(calc_r);
	calc_r.press_edit();
}
