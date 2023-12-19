#include "money.h"
#include <stdexcept>

namespace ML = Money_lib;
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

ML::Monetary_math::Monetary_math() : is_active{ true }
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

double ML::Monetary_math::get_exchange_rate(ML::Currency_ID id_a,
                                            ML::Currency_ID id_b) const
{
	ML::Currency_pair p{ tbl.get(id_a, id_b) };
	if (p.base == id_a) {
		return p.xrate;
	} else {
		return 1 / p.xrate;
	}
}

void ML::Monetary_math::add_exchange_rate(ML::Currency_ID id_a,
                                          ML::Currency_ID id_b, double xrate)
{
	validate_status(status());
	try {
		tbl.add({ id_a, id_b, xrate });
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

ML::Money ML::Monetary_math::new_combined_money(Monetary_math& self,
                                                double amt_as_dbl,
                                                ML::Currency_ID id)
{
	validate_status(status());
	try {
		amt_as_dbl *= 100;
		long amt_as_long{ static_cast<long>(amt_as_dbl) };
		if (amt_as_dbl != amt_as_long) {
			throw std::runtime_error("Cannot create Money from the given "
									 "floating-point value since it would lead "
									 "to information loss");
		}
		return { self, amt_as_long, id };
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
	double xrate{ mm.get_exchange_rate(in, out) };
	return static_cast<long>((10 * amt * xrate + 5) / 10);
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

