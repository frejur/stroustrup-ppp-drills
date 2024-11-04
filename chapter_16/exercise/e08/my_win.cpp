#include "my_win.h"
#include "../share/ch16_helpers.h"
#include "../share/money/money.h"
#include <FL/Fl_Output.H>
#include <sstream>

namespace {
constexpr int window_top_margin{16};
constexpr int horizontal_padding{4};
constexpr int vertical_padding{4};
constexpr int input_field_width{136};
constexpr int input_field_height{24};
constexpr int dropdown_button_width{input_field_width};
constexpr int dropdown_button_height{24};
constexpr int switch_button_width{24};
constexpr int switch_button_height{24};
constexpr int button_font_size{12};
constexpr int status_font_size{12};

// A less verbose version of Graph_lib::reference_to, to save horizontal space
My_window& Win_ref(void* pw)
{
	return *static_cast<My_window*>(pw);
}

const std::string& dropdown_bg_file_path()
{
	static const std::string p{"dropd_bg.png"};
	return p;
}
const std::string& switch_bg_file_path()
{
	static const std::string p{"switch_bg.png"};
	return p;
}

const Graph_lib::Color& button_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::white};
	return c;
}

const Graph_lib::Color& button_bg_color()
{
	static const Graph_lib::Color c{
	    Graph_lib::Color(fl_rgb_color(100, 100, 100))};
	return c;
}

const Graph_lib::Font& button_font()
{
	static const Graph_lib::Font f{Graph_lib::Font::helvetica};
	return f;
}

// Position constants
constexpr int dropdown_y_position{window_top_margin + input_field_height
                                  + vertical_padding};
constexpr int dropdown_negative_x_offset{
    switch_button_width / 2 + horizontal_padding + dropdown_button_width};
constexpr int dropdown_positive_x_offset{switch_button_width / 2
                                         + horizontal_padding};
constexpr int status_text_y_position{dropdown_y_position + dropdown_button_height
                                     + vertical_padding + status_font_size};

const Graph_lib::Point& switch_button_position(int mid_x)
{
	static const Graph_lib::Point p{mid_x - switch_button_width / 2,
	                                dropdown_y_position};
	return p;
}

int ellipsis_width()
{
	static const int w{
	    ch16_hlp::calc_lb_w("...", button_font(), button_font_size)};
	return w;
}

} // namespace

//------------------------------------------------------------------------------

// Hardcoded variations of the same callback... There are better ways I'm sure.
const std::vector<Graph_lib::Callback> My_window::dropd_l_cb_v
    = {[](void*, void* pw) { Win_ref(pw).select(Side::Left, 0); },
       [](void*, void* pw) { Win_ref(pw).select(Side::Left, 1); },
       [](void*, void* pw) { Win_ref(pw).select(Side::Left, 2); },
       [](void*, void* pw) { Win_ref(pw).select(Side::Left, 3); },
       [](void*, void* pw) { Win_ref(pw).select(Side::Left, 4); },
       [](void*, void* pw) { Win_ref(pw).select(Side::Left, 5); },
       [](void*, void* pw) { Win_ref(pw).select(Side::Left, 6); },
       [](void*, void* pw) { Win_ref(pw).select(Side::Left, 7); },
       [](void*, void* pw) { Win_ref(pw).select(Side::Left, 8); },
       [](void*, void* pw) { Win_ref(pw).select(Side::Left, 9); },
       [](void*, void* pw) { Win_ref(pw).select(Side::Left, 10); },
       [](void*, void* pw) { Win_ref(pw).select(Side::Left, 11); }};

const std::vector<Graph_lib::Callback> My_window::dropd_r_cb_v
    = {[](void*, void* pw) { Win_ref(pw).select(Side::Right, 0); },
       [](void*, void* pw) { Win_ref(pw).select(Side::Right, 1); },
       [](void*, void* pw) { Win_ref(pw).select(Side::Right, 2); },
       [](void*, void* pw) { Win_ref(pw).select(Side::Right, 3); },
       [](void*, void* pw) { Win_ref(pw).select(Side::Right, 4); },
       [](void*, void* pw) { Win_ref(pw).select(Side::Right, 5); },
       [](void*, void* pw) { Win_ref(pw).select(Side::Right, 6); },
       [](void*, void* pw) { Win_ref(pw).select(Side::Right, 7); },
       [](void*, void* pw) { Win_ref(pw).select(Side::Right, 8); },
       [](void*, void* pw) { Win_ref(pw).select(Side::Right, 9); },
       [](void*, void* pw) { Win_ref(pw).select(Side::Right, 10); },
       [](void*, void* pw) { Win_ref(pw).select(Side::Right, 11); }};

const int My_window::num_cb = valid_num_cb(dropd_l_cb_v.size(),
                                           dropd_r_cb_v.size());

//------------------------------------------------------------------------------

void In_box_control::attach(Graph_lib::Window& win)
{
	pw = new Fl_Input(loc.x, loc.y, width, height, label.c_str());
	pw->callback(reinterpret_cast<Fl_Callback*>(do_it), &win); // pass the window

	// Trigger callback upon edit
	pw->when(FL_WHEN_CHANGED);
	own = &win;
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

My_window::My_window(Graph_lib::Point xy,
                     int w,
                     int h,
                     const string& title,
                     const std::vector<Money_lib::Currency> currencies,
                     const std::vector<Money_lib::Currency_pair>& exchange_rates)
    : Window(xy, w, h, title)
    , in_l({x_max() / 2 - dropdown_negative_x_offset, window_top_margin},
           input_field_width,
           input_field_height,
           "",
           cb_upd_in_l)
    , in_r({x_max() / 2 + dropdown_positive_x_offset, window_top_margin},
           input_field_width,
           input_field_height,
           "",
           cb_upd_in_r)
    , btn_sw(switch_button_position(x_max() / 2),
             switch_button_width,
             switch_button_height,
             "",
             cb_switch,
             switch_bg_file_path())
    , btn_dropd_l({x_max() / 2 - dropdown_negative_x_offset,
                   dropdown_y_position},
                  dropdown_button_width,
                  dropdown_button_height,
                  "",
                  cb_upd_dropd_l_btn,
                  dropdown_bg_file_path())
    , btn_dropd_r({x_max() / 2 + dropdown_positive_x_offset,
                   dropdown_y_position},
                  dropdown_button_width,
                  dropdown_button_height,
                  "",
                  cb_upd_dropd_r_btn,
                  dropdown_bg_file_path())
    , dropd_l({x_max() / 2 - dropdown_negative_x_offset,
               dropdown_y_position + dropdown_button_height}, // Place below
              dropdown_button_width,
              dropdown_button_height,
              "")
    , dropd_r({x_max() / 2 + dropdown_positive_x_offset,
               dropdown_y_position + dropdown_button_height}, // Place below
              dropdown_button_width,
              dropdown_button_height,
              "")
    , txt_status({x_max() / 2 - dropdown_negative_x_offset,
                  status_text_y_position},
                 "Status")
{
	size_range(w, h, w, h); // Lock window size

	// Setup monetary math session
	mm_s.set_vehicle_currency(Money_lib::DEFAULT_CURRENCY().id);
	for (const Money_lib::Currency& cur : currencies) {
		mm_s.add_currency(cur);
	}
	for (const Money_lib::Currency_pair& xr : exchange_rates) {
		mm_s.add_exchange_rate(xr.base, xr.counter, xr.xrate.value());
	}

	// Get currencies that can at least be converted to and from 'USD'
	std::vector<Money_lib::Currency> avail_cur
	    = mm_s.get_currencies_convertible_with_id(
	        Money_lib::DEFAULT_CURRENCY().id);
	avail_cur.push_back(Money_lib::DEFAULT_CURRENCY());
	num_cur = valid_num_cur(avail_cur.size());

	// Input boxes and 'Switch' button
	attach(in_l);
	attach(in_r);
	btn_sw.set_fill_color(button_bg_color());
	attach(btn_sw);

	// Status text
	txt_status.set_font_size(status_font_size);
	attach(txt_status);

	// Setup dropdowns
	setup_dropdown(btn_dropd_l,
	               dropd_l,
	               dropdown_button_width,
	               dropdown_button_height,
	               button_font(),
	               button_font_size,
	               avail_cur,
	               Money_lib::Currency_ID::USD,
	               dropd_l_cb_v);
	setup_dropdown(btn_dropd_r,
	               dropd_r,
	               dropdown_button_width,
	               dropdown_button_height,
	               button_font(),
	               button_font_size,
	               avail_cur,
	               Money_lib::Currency_ID::EUR,
	               dropd_r_cb_v);
	in_l.put("1.0");
	convert(Side::Left);
}

//------------------------------------------------------------------------------

std::string My_window::trim_currency_name(const string& name,
                                          Graph_lib::Font font,
                                          int font_size,
                                          int max_width,
                                          int ellipsis_width)
{
	if (ellipsis_width < 1) {
		throw std::runtime_error("Ellipsis width cannot be less than 1");
	}
	if (ellipsis_width >= max_width) {
		throw std::runtime_error("Ellipsis width exceeds max width");
	}

	max_width = static_cast<int>(
	    std::round(max_width * 0.95)); // TODO: Find out why this is necessary

	int init_w = ch16_hlp::calc_lb_w(name, font, font_size);
	if (init_w > max_width) {
		std::string new_name;
		for (int i = 0; i < name.size(); ++i) {
			int new_w = ch16_hlp::calc_lb_w(new_name + name[i], font, font_size);
			if (new_w > (max_width - ellipsis_width)) {
				if (i == 0) {
					return "";
				} else {
					return new_name + "...";
				}
			}
			new_name += name[i];
		}
	}
	return name;
}

//------------------------------------------------------------------------------

void My_window::setup_dropdown(
    shp_btn::Shape_button& button,
    Currency_menu& menu,
    int width,
    int height,
    Graph_lib::Font font,
    int font_size,
    const std::vector<Money_lib::Currency>& currencies,
    const Money_lib::Currency_ID selected_id,
    const std::vector<Graph_lib::Callback>& callbacks)
{
	std::ostringstream oss;
	int count = 0;
	Money_lib::Currency selection{Money_lib::Currency_ID::Not_a_currency,
	                              "",
	                              ""};
	int selection_id = -1;
	menu.set_color(button_color());
	menu.set_fill_color(button_bg_color());
	for (const Money_lib::Currency& cur : currencies) {
		oss.str("");
		oss << cur.symbol << ", " << cur.name;
		menu.add({0, 0},
		         width,
		         height,
		         trim_currency_name(oss.str(),
		                            font,
		                            font_size,
		                            width,
		                            ellipsis_width()),
		         callbacks[count]);
		if (cur.id == selected_id) {
			if (selection_id != -1) {
				throw std::runtime_error(
				    "Could not create dropdown, duplicate currency detected");
			}
			selection = cur;
			selection_id = count;
		}
		menu.set_currency_id_at_index(cur.id, menu.number_of_options() - 1);
		++count;
	}
	attach(menu);

	if (selection.id == Money_lib::Currency_ID::Not_a_currency) {
		throw std::runtime_error(
		    "Could not create dropdown, the currency specified as the initial "
		    "selection does not exist in the provided list of currencies.");
	}

	oss.str("");
	oss << selection.symbol << ", " << selection.name;
	button.set_fill_color(button_bg_color());
	button.set_font(font);
	button.set_font_size(font_size);
	button.set_label(oss.str());
	button.set_alignment(shp_btn::Text_box::Alignment::Left);
	attach(button);

	attach(menu);
	menu.sort();
	menu.select(selection_id);
	menu.hide();
}

//------------------------------------------------------------------------------

int My_window::valid_num_cb(int n_left_cb, int n_right_cb)
{
	if (n_left_cb != n_right_cb) {
		throw std::runtime_error("Callback vectors size mismatch");
	}
	return n_left_cb;
}

int My_window::valid_num_cur(int n) const
{
	if (n < 2) {
		throw std::runtime_error("At least two currencies need to be provided");
	}

	if (n > dropd_r_cb_v.size()) {
		throw std::runtime_error("The number of currencies cannot exceed "
		                         + std::to_string(dropd_r_cb_v.size()));
	}

	return n;
}

//------------------------------------------------------------------------------
