#ifndef NARROW_CAST_H
#define NARROW_CAST_H
#include <stdexcept>

// (Extracted from stdlibfacilities.h)

// run-time checked narrowing cast (type conversion). See ???.
template<class R, class A> R narrow_cast(const A& a)
{
	R r = R(a);
	if (A(r) != a) {
		throw std::runtime_error("info loss");
	}
	return r;
}

#endif // NARROW_CAST_H
