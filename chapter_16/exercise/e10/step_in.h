#ifndef STEP_IN_H
#define STEP_IN_H

#include "../share/shape_button.h"
#include "valid_dbl_mm.h"
#include "valid_int_mm.h"

class Step_in_box; // Forward declare

//------------------------------------------------------------------------------
// A custom button attached to a Step_in_box rather than a window object
//------------------------------------------------------------------------------

class Step_button : public shp_btn::Shape_button
{
public:
	using shp_btn::Shape_button::Shape_button;
	void attach(Graph_lib::Window& win, Step_in_box& st_in_box);

private:
	virtual void attach(Graph_lib::Window&) override {}; // disable / hide
};

//------------------------------------------------------------------------------
// An input field that combines validation after edit with '+' and '-'
// buttons that can be used to tweak the value in increments. Disable either
// button when the minimum or maximum value has been reached.
//------------------------------------------------------------------------------

class Step_in_box : public Graph_lib::Widget
{
protected:
	Step_in_box(Graph_lib::Point top_left,
	            int width,
	            int height,
	            const std::string& label,
	            Graph_lib::Callback callback_fn_after_edit);

public:
	virtual void move(int offs_x, int offs_y) override;

	void increase();
	void decrease();
	virtual void post_increase_action();
	virtual void post_decrease_action();
	virtual bool value_is_min() = 0;
	virtual bool value_is_max() = 0;

	bool is_enabled() const { return enabled; }
	void enable();
	void disable();

protected:
	bool enabled;
	bool is_min;
	bool is_max;
	Step_button btn_incr;
	Step_button btn_decr;

	virtual void in_incr() = 0;
	virtual void in_decr() = 0;
	virtual bool next_incr_is_max() = 0;
	virtual bool next_decr_is_min() = 0;
	virtual void in_set_to_min() = 0;
	virtual void in_set_to_max() = 0;
	virtual void move_in_box(int offs_x, int offs_y) = 0;
	virtual void enable_in_box() = 0;
	virtual void disable_in_box() = 0;
};

#endif // STEP_IN_H
