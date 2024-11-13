#include "valid_dbl_mm.h"

namespace {
constexpr double min_value_lower_limit{-2056};
constexpr double max_value_lower_limit{-2055};
constexpr double min_value_upper_limit{max_value_lower_limit * -1};
constexpr double max_value_upper_limit{min_value_lower_limit * -1};
double valid_min(const double i);
double valid_max(const double val_min, const double val_max);
} // namespace

Validated_double_min_max_in_box::Validated_double_min_max_in_box(
    Graph_lib::Point top_left,
    int width,
    int height,
    const string& label,
    double default_value_as_double,
    double min_value,
    double max_value,
    Graph_lib::Callback callback_fn)
    : Validated_double_in_box(top_left,
                              width,
                              height,
                              label,
                              default_value_as_double,
                              callback_fn)
    , min_val(valid_min(min_value))
    , max_val(valid_max(min_val, max_value))
{}

Validated_in_box::State_and_converted_value
Validated_double_min_max_in_box::conv_and_check_val(const string& s)
{
	Converted_value val{Converted_value::Value_type::Double_value, s};
	if (!val.has_succeeded()) {
		return {State::Invalid, val};
	}

	State final_st = State::Not_validated;
	double val_dbl = val.get_double();
	if (val_dbl < min_value() || val_dbl > max_value()) {
		final_st = State::Invalid;
	} else {
		final_st = State::Valid;
	}
	return {final_st, val};
}

//------------------------------------------------------------------------------

namespace {
double valid_min(const double i)
{
	if (i < min_value_lower_limit || i > min_value_upper_limit) {
		throw std::runtime_error(
		    "Invalid minimum value, expected a value between "
		    + std::to_string(min_value_lower_limit) + " and "
		    + std::to_string(min_value_upper_limit) + " but got "
		    + std::to_string(i));
	}
	return i;
}
double valid_max(const double val_min, const double val_max)
{
	if (val_max <= val_min) {
		throw std::runtime_error(
		    "Invalid maximum value, expected a value greater than the minimum "
		    + std::to_string(val_min) + ", but got " + std::to_string(val_max));
	}
	if (val_max < max_value_lower_limit || val_max > max_value_upper_limit) {
		throw std::runtime_error(
		    "Invalid maximum value, expected a value between "
		    + std::to_string(max_value_lower_limit) + " and "
		    + std::to_string(max_value_upper_limit) + " but got "
		    + std::to_string(val_max));
	}
	return val_max;
}
} // namespace
