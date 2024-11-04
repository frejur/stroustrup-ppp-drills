#include "parse_xrate.h"
#include <fstream>
#include <sstream>

namespace {
const std::vector<Currency_ID_and_symbol>& currencies()
{
	static const std::vector<Currency_ID_and_symbol>
	    c{{Money_lib::Currency_ID::USD, "USD"},
	      {Money_lib::Currency_ID::EUR, "EUR"},
	      {Money_lib::Currency_ID::JPY, "JPY"},
	      {Money_lib::Currency_ID::GBP, "GBP"},
	      {Money_lib::Currency_ID::CAD, "CAD"},
	      {Money_lib::Currency_ID::AUD, "AUD"},
	      {Money_lib::Currency_ID::CHF, "CHF"},
	      {Money_lib::Currency_ID::CNY, "CNY"},
	      {Money_lib::Currency_ID::INR, "INR"},
	      {Money_lib::Currency_ID::BRL, "BRL"},
	      {Money_lib::Currency_ID::ZAR, "ZAR"},
	      {Money_lib::Currency_ID::KRW, "KRW"}};
	return c;
}
} // namespace
//------------------------------------------------------------------------------

std::istream& operator>>(std::istream& is, String_surrounded_by_quotes& s)
{
	char l_quo{}, r_quo{}; // quotes

	is >> l_quo;
	if (l_quo != '"') {
		is.clear(std::ios_base::badbit);
		return is;
	}

	bool found_r_quo = false;
	std::string extr_s;
	while (is) {
		is.get(r_quo);
		if (r_quo == '"') {
			found_r_quo = true;
			break;
		}
		extr_s += r_quo;
	}
	if (!found_r_quo) {
		is.clear(std::ios_base::badbit);
	} else {
		s.value = extr_s;
	}
	return is;
}

//------------------------------------------------------------------------------

std::istream& operator>>(std::istream& is, Money_lib::Currency_ID& id)
{
	std::string id_str;
	char c{};
	while (is.get(c)) {
		id_str += c;
		if (id_str.size() == 3) {
			break;
		}
	}
	using CID = Money_lib::Currency_ID;
	id = CID::Not_a_currency;
	for (const Currency_ID_and_symbol& id_and_s : currencies()) {
		if (id_and_s.symbol == id_str) {
			id = id_and_s.id;
			break;
		}
	}

	if (id == CID::Not_a_currency) {
		is.clear(std::ios_base::badbit);
	}
	return is;
}

//------------------------------------------------------------------------------

std::istream& operator>>(std::istream& is, Money_lib::Currency& cur)
{
	char l_par{}, r_par{}; // parentheses
	char cm_0, cm_1;       // commas

	is >> l_par;
	if (l_par != '(') {
		is.clear(std::ios_base::badbit);
		return is;
	}

	String_surrounded_by_quotes str_id;
	is >> str_id;

	if (!is) {
		return is;
	}

	std::istringstream iss;
	iss.str(str_id.value);
	Money_lib::Currency_ID id;
	iss >> id;
	if (id == Money_lib::Currency_ID::Not_a_currency) {
		is.clear(std::ios_base::badbit);
		return is;
	}

	String_surrounded_by_quotes str_name;
	String_surrounded_by_quotes str_symbol;
	is >> cm_0 >> str_name >> cm_1 >> str_symbol >> r_par;

	if (!is || cm_0 != ',' || str_name.value == "" || cm_1 != ','
	    || str_symbol.value == "" || r_par != ')') {
		is.clear(std::ios_base::badbit);
		return is;
	}

	cur = {id, str_name.value, str_symbol.value};
	return is;
}

//------------------------------------------------------------------------------

std::istream& operator>>(std::istream& is, Money_lib::Currency_pair& cur)
{
	char l_par{}, r_par{}; // parentheses
	char cm_0, cm_1;       // commas

	is >> l_par;
	if (l_par != '(') {
		is.clear(std::ios_base::badbit);
		return is;
	}

	String_surrounded_by_quotes str_id_base;
	is >> str_id_base;

	if (!is) {
		return is;
	}

	std::istringstream iss;
	iss.str(str_id_base.value);
	Money_lib::Currency_ID id_base;
	iss >> id_base;
	if (id_base == Money_lib::Currency_ID::Not_a_currency) {
		is.clear(std::ios_base::badbit);
		return is;
	}

	is >> cm_0;

	if (!is || cm_0 != ',') {
		is.clear(std::ios_base::badbit);
		return is;
	}

	String_surrounded_by_quotes str_id_counter;
	is >> str_id_counter;

	if (!is) {
		return is;
	}

	iss.str(str_id_counter.value);
	Money_lib::Currency_ID id_counter;
	iss >> id_counter;
	if (id_counter == Money_lib::Currency_ID::Not_a_currency) {
		is.clear(std::ios_base::badbit);
		return is;
	}

	long double xrate = 0;
	is >> cm_1 >> xrate >> r_par;

	if (!is || cm_0 != ',' || r_par != ')') {
		is.clear(std::ios_base::badbit);
		return is;
	}

	cur = {id_base, id_counter, xrate};
	return is;
};

//------------------------------------------------------------------------------

std::vector<Money_lib::Currency> read_currencies_from_file(
    const std::string& filename)
{
	std::ifstream ifs{filename};
	if (!ifs) {
		throw std::runtime_error("Could not open file '" + filename
		                         + "' for reading");
	}
	std::vector<Money_lib::Currency> cur_v;
	Money_lib::Currency cur;
	while (ifs >> cur) {
		cur_v.push_back(cur);
	}
	return cur_v;
}

std::vector<Money_lib::Currency_pair> read_exchange_rates_from_file(
    const std::string& filename)
{
	std::ifstream ifs{filename};
	if (!ifs) {
		throw std::runtime_error("Could not open file '" + filename
		                         + "' for reading");
	}
	std::vector<Money_lib::Currency_pair> cur_p_v;
	Money_lib::Currency_pair cur_p;
	while (ifs >> cur_p) {
		cur_p_v.push_back(cur_p);
	}
	return cur_p_v;
}
