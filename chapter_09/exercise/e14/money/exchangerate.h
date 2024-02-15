#ifndef EXCHANGERATE_H
#define EXCHANGERATE_H
#include "moneyhelpers.h"

namespace Exchange_rate_lib { // -----------------------------------------------

class Exchange_rate
{
public:
	Exchange_rate() {};
	Exchange_rate(long double xrate);
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
