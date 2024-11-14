#include "step_in_dbl.h"

namespace {
constexpr double min_increment{1.0};
constexpr double max_increment{256.0};
double valid_incr(double incr, double min, double max);
} // namespace

//------------------------------------------------------------------------------

Step_double_in_box::Step_double_in_box(Graph_lib::Point top_left,
                                       int width,
                                       int height,
                                       const string& label,
                                       double default_value,
                                       double min_value,
                                       double max_value,
                                       double increment,
                                       Graph_lib::Callback callback_fn_after_edit)
    : Step_in_box::Step_in_box(top_left,
                               width,
                               height,
                               label,
                               callback_fn_after_edit)
    , incr(valid_incr(increment, min_value, max_value))
    , in(top_left,
         width,
         height,
         label,
         default_value,
         min_value,
         max_value,
         callback_fn_after_edit)
{}
//------------------------------------------------------------------------------
void Step_double_in_box::attach(Graph_lib::Window& win)
{
	in.attach(win);
	btn_incr.attach(win, *this);
	btn_decr.attach(win, *this);
	pw = nullptr;
	own = &win;
}
//------------------------------------------------------------------------------

bool Step_double_in_box::value_is_min()
{
	return (in.get_valid_double() <= in.min_value());
}

bool Step_double_in_box::value_is_max()
{
	return (in.get_valid_double() >= in.max_value());
}

//------------------------------------------------------------------------------

void Step_double_in_box::in_incr()
{
	double cur_val{in.get_valid_double()};
	in.set_value(cur_val + increment());
}

void Step_double_in_box::in_decr()
{
	double cur_val{in.get_valid_double()};
	in.set_value(cur_val - increment());
}
bool Step_double_in_box::next_incr_is_max()
{
	double cur_val{in.get_valid_double()};
	double max_val = in.max_value();
	return (cur_val + increment() >= max_val);
}
bool Step_double_in_box::next_decr_is_min()
{
	double cur_val{in.get_valid_double()};
	double min_val = in.min_value();
	return (cur_val - increment() <= min_val);
}
void Step_double_in_box::in_set_to_min()
{
	double cur_val{in.get_valid_double()};
	double min_val = in.min_value();
	if (cur_val != min_val) {
		in.set_value(min_val);
	}
}
void Step_double_in_box::in_set_to_max()
{
	double cur_val{in.get_valid_double()};
	double max_val = in.max_value();
	if (cur_val != max_val) {
		in.set_value(max_val);
	}
}
void Step_double_in_box::move_in_box(int offs_x, int offs_y)
{
	in.move(offs_x, offs_y);
}
void Step_double_in_box::enable_in_box()
{
	in.enable();
}
void Step_double_in_box::disable_in_box()
{
	in.disable();
}

//------------------------------------------------------------------------------
namespace {
void cb_incr(void*, void* st_in_box)
{
	Step_double_in_box& b{*static_cast<Step_double_in_box*>(st_in_box)};
	b.increase();
	b.post_increase_action();
}
void cb_decr(void*, void* st_in_box)
{
	Step_double_in_box& b{*static_cast<Step_double_in_box*>(st_in_box)};
	b.decrease();
	b.post_decrease_action();
}

double valid_incr(double incr, double min, double max)
{
	double max_incr = (std::fmin)(max - min, max_increment);
	if (incr < min_increment || incr > max_incr) {
		throw std::runtime_error(
		    "Invalid incremental value, expected a value between "
		    + std::to_string(min_increment) + " and " + std::to_string(max_incr)
		    + " but got " + std::to_string(incr));
	}
	return incr;
}
} // namespace
