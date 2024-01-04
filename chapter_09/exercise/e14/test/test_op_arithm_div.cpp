#include "test.h"

using namespace Money_lib;

void test_op_arithm_div(Monetary_math_session& s,
                        long a, Money_lib::Currency_ID id_a,
                        long b, Money_lib::Currency_ID id_b,
                        long double expected)
{
	try {
		Money m_a{ s.new_money(a, id_a) };
		Money m_b{ s.new_money(b, id_b) };
		std::cout
			<< "Calculating " << a << " / " << b << "... ";
		long double result{ m_a / m_b };
		if (result != expected) {
			throw std::runtime_error(
				"Expected " + std::to_string(expected) + " " +
				" but got " +
				std::to_string(result)
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

void test_op_arithm_div(Monetary_math_session& s, long a, long b,
                        long double expected)
{
	Money m_a{ s.new_money(a) };
	Money m_b{ s.new_money(b) };
	test_op_arithm_div(s, m_a.amount(), m_a.currency().id, m_b.amount(),
	                   m_b.currency().id, expected);
}

void test_op_arithm_div(Monetary_math_session& s, Money m_a, Money m_b,
                        long double expected)
{
	test_op_arithm_div(s, m_a.amount(), m_a.currency().id, m_b.amount(),
	                   m_b.currency().id, expected);
}

void test_op_arithm_div(Monetary_math_session& s, long amount, Currency_ID id,
                        long double denominator, long expected_amount)
{
	try {
		Money m_a{ s.new_money(amount, id) };
		std::cout
			<< "Calculating " << m_a << " / " << denominator << "... ";
		Money result{ m_a / denominator };
		Money_lib::Currency_ID expected_id{ result.currency().id };
		if (result.amount() != expected_amount ||
		    result.currency().id != expected_id) {
			throw std::runtime_error(
				"Expected " + std::to_string(expected_amount / 100.0) + " " +
				m_a.currency().symbol + " but got " +
				std::to_string(result.as_floating_point()) + " " +
				result.currency().symbol
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

