#ifndef VALID_DBL_MM_H
#define VALID_DBL_MM_H
#include "valid_in.h"

class Validated_double_min_max_in_box : public Validated_double_in_box
{
public:
	Validated_double_min_max_in_box(Graph_lib::Point top_left,
	                                int width,
	                                int height,
	                                const std::string& label,
	                                double default_value_as_double,
	                                double min_value,
	                                double max_value,
	                                Graph_lib::Callback callback_fn);
	double min_value() const { return min_val; }
	double max_value() const { return max_val; }
	void set_value(double d);

protected:
	virtual State_and_converted_value conv_and_check_val(
	    const std::string& s) override;

private:
	double min_val;
	double max_val;
};

#endif // VALID_DBL_MM_H
