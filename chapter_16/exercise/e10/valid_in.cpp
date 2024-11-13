#include "valid_in.h"
#include "../share/ch16_helpers.h"
#include <FL/Fl_Output.H>

namespace {
constexpr int frame_thickness = 2;
const Graph_lib::Color& frame_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::red};
	return c;
}
const Graph_lib::Line_style& frame_style()
{
	static const Graph_lib::Line_style& s{
	    Graph_lib::Line_style(Graph_lib::Line_style::solid, frame_thickness)};
	return s;
}

std::string initial_int_str(int i);
std::string initial_double_str(double i);
} // namespace
//------------------------------------------------------------------------------

Converted_value::Converted_value()
    : success(false)
    , type_(Value_type::Not_a_type)
    , value_int(0)
    , value_double(0) {};

Converted_value::Converted_value(Value_type t, const string& s)
    : success(false)
    , type_(t)
    , value_int(0)
    , value_double(0)
{
	std::istringstream istr{s};
	int new_i;
	double new_d;
	if (t == Value_type::Integer_value) {
		istr >> new_i;
	} else {
		istr >> new_d;
	}

	if (istr) {
		char c;
		success = true; // Assume true, check that only whitespace remains
		while (istr.get(c)) {
			if (!std::isspace(static_cast<unsigned char>(c))) {
				success = false;
				break;
			}
		}
	}

	if (success) {
		if (t == Value_type::Integer_value) {
			value_int = new_i;
		} else {
			value_double = new_d;
		}
	}
}

int Converted_value::get_int() const
{
	if (type_ == Value_type::Integer_value) {
		return value_int;
	} else {
		return static_cast<int>(value_double); // Possible, but not recommended
	}
}

double Converted_value::get_double() const
{
	if (type_ == Value_type::Double_value) {
		return value_double;
	} else {
		return static_cast<double>(value_int); // Possible, but not recommended
	}
}
//------------------------------------------------------------------------------

Validated_in_box::Validated_in_box(Graph_lib::Point top_left,
                                   int w,
                                   int h,
                                   const std::string& label,
                                   const string& default_value_as_string,
                                   Graph_lib::Callback callback_fn)
    : Graph_lib::Widget(top_left, w, h, label, callback_fn)
    , enabled(true)
    , is_attached(false)
    , state(State::Not_validated)
    , default_val(default_value_as_string)
    , conv_val(Converted_value::Value_type::Integer_value, "0")
    , frame_clr(frame_color())
    , frame_sty(frame_style())
    , frame({top_left.x - frame_thickness, top_left.y - frame_thickness},
            w + frame_thickness * 2,
            h + frame_thickness * 2)
{
	int t = 0;
}
//------------------------------------------------------------------------------

void Validated_in_box::attach(Graph_lib::Window& win)
{
	if (is_attached) {
		return;
	}

	// Attach Widget
	pw = new Fl_Input(loc.x, loc.y, width, height, label.c_str());
	pw->callback(reinterpret_cast<Fl_Callback *>(do_it),
	             &win); // pass the window
	// Trigger callback upon edit
	pw->when(FL_WHEN_CHANGED);
	own = &win;

	// Attach shape
	win.attach(frame);

	// Check if the above changed the internal positional attrib. - Update shape
	if (frame.point(0).x != loc.x || frame.point(1).y != loc.y) {
		int offs_x = loc.x - frame.point(0).x;
		int offs_y = loc.y - frame.point(0).y;
		frame.move(offs_x, offs_y);
	}

	is_attached = true;

	put(default_val);
	check_default_val();
	reset_frame();
}

void Validated_in_box::move(int dx, int dy)
{
	Graph_lib::Widget::move(dx, dy);
	frame.move(dx, dy);
}
//------------------------------------------------------------------------------

void Validated_in_box::validate()
{
	if (get_state() == State::Valid && raw_value() == latest_value()) {
		return;
	}

	// Convert and validate
	conv_val = Converted_value();
	State_and_converted_value st_val = conv_and_check_val(raw_value());

	state = st_val.state;
	if (state == State::Valid) {
		conv_val = st_val.value;
		reset_frame();
	} else {
		mark_frame();
	}
}
//------------------------------------------------------------------------------

string Validated_in_box::raw_value() const
{
	Fl_Input& p = *static_cast<Fl_Input*>(pw);
	return string{p.value()};
}

string Validated_in_box::default_value() const
{
	return default_val;
}

string Validated_in_box::latest_value() const
{
	return latest_val;
};

//------------------------------------------------------------------------------

int Validated_in_box::label_width() const
{
	Fl_Input& p = *static_cast<Fl_Input*>(pw);
	return ch16_hlp::calc_lb_w(label, p.labelfont(), p.labelsize());
}
//------------------------------------------------------------------------------
string Validated_in_box::get_valid_string()
{
	validate();
	if (get_state() == State::Valid) {
		return raw_value();
	} else {
		return default_value();
	}
}

int Validated_in_box::get_valid_int()
{
	validate();
	int val_int = default_val_int;
	if (get_state() == State::Valid) {
		val_int = conv_val.get_int();
	}
	return val_int;
}

double Validated_in_box::get_valid_double()
{
	validate();
	double val_double = default_val_double;
	if (get_state() == State::Valid) {
		val_double = conv_val.get_double();
	}
	return val_double;
}
//------------------------------------------------------------------------------

void Validated_in_box::check_default_val()
{
	State_and_converted_value st_val = conv_and_check_val(default_val);
	if (!st_val.value.has_succeeded() || st_val.state != State::Valid) {
		throw std::runtime_error("Invalid default value");
	}
	conv_val = st_val.value;
	state = st_val.state;
}
//------------------------------------------------------------------------------

void Validated_in_box::put(const string& s)
{
	Fl_Input& p = *static_cast<Fl_Input*>(pw);
	p.value(s.c_str());
	latest_val = s;
}
//------------------------------------------------------------------------------

void Validated_in_box::mark_frame()
{
	frame.set_color(frame_clr);
	frame.set_style(frame_sty);
	redraw_window();
}

void Validated_in_box::reset_frame()
{
	frame.set_color(Graph_lib::Color(Graph_lib::Color::black,
	                                 Graph_lib::Color::Transparency::invisible));
	redraw_window();
}

//------------------------------------------------------------------------------
namespace {
std::string initial_int_str(int i)
{
	std::ostringstream oss{};
	oss << i;
	return oss.str();
}
} // namespace

Validated_int_in_box::Validated_int_in_box(Graph_lib::Point top_left,
                                           int width,
                                           int height,
                                           const string& label,
                                           int default_value_as_int,
                                           Graph_lib::Callback callback_fn)
    : Validated_in_box(top_left,
                       width,
                       height,
                       label,
                       initial_int_str(default_value_as_int),
                       callback_fn)
{}

//------------------------------------------------------------------------------
namespace {
std::string initial_double_str(double d)
{
	std::ostringstream oss{};
	oss << d;
	return oss.str();
}
} // namespace

Validated_double_in_box::Validated_double_in_box(Graph_lib::Point top_left,
                                                 int width,
                                                 int height,
                                                 const string& label,
                                                 int default_value_as_double,
                                                 Graph_lib::Callback callback_fn)
    : Validated_in_box(top_left,
                       width,
                       height,
                       label,
                       initial_double_str(default_value_as_double),
                       callback_fn)
{}
