#include "test.h"
using namespace Money_lib;

void test_op_arithm_mult(Monetary_math_session& s, long amount, Currency_ID id,
                         long double factor, long expected_amount)
{
	try {
		Money m{ s.new_money(amount, id) };
		std::cout
			<< "Calculating " << m << " * " << factor << "... ";
		Money result_a{ m * factor };
		Money result_b{ factor * m };
		Money_lib::Currency_ID expected_id_a{ result_a.currency().id };
		Money_lib::Currency_ID expected_id_b{ result_b.currency().id };
		if (result_a.amount() != expected_amount ||
		    result_a.currency().id != id) {
			throw std::runtime_error(
				"Expected " + std::to_string(expected_amount / 100.0) + " " +
				m.currency().symbol + " but got " +
				std::to_string(result_a.as_floating_point()) + " " +
				result_a.currency().symbol
			);
		}
		if (result_b.amount() != expected_amount ||
		    result_b.currency().id != id) {
			throw std::runtime_error(
				"Expected " + std::to_string(expected_amount / 100.0) + " " +
				m.currency().symbol + " but got " +
				std::to_string(result_b.as_floating_point()) + " " +
				result_b.currency().symbol
			);
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
