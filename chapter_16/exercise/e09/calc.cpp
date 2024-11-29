#include "calc.h"
#include "../share/ch16_helpers.h"
#include "cb_mgr.h"

namespace {

const std::string& icons_file_path()
{
	static const std::string s{"img_e09/calc_icons.png"};
	return s;
}

const Graph_lib::Color& transparent()
{
	static const Graph_lib::Color c{Graph_lib::Color::black,
	                                Graph_lib::Color::Transparency::invisible};
	return c;
}

} // namespace
//------------------------------------------------------------------------------

My_calculator::My_calculator(Graph_lib::Window& parent_window,
                             Graph_lib::Point top_left,
                             Calculator_callback_manager cb_mgr)
    : w(constants::display_width + constants::margin * 2)
    , h(constants::button_width * 6 + constants::button_padding * 5
        + constants::margin * 2)
    , expr_state(State::Blank)
    , mode(Mode::Calculator)
    , tl(top_left)
    , win(parent_window)
    , frame(top_left, w, h)
    , preview_expr("0")
    , pending_expr("0")
    , in_expr{{0, 0}, w, constants::field_height, "", cb_mgr.cb_in_expr}

    // Widgets, note that their final placement is adjusted later in the
    // 'setup_*' helper methods

    // Expression editor widgets
    , out_expr{{0, 0},
               constants::output_field_width,
               constants::field_height,
               "="}
    , btn_cancel({0, 0},
                 constants::cancel_button_width,
                 constants::field_height,
                 "Cancel",
                 cb_mgr.cb_cancel)
    , btn_ok({0, 0},
             constants::ok_button_width,
             constants::field_height,
             "OK",
             cb_mgr.cb_ok)
    , btn_display({0, 0},
                  constants::display_width,
                  constants::button_height,
                  "",
                  cb_mgr.cb_display,
                  icons_file_path())

    // Display
    , txt_display({0, 0}, "")
    , num_digits(0) // Count number of digits in the current number displayed
    , num_dots(0)   // See above

    // Buttons, row 1
    , btn_clr({0, 0},
              constants::button_width,
              constants::button_height,
              "",
              cb_mgr.cb_clr,
              icons_file_path())
    , btn_und({0, 0},
              constants::button_width,
              constants::button_height,
              "",
              cb_mgr.cb_und,
              icons_file_path())
    , btn_eqs({0, 0},
              constants::button_width,
              constants::button_height,
              "",
              cb_mgr.cb_eqs,
              icons_file_path())
    , btn_mlt({0, 0},
              constants::button_width,
              constants::button_height,
              "",
              cb_mgr.cb_mlt,
              icons_file_path())

    // Buttons, row 2
    , btn_n_7({0, 0},
              constants::button_width,
              constants::button_height,
              "",
              cb_mgr.cb_n_7,
              icons_file_path())
    , btn_n_8({0, 0},
              constants::button_width,
              constants::button_height,
              "",
              cb_mgr.cb_n_8,
              icons_file_path())
    , btn_n_9({0, 0},
              constants::button_width,
              constants::button_height,
              "",
              cb_mgr.cb_n_9,
              icons_file_path())
    , btn_div({0, 0},
              constants::button_width,
              constants::button_height,
              "",
              cb_mgr.cb_div,
              icons_file_path())

    // Buttons, row 3
    , btn_n_4({0, 0},
              constants::button_width,
              constants::button_height,
              "",
              cb_mgr.cb_n_4,
              icons_file_path())
    , btn_n_5({0, 0},
              constants::button_width,
              constants::button_height,
              "",
              cb_mgr.cb_n_5,
              icons_file_path())
    , btn_n_6({0, 0},
              constants::button_width,
              constants::button_height,
              "",
              cb_mgr.cb_n_6,
              icons_file_path())
    , btn_sub({0, 0},
              constants::button_width,
              constants::button_height,
              "",
              cb_mgr.cb_sub,
              icons_file_path())

    // Buttons, row 4
    , btn_n_1({0, 0},
              constants::button_width,
              constants::button_height,
              "",
              cb_mgr.cb_n_1,
              icons_file_path())
    , btn_n_2({0, 0},
              constants::button_width,
              constants::button_height,
              "",
              cb_mgr.cb_n_2,
              icons_file_path())
    , btn_n_3({0, 0},
              constants::button_width,
              constants::button_height,
              "",
              cb_mgr.cb_n_3,
              icons_file_path())

    // Buttons, row 5
    , btn_n_0({0, 0},
              constants::number_zero_button_width,
              constants::button_height,
              "",
              cb_mgr.cb_n_0,
              icons_file_path())
    , btn_dot({0, 0},
              constants::button_width,
              constants::button_height,
              "",
              cb_mgr.cb_dot,
              icons_file_path())
    , btn_add({0, 0},
              constants::button_width,
              constants::plus_button_height,
              "",
              cb_mgr.cb_add,
              icons_file_path())
{
	// Frame
	frame.set_color(transparent());
	frame.set_fill_color(constants::frame_color());
	win.attach(frame);

	setup_all_expr_widgets(); // Fields, modal buttons

	setup_all_buttons(); //      Calculator buttons
	btn_und.disable();
}

//------------------------------------------------------------------------------

void My_calculator::move(int offs_x, int offs_y)
{
	tl.x += offs_x;
	tl.y += offs_y;

	frame.move(offs_x, offs_y);   //--------Frame
	in_expr.move(offs_x, offs_y); //--------Input fields
	out_expr.move(offs_x, offs_y);
	btn_cancel.move(offs_x, offs_y); //-----Modal buttons
	btn_ok.move(offs_x, offs_y);
	btn_display.move(offs_x, offs_y); //----Display
	txt_display.move(offs_x, offs_y);
	btn_clr.move(offs_x, offs_y); //--------Buttons, row 1
	btn_und.move(offs_x, offs_y);
	btn_eqs.move(offs_x, offs_y);
	btn_mlt.move(offs_x, offs_y);
	btn_n_7.move(offs_x, offs_y); //--------Buttons, row 2
	btn_n_8.move(offs_x, offs_y);
	btn_n_9.move(offs_x, offs_y);
	btn_div.move(offs_x, offs_y);
	btn_n_4.move(offs_x, offs_y); //--------Buttons, row 3
	btn_n_5.move(offs_x, offs_y);
	btn_n_6.move(offs_x, offs_y);
	btn_sub.move(offs_x, offs_y);
	btn_n_1.move(offs_x, offs_y); //--------Buttons, row 4
	btn_n_2.move(offs_x, offs_y);
	btn_n_3.move(offs_x, offs_y); //--------Buttons, row 5
	btn_n_0.move(offs_x, offs_y);
	btn_dot.move(offs_x, offs_y);
	btn_add.move(offs_x, offs_y);
}

//------------------------------------------------------------------------------

void My_calculator::upd_txt_display(const string& s)
{
	txt_display.set_label(s);

	// Adjust X position to align text to the right (Assumes the Y position is
	//                                               already correct)
	int target_x = 0;
	const int current_x = txt_display.point(0).x;
	int txt_w{ch16_hlp::calc_lb_w(s,
	                              constants::display_font(),
	                              constants::display_font_size)};
	int adj_pad{static_cast<int>(std::round(constants::display_padding * 2.5))};
	target_x = btn_display.position().x
	           + (btn_display.width() - adj_pad - txt_w);
	txt_display.move(target_x - current_x, 0);
	win.redraw();
}

//------------------------------------------------------------------------------

void My_calculator::attach(Modal_button& b)
{
	win.begin();
	b.attach(win, *this);
	win.end();
}

void My_calculator::attach(Calculator_button& b)
{
	win.begin();
	b.attach(win, *this);
	win.end();
}

void My_calculator::attach(In_box_control& in)
{
	win.begin();
	in.attach(win, *this);
	win.end();
}

void My_calculator::attach(Out_box_control& out)
{
	win.begin();
	out.attach(win, *this);
	win.end();
}
//------------------------------------------------------------------------------

void My_calculator::eval_expr(bool add_to_stack)
{
	std::string e = (mode == Mode::Calculator) ? pending_expr : preview_expr;
	if (e == "") {
		e = "0";
	}
	istr.str(e + "\n");
	ostr.str("");

	expr_state = State::Error; // Assume failure to evaluate
	try {
		ostr << calc::statement(tstr, istr);
		tstr.get(istr); // consume newline
		expr_state = State::Valid;
	} catch (const std::exception& e) {
		istr.clear(std::ios_base::goodbit);
		ostr.clear(std::ios_base::goodbit);
		if (tstr.buffer_is_full()) {
			tstr.get(istr);
		}
		ostr << e.what();
	} catch (...) {
		ostr << "Error";
	}

	if (mode == Mode::Calculator) {
		num_digits = 0;
		num_dots = 0;
		if (expr_state == State::Error) {
			upd_txt_display("Error");
			return;
		}
		if (add_to_stack
		    && (und_stack.number_of_expressions() == 0
		        || e != und_stack.latest())) {
			und_stack.add_expression(e);
			pending_expr = e;
		}
		upd_txt_display(ostr.str());
	} else {
		out_expr.put(ostr.str());
	}
};

//------------------------------------------------------------------------------
// Expression editor
void My_calculator::update_expression()
{
	preview_expr = in_expr.get_string();
	eval_expr(false);
}

void My_calculator::press_cancel()
{
	if (mode != Mode::Expression_editor) {
		return;
	}
	close_editor();
	eval_expr(false);
	preview_expr = pending_expr;

	if (expr_state == State::Valid) {
		expr_state = State::Blank;
	}

	num_digits = 0;
	num_dots = 0;
}

void My_calculator::press_ok()
{
	if (mode != Mode::Expression_editor) {
		return;
	}
	if (expr_state == State::Valid) {
		// Save valid expression, update current pending expression
		std::string e = in_expr.get_string();
		if (e != pending_expr) {
			und_stack.add_expression(in_expr.get_string());
			pending_expr = e;
			upd_txt_display(ostr.str());
			btn_und.normalize();
		}

		close_editor();
		mode = Mode::Calculator;
		num_digits = 0;
		num_dots = 0;
	}
}

//------------------------------------------------------------------------------
// Buttons

void My_calculator::press_edit()
{
	if (mode == Mode::Expression_editor) {
		return;
	}

	// Fetch and evaluate pending expression
	if (num_digits > 0) {
		// Add any active digits to preview
		press_operator(Operator_type::Equals, true);
	}

	in_expr.put(preview_expr);
	open_editor();
	eval_expr(false);
}

void My_calculator::press_clear()
{
	if (mode == Mode::Expression_editor) {
		return;
	}

	und_stack.clear();
	preview_expr = "0";
	pending_expr = "0";
	upd_txt_display("0");
	expr_state = State::Blank;
	num_digits = 0;
	num_dots = 0;
	btn_und.disable();
}

void My_calculator::press_undo()
{
	if (mode == Mode::Expression_editor) {
		return;
	}

	if (num_digits > 0 && und_stack.number_of_expressions() == 0) {
		press_clear();
		return;
	}

	bool digits_or_error = (num_digits > 0 || expr_state == State::Error);

	if ((und_stack.number_of_expressions() == 1 && !digits_or_error)
	    || und_stack.number_of_expressions() == 0) {
		expr_state = State::Blank;
		btn_und.disable();
		return;
	}

	pending_expr = !digits_or_error
	                   ? (und_stack.remove_latest(), und_stack.latest())
	                   : und_stack.latest();
	preview_expr = pending_expr;
	eval_expr(false);

	if (und_stack.number_of_expressions() == 1) {
		btn_und.disable();
	}
}

void My_calculator::press_operator(Operator_type t, bool preview)
{
	if (mode != Mode::Calculator) {
		return;
	}

	if (num_digits == 0 && und_stack.number_of_expressions() == 0) {
		pending_expr = "0";
		num_digits = 1;
	}

	if (num_digits > 0) {
		// Assume preview at this point
		switch (expr_state) {
		case State::Blank:
		case State::Valid:
			preview_expr = txt_display.label();
			break;
		case State::Add:
			preview_expr = pending_expr + " + " + txt_display.label();
			break;
		case State::Subtract:
			preview_expr = pending_expr + " - " + txt_display.label();
			break;
		case State::Divide:
			preview_expr = "(" + pending_expr + ") / " + txt_display.label();
			break;
		case State::Multiply:
			preview_expr = "(" + pending_expr + ") * " + txt_display.label();
			break;
		case State::Error:
			return;
			break;
		}

		// Update expression if the preview flag has not been set
		if (!preview) {
			pending_expr = preview_expr;
			eval_expr(); // Evaluates and adds to undo stack if succesful
			if (expr_state == State::Error) {
				return;
			}
		}
	}

	switch (t) {
	case Operator_type::Add:
		expr_state = State::Add;
		break;
	case Operator_type::Subtract:
		expr_state = State::Subtract;
		break;
	case Operator_type::Divide:
		expr_state = State::Divide;
		break;
	case Operator_type::Multiply:
		expr_state = State::Multiply;
		break;
	case Operator_type::Equals:
		expr_state = State::Blank;
		break;
	}

	// Update Undo button appearance
	if (!preview && und_stack.number_of_expressions() > 1) {
		btn_und.normalize();
		win.redraw();
	}
}

void My_calculator::press_number(char i)
{
	if (i < 0 || i > 9 || mode == Mode::Expression_editor
	    || expr_state == State::Error) {
		return;
	}

	if (i == 0 && txt_display.label() == "0") {
		return;
	}

	if (num_digits == 0) {
		if (expr_state == State::Blank) {
			// Discard and start entering a new number
			pending_expr = "";
		}
		upd_txt_display(std::to_string((int) i));
		num_digits = 1;
		return;
	}

	upd_txt_display(txt_display.label() + std::to_string((int) i));
	++num_digits;
}

void My_calculator::press_dot()
{
	if (mode == Mode::Calculator && expr_state != State::Error) {
		if (num_dots == 0) {
			++num_dots;
			if (num_digits == 0) {
				upd_txt_display("0.");
			} else {
				upd_txt_display(txt_display.label() + ".");
			}
			num_digits = (std::max)(num_digits, 1); // There's at least one
			                                        // digit in 0.1234... etc.
		}
	}
}

//------------------------------------------------------------------------------
// Change color

void My_calculator::set_frame_color(Graph_lib::Color c)
{
	frame.set_fill_color(c);
}

void My_calculator::set_display_color(Graph_lib::Color c)
{
	btn_display.set_fill_color(c);
}

void My_calculator::set_button_color(Button_ID id, Graph_lib::Color c)
{
	switch (id) {
	case Button_ID::Add:
		btn_add.set_fill_color(c);
		break;
	case Button_ID::N_0:
		btn_n_0.set_fill_color(c);
		break;
	case Button_ID::N_1:
		btn_n_1.set_fill_color(c);
		break;
	case Button_ID::N_2:
		btn_n_2.set_fill_color(c);
		break;
	case Button_ID::N_3:
		btn_n_3.set_fill_color(c);
		break;
	case Button_ID::N_4:
		btn_n_4.set_fill_color(c);
		break;
	case Button_ID::N_5:
		btn_n_5.set_fill_color(c);
		break;
	case Button_ID::N_6:
		btn_n_6.set_fill_color(c);
		break;
	case Button_ID::N_7:
		btn_n_7.set_fill_color(c);
		break;
	case Button_ID::N_8:
		btn_n_8.set_fill_color(c);
		break;
	case Button_ID::N_9:
		btn_n_9.set_fill_color(c);
		break;
	case Button_ID::Equals:
		btn_eqs.set_fill_color(c);
		break;
	case Button_ID::Multiply:
		btn_mlt.set_fill_color(c);
		break;
	case Button_ID::Divide:
		btn_div.set_fill_color(c);
		break;
	case Button_ID::Subtract:
		btn_sub.set_fill_color(c);
		break;
	case Button_ID::Dot:
		btn_dot.set_fill_color(c);
		break;
	case Button_ID::Clear:
		btn_clr.set_fill_color(c);
		break;
	case Button_ID::Undo:
		btn_und.set_fill_color(c);
		break;
	case Button_ID::Edit:
		break; // Use set_display_color() instead
	}
}

void My_calculator::set_color_of_action_buttons(Graph_lib::Color c)
{
	set_button_color(Button_ID::Clear, c);
	set_button_color(Button_ID::Undo, c);
	win.redraw();
}

void My_calculator::set_color_of_operator_buttons(Graph_lib::Color c)
{
	set_button_color(Button_ID::Multiply, c);
	set_button_color(Button_ID::Divide, c);
	set_button_color(Button_ID::Add, c);
	set_button_color(Button_ID::Subtract, c);
	set_button_color(Button_ID::Equals, c);
	win.redraw();
}

void My_calculator::set_color_of_numerical_buttons(Graph_lib::Color c)
{
	set_button_color(Button_ID::N_0, c);
	set_button_color(Button_ID::N_1, c);
	set_button_color(Button_ID::N_2, c);
	set_button_color(Button_ID::N_3, c);
	set_button_color(Button_ID::N_4, c);
	set_button_color(Button_ID::N_5, c);
	set_button_color(Button_ID::N_6, c);
	set_button_color(Button_ID::N_7, c);
	set_button_color(Button_ID::N_8, c);
	set_button_color(Button_ID::N_9, c);
	set_button_color(Button_ID::Dot, c);
	win.redraw();
}

//------------------------------------------------------------------------------

void My_calculator::open_editor()
{
	if (mode == Mode::Expression_editor) {
		return;
	}
	mode = Mode::Expression_editor;

	// Toggle visiblity
	in_expr.show();
	out_expr.show();
	btn_cancel.show();
	btn_ok.show();
}

void My_calculator::close_editor()
{
	if (mode == Mode::Calculator) {
		return;
	}
	mode = Mode::Calculator;

	// Toggle visiblity
	in_expr.hide();
	out_expr.hide();
	btn_cancel.hide();
	btn_ok.hide();
}
