#ifndef CB_ID_H
#define CB_ID_H
#include "calc.h"

// Used in conjunction with the Calculator_callback_manager to setup the
// callbacks when initializing a new calculator object
struct Callback_and_ID
{
	Callback_and_ID(Graph_lib::Callback cb,
	                My_calculator::Expression_widget_ID id);

	Callback_and_ID(Graph_lib::Callback cb, My_calculator::Button_ID id);

	Graph_lib::Callback callback;
	My_calculator::Widget_type type;
	My_calculator::Expression_widget_ID expr_widget_id;
	My_calculator::Button_ID button_id;
};

#endif // CB_ID_H
