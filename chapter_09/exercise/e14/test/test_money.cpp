#include "test.h"

using namespace Money_lib;

void test_money()
{
	Monetary_math_session s{ test_mmath_init_session() };
	s.deactivate();
	test_money_exp_failure(s);
	s.reset();


	Monetary_math_session s2{ test_mmath_init_session() };
	Money m1{ test_money_exp_success(s) };
	Money m2{ test_money_exp_success(s2) };
	test_money_validate_session_exp_success(
		m1, m1,
		"Validating sessions"
	);
	test_money_validate_session_exp_failure(
		m1, m2,
		"Attempting to validate mismatching sessions"
	);
	s.deactivate();
	test_money_validate_session_exp_failure(
		m1, m1,
		"Attempting to validate inactive session"
	);
}

void test_money_exp_failure(Monetary_math_session& s)
{
	std::cout << "Attempting to add Money to an inactive session... ";
	try {
		Money m{ s.new_money() };
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

Money test_money_exp_success(Monetary_math_session& s)
{
	std::cout << "Adding Money...";
	try {
		Money m{ s.new_money() };
		std::cout << "PASSED" << '\n';
		return m;
	}
	catch (std::exception& e) {
		std::cout << "FAILED" << '\n';
		throw e;
	}
	catch (...) {
		std::cout << "FAILED" << '\n';
		throw std::runtime_error("Unknown error");
	}
}

void test_money_validate_session_exp_failure(Money a, Money b,
                                             const std::string& description)
{
	std::cout << description << "... ";
	try {

		validate_session(a, b);
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

void test_money_validate_session_exp_success(Money a, Money b,
                                             const std::string& description)
{
	std::cout << description << "... ";
	try {
		validate_session(a, b);
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
