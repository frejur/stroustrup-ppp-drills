#include "test.h"

using namespace Money_lib;

void test_op_arithm_sub(Monetary_math_session& s,
                        long a, Money_lib::Currency_ID id_a,
                        long b, Money_lib::Currency_ID id_b,
                        long expected, Money_lib::Currency expected_cur)
{
	try {
		Money m_a{ s.new_money(a, id_a) };
		Money m_b{ s.new_money(b, id_b) };
		std::cout
			<< "Calculating " << a << " - " << b << "... ";
		Money result{ m_a - m_b };
		if ((result.amount() != expected) ||
		    (result.currency().id != expected_cur.id))
		{
			throw std::runtime_error(
				"Expected " + std::to_string(expected / 100.0) + " " +
				expected_cur.symbol + " but got " +
				std::to_string(result.as_floating_point()) + " " +
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

void test_op_arithm_sub(Monetary_math_session& s, long a, long b, long expected)
{
	Money m_a{ s.new_money(a) };
	Money m_b{ s.new_money(b) };
	Money m_expected{ s.new_money(expected) };
	test_op_arithm_sub(s, m_a.amount(), m_a.currency().id,
	                   m_b.amount(), m_b.currency().id,
	                   m_expected.amount(), m_expected.currency());
}

void test_op_arithm_sub(Monetary_math_session& s, Money m_a, Money m_b,
                        Money m_expected)
{
	test_op_arithm_sub(s, m_a.amount(), m_a.currency().id,
	                   m_b.amount(), m_b.currency().id,
	                   m_expected.amount(), m_expected.currency());
}
