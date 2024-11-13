#ifndef VALID_IN_H
#define VALID_IN_H
#include "../../lib/GUI.h"
#include "../../lib/Graph.h"
// String conversion helpers

enum class Value_type { Integer_value, Double_value };

class Converted_value
{
public:
	Converted_value(Value_type t, const std::string& s);
	bool has_succeeded() const { return success; }
	int get_int();
	double get_double();

private:
	bool success;
	Value_type type;
	int value_int;
	double value_double;
};

//------------------------------------------------------------------------------
// An In_box that validates its value and triggers its callback function when
// edited. Mainly (See more details below)
//
// Depending on the derived type, calling `get_valid_int()`,
// get_valid_double()` or `get_valid_string()` validates the current contents
// and returns the default value if not valid. An invalid value will also result
// in the border of the input field being colored red.
//
// The same validation functionality described above can be achieved by calling
// `validate()`, but this method does not return a value.
//------------------------------------------------------------------------------

class Validated_in_box : public Graph_lib::Widget
{
public:
	Validated_in_box(Graph_lib::Point top_left,
	                 int width,
	                 int height,
	                 const std::string& label,
	                 const std::string& default_value_as_string,
	                 Graph_lib::Callback callback_fn);

	// Widget overides
	virtual void attach(Graph_lib::Window &win) override;
	virtual void move(int dx, int dy) override;

	// Enable / disable
	void enable() { enabled = true; };
	void disable() { enabled = false; };
	bool is_enabled() const { return enabled; };

	// Validation, state
	enum class State { Invalid, Not_validated, Valid };
	State get_state() const { return state; }
	void validate();

	// Value
	std::string raw_value() const;     // Returns: Non-validated input,
	std::string default_value() const; //          Default value (Always valid),
	std::string latest_value() const;  //          Latest value (Used to check
	                                   //                        for updates)
	void reset() { put(default_val); }

	int label_width() const; // Useful for more precise placement

	// Override frame appearance defaults
	void set_frame_color(Graph_lib::Color c) { frame.set_color(c); };
	void set_frame_style(Graph_lib::Line_style s) { frame.set_style(s); };

private:
	bool enabled;
	bool is_attached;
	State state;
	std::string default_val;
	std::string latest_val;
	Graph_lib::Color frame_clr;
	Graph_lib::Line_style frame_sty;
	Graph_lib::Rectangle frame;

protected:
	// Depending on the derived type, one of these getters should be made public
	virtual std::string get_valid_string();
	virtual int get_valid_int();
	virtual double get_valid_double();

	// Derived types need to implement this to reflect their specific
	// conditions for what qualifies as a valid value
	void check_default_val(); // Only used for initialization, will throw
	                          // an exception on failure
	virtual State check_val(const std::string& s) = 0;

	void put(const std::string& s); // Update input field

	// Frame appearance
	void mark_frame();
	void reset_frame();
};
//------------------------------------------------------------------------------

class Validated_string_in_box : public Validated_in_box
{
public:
	using Validated_in_box::get_valid_string;
	using Validated_in_box::Validated_in_box;
};
//------------------------------------------------------------------------------

class Validated_int_in_box : public Validated_in_box
{
public:
	Validated_int_in_box(Graph_lib::Point top_left,
	                     int width,
	                     int height,
	                     const std::string& label,
	                     int default_value_as_int,
	                     Graph_lib::Callback callback_fn);
	using Validated_in_box::get_valid_int;
};
//------------------------------------------------------------------------------

class Validated_double_in_box : public Validated_in_box
{
public:
	Validated_double_in_box(Graph_lib::Point top_left,
	                        int width,
	                        int height,
	                        const std::string& label,
	                        int default_value_as_double,
	                        Graph_lib::Callback callback_fn);
	using Validated_in_box::get_valid_double;
};

#endif // VALID_IN_H
