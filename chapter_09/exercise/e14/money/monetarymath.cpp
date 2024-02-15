#include "money.h"
#include <stdexcept>

namespace ML = Money_lib;
namespace MLH = Money_lib_helpers;
namespace XRT = Exchange_rate_lib;

//------------------------------------------------------------------------------
// Helpers (Defintions at the bottom)

void validate_status(const bool status);
std::string trim_whitespace(const std::string& s);
bool only_alphanumericals(const std::string& s);

//------------------------------------------------------------------------------

const ML::Currency& ML::DEFAULT_CURRENCY() {
	static ML::Currency cur{ ML::Currency_ID::USD, "U.S. Dollars", "USD" };
	return cur;
}

ML::Monetary_math::Monetary_math(std::istream& istr) : is_active{ true },
	                                                   is{ istr }
{
	add_currency(ML::DEFAULT_CURRENCY());
	is_active = has_currency();
}

ML::Currency ML::Monetary_math::get_currency(ML::Currency_ID id) const {
	if (id == ML::Currency_ID::Not_a_currency) {
		throw std::runtime_error("Invalid currency ID");
	}
	for (ML::Currency c : cur_v) {
		if (c.id == id) {
			return c;
		}
	}
	return { ML::Currency_ID::Not_a_currency, {}, {} };
}

ML::Currency ML::Monetary_math::get_currency_by_symbol(
	const std::string& symbol
) const
{
	for (ML::Currency c : cur_v) {
		if (c.symbol == symbol) {
			return c;
		}
	}
	return { ML::Currency_ID::Not_a_currency, {}, {} };
};

std::vector<std::string> ML::Monetary_math::get_currency_list() const {
	std::vector<std::string> list;
	if (cur_v.size() == 0) {
		list.push_back("No currencies available");
	} else {
		for (const Money_lib::Currency& c : cur_v) {
			list.push_back(c.symbol + "    (" + c.name + ")");
		}
	}
	return list;
}

void ML::Monetary_math::add_currency(ML::Currency cur) {
	validate_status(status());
	std::string name;
	try {
		if (cur.id == ML::Currency_ID::Not_a_currency) {
			throw std::runtime_error("Invalid currency ID");
		}
		if (cur.symbol.size() == 0 || !only_alphanumericals(cur.symbol)) {
			throw std::runtime_error("Invalid currency symbol");
		}
		name = trim_whitespace(cur.name);
		if (name.size() == 0) {
			throw std::runtime_error("Invalid currency name");
		}
		if (get_currency(cur.id).id != ML::Currency_ID::Not_a_currency) {
			throw std::runtime_error("Cannot add currency, it already exists");
		}
	} catch (std::exception& e) {
		is_active = false;
		throw e;
	}
	cur_v.push_back( { cur.id, name, cur.symbol });
}

void ML::Monetary_math::add_currency(Currency_ID id, const std::string& name,
                                     const std::string& symbol)
{
	add_currency({ id, name, symbol });
}

XRT::Exchange_rate ML::Monetary_math::get_exchange_rate(ML::Currency_ID id_a,
                                                        ML::Currency_ID id_b)
	const
{
	ML::Currency_pair p{ tbl.get(id_a, id_b) };
	if (p.base == id_a) {
		return p.xrate;
	} else {
		p.xrate.flip_currencies();
		return p.xrate;
	}
}

void ML::Monetary_math::add_exchange_rate(ML::Currency_ID id_a,
                                          ML::Currency_ID id_b,
                                          double xrate_as_dbl)
{
	validate_status(status());
	try {
		tbl.add({ id_a, id_b, { xrate_as_dbl } });
	}
	catch (std::exception& e) {
		is_active = false;
		throw e;
	}
}

//------------------------------------------------------------------------------

ML::Money ML::Monetary_math::new_money(Monetary_math& self,
                                       long amt_in_c, ML::Currency_ID id)
{
	validate_status(status());
	try {
		return { self, amt_in_c, id };
	}
	catch (std::exception& e) {
		is_active = false;
		throw e;
	}
}

ML::Money ML::Monetary_math::new_decimal_money(Monetary_math& self,
                                                double amt_as_dbl,
                                                ML::Currency_ID id)
{
	validate_status(status());
	try {
		return{ self, MLH::decimal_to_cents(amt_as_dbl), id };
	}
	catch (std::exception& e) {
		is_active = false;
		throw e;
	}
}

//------------------------------------------------------------------------------

bool ML::operator==(const ML::Monetary_math_session& mm, const bool b) {
	return mm.status() == b;
}

bool ML::operator!=(const ML::Monetary_math_session& mm, const bool b) {
	return !ML::operator==(mm, b);
}

//------------------------------------------------------------------------------

long ML::convert_currency_amt(long amt, ML::Currency_ID in, ML::Currency_ID out,
                              const ML::Monetary_math& mm)
{
	long new_amt{ 0 };
	if (amt != 0) {
		XRT::Exchange_rate xrate{ mm.get_exchange_rate(in, out) };
		new_amt = xrate * amt;
	}
	return new_amt;
}

//------------------------------------------------------------------------------

void validate_status(const bool status) {
	if (status == false) {
		throw std::runtime_error("Monetary_math session is inactive or was "
		                         "not properly initialized");
	}
}

std::string trim_whitespace(const std::string& s) {
	if (s.size() == 0) {
		return s;
	}
	std::string new_s { "" };
	bool found_non_ws { false };
	if (isspace(s.front())) {
		for (char c : s) {
			if (found_non_ws) {
				new_s.push_back(c);
			} else if(!isspace(c)) {
				new_s.push_back(c);
				found_non_ws = true;
			}
		}
		if (new_s.size() == 0) {
			return new_s;
		}
	} else {
		new_s = s;
	}

	if (isspace(new_s.back())) {
		for (int i = new_s.size() - 1; i >= 0; --i) {
			if(isspace(new_s[i])) {
				new_s.pop_back();
			} else {
				break;
			}
		}
	}

	return new_s;
}

bool only_alphanumericals(const std::string& s) {
	for (char c: s) {
		if (!isalnum(c)) {
			return false;
		}
	}
	return true;
}

