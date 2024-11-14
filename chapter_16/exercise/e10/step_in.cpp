#include "step_in.h"
#include <cmath>

namespace {
constexpr int padding{4};
void cb_incr(void*, void* st_in_box);
void cb_decr(void*, void* st_in_box);

constexpr int min_increment{1};
constexpr int max_increment{256};
int valid_incr(int incr, int min, int max);
} // namespace
//------------------------------------------------------------------------------

void Step_button::attach(Graph_lib::Window& win, Step_in_box& st_in_box)
{
	shp_btn::Shape_button::attach(win);
	pw->callback(reinterpret_cast<Fl_Callback*>(do_it),
	             &st_in_box); // pass the Step_in_box
	own = &win;
}
//------------------------------------------------------------------------------

Step_in_box::Step_in_box(Graph_lib::Point top_left,
                         int width,
                         int height,
                         const string& label,
                         Graph_lib::Callback callback_fn_after_edit)

    : Graph_lib::Widget({0, 0}, 1, 1, "", callback_fn_after_edit)
    , enabled(true)
    , is_min(false)
    , is_max(false)
    , btn_incr({top_left.x + width + height + padding * 2, top_left.y},
               height,
               height,
               "+",
               cb_incr)
    , btn_decr({top_left.x + width + padding, top_left.y},
               height,
               height,
               " -  ", // Lame attempt at centering
               cb_decr)
{
	btn_incr.set_font_size(height);
	btn_incr.set_font(Graph_lib::Font::courier_bold);
	btn_decr.set_font_size(height);
	btn_decr.set_font(Graph_lib::Font::courier_bold);
}
//------------------------------------------------------------------------------

void Step_in_box::post_increase_action()
{
	do_it(nullptr, own); // Call 'after-edit-callback' by default
}
void Step_in_box::post_decrease_action()
{
	do_it(nullptr, own); // Call 'after-edit-callback' by default
}
//------------------------------------------------------------------------------

void Step_in_box::move(int offs_x, int offs_y)
{
	btn_incr.move(offs_x, offs_y);
	btn_decr.move(offs_x, offs_y);
	move_in_box(offs_x, offs_y);
}
//------------------------------------------------------------------------------

void Step_in_box::increase()
{
	if (enabled && !value_is_max()) {
		if (next_incr_is_max()) {
			in_set_to_max();
			btn_incr.disable();
		} else {
			in_incr();
		}
	}
}

void Step_in_box::decrease()
{
	if (enabled && !value_is_min()) {
		if (next_decr_is_min()) {
			in_set_to_min();
			btn_decr.disable();
		} else {
			in_decr();
		}
	}
}

//------------------------------------------------------------------------------
void Step_in_box::enable()
{
	if (enabled) {
		return;
	}

	enable_in_box();
	enabled = true;
}

void Step_in_box::disable()
{
	if (!enabled) {
		return;
	}

	disable_in_box();
	enabled = false;
}

//------------------------------------------------------------------------------

Step_int_in_box::Step_int_in_box(Graph_lib::Point top_left,
                                 int width,
                                 int height,
                                 const string& label,
                                 int default_value,
                                 int min_value,
                                 int max_value,
                                 int increment,
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
void Step_int_in_box::attach(Graph_lib::Window& win)
{
	in.attach(win);
	btn_incr.attach(win, *this);
	btn_decr.attach(win, *this);
	pw = nullptr;
	own = &win;
}
//------------------------------------------------------------------------------

bool Step_int_in_box::value_is_min()
{
	return (in.get_valid_int() <= in.min_value());
}

bool Step_int_in_box::value_is_max()
{
	return (in.get_valid_int() >= in.max_value());
}

//------------------------------------------------------------------------------

void Step_int_in_box::in_incr()
{
	int cur_val{in.get_valid_int()};
	in.set_value(cur_val + increment());
}

void Step_int_in_box::in_decr()
{
	int cur_val{in.get_valid_int()};
	in.set_value(cur_val - increment());
}
bool Step_int_in_box::next_incr_is_max()
{
	int cur_val{in.get_valid_int()};
	int max_val = in.max_value();
	return (cur_val + increment() >= max_val);
}
bool Step_int_in_box::next_decr_is_min()
{
	int cur_val{in.get_valid_int()};
	int min_val = in.min_value();
	return (cur_val - increment() <= min_val);
}
void Step_int_in_box::in_set_to_min()
{
	int cur_val{in.get_valid_int()};
	int min_val = in.min_value();
	if (cur_val != min_val) {
		in.set_value(min_val);
	}
}
void Step_int_in_box::in_set_to_max()
{
	int cur_val{in.get_valid_int()};
	int max_val = in.max_value();
	if (cur_val != max_val) {
		in.set_value(max_val);
	}
}
void Step_int_in_box::move_in_box(int offs_x, int offs_y)
{
	in.move(offs_x, offs_y);
}
void Step_int_in_box::enable_in_box()
{
	in.enable();
}
void Step_int_in_box::disable_in_box()
{
	in.disable();
}

//------------------------------------------------------------------------------
namespace {
void cb_incr(void*, void* st_in_box)
{
	Step_int_in_box& b{*static_cast<Step_int_in_box*>(st_in_box)};
	b.increase();
	b.post_increase_action();
}
void cb_decr(void*, void* st_in_box)
{
	Step_int_in_box& b{*static_cast<Step_int_in_box*>(st_in_box)};
	b.decrease();
	b.post_decrease_action();
}

int valid_incr(int incr, int min, int max)
{
	int max_incr = (std::min)(max - min, max_increment);
	if (incr < min_increment || incr > max_incr) {
		throw std::runtime_error(
		    "Invalid incremental value, expected a value between "
		    + std::to_string(min_increment) + " and " + std::to_string(max_incr)
		    + " but got " + std::to_string(incr));
	}
	return incr;
}
} // namespace
