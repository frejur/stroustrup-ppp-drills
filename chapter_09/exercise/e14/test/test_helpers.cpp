#include "test.h"

using namespace Money_lib;
namespace MLH = Money_lib_helpers;

//------------------------------------------------------------------------------

Money new_conv_money(Monetary_math_session& s,
                         Money m_in,
                         const double xrate,
                         const Currency_ID id_out)
{
	long amt{ m_in.amount() };
	long new_amt{ 0 };
	if (amt != 0) {
		long long xrate_l{ static_cast<long long>(xrate * MLH::XRATE_FACTOR()) };
		long long f{ MLH::XRATE_FACTOR() / 10 };
		int sign = amt > 0 ? 1 : -1;
		long long temp{ (amt * xrate_l) / f + (sign * 5) };
		new_amt = static_cast<long>(temp / 10);
	}
	return s.new_money(new_amt, id_out);
}
