#ifndef STEP_IN_DBL_H
#define STEP_IN_DBL_H

#include "step_in.h"

class Step_double_in_box : public Step_in_box
{
public:
	Step_double_in_box(Graph_lib::Point top_left,
	                   int width,
	                   int height,
	                   const std::string& label,
	                   double default_value,
	                   double min_value,
	                   double max_value,
	                   double increment,
	                   Graph_lib::Callback callback_fn_after_edit);
	virtual void attach(Graph_lib::Window& win) override;
	virtual bool value_is_min() override;
	virtual bool value_is_max() override;

	double value() { return in.get_valid_double(); }
	double increment() const { return incr; }

private:
	double incr;

protected:
	Validated_double_min_max_in_box in;

	virtual void in_incr() override;
	virtual void in_decr() override;
	virtual bool next_incr_is_max() override;
	virtual bool next_decr_is_min() override;
	virtual void in_set_to_min() override;
	virtual void in_set_to_max() override;
	virtual void move_in_box(int offs_x, int offs_y) override;
	virtual void enable_in_box() override;
	virtual void disable_in_box() override;
};

#endif // STEP_IN_DBL_H
