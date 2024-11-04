#ifndef EXCHANGERATE_H
#define EXCHANGERATE_H
#include "moneyhelpers.h"

namespace Exchange_rate_lib { // -----------------------------------------------

class Exchange_rate
{
public:
	Exchange_rate() {};
	Exchange_rate(long double xrate);

	// Calculates the cross rate
	Exchange_rate(const Exchange_rate use_as_base,
	              const Exchange_rate use_as_counter);

	long double value() const;
	long long as_integer() const;
	int scale_factor() const;
	void flip_currencies();
private:
	int whole{ 1 };
	long long fract{ 0 };
	int exp{ 0 };
	void update(long double xrate);
	void update(int whole_num, long long fract_num, int fract_exp) {
		whole = whole_num;
		fract = fract_num;
		exp = fract_exp;
	};
};

long operator*(Exchange_rate xrate, long f);

} // namespace Exchange_rate_lib -----------------------------------------------

#endif // EXCHANGERATE_H
