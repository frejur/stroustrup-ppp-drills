#include "calc.h"

namespace {
// Placement helpers, definitions at the bottom
void widget_x_offs(Graph_lib::Point& offs,
                   My_calculator::Button_ID id,
                   int margin,
                   int button_width,
                   int button_padding);
void widget_y_offs(Graph_lib::Point& offs,
                   My_calculator::Button_ID id,
                   int margin,
                   int button_height,
                   int button_padding);
bool btn_is_num(My_calculator::Button_ID id);
bool btn_is_op(My_calculator::Button_ID id);
bool btn_is_act(My_calculator::Button_ID id);
} // namespace

void My_calculator::setup_all_buttons()
{
	// Display
	setup_button(btn_display, Button_ID::Edit);
	setup_txt_display();

	// Buttons, row 1
	setup_button(btn_clr, Button_ID::Clear);
	setup_button(btn_und, Button_ID::Undo);
	setup_button(btn_eqs, Button_ID::Equals);
	setup_button(btn_mlt, Button_ID::Multiply);

	// Buttons, row 2
	setup_button(btn_n_7, Button_ID::N_7);
	setup_button(btn_n_8, Button_ID::N_8);
	setup_button(btn_n_9, Button_ID::N_9);
	setup_button(btn_div, Button_ID::Divide);

	// Buttons, row 3
	setup_button(btn_n_4, Button_ID::N_4);
	setup_button(btn_n_5, Button_ID::N_5);
	setup_button(btn_n_6, Button_ID::N_6);
	setup_button(btn_sub, Button_ID::Subtract);

	// Buttons, row 4
	setup_button(btn_n_1, Button_ID::N_1);
	setup_button(btn_n_2, Button_ID::N_2);
	setup_button(btn_n_3, Button_ID::N_3);

	// Buttons, row 5
	setup_button(btn_n_0, Button_ID::N_0);
	setup_button(btn_dot, Button_ID::Dot);
	setup_button(btn_add, Button_ID::Add);

	// Move down 'Plus' sign
	btn_add.offset_image(0,
	                     constants::button_height + constants::button_padding);
};

//------------------------------------------------------------------------------

void My_calculator::setup_button(Calculator_button& button, Button_ID id)
{
	attach(button); // This needs to preceed any other operations

	using c_ = constants; // Save up on horizontal space

	// Move masking area to correct region of spritesheet
	Graph_lib::Point offs_mask{masking_offset(id, c_::sprite_size)};
	button.set_mask(offs_mask.x, offs_mask.y, c_::sprite_size, c_::sprite_size);

	// Placement
	Graph_lib::Point offs_xy;
	widget_x_offs(offs_xy, id, c_::margin, c_::button_width, c_::button_padding);
	widget_y_offs(offs_xy, id, c_::margin, c_::button_height, c_::button_padding);
	button.move(offs_xy.x, offs_xy.y);

	// Appearance
	if (btn_is_act(id)) {
		button.set_fill_color(c_::action_button_color());
	} else if (btn_is_op(id)) {
		button.set_fill_color(c_::operator_button_color());
	} else if (btn_is_num(id)) {
		button.set_fill_color(c_::numerical_button_color());
	} else {
		button.set_fill_color(c_::display_bg_color());
	}
	button.set_color(
	    Graph_lib::Color(Graph_lib::Color::black,
	                     Graph_lib::Color::Transparency::invisible));
}

//------------------------------------------------------------------------------

void My_calculator::setup_txt_display()
{
	win.attach(txt_display);

	txt_display.set_color(constants::display_color());
	txt_display.set_font(constants::display_font());
	txt_display.set_font_size(constants::display_font_size);

	// Assumes the display button has already been placed
	int target_y = btn_display.position().y;
	int ofnt = fl_font();
	int osz = fl_size();
	fl_font(constants::display_font().as_int(), constants::display_font_size);
	target_y += (btn_display.height() - constants::display_padding)
	            - fl_descent() / 2;
	fl_font(ofnt, osz);
	txt_display.move(0, target_y);

	upd_txt_display(constants::display_intial_value());
}

//------------------------------------------------------------------------------

namespace {

void widget_x_offs(Graph_lib::Point& offset,
                   My_calculator::Button_ID id,
                   int margin,
                   int button_width,
                   int button_padding)
{
	using bid_ = My_calculator::Button_ID; // Save up on horizontal space

	switch (id) {
	// Display, and Buttons: column 1
	case bid_::Edit:
	case bid_::Clear:
	case bid_::N_7:
	case bid_::N_4:
	case bid_::N_1:
	case bid_::N_0:
		offset.x = margin;
		break;

	// Buttons, column 2
	case bid_::Undo:
	case bid_::N_8:
	case bid_::N_5:
	case bid_::N_2:
		offset.x = margin + button_width + button_padding;
		break;

	// Buttons, column 3
	case bid_::Equals:
	case bid_::N_9:
	case bid_::N_6:
	case bid_::N_3:
	case bid_::Dot:
		offset.x = margin + 2 * (button_width + button_padding);
		break;

	// Buttons, column 4
	case bid_::Multiply:
	case bid_::Divide:
	case bid_::Subtract:
	case bid_::Add:
		offset.x = margin + 3 * (button_width + button_padding);
		break;
	}
};

void widget_y_offs(Graph_lib::Point& offset,
                   My_calculator::Button_ID id,
                   int margin,
                   int button_height,
                   int button_padding)
{
	using bid_ = My_calculator::Button_ID; // Save up on horizontal space

	switch (id) {
	// Display
	case bid_::Edit:
		offset.y = margin;
		break;

	// Buttons, row 1
	case bid_::Clear:
	case bid_::Undo:
	case bid_::Equals:
	case bid_::Multiply:
		offset.y = margin + button_height + button_padding;
		break;

	// Buttons, row 2
	case bid_::N_7:
	case bid_::N_8:
	case bid_::N_9:
	case bid_::Divide:
		offset.y = margin + 2 * (button_height + button_padding);
		break;

	// Buttons, row 3
	case bid_::N_4:
	case bid_::N_5:
	case bid_::N_6:
	case bid_::Subtract:
		offset.y = margin + 3 * (button_height + button_padding);
		break;

	// Buttons, row 4 (And plus button)
	case bid_::N_1:
	case bid_::N_2:
	case bid_::N_3:
	case bid_::Add:
		offset.y = margin + 4 * (button_height + button_padding);
		break;

	// Buttons, row 5 (Except plus button)
	case bid_::N_0:
	case bid_::Dot:
		offset.y = margin + 5 * (button_height + button_padding);
		break;
	}
}

bool btn_is_num(My_calculator::Button_ID id)
{
	using bid_ = My_calculator::Button_ID; // Save up on horizontal space
	return (id == bid_::N_0 || id == bid_::N_1 || id == bid_::N_2
	        || id == bid_::N_3 || id == bid_::N_4 || id == bid_::N_5
	        || id == bid_::N_6 || id == bid_::N_7 || id == bid_::N_8
	        || id == bid_::N_9 || id == bid_::Dot);
}
bool btn_is_op(My_calculator::Button_ID id)
{
	using bid_ = My_calculator::Button_ID; // Save up on horizontal space
	return (id == bid_::Add || id == bid_::Subtract || id == bid_::Multiply
	        || id == bid_::Divide || id == bid_::Equals);
}
bool btn_is_act(My_calculator::Button_ID id)
{
	using bid_ = My_calculator::Button_ID; // Save up on horizontal space
	return (id == bid_::Clear || id == bid_::Undo);
}
} // namespace
