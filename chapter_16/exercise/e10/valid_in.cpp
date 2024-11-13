#include "valid_in.h"
#include "../share/ch16_helpers.h"
#include <FL/Fl_Output.H>

namespace {
constexpr int frame_thickness = 2;
const Graph_lib::Color &frame_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::red};
	return c;
}
const Graph_lib::Line_style &frame_style()
{
	static const Graph_lib::Line_style &s{
	    Graph_lib::Line_style(Graph_lib::Line_style::solid, frame_thickness)};
	return s;
}
} // namespace

//------------------------------------------------------------------------------

Validated_in_box::Validated_in_box(Graph_lib::Point top_left,
                                   int w,
                                   int h,
                                   const std::string &label,
                                   Graph_lib::Callback callback_fn)
    : Graph_lib::Widget(top_left, w, h, label, callback_fn)
    , enabled(true)
    , frame({top_left.x - frame_thickness, top_left.y - frame_thickness},
            width + frame_thickness * 2,
            height + frame_thickness * 2)
    , state(State::Not_validated)

{
	frame.set_style(frame_style());
	frame.set_color(frame_color());
}

//------------------------------------------------------------------------------

void Validated_in_box::attach(Graph_lib::Window &win)
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
};

//------------------------------------------------------------------------------

int Validated_in_box::label_width() const
{
	return ch16_hlp::calc_lb_w(label, (*pw).labelfont(), (*pw).labelsize());
}
