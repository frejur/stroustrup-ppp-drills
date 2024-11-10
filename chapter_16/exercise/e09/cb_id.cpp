#include "cb_id.h"

Callback_and_ID::Callback_and_ID(Graph_lib::Callback cb,
                                 My_calculator::Expression_widget_ID id)
    : type(My_calculator::Widget_type::Expression_widget)
    , expr_widget_id(id)
{
	callback = cb;
};
Callback_and_ID::Callback_and_ID(Graph_lib::Callback cb,
                                 My_calculator::Button_ID id)
    : type(My_calculator::Widget_type::Button)
    , button_id(id)
{
	callback = cb;
};
