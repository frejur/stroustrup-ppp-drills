#include "cb_mgr.h"
#include "calc.h"
#include "cb_id.h"

Calculator_callback_manager::Calculator_callback_manager(
    std::initializer_list<Callback_and_ID> cb_and_id)
{
	using wid_ = My_calculator::Expression_widget_ID;
	using bid_ = My_calculator::Button_ID;

	setup_default_cb();

	for (const Callback_and_ID& cid : cb_and_id) {
		// Assign any Widget callbacks
		if (cid.type == My_calculator::Widget_type::Expression_widget) {
			switch (cid.expr_widget_id) {
			case wid_::Expression_field:
				cb_in_expr = cid.callback;
				break;
			case wid_::Result_field:
				// No callback
				break;
			case wid_::OK_button:
				cb_ok = cid.callback;
				break;
			case wid_::Cancel_button:
				cb_cancel = cid.callback;
				break;
			}
		} else {
			// Assign any Button callbacks
			switch (cid.button_id) {
			case bid_::Clear:
				cb_clr = cid.callback;
				break;
			case bid_::N_0:
				cb_n_0 = cid.callback;
				break;
			case bid_::N_1:
				cb_n_1 = cid.callback;
				break;
			case bid_::N_2:
				cb_n_2 = cid.callback;
				break;
			case bid_::N_3:
				cb_n_3 = cid.callback;
				break;
			case bid_::N_4:
				cb_n_4 = cid.callback;
				break;
			case bid_::N_5:
				cb_n_5 = cid.callback;
				break;
			case bid_::N_6:
				cb_n_6 = cid.callback;
				break;
			case bid_::N_7:
				cb_n_7 = cid.callback;
				break;
			case bid_::N_8:
				cb_n_8 = cid.callback;
				break;
			case bid_::N_9:
				cb_n_9 = cid.callback;
				break;
			case bid_::Equals:
				cb_eqs = cid.callback;
				break;
			case bid_::Multiply:
				cb_mlt = cid.callback;
				break;
			case bid_::Divide:
				cb_div = cid.callback;
				break;
			case bid_::Subtract:
				cb_sub = cid.callback;
				break;
			case bid_::Add:
				cb_add = cid.callback;
				break;
			case bid_::Dot:
				cb_dot = cid.callback;
				break;
			case bid_::Edit:
				cb_display = cid.callback;
				break;
			case bid_::Undo:
				cb_und = cid.callback;
				break;
			}
		}
	}
};

void Calculator_callback_manager::setup_default_cb()
{
	cb_in_expr = [](void*, void* pw) {
		(*static_cast<My_calculator*>(pw)).update_expression();
	};
	cb_ok = [](void*, void* pw) {
		(*static_cast<My_calculator*>(pw)).press_ok();
	};
	cb_cancel = [](void*, void* pw) {
		(*static_cast<My_calculator*>(pw)).press_cancel();
	};
	cb_display = [](void*, void* pw) {
		(*static_cast<My_calculator*>(pw)).press_edit();
	};
	cb_clr = [](void*, void* pw) {
		(*static_cast<My_calculator*>(pw)).press_clear();
	};
	cb_und = [](void*, void* pw) {
		(*static_cast<My_calculator*>(pw)).press_undo();
	};
	cb_eqs = [](void*, void* pw) {
		(*static_cast<My_calculator*>(pw))
		    .press_operator(My_calculator::Operator_type::Equals);
	};
	cb_mlt = [](void*, void* pw) {
		(*static_cast<My_calculator*>(pw))
		    .press_operator(My_calculator::Operator_type::Multiply);
	};
	cb_n_7 = [](void*, void* pw) {
		(*static_cast<My_calculator*>(pw)).press_number(7);
	};
	cb_n_8 = [](void*, void* pw) {
		(*static_cast<My_calculator*>(pw)).press_number(8);
	};
	cb_n_9 = [](void*, void* pw) {
		(*static_cast<My_calculator*>(pw)).press_number(9);
	};
	cb_div = [](void*, void* pw) {
		(*static_cast<My_calculator*>(pw))
		    .press_operator(My_calculator::Operator_type::Divide);
	};
	cb_n_4 = [](void*, void* pw) {
		(*static_cast<My_calculator*>(pw)).press_number(4);
	};
	cb_n_5 = [](void*, void* pw) {
		(*static_cast<My_calculator*>(pw)).press_number(5);
	};
	cb_n_6 = [](void*, void* pw) {
		(*static_cast<My_calculator*>(pw)).press_number(6);
	};
	cb_sub = [](void*, void* pw) {
		(*static_cast<My_calculator*>(pw))
		    .press_operator(My_calculator::Operator_type::Subtract);
	};
	cb_n_1 = [](void*, void* pw) {
		(*static_cast<My_calculator*>(pw)).press_number(1);
	};
	cb_n_2 = [](void*, void* pw) {
		(*static_cast<My_calculator*>(pw)).press_number(2);
	};
	cb_n_3 = [](void*, void* pw) {
		(*static_cast<My_calculator*>(pw)).press_number(3);
	};
	cb_n_0 = [](void*, void* pw) {
		(*static_cast<My_calculator*>(pw)).press_number(0);
	};
	cb_dot = [](void*, void* pw) {
		(*static_cast<My_calculator*>(pw)).press_dot();
	};
	cb_add = [](void*, void* pw) {
		(*static_cast<My_calculator*>(pw))
		    .press_operator(My_calculator::Operator_type::Add);
	};
}
