#ifndef MY_WIN_H
#define MY_WIN_H

#include "../../lib/Graph.h"
#include "../../lib/Window.h"
#include "../share/dropd.h"
#include "../share/image_button.h"
#include "../share/money/money.h"

// An In_box that triggers its callback function when edited
class In_box_control : public Graph_lib::Widget
{
public:
	In_box_control(Graph_lib::Point xy,
	               int w,
	               int h,
	               const string& s,
	               Graph_lib::Callback callback_fn)
	    : Graph_lib::Widget(xy, w, h, s, callback_fn)
	{}

	int get_int();
	string get_string();
	void clear();
	void put(const std::string& s);
	void attach(Graph_lib::Window& win);

private:
	bool ignore_next;
};

//------------------------------------------------------------------------------

class Currency_option : public dropd::Dropdown_option
{
public:
	Currency_option(Graph_lib::Point top_left,
	                int width,
	                int height,
	                const std::string& label,
	                Graph_lib::Callback callback_fn,
	                Graph_lib::Color bg_color,
	                Money_lib::Currency_ID currency_id)
	    : Dropdown_option::Dropdown_option(top_left,
	                                       width,
	                                       height,
	                                       label,
	                                       callback_fn,
	                                       bg_color)
	    , cur_id(currency_id){};
	void set_currency_id(Money_lib::Currency_ID id) { cur_id = id; };
	Money_lib::Currency_ID currency_id() const { return cur_id; };

private:
	Money_lib::Currency_ID cur_id;
};

//------------------------------------------------------------------------------

class Currency_menu : public dropd::Dropdown_menu
{
public:
	using Dropdown_menu::Dropdown_menu;

	void set_currency_id_at_index(Money_lib::Currency_ID id, int idx)
	{
		static_cast<Currency_option&>(selection[valid_sel_idx(idx)])
		    .set_currency_id(id);
	};
	Money_lib::Currency_ID get_currency_id_at_index(int idx) const
	{
		return static_cast<const Currency_option&>(selection[valid_sel_idx(idx)])
		    .currency_id();
	};

	virtual New_option new_option(Graph_lib::Point top_left,
	                              int width,
	                              int height,
	                              const std::string& label,
	                              Graph_lib::Callback cb_function)
	{
		Currency_option* o
		    = new Currency_option(top_left,
		                          width,
		                          height,
		                          label,
		                          cb_function,
		                          fill_color(),
		                          Money_lib::Currency_ID::Not_a_currency);
		return {o};
	};
};

//------------------------------------------------------------------------------

enum class Side { Left, Right };

class My_window : public Graph_lib::Window
{
public:
	My_window(Graph_lib::Point xy,
	          int w,
	          int h,
	          const string& title,
	          const std::vector<Money_lib::Currency> currencies,
	          const std::vector<Money_lib::Currency_pair>& exchange_rates);

	// Callback actions
	void toggle_dropdown(Side id);
	void select(Side id, int selection);
	void convert(Side id);
	void switch_currencies();

private:
	In_box_control in_l;
	In_box_control in_r;
	shp_btn::Image_button btn_sw;
	shp_btn::Image_button btn_dropd_l;
	shp_btn::Image_button btn_dropd_r;
	Currency_menu dropd_l;
	Currency_menu dropd_r;
	Graph_lib::Text txt_status;

	static const std::vector<Graph_lib::Callback> dropd_l_cb_v;
	static const std::vector<Graph_lib::Callback> dropd_r_cb_v;
	static const int num_cb;
	int num_cur;
	Money_lib::Monetary_math_session mm_s;

	std::string trim_currency_name(const std::string& name,
	                               Graph_lib::Font font,
	                               int font_size,
	                               int max_width,
	                               int ellipsis_width);

	// Setup widgets
	void setup_dropdown(shp_btn::Shape_button& button,
	                    Currency_menu& menu,
	                    int width,
	                    int height,
	                    Graph_lib::Font font,
	                    int font_size,
	                    const std::vector<Money_lib::Currency>& currencies,
	                    const Money_lib::Currency_ID selected_id,
	                    const std::vector<Graph_lib::Callback>& callbacks);

	// Callback functions
	static void cb_upd_in_l(void*, void* pw);
	static void cb_upd_in_r(void*, void* pw);
	static void cb_upd_dropd_l_btn(void*, void* pw);
	static void cb_upd_dropd_r_btn(void*, void* pw);
	static void cb_switch(void*, void* pw);

	static int valid_num_cb(int n_left_cb, int n_right_cb);
	int valid_num_cur(int n) const;
};

#endif // MY_WIN_H
