#include "test.h"

using namespace Money_lib;

void test_op_arithm() {
	// Assumes the default currency is USD
	Monetary_math_session s{ test_mmath_init_session() };
	const Currency cur_eur{ Currency_ID::EUR, "Euros", "EUR" };
	const Currency cur_yen{ Currency_ID::JPY, "Japanese Yen", "JPY" };
	const Currency_pair xrate_eur{
		Currency_ID::USD, Currency_ID::EUR, 0.91572436
	};
	const Currency_pair xrate_yen{
		Currency_ID::USD, Currency_ID::JPY, 142.49671
	};
	s.add_currency(cur_eur);
	s.add_currency(cur_yen);
	s.add_exchange_rate(xrate_eur.base, xrate_eur.counter, xrate_eur.xrate);
	s.add_exchange_rate(xrate_yen.base, xrate_yen.counter, xrate_yen.xrate);

	// Addition
	Money m{ s.new_money() };
	test_op_arithm_add(s, m, m, m);

	test_op_arithm_add(s, 297, 654, 297 + 654);

	test_op_arithm_add(s, 0, Currency_ID::EUR, 100, Currency_ID::USD,
	                   static_cast<long>((xrate_eur.xrate * 100 * 10 + 5) / 10),
	                   cur_eur);
	test_op_arithm_add(s, 0, Currency_ID::EUR, 2700, Currency_ID::USD,
	                   2472, cur_eur);

	// Subtraction
	Money m2{ s.new_money() };
	test_op_arithm_sub(s, m, m, m);

	test_op_arithm_sub(s, -133, 7, -140);

	test_op_arithm_sub(s, 1100, Currency_ID::EUR, 100, Currency_ID::USD,
	                   1100 -
	                   static_cast<long>((xrate_eur.xrate * 100 * 10 + 5) / 10),
	                   cur_eur);
	test_op_arithm_sub(s, 7999, Currency_ID::EUR, 2353, Currency_ID::USD,
	                   7999 -
	                   static_cast<long>(
	                       (xrate_eur.xrate * 2353 * 10 + 5) / 10
	                   ),
	                   cur_eur);

	// Division
	Money m3{ s.new_money(1) };
	// test_op_arithm_div(s, m, m, m);
	// Same currency
	// Different currency
	// Floating-point division

	// Test multiplication
	// Floating-point multiplication
}


