#include "in_out_ctrl.h"
#include "../share/ch16_helpers.h"
#include <FL/Fl_Output.H>

void In_box_control::attach(Graph_lib::Window& win, My_calculator& calc)
{
	pw = new Fl_Input(loc.x, loc.y, width, height, label.c_str());
	pw->callback(reinterpret_cast<Fl_Callback*>(do_it),
	             &calc); // pass the calculator

	// Trigger callback upon edit
	pw->when(FL_WHEN_CHANGED);
	own = &win;
}

void In_box_control::move(int dx, int dy)
{
	bool backup_is_visible = !is_hidden;
	Graph_lib::Widget::move(dx, dy);
	if (!backup_is_visible) {
		hide();
	}
}

void In_box_control::hide()
{
	is_hidden = true;
	Graph_lib::Widget::hide();
}

void In_box_control::show()
{
	is_hidden = false;
	Graph_lib::Widget::show();
}

string In_box_control::get_string()
{
	Fl_Input* p = static_cast<Fl_Input*>(pw);
	return string{p->value()};
}

void In_box_control::clear()
{
	put("");
}

void In_box_control::put(const string& s)
{
	(*static_cast<Fl_Output*>(pw)).value(s.c_str());
}

//------------------------------------------------------------------------------

void Out_box_control::attach(Graph_lib::Window& win, My_calculator& calc)
{
	pw = new Fl_Output(loc.x, loc.y, width, height, label.c_str());
	pw->callback(reinterpret_cast<Fl_Callback*>(do_it),
	             &calc); // pass the calculator
	own = &win;
}

int Out_box_control::label_width() const
{
	return ch16_hlp::calc_lb_w(label, (*pw).labelfont(), (*pw).labelsize());
}

void Out_box_control::move(int dx, int dy)
{
	bool backup_is_visible = !is_hidden;
	Graph_lib::Widget::move(dx, dy);
	if (!backup_is_visible) {
		hide();
	}
}

void Out_box_control::hide()
{
	is_hidden = true;
	Graph_lib::Widget::hide();
}

void Out_box_control::show()
{
	is_hidden = false;
	Graph_lib::Widget::show();
}
