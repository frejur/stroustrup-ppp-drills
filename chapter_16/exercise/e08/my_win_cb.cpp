#include "my_win.h"

void My_window::cb_upd_in_l(void*, void* pw)
{
	(*static_cast<My_window*>(pw)).convert(Side::Left);
}

void My_window::cb_upd_in_r(void*, void* pw)
{
	(*static_cast<My_window*>(pw)).convert(Side::Right);
}

void My_window::cb_upd_dropd_l_btn(void*, void* pw)
{
	(*static_cast<My_window*>(pw)).toggle_dropdown(Side::Left);
}

void My_window::cb_upd_dropd_r_btn(void*, void* pw)
{
	(*static_cast<My_window*>(pw)).toggle_dropdown(Side::Right);
}

void My_window::cb_switch(void*, void* pw)
{
	(*static_cast<My_window*>(pw)).switch_currencies();
}

//------------------------------------------------------------------------------

void My_window::select(Side s, int selection)
{
	shp_btn::Image_button& btn = (s == Side::Left) ? btn_dropd_l : btn_dropd_r;
	Currency_menu& m_primary = (s == Side::Left) ? dropd_l : dropd_r;
	Currency_menu& m_secondary = (s == Side::Left) ? dropd_r : dropd_l;

	btn.set_label(m_primary.get_label_by_index(selection));
	m_primary.select(selection);
	m_primary.hide();
	m_secondary.hide();
	convert(Side::Left); // Always convert Left -> Right
}

//------------------------------------------------------------------------------

void My_window::toggle_dropdown(Side s)
{
	shp_btn::Image_button& btn = (s == Side::Left) ? btn_dropd_l : btn_dropd_r;
	Currency_menu& m_primary = (s == Side::Left) ? dropd_l : dropd_r;
	Currency_menu& m_secondary = (s == Side::Left) ? dropd_r : dropd_l;

	if (m_primary.is_hidden()) {
		btn.activate();
		m_primary.show();
		m_secondary.hide();
	} else {
		btn.normalize();
		m_primary.hide();
		m_secondary.hide();
	}
}

//------------------------------------------------------------------------------

void My_window::convert(Side s)
try {
	// Widget shorthands
	using BTN = shp_btn::Image_button;
	In_box_control& in_from = (s == Side::Left) ? in_l : in_r;
	In_box_control& in_into = (s == Side::Left) ? in_r : in_l;
	Currency_menu& dd_from = (s == Side::Left) ? dropd_l : dropd_r;
	Currency_menu& dd_into = (s == Side::Left) ? dropd_r : dropd_l;
	BTN& dd_btn_from = (s == Side::Left) ? btn_dropd_l : btn_dropd_r;
	BTN& dd_btn_into = (s == Side::Left) ? btn_dropd_r : btn_dropd_l;

	// Close dropdown menus
	dd_from.hide();
	dd_into.hide();
	dd_btn_from.normalize();
	dd_btn_into.normalize();

	// Get selected currencies
	Money_lib::Currency_ID cur_from{
	    dd_from.get_currency_id_at_index(dd_from.get_selection())};
	Money_lib::Currency_ID cur_into{
	    dd_into.get_currency_id_at_index(dd_into.get_selection())};

	if (cur_from == cur_into) {
		// Same currency, no conversion needed
		in_into.put(in_from.get_string());
		txt_status.set_label("No conversion needed");
		return;
	}

	// Fetch input
	std::istringstream is;
	long double val_from = 0;
	is.str(in_from.get_string());
	is >> val_from;

	in_into.put("");
	txt_status.set_label("Error: Invalid syntax");
	if (is) {
		// Convert
		Money_lib::Money m_from = mm_s.new_decimal_money(val_from, cur_from);
		Money_lib::Money m_into = mm_s.new_money(0, cur_into);
		Money_lib::Money result = m_into + m_from;

		// Update Input values
		std::ostringstream os;
		os << result.as_floating_point();
		in_into.put(os.str());

		// Update status
		Exchange_rate_lib::Exchange_rate xrate{
		    mm_s.get_exchange_rate(cur_from, cur_into)};
		os.str("");
		os << "1 " << mm_s.get_currency(cur_from).symbol << " = "
		   << xrate.value() << " " << mm_s.get_currency(cur_into).symbol;
		txt_status.set_label(os.str());
	}
} catch (const std::exception& e) {
	std::ostringstream os;
	os << "Error: " << e.what();
	txt_status.set_label(os.str());
	mm_s.reset(); // Recover from error
} catch (...) {
	txt_status.set_label("Unknown error");
	mm_s.reset(); // Recover from error
}

//------------------------------------------------------------------------------

void My_window::switch_currencies()
{
	std::string l_label = btn_dropd_l.label();
	btn_dropd_l.set_label(btn_dropd_r.label());
	btn_dropd_r.set_label(l_label);

	int l_sel = dropd_l.get_selection();
	dropd_l.select(dropd_r.get_selection());
	dropd_r.select(l_sel);

	convert(Side::Left);
}
