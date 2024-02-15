#include "test.h"

using namespace Money_lib;

void test_op_arithm() {
	// Assumes the default currency is USD
	Monetary_math_session s{ test_mmath_init_session() };
	const Currency cur_eur{ Currency_ID::EUR, "Euros", "EUR" };
	const Currency cur_yen{ Currency_ID::JPY, "Japanese Yen", "JPY" };
	const double xrate_eur{ 0.915724 };
	const double xrate_yen{ 142.496 };
	s.add_currency(cur_eur);
	s.add_currency(cur_yen);
	s.add_exchange_rate(DEFAULT_CURRENCY().id, cur_eur.id, xrate_eur);
	s.add_exchange_rate(DEFAULT_CURRENCY().id, cur_yen.id, xrate_yen);

	// Addition
	Money m{ s.new_money() };
	test_op_arithm_add(s, m, m, m);

	test_op_arithm_add(s, 297, 654, 297 + 654);

	test_op_arithm_add(s, 0, Currency_ID::EUR, 100, Currency_ID::USD,
	                   static_cast<long>((xrate_eur * 100 * 10 + 5) / 10),
	                   cur_eur);
	test_op_arithm_add(s, 0, Currency_ID::JPY, 2700, Currency_ID::USD,
	                   static_cast<long>(
	                       (xrate_yen * 2700 * 10 + 5) / 10
	                   ),
	                   cur_yen);

	// Subtraction
	Money m2{ s.new_money() };
	test_op_arithm_sub(s, m, m, m);

	test_op_arithm_sub(s, -133, 7, -140);

	test_op_arithm_sub(s, 1100, Currency_ID::EUR, 100, Currency_ID::USD,
	                   1100 -
	                   static_cast<long>((xrate_eur * 100 * 10 + 5) / 10),
	                   cur_eur);
	test_op_arithm_sub(s, 7999, Currency_ID::EUR, 2353, Currency_ID::USD,
	                   7999 -
	                   static_cast<long>(
	                       (xrate_eur * 2353 * 10 + 5) / 10
	                   ),
	                   cur_eur);

	// Division by Money of the same currency
	Money m3{ s.new_money(1234) };
	test_op_arithm_div(s, m3, m3, 1);
	Money m4{ s.new_money(2) };
	test_op_arithm_div(s, m3, m4, 617);
	Money m5{ s.new_money(-8889) };
	test_op_arithm_div(s, m5, m4, -4444.5);
	Money m6{ s.new_money(-4) };
	test_op_arithm_div(s, m5, m6, 2222.25);
	Money m7{ s.new_money(1, Currency_ID::JPY) }; /* Should equal zero when
	                                               * converted to USD */
	test_op_arithm_div_by_zero(s, m6, m7);
	s.reset();

	// Division by Money of different currency
	Money m8{ s.new_money(100) };
	Money m9{ s.new_money((xrate_eur * 1000 + 5) / 10, Currency_ID::EUR) };
	test_op_arithm_div(s, m8, m9, 1);
	Money m10{ s.new_money(-200) };
	Money m11{ s.new_money((xrate_yen * 1000 + 5) / 10, Currency_ID::JPY) };
	test_op_arithm_div(s, m10, m11, -2);

	// Division by non-monetary number
	test_op_arithm_div(s, 1, Currency_ID::USD, 3, 0);
	test_op_arithm_div(s, 1000, Currency_ID::EUR, 2, 500);
	test_op_arithm_div(s, -10, Currency_ID::JPY, -0.5, 20);
	test_op_arithm_div_by_zero(s);
	s.reset();

	// Multiplication
	test_op_arithm_mult(s, 50, Currency_ID::USD, 2, 100);
	test_op_arithm_mult(s, 1, Currency_ID::EUR, 0.49, 0);
	test_op_arithm_mult(s, 333, Currency_ID::JPY, 3.001, 999);
}


