#ifndef STEP_IN_INT_H
#define STEP_IN_INT_H
#include "step_in.h"

class Step_int_in_box : public Step_in_box
{
public:
	Step_int_in_box(Graph_lib::Point top_left,
	                int width,
	                int height,
	                const std::string& label,
	                int default_value,
	                int min_value,
	                int max_value,
	                int increment,
	                Graph_lib::Callback callback_fn_after_edit);
	virtual void attach(Graph_lib::Window& win) override;
	virtual bool value_is_min() override;
	virtual bool value_is_max() override;

	int value() { return in.get_valid_int(); }
	int increment() const { return incr; }

private:
	int incr;

protected:
	Validated_int_min_max_in_box in;

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

#endif // STEP_IN_INT_H
