#include "../../lib/Debug_window.h"
#include "../../lib/Graph.h"
#include "distr_ctrl.h"
#include "e17_helpers.h"
#include "shp_distr.h"

// Exercise 17. Class diagram for std::exception

const std::string& info_click()
{
	static const std::string s{
	    "Click on any of the nodes marked '...' to expand them"};
	return s;
}

//------------------------------------------------------------------------------

void e17()
{
	using namespace ch14_e17;
	using Nodes = Graph_lib::Vector_ref<Node>;
	using Controllers = Graph_lib::Vector_ref<Controller>;
	constexpr bool ENABLE_DEBUG{false};
	constexpr bool ENABLE_CLICK{true};

	constexpr int win_w{1024};
	constexpr int win_h{480};
	GL::Point c{static_cast<int>(win_w * 0.5 + 0.5),
	            static_cast<int>(win_h * 0.5 + 0.5)};
	Debug_window win{{10, 10},
	                 win_w,
	                 win_h,
	                 "do2-2b-ro2",
	                 ENABLE_DEBUG,
	                 ENABLE_CLICK};

	constexpr int h_root{24};
	constexpr int h_lvl_0{18};
	constexpr int h_lvl_1{16};
	constexpr int h_lvl_2{14};

	// Adjust root placement
	c.x -= 32;
	c.y = 64;

	// Logic error, sub tree ---------------------------------------------------
	Node log_err_inv_arg{c, "invalid_argument", h_lvl_1};
	Node log_err_dom_err{c, "domain_error", h_lvl_1};
	Node log_err_len_err{c, "length_error", h_lvl_1};
	Node log_err_outof_r{c, "out_of_range", h_lvl_1};
	Node log_err_fut_err{c, "future_error", h_lvl_1};
	Nodes log_err_all;
	add_node_refs(log_err_all,
	              {&log_err_inv_arg,
	               &log_err_dom_err,
	               &log_err_len_err,
	               &log_err_outof_r,
	               &log_err_fut_err});

	batch_attach(win, log_err_all);
	ch14_e17::Node_distributor d_log_err{c, 120};
	batch_add_node(d_log_err, log_err_all);
	d_log_err.sort(true);
	bool log_err_has_been_init{false};

	// System error, sub tree --------------------------------------------------
	// Will be initialized along with the runtime error sub tree (See below)
	Node run_err_sys_err_fail{c, "ios_base::failure", h_lvl_2};
	Node run_err_sys_err_file{c, "filesystem::filesystem_error", h_lvl_2};
	Nodes run_err_sys_err_all;
	add_node_refs(run_err_sys_err_all,
	              {&run_err_sys_err_fail, &run_err_sys_err_file});
	batch_attach(win, run_err_sys_err_all);
	ch14_e17::Node_distributor d_run_err_sys_err{c, 120};
	batch_add_node(d_run_err_sys_err, run_err_sys_err_all);

	// Runtime error, sub classes ----------------------------------------------
	Node run_err_rge_err{c, "range error", h_lvl_1};
	Node run_err_oflow{c, "overflow_error", h_lvl_1};
	Node run_err_uflow{c, "underflow_error", h_lvl_1};
	Node run_err_regex{c, "regex_error", h_lvl_1};
	Node run_err_sys_err{c, "system_error", h_lvl_1};
	Node run_err_tx_exc{c, "tx_exception", h_lvl_1};
	Node run_err_nonex_ltime{c, "nonexistent_local_time", h_lvl_1};
	Node run_err_amb_ltime{c, "ambiguous_local_time", h_lvl_1};
	Node run_err_fmt_err{c, "format_error", h_lvl_1};
	Nodes run_err_all;
	add_node_refs(run_err_all,
	              {&run_err_rge_err,
	               &run_err_oflow,
	               &run_err_uflow,
	               &run_err_regex,
	               &run_err_sys_err,
	               &run_err_tx_exc,
	               &run_err_nonex_ltime,
	               &run_err_amb_ltime,
	               &run_err_fmt_err});

	batch_attach(win, run_err_all);
	ch14_e17::Node_distributor d_run_err{c, 170};
	batch_add_node(d_run_err, run_err_all);
	d_run_err.sort(true);
	d_run_err.place_in_middle(run_err_sys_err);
	bool run_err_has_been_init{false};

	// Single sub nodes / exceptions -------------------------------------------
	Node exc_bad_cst_any{c, "bad_any_cast", h_lvl_1, c};
	Node exc_b_alloc_arr{c, "bad_array_new_length", h_lvl_1, c};
	win.attach(exc_bad_cst_any);
	win.attach(exc_b_alloc_arr);

	// Base exceptions ---------------------------------------------------------
	Node exc_log_err{c, "logic_error", h_lvl_0, c};
	exc_log_err.toggle_symbol();
	Node exc_run_err{c, "runtime_error", h_lvl_0, c};
	exc_run_err.toggle_symbol();
	Node exc_bad_typ{c, "bad_typeid", h_lvl_0, c};
	Node exc_bad_cst{c, "bad_cast", h_lvl_0, c};
	exc_bad_cst.toggle_symbol();
	Node exc_bap_opt{c, "bad_optional_access", h_lvl_0, c};
	Node exc_bad_exp{c, "bad_expected_access", h_lvl_0, c};
	Node exc_weak_pt{c, "bad_weak_ptr", h_lvl_0, c};
	Node exc_fn_call{c, "bad_function_call", h_lvl_0, c};
	Node exc_b_alloc{c, "bad_alloc", h_lvl_0, c};
	exc_b_alloc.toggle_symbol();
	Node exc_bad_exc{c, "bad_exception", h_lvl_0, c};
	Node exc_var_acc{c, "bad_variant_access", h_lvl_0, c};
	Nodes exc_all;
	add_node_refs(exc_all,
	              {&exc_log_err,
	               &exc_run_err,
	               &exc_bad_typ,
	               &exc_bad_cst,
	               &exc_bap_opt,
	               &exc_bad_exp,
	               &exc_weak_pt,
	               &exc_fn_call,
	               &exc_b_alloc,
	               &exc_bad_exc,
	               &exc_var_acc});

	batch_attach(win, exc_all);
	ch14_e17::Node_distributor d_exc{c};
	batch_add_node(d_exc, exc_all);
	d_exc.sort(true);
	d_exc.place_in_middle(exc_log_err);
	d_exc.place_in_middle(exc_run_err);
	d_exc.distribute();

	bool exc_bad_cst_any_has_been_init{false};
	bool exc_b_alloc_arr_has_been_init{false};

	// Root --------------------------------------------------------------------
	Node r{{c.x, c.y}, "std::exception", h_root};
	r.move(-static_cast<int>(std::round(r.width() * 0.5)),
	       -static_cast<int>(std::round(r.height() * 0.5)));
	r.set_fill_color(Graph_lib::Color::white);
	win.attach(r);

	Graph_lib::Text info{{64, 32}, info_click()};
	info.set_color(Graph_lib::Color::black);
	win.attach(info);

	// Controllers -------------------------------------------------------------
	Distributor_controller ctrl_log_err{d_log_err};
	Distributor_controller ctrl_run_err{d_run_err};
	Distributor_controller ctrl_run_err_sys_err{d_run_err_sys_err};
	Shape_controller ctrl_exc_bad_cst_any{exc_bad_cst_any};
	Shape_controller ctrl_exc_b_alloc_arr{exc_b_alloc_arr};
	Controllers ctrl_all;
	add_controller_refs(
	    ctrl_all,
	    std::initializer_list<Controller*>{&ctrl_log_err,
	                                       &ctrl_run_err,
	                                       &ctrl_run_err_sys_err,
	                                       &ctrl_exc_bad_cst_any,
	                                       &ctrl_exc_b_alloc_arr});
	batch_hide(ctrl_all);

	while (win.shown()) {
		if (win.click_has_been_registered()) {
			const Graph_lib::Shape& e{
			    d_exc.element_at_point(win.click_position())};
			if (!is_sentinel(e)
			    && (&e == &exc_log_err || &e == &exc_run_err
			        || &e == &exc_bad_cst || &e == &exc_b_alloc)) {
				d_exc.distribute();

				if (&e == &exc_log_err) {
					if (!ctrl_log_err.is_visible()) {
						move_node_forward(d_exc, e);
						if (!log_err_has_been_init) {
							init_sub_tree(node_center(d_exc, e),
							              d_log_err,
							              log_err_all);
							log_err_has_been_init = true;
						}
						batch_hide(ctrl_all);
						ctrl_log_err.show();
					} else {
						batch_hide(ctrl_all);
					}
				}

				if (&e == &exc_run_err) {
					if (!ctrl_run_err.is_visible()) {
						move_node_forward(d_exc, e);
						if (!run_err_has_been_init) {
							init_sub_tree(node_center(d_exc, e),
							              d_run_err,
							              run_err_all);
							init_sub_tree(node_center(d_run_err,
							                          run_err_sys_err),
							              d_run_err_sys_err,
							              run_err_sys_err_all);
							run_err_has_been_init = true;
						}
						batch_hide(ctrl_all);
						ctrl_run_err.show();
						ctrl_run_err_sys_err.show();
					} else {
						batch_hide(ctrl_all);
					}
				}

				if (&e == &exc_bad_cst) {
					if (!ctrl_exc_bad_cst_any.is_visible()) {
						move_node_forward(d_exc, e);
						if (!exc_bad_cst_any_has_been_init) {
							init_sub_node(d_exc, exc_bad_cst_any, exc_bad_cst);
							exc_bad_cst_any_has_been_init = true;
						}
						batch_hide(ctrl_all);
						ctrl_exc_bad_cst_any.show();
					} else {
						batch_hide(ctrl_all);
					}
				}

				if (&e == &exc_b_alloc) {
					if (!ctrl_exc_b_alloc_arr.is_visible()) {
						move_node_forward(d_exc, e);
						if (!exc_b_alloc_arr_has_been_init) {
							init_sub_node(d_exc, exc_b_alloc_arr, exc_b_alloc);
							exc_b_alloc_arr_has_been_init = true;
						}
						batch_hide(ctrl_all);
						ctrl_exc_b_alloc_arr.show();
					} else {
						batch_hide(ctrl_all);
					}
				}
			}
		}
		win.wait_for_click();
	}
}


int main() {
	try {
		e17();
		return 0;
	} catch (exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	} catch (...) {
		std::cerr << "Unknown error\n";
		return 2;
	}
	return 0;
}
