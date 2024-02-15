#include "money.h"
#include "moneyhelpers.h"
#include <stdexcept>

namespace ML = Money_lib;
namespace MLH = Money_lib_helpers;

//------------------------------------------------------------------------------

ML::Money::Money(ML::Monetary_math& mmm, long cc, ML::Currency_ID id)
: mm{ mmm }, cur{ mm.get_currency(id) }, c{ cc }
{
	if (mm != true) {
		throw std::runtime_error("Cannot create money, the Monetary_math "
		                         "session has not been properly initialized "
		                         "or is no longer active");
	}
}
// Update ----------------------------------------------------------------------

void ML::Money::update_amount(long new_amt, Currency_ID new_id) {
	ML::Currency temp_cur = cur;

	try {
		ML::validate_session(mm);

		if (new_id != cur.id) {
			temp_cur = mm.get_currency(new_id);
			if (temp_cur.id == ML::Currency_ID::Not_a_currency) {
				throw std::runtime_error("Cannot change to an invalid"
				                         "Currency");
			}
		}
	}
	catch (std::exception& e) {
		deactivate_session();
		throw e;
	}

	c = new_amt;
	cur = temp_cur;
}

void ML::Money::update_decimal_amount(double new_amt, Currency_ID new_id) {
	ML::Currency temp_cur = cur;
	long temp_c = c;

	try {
		ML::validate_session(mm);

		if (new_id != cur.id) {
			temp_cur = mm.get_currency(new_id);
			if (temp_cur.id == ML::Currency_ID::Not_a_currency) {
				throw std::runtime_error("Cannot change to an invalid"
				                         "Currency");
			}
		}
		temp_c = MLH::decimal_to_cents(new_amt);
	}
	catch (std::exception& e) {
		deactivate_session();
		throw e;
	}

	cur = temp_cur;
	c = temp_c;
}

// Arithmetic operators --------------------------------------------------------

ML::Money ML::operator+(ML::Money& a, const ML::Money& b) {
	try {
		ML::validate_session(a, b);
		if (a.currency().id != b.currency().id) {
			long conv_amt{ convert_currency_amt(b.amount(), b.currency().id,
			               a.currency().id, a.session()) };
			return a.new_amount(a.amount() + conv_amt);
		}
		return a.new_amount(a.amount() + b.amount());
	}
	catch (std::exception& e) {
		a.deactivate_session();
		throw e;
	}
}

ML::Money ML::operator-(ML::Money& a, const ML::Money& b) {
	try {
		ML::validate_session(a, b);
		if (a.currency().id != b.currency().id) {
			long conv_amt{ convert_currency_amt(b.amount(), b.currency().id,
						   a.currency().id, a.session()) };
			return a.new_amount(a.amount() - conv_amt);
		}
		return a.new_amount(a.amount() - b.amount());
	}
	catch (std::exception& e) {
		a.deactivate_session();
		throw e;
	}
}

long double ML::operator/(ML::Money& a, const ML::Money& b) {
	try {
		if (b.amount() == 0) {
			throw std::runtime_error("Cannot divide by zero");
		}
		ML::validate_session(a, b);
		if (a.currency().id != b.currency().id) {
			long conv_amt{ convert_currency_amt(b.amount(), b.currency().id,
						   a.currency().id, a.session()) };
			if (conv_amt == 0) {
				throw std::runtime_error("Cannot divide by zero");
			}
			return a.amount() / static_cast<long double>(conv_amt);
		}
		return a.amount() / static_cast<double>(b.amount());
	}
	catch (std::exception& e) {
		a.deactivate_session();
		throw e;
	}
}

ML::Money ML::operator/(ML::Money& a, const double b) {
	try {
		if (b == 0) {
			throw std::runtime_error("Cannot divide by zero");
		}
		ML::validate_session(a);
		long q {
			static_cast<long>(((a.amount() * 10) / b + 5) / 10)
		};
		return a.new_amount(q);
	}
	catch (std::exception& e) {
		a.deactivate_session();
		throw e;
	}
}

ML::Money ML::operator*(ML::Money& a, const double b) {
	try {
		ML::validate_session(a);
		long p{ a.amount() };
		if (p == 0 || b == 0) {
			return a.new_amount(0);
		}
		int sign{ (a.amount() < 0) ? -1 : 1 };
		p = (
			static_cast<long>(((a.amount() * 10) * b + (5 * sign)) / 10)
		);
		return a.new_amount(p);
	}
	catch (std::exception& e) {
		a.deactivate_session();
		throw e;
	}
}

ML::Money ML::operator*(const double a, ML::Money& b) {
	return b * a;
}

// Comparison operators --------------------------------------------------------

bool ML::operator==(ML::Money& a, const ML::Money& b) {
	try {
		ML::validate_session(a, b);
		if (b.amount() != 0 && (a.currency().id != b.currency().id)) {
			long conv_amt{ convert_currency_amt(b.amount(), b.currency().id,
						   a.currency().id, a.session()) };
			return a.amount() == conv_amt;
		}
		return a.amount() == b.amount();
	}
	catch (std::exception& e) {
		a.deactivate_session();
		throw e;
	}
}

bool ML::operator!=(ML::Money& a, const ML::Money& b) {
	return !ML::operator==(a, b);
}

bool ML::operator<(ML::Money& a, const ML::Money& b) {
	try {
		ML::validate_session(a, b);
		if (a.currency().id != b.currency().id) {
			long conv_amt{ convert_currency_amt(b.amount(), b.currency().id,
						   a.currency().id, a.session()) };
			return a.amount() < conv_amt;
		}
		return a.amount() < b.amount();
	}
	catch (std::exception& e) {
		a.deactivate_session();
		throw e;
	}
}

bool ML::operator<=(ML::Money& a, const ML::Money& b) {
	return ML::operator<(a, b) || ML::operator==(a, b);
}

bool ML::operator>(ML::Money& a, const ML::Money& b) {
	return !ML::operator<(a, b) && ML::operator!=(a, b);
}

bool ML::operator>=(ML::Money& a, const ML::Money& b) {
	return !ML::operator<(a, b) || ML::operator==(a, b);
}

// Input / Output operators ----------------------------------------------------

std::ostream& ML::operator<<(std::ostream& os, ML::Money m) {
	os << m.as_floating_point() << ' ' << m.currency().symbol;
	return os;
}

std::istream& ML::operator>>(std::istream& is, ML::Money& m) {
	double val{};
	std::string symbol;

	if (!m.session().status()) {
		return is;
	}

	is >> val >> symbol;
	if (!is) {
		return is;
	}

	ML::Currency cur{ m.session().get_currency_by_symbol(symbol) };
	try {
		m.update_decimal_amount(val, cur.id);
	}
	catch (...) {
		is.clear(std::ios_base::failbit);
		try { throw; }
		catch (const std::exception& e) { throw e; }
		catch (...) { throw std::runtime_error("Unknown error"); }
	}

	return is;
}

//------------------------------------------------------------------------------

void ML::validate_session(const ML::Money&a) {
	if (a.session().status() != true) {
		throw std::runtime_error("The Monetary_math session is no longer "
		                         "active");
	}
}

void ML::validate_session(const ML::Money&a, const ML::Money& b) {
	if (&a.session() != &b.session()) {
		throw std::runtime_error("Monetary_math session mismatch");
	}
	ML::validate_session(a);
}
