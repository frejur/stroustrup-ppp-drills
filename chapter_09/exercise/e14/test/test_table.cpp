#include "test.h"

using namespace Money_lib;

void test_table()
{
	// Assumes there are at least two defined Currency IDs in addition to
	// 'Not_a_currency' which starts off the enum, at index -1
	Monetary_math_session s{ test_mmath_init_session() };

	Currency_ID na_c{ static_cast<Currency_ID>(-1) };
	test_table_add_exp_failure(
		s, { na_c, DEFAULT_CURRENCY().id, 1.0 },
	    "Attempting to add a Currency pair where base is Not a currency"
	);
	s.reset();
	test_table_add_exp_failure(
		s, { DEFAULT_CURRENCY().id, na_c, 1.0 },
	    "Attempting to add a Currency pair where counter is Not a currency"
	);
	s.reset();
	test_table_add_exp_failure(
		s, { DEFAULT_CURRENCY().id, DEFAULT_CURRENCY().id, 1.0 },
	    "Attempting to add a Currency pair where base is identical to counter"
	);
	s.reset();

	Currency_ID id_a{ static_cast<Currency_ID>(0) };
	Currency_ID id_b{ static_cast<Currency_ID>(1) };
	test_table_add_exp_success( s, {id_a, id_b, 1.0}, "Adding Currency pair");

	test_table_add_exp_failure(
		s, { id_a, id_b, 1.0 },
	    "Attempting to add a duplicate Currency pair, same order"
	);
	s.reset();
	test_table_add_exp_failure(
		s, { id_b, id_a, 1.0 },
	    "Attempting to add a duplicate Currency pair, reversed order"
	);
	s.reset();

	Monetary_math_session s2{ test_mmath_init_session() };
	test_table_add_exp_failure(
		s2, { id_b, id_a, 0 },
	    "Attempting to add an exchange rate that is zero"
	);
	s.reset();

	Monetary_math_session s3{ test_mmath_init_session() };
	test_table_add_exp_failure(
		s3, { id_b, id_a, -1.23 },
	    "Attempting to add an exchange rate that is less than zero"
	);
	s.reset();
}


void test_table_add_exp_failure(Monetary_math_session& s, Currency_pair p,
                                const std::string& description)
{
	std::cout << description << "... ";
	try {
		s.add_exchange_rate(p.base, p.counter, p.xrate);
	}
	catch (std::exception& e) {
		std::cout << "PASSED" << '\n';
		std::cout << "  Function threw exception as expected:" << '\n';
		std::cout << "    \"" << e.what() << '"' << '\n';
		return;
	}
	catch (...) {
		std::cout << "FAILED" << '\n';
		throw std::runtime_error("Unknown error");
	}
	std::cout << "FAILED" << '\n';
	throw std::runtime_error("Expected an exception to be thrown");
}

void test_table_add_exp_success(Monetary_math_session& s, Currency_pair p,
                                const std::string& description)
{
	std::cout << description << "... ";
	try {
		s.add_exchange_rate(p.base, p.counter, p.xrate);
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
