#ifndef CB_MGR_H
#define CB_MGR_H
#include "../../lib/GUI.h"

struct Callback_and_ID; // Forward declare

// Used to initialize the calculator object width the default callbacks,
// but can also be used to intercept, disable or modify the default functionality.
struct Calculator_callback_manager
{
	// static Calculator_callback_manager create(
	//     std::initializer_list<Callback_and_ID> cb_and_id);
	Calculator_callback_manager(std::initializer_list<Callback_and_ID> cb_and_id);

	Graph_lib::Callback cb_in_expr;
	Graph_lib::Callback cb_ok;
	Graph_lib::Callback cb_cancel;
	Graph_lib::Callback cb_display;
	Graph_lib::Callback cb_clr;
	Graph_lib::Callback cb_und;
	Graph_lib::Callback cb_eqs;
	Graph_lib::Callback cb_mlt;
	Graph_lib::Callback cb_n_7;
	Graph_lib::Callback cb_n_8;
	Graph_lib::Callback cb_n_9;
	Graph_lib::Callback cb_div;
	Graph_lib::Callback cb_n_4;
	Graph_lib::Callback cb_n_5;
	Graph_lib::Callback cb_n_6;
	Graph_lib::Callback cb_sub;
	Graph_lib::Callback cb_n_1;
	Graph_lib::Callback cb_n_2;
	Graph_lib::Callback cb_n_3;
	Graph_lib::Callback cb_n_0;
	Graph_lib::Callback cb_dot;
	Graph_lib::Callback cb_add;

	void setup_default_cb();

private:
};

#endif // CB_MGR_H
