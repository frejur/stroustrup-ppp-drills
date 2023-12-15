#ifndef RATIONAL_H
#define RATIONAL_H

namespace RAT{ // --------------------------------------------------------------

class Rational
{
public:
	Rational();
	Rational(long p, long q);

	double to_double() const;

	long get_p() const { return p; };
	long get_q() const { return q; };
	void make_simple(); // Divide by greatest common divisor
private:
	long p; // nominator
	long q; // denominator
};

// -----------------------------------------------------------------------------

long greatest_common_divisor(long p, long q);

// -----------------------------------------------------------------------------

Rational operator+(const Rational& a, const Rational& b);
Rational operator-(const Rational& a, const Rational& b);
Rational operator*(const Rational& a, const Rational& b);
Rational operator/(const Rational& a, const Rational& b);

const bool operator==(const Rational& a, const Rational& b);
const bool operator!=(const Rational& a, const Rational& b);

} // namespace RAT -------------------------------------------------------------

#endif // RATIONAL_H
