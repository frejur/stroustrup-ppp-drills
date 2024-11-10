#include "calc.h"

void My_calculator::setup_all_expr_widgets()
{
	// Expression fields
	setup_expr_widget(in_expr, Expression_widget_ID::Expression_field);
	setup_expr_widget(out_expr, Expression_widget_ID::Result_field);

	// Expression buttons
	setup_expr_widget(btn_cancel, Expression_widget_ID::Cancel_button);
	setup_expr_widget(btn_ok, Expression_widget_ID::OK_button);
};

void My_calculator::setup_expr_widget(Graph_lib::Widget& widget,
                                      Expression_widget_ID id)
{

	using c_ = constants; // save up on horizontal space
	using eid_ = Expression_widget_ID;

	if (id == eid_::Expression_field) {
		attach(static_cast<In_box_control&>(widget));
	} else if (id == eid_::Result_field) {
		attach(static_cast<Out_box_control&>(widget));
	} else {
		attach(static_cast<Modal_button&>(widget));
	}

	// Placement
	Graph_lib::Point offs;
	switch (id) {
	case eid_::Expression_field:
		offs = {tl.x, tl.y - (c_::field_height * 2 + c_::field_padding * 2)};
		break;
	case eid_::Result_field:
	case eid_::Cancel_button:
	case eid_::OK_button:
		offs.y = tl.y - (c_::field_height + c_::field_padding);

		if (id == eid_::Result_field) {
			int lb_w = static_cast<Out_box_control&>(widget).label_width();
			offs.x = tl.x + lb_w;
		} else {
			offs.x = tl.x + w - c_::cancel_button_width;
			offs.x -= (id == eid_::OK_button)
			              ? c_::field_padding + c_::ok_button_width
			              : 0;
		}
		break;
	}

	widget.move(offs.x, offs.y);
	widget.hide(); // Hidden at the start
}
