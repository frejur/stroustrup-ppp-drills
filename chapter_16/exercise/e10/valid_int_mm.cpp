#include "valid_int_mm.h"

namespace {
constexpr int min_value_lower_limit{-2056};
constexpr int max_value_lower_limit{-2055};
constexpr int min_value_upper_limit{max_value_lower_limit * -1};
constexpr int max_value_upper_limit{min_value_lower_limit * -1};
int valid_min(const int i);
int valid_max(const int val_min, const int val_max);
} // namespace

Validated_int_min_max_in_box::Validated_int_min_max_in_box(
    Graph_lib::Point top_left,
    int width,
    int height,
    const string& label,
    int default_value_as_int,
    int min_value,
    int max_value,
    Graph_lib::Callback callback_fn)
    : Validated_int_in_box(top_left,
                           width,
                           height,
                           label,
                           default_value_as_int,
                           callback_fn)
    , min_val(valid_min(min_value))
    , max_val(valid_max(min_val, max_value))
{}

void Validated_int_min_max_in_box::set_value(int i)
{
	put(std::to_string(i));
	validate();
}

Validated_in_box::State_and_converted_value
Validated_int_min_max_in_box::conv_and_check_val(const string& s)
{
	Converted_value val{Converted_value::Value_type::Integer_value, s};
	if (!val.has_succeeded()) {
		return {State::Invalid, val};
	}

	State final_st = State::Not_validated;
	int val_int = val.get_int();
	if (val_int < min_value() || val_int > max_value()) {
		final_st = State::Invalid;
	} else {
		final_st = State::Valid;
	}
	return {final_st, val};
}

//------------------------------------------------------------------------------

namespace {
int valid_min(const int i)
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
int valid_max(const int val_min, const int val_max)
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
