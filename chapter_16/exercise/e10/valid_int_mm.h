#ifndef VALID_INT_MM_H
#define VALID_INT_MM_H
#include "valid_in.h"

class Validated_int_min_max_in_box : public Validated_int_in_box
{
public:
	Validated_int_min_max_in_box(Graph_lib::Point top_left,
	                             int width,
	                             int height,
	                             const std::string& label,
	                             int default_value_as_int,
	                             int min_value,
	                             int max_value,
	                             Graph_lib::Callback callback_fn);
	int min_value() const { return min_val; }
	int max_value() const { return max_val; }

protected:
	virtual State_and_converted_value conv_and_check_val(
	    const std::string& s) override;

private:
	int min_val;
	int max_val;
};

#endif // VALID_INT_MM_H
