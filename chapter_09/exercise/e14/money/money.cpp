#include "money.h"
#include <stdexcept>

namespace ML = Money_lib;

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

double ML::operator/(ML::Money& a, const ML::Money& b) {
	try {
		if (b.amount() == 0) {
			throw std::runtime_error("Cannot divide by zero");
		}
		ML::validate_session(a, b);
		if (a.currency().id != b.currency().id) {
			long conv_amt{ convert_currency_amt(b.amount(), b.currency().id,
						   a.currency().id, a.session()) };
			return a.amount() / static_cast<double>(conv_amt);
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
		long p {
			static_cast<long>(((a.amount() * 10) * b + 5) / 10)
		};
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
		if (a.currency().id != b.currency().id) {
			long conv_amt{ convert_currency_amt(b.amount(), a.currency().id,
						   b.currency().id, a.session()) };
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
			long conv_amt{ convert_currency_amt(b.amount(), a.currency().id,
						   b.currency().id, a.session()) };
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
	return ML::operator>(a, b) || ML::operator==(a, b);
}

bool ML::operator>(ML::Money& a, const ML::Money& b) {
	return !ML::operator<(a, b) && ML::operator!=(a, b);
}

bool ML::operator>=(ML::Money& a, const ML::Money& b) {
	return !ML::operator<(a, b) || ML::operator==(a, b);
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
