#include "rational.h"
#include <stdexcept>

RAT::Rational::Rational() : Rational(0, 1) {}

RAT::Rational::Rational(long pp, long qq) : p{ pp }, q{ qq }
{
	if (q == 0) {
		throw std::runtime_error("Denominator must not be zero");
	}
	make_simple();
}

// -----------------------------------------------------------------------------

double RAT::Rational::to_double() const
{
	return static_cast<double>(p) / static_cast<double>(q);
}

// -----------------------------------------------------------------------------

void RAT::Rational::make_simple() {
	const long gcd{ greatest_common_divisor(p, q) };

	// Swap signs if denominator is negative...
	// This is more predictable as we always end up with either:
	//      A. p > 0 && q > 0
	// or:  B. p < 0 && q > 0
	if (q < 0) {
		p = -p;
		q = -q;
	}

	p /= gcd;
	q /= gcd;
}

long RAT::greatest_common_divisor(long p, long q) {
	// Euclid's algorithm
	int rem = 0;
	while ((rem = p % q) != 0) {
		p = q;
		q = rem;
	}
	return (q < 0) ? -q : q;
}

// -----------------------------------------------------------------------------

RAT::Rational RAT::operator*(const Rational &a, const Rational &b)
{
	RAT::Rational r{a.get_p() * b.get_p(), a.get_q() * b.get_q() };
	r.make_simple();
	return r;
}

RAT::Rational RAT::operator/(const Rational &a, const Rational &b)
{
	if (b.get_q() == 0) {
		throw std::runtime_error("Cannot divide by zero");
	}
	return a * RAT::Rational(b.get_q(), b.get_p());
}
RAT::Rational RAT::operator+(const Rational &a, const Rational &b)
{
	RAT::Rational r =
		(a.get_q() == b.get_q())
		? RAT::Rational{ a.get_p() + b.get_p(), a.get_q() }
		: RAT::Rational{ a.get_p() * b.get_q() + b.get_p() * a.get_q(),
		                 a.get_q() * b.get_q() };
	r.make_simple();
	return r;
}

RAT::Rational RAT::operator-(const Rational &a, const Rational &b)
{
	RAT::Rational r =
		(a.get_q() == b.get_q())
		? RAT::Rational{ a.get_p() - b.get_p(), a.get_q() }
		: RAT::Rational{ a.get_p() * b.get_q() - b.get_p() * a.get_q(),
		                 a.get_q() * b.get_q() };
	r.make_simple();
	return r;
}

const bool RAT::operator==(const Rational &a, const Rational &b)
{
	return (a.get_p() == b.get_p()) && (a.get_q() == b.get_q());
}

const bool RAT::operator!=(const Rational &a, const Rational &b) {
	return !RAT::operator==(a, b);
}

