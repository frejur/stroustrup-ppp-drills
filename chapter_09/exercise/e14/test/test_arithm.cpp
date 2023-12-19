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

	Money m{ s.new_money() };
	test_op_arithm_add(s, m, m, m);

	{	Money m_a{ s.new_money(297) };
		Money m_b{ s.new_money(654) };
		Money result{ s.new_money(297+654) };
		test_op_arithm_add(s, m_a, m_b, result);
	}

	{	Money m_a{ s.new_money(0, Currency_ID::EUR) };
		Money m_b{ s.new_money(100, Currency_ID::USD) };
		Money expected{ s.new_money(
			static_cast<long>(
				(xrate_eur.xrate * 100 * 10 + 5) / 10),
			Currency_ID::EUR)
		};
		test_op_arithm_add(s, m_a, m_b, expected);
	}

	{	Money m_a{ s.new_money(0, Currency_ID::EUR) };
		Money m_b{ s.new_money(2700, Currency_ID::USD) };
		Money expected{ s.new_money( 2472, Currency_ID::EUR) };
		test_op_arithm_add(s, m_a, m_b, expected);
	}
	// Test addition
	// Same currency
	// Different currency

	// Test subtraction
	// Same currency
	// Different currency

	// Test division
	// Same currency
	// Different currency
	// Floating-point division

	// Test multiplication
	// Floating-point multiplication
}



void test_op_arithm_add(Monetary_math_session& s, Money a, Money b,
                        Money expected)
{
	try {
		std::cout
			<< "Calculating " << a.amount() << " " << a.currency().symbol
			<< " + " << b.amount() << " " << b.currency().symbol << "... ";
		Money result{ a + b };
		if (result.amount() != expected.amount() ||
		    result.currency().id != expected.currency().id) {
			throw std::runtime_error(
				"Expected " + std::to_string(expected.amount()) + " " +
				expected.currency().symbol + " but got " +
				std::to_string(result.amount()) + " " +
				result.currency().symbol);
		}
	}
	catch (std::exception& e) {
		std::cout << "FAILED" << '\n';
		throw e;
	}
	catch (...) {
		std::cout << "FAILED" << '\n';
		throw std::runtime_error("Unknown error");
	}
	std::cout << "PASSED" << '\n';
}
