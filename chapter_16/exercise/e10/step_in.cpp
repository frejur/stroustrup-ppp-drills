#include "step_in.h"
#include <cmath>

namespace {
constexpr int padding{4};
void cb_incr(void*, void* st_in_box);
void cb_decr(void*, void* st_in_box);
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

namespace {
void cb_incr(void*, void* st_in_box)
{
	Step_in_box& b{*static_cast<Step_in_box*>(st_in_box)};
	b.increase();
	b.post_increase_action();
}
void cb_decr(void*, void* st_in_box)
{
	Step_in_box& b{*static_cast<Step_in_box*>(st_in_box)};
	b.decrease();
	b.post_decrease_action();
}
} // namespace
