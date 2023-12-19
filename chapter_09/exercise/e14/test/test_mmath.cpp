#include "test.h"

using namespace Money_lib;

void test_mmath()
{
	Monetary_math_session s{ test_mmath_init_session() };

	test_mmath_get_currency_exp_failure(s);
	s.reset();

	test_mmath_add_currency(s);
	s.reset();

	test_new_money(s);
}

Monetary_math_session test_mmath_init_session() {
	try {
		// Initialize session
		std::cout << "Initializing session... ";
		Monetary_math_session ss{};
		std::cout << "PASSED" << '\n';
		return ss;
	}
	catch (std::exception& e) {
		std::cout << "FAILED" << '\n';
		throw e;
	}
	catch (...) {
		std::cout << "FAILED" << '\n';
		throw std::runtime_error("Unknown error");
	}
	return {};
}

void test_mmath_get_currency_exp_failure(Monetary_math_session& s) {
	// Invalid ID
	std::cout << "Attempting to get invalid currency... ";
	try {
		Currency c{ s.session().get_currency(Currency_ID::Not_a_currency) };
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

Currency test_mmath_get_currency_exp_success(Monetary_math_session& s,
                                             Currency_ID id) {
	// Invalid ID
	Currency c;
	std::cout
		<< "Getting currency for index " << static_cast<int>(id) << "... ";
	try {
		c = s.session().get_currency(id);
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
	return c;
}

void test_mmath_add_currency(Monetary_math_session& s) {
	// Assumes there are at least two defined Currency IDs in addition to
	// 'Not_a_currency' which starts off the enum, at index -1

	// Test for invalid input
	int step{ 1 };
	int num_steps{ 5 };
	while (step <= num_steps)
	try {
		if (step==1) {
			std::cout << "Attempting to add currency with an invalid ID... ";
			s.add_currency(Currency_ID::Not_a_currency, "Test", "TST");
		}
		if (step==2) {
			std::cout
				<< "Attempting to add currency with 'empty' symbol... ";
			s.add_currency(static_cast<Currency_ID>(1), "Test", "");
		}
		if (step==3) {
			std::cout
				<< "Attempting to add currency with an invalid symbol... ";
			s.add_currency(static_cast<Currency_ID>(1), "Test", "$");
		}
		if (step==4) {
			std::cout
				<< "Attempting to add currency with an invalid name... ";
			s.add_currency(static_cast<Currency_ID>(1), "\t", "TST");
		}
		if (step==5) {
			std::cout << "Attempting to add duplicate currency... ";
			s.add_currency(DEFAULT_CURRENCY());
		}
		throw 0; // reaching this points means one of the tests failed
	}
	catch (std::exception& e) {
		std::cout << "PASSED" << '\n';
		std::cout << "  Function threw exception as expected:" << '\n';
		std::cout << "    \"" << e.what() << '"' << '\n';
		++step;
		s.reset();
		continue;
	}
	catch (...) {
		std::cout << "FAILED" << '\n';
		throw std::runtime_error("Unknown error");
	}

	// Test trimmed name
	std::string name{ "Test name" };
	std::string ws_name{ "   " + name + "\t " };
	try {
		std::cout
			<< "Adding currency \"" << ws_name << "\" (Should be trimmed)... ";
		s.add_currency(static_cast<Currency_ID>(1), ws_name, "TST");
		std::string final_name{
			s.session().get_currency(static_cast<Currency_ID>(1)).name
		};
		if (name != final_name)
		{
			throw std::runtime_error("\"" + name + "\" is not equal to: \"" +
			                         final_name + "\"");
		}
		std::cout << "PASSED" << '\n';
		return;
	}
	catch (std::exception& e) {
		std::cout << "FAILED" << '\n';
		throw e;
	}
	catch (...) {
		std::cout << "FAILED" << '\n';
		throw std::runtime_error("Unknown error");
	}
	std::cout << "FAILED" << '\n';
	throw std::runtime_error("Expected an exception to be thrown");
}

void test_new_money(Money_lib::Monetary_math_session& s) {
	// Test for invalid input due to information loss
	int step{ 1 };
	int num_steps{ 3 };
	while (step <= num_steps)
	try {
		if (step==1) {
			double val{ 0.001 };
			std::cout << "Attempting to initialize Money with floating-point "
			             "value " << val << "... ";
			Money m{ s.new_combined_money(val) };
		}
		if (step==2) {
			double val{ -3.123 };
			std::cout << "Attempting to initialize Money with floating-point "
			             "value " << val << "... ";
			Money m{ s.new_combined_money(val) };
		}
		if (step==3) {
			double val{ 1/3.0 };
			std::cout << "Attempting to initialize Money with floating-point "
			             "value " << val << "... ";
			Money m{ s.new_combined_money(val) };
		}
		throw 0; // reaching this points means one of the tests failed
	}
	catch (std::exception& e) {
		std::cout << "PASSED" << '\n';
		std::cout << "  Function threw exception as expected:" << '\n';
		std::cout << "    \"" << e.what() << '"' << '\n';
		++step;
		s.reset();
		continue;
	}
	catch (...) {
		std::cout << "FAILED" << '\n';
		throw std::runtime_error("Unknown error");
	}

	s.reset();

	// Test add new Money
	long test_0{ 123456 };
	test_new_money_single(s, test_0);
	long test_1{ -99 };
	test_new_money_single(s, test_1);
	double test_2{ 25.55 };
	test_new_combined_money_single(s, test_2, 2555);
	double test_3{ -0.01 };
	test_new_combined_money_single(s, test_3, -1);
	long test_4{ 0 };
	test_new_money_single(s, test_4, 0);
	double test_5{ 0 };
	test_new_money_single(s, test_5, 0);
}

void test_new_money_single(Money_lib::Monetary_math_session& s,
                           const long value, const long expected)
{
	try {
		std::cout
			<< "Adding new Money: " << value << DEFAULT_CURRENCY().symbol
			<< "... ";
		Money m{ s.new_money(value) };
		if (m.amount() != expected) {
			throw std::runtime_error("Expected " + std::to_string(expected) +
			                         " but got " + std::to_string(m.amount()));
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

void test_new_money_single(Money_lib::Monetary_math_session& s,
                           const long value)
{
	test_new_money_single(s, value, value);
}

void test_new_combined_money_single(Money_lib::Monetary_math_session& s,
                                    const double value, const long expected)
{
	try {
		std::cout
			<< "Adding new Money: " << value << DEFAULT_CURRENCY().symbol
			<< "... ";
		Money m{ s.new_combined_money(value) };
		if (m.amount() != expected) {
			throw std::runtime_error("Expected " + std::to_string(expected) +
			                         " but got " + std::to_string(m.amount()));
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

