#include "test_interactive.h"
namespace ML = Money_lib;
namespace MLH = Money_lib_helpers;
using PA_Type = Parser_Action_Type;

// Print stuff -----------------------------------------------------------------
void print_intro() {
	std::cout <<
		"Enter an expression. (Type '" << Key_help << "' for more info or"
		" '" << Key_quit <<"' to exit)" << '\n' <<
		"Example:" " '1 USD + 2 EUR'" << '\n';
}

void print_more_info() {
	std::cout <<
		"The parser support expressions in the following format:" << '\n' <<
		"  Value Currency(Optional) Operator Value Currency(Optional)" << '\n';

	std::cout << '\n';

	std::cout <<
		"     Value: " "A floating-point value" << '\n' <<
		"  Currency: " "A three-character code, type '" << Key_currencies <<
		             "' to list available currencies." << '\n' <<
		"  Operator: " "Type '" << Key_operators << '\'' << '\n';

	std::cout << '\n';

	std::cout <<
		"The Currency is optional to allow for expressions such as:" << "\n"
		"  1 USD * 2" << '\n';
}

void print_currencies(const ML::Monetary_math_session& session) {
	std::cout << "Available currencies: " << '\n';
	for (const std::string& s: session.get_currency_list()) {
		std::cout << "  " << s << '\n';
	}
}

void print_operators() {
	std::cout
		<< "Available operators: " << '\n';
	bool is_first{ true };
	for (const ML::Money_Operator& op: ML::Money_Operators) {
		std::cout << (is_first ? "  " : ", ") << op.symbol;
		is_first = false;
	}
	std::cout << '\n';
}

// Istream manipulation ---------------------------------------------------------

void clear_buffer(std::istream& is)
{
	for (char temp{};
	     is.get(temp) && temp != '\n';
	     ) { /* Repeat until newline */ }
}

std::string string_until_newline(std::istream& is) {
	std::string s;
	for (char temp{};
	     is.get(temp) && temp != '\n';
	     s += temp) { /* Repeat until newline */ }
	return s + '\n';
}

void putback_string(const std::string& s, std::istream& is)
{
	for (int i = s.size(); i > 0; --i) {
		is.putback(s[i-1]);
	}
}

//------------------------------------------------------------------------------

void setup_session(ML::Monetary_math_session& s) {
	const ML::Currency cur_eur{
		ML::Currency_ID::EUR, "Euros", "EUR"
	};
	const ML::Currency cur_yen{
		ML::Currency_ID::JPY, "Japanese Yen", "JPY"
	};
	const double xrate_eur{ 0.915724 };
	const double xrate_yen{ 142.496 };
	s.add_currency(cur_eur);
	s.add_currency(cur_yen);
	s.add_exchange_rate(ML::DEFAULT_CURRENCY().id, cur_eur.id, xrate_eur);
	s.add_exchange_rate(ML::DEFAULT_CURRENCY().id, cur_yen.id, xrate_yen);

	// EUR <-> JPY
	long long xrate_yen_ll{ static_cast<long long>(
		MLH::XRATE_FACTOR() * xrate_yen) };
	double xrate_eur_yen{ static_cast<double>(
		xrate_yen_ll / xrate_eur / MLH::XRATE_FACTOR()) };
	s.add_exchange_rate(cur_eur.id, cur_yen.id, xrate_eur_yen);
}

//------------------------------------------------------------------------------
int word_count(const std::string& s, int max) {
	int count = 0;
	if (s.size() == 0 || max < 1) {
		return count;
	}
	bool prev_char_is_space = true;
	bool current_char_is_space = true;
	for (char c: s) {
		current_char_is_space = isspace(c);
		if (prev_char_is_space && !current_char_is_space) {
			++count;
			if (count == max) {
				break;
			}
		}
		prev_char_is_space = current_char_is_space;
	}
	return count;
}

ML::Money_Operator get_operator_by_symbol(const std::string& s) {
	ML::Money_Operator final_op{ ML::Money_Operator_ID::Not_an_operator };
	for (const ML::Money_Operator& op: ML::Money_Operators) {
		if (op.symbol == s) {
			final_op = op;
			break;
		}
	}
	return final_op;
}

void Money_Expression::parse_money_money() {
	expr_t = Money_Expression_Type::Money_Money;
	reset();

	try {
		if (!istr) {
			error = "The input stream is in a bad state";
			return;
		}

		std::string str_op_error; // Store error message if exception is thrown
		try {
			istr >> money_a;
		} catch (const std::exception& e) { str_op_error = e.what(); }

		if (!istr) {
			error = "Invalid input, expected a floating-point value followed by"
					" a currency. ";
			error += (str_op_error.size() ? "\n" : "") + str_op_error;
			return;
		}

		std::string symbol;
		istr >> symbol;
		if (!istr) {
			error = "Invalid input, expected a string";
			return;
		}

		op = get_operator_by_symbol(symbol);
		if (op.id == ML::Money_Operator_ID::Not_an_operator) {
			error = "Invalid input, expected an operator";
			return;
		}

		str_op_error = "";
		try {
			istr >> money_b;
		} catch (const std::exception& e) { str_op_error = e.what(); }
		if (!istr) {
			error = "Invalid input, expected a floating-point value followed by"
					" a currency.";
			error += (str_op_error.size() ? "\n" : "") + str_op_error;
			return;
		}
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		error = e.what();
	}
	catch (...) {
		error = "Unknown error";
	}

	parse_success = true;
	clear_buffer(istr);
}

void Money_Expression::parse_money_value(bool reverse) {
	expr_t = Money_Expression_Type::Money_Value;
	reset();

	static std::string error_money{ "Invalid input, expected a floating-point "
	                                "value followed by a currency" };
	static std::string error_value{ "Invalid input, expected a floating-point "
	                                "value" };

	try {
		if (!istr) {
			error = "The input stream is in a bad state";
			return;
		}
		std::string str_op_error; // Store error message if exception is thrown

		if (!reverse) {
			try {
				istr >> money_a;
			} catch (const std::exception& e) { str_op_error = e.what(); }

			if (!istr) {
				error = error_money;
				error += (str_op_error.size() ? "\n" : "") + str_op_error;
				return;
			}
		} else {
			istr >> val;
			if (!istr) {
				error = error_value;
				return;
			}
		}

		std::string symbol;
		istr >> symbol;
		if (!istr) {
			error = "Invalid input, expected a string";
			return;
		}

		op = get_operator_by_symbol(symbol);
		if (op.id == ML::Money_Operator_ID::Not_an_operator) {
			error = "Invalid input, expected an operator";
			return;
		}

		if (!reverse) {
			istr >> val;
			if (!istr) {
				error = error_value;
				return;
			}
		} else {
			str_op_error = "";
			try {
				istr >> money_a;
			} catch (const std::exception& e) { str_op_error = e.what(); }

			if (!istr) {
				error = error_money;
				error += (str_op_error.size() ? "\n" : "") + str_op_error;
				return;
			}
		}
	}
	catch (const std::exception& e) {
		error = e.what();
	}
	catch (...) {
		error = "Unknown error";
	}

	reverse_terms = reverse ? true : false;
	parse_success = true;
	clear_buffer(istr);
}

void Money_Expression::evaluate()
{
	eval_success = false;
	if (!parse_success) {
		error = "Cannot evaluate before parsing";
		return;
	}
	if (op.id == ML::Money_Operator_ID::Not_an_operator) {
		error = "Not an operator";
		return;
	}

	error = "";
	try {
		if (expr_t == Money_Expression_Type::Money_Money) {
			switch (op.id) {
			case ML::Money_Operator_ID::Addition:
				result_t = Money_Result_Type::Money;
				update_result(money_a + money_b);
				break;
			case ML::Money_Operator_ID::Subtraction:
				result_t = Money_Result_Type::Money;
				update_result(money_a - money_b);
				break;
			case ML::Money_Operator_ID::Division:
				result_t = Money_Result_Type::Decimal_Number;
				result_val = money_a / money_b;
				break;
			case ML::Money_Operator_ID::Less_than:
				result_t = Money_Result_Type::Boolean;
				result_comp = money_a < money_b;
				break;
			case ML::Money_Operator_ID::Less_than_or_equal_to:
				result_t = Money_Result_Type::Boolean;
				result_comp = money_a <= money_b;
				break;
			case ML::Money_Operator_ID::Equal_to:
				result_t = Money_Result_Type::Boolean;
				result_comp = money_a == money_b;
				break;
			case ML::Money_Operator_ID::Not_equal_to:
				result_t = Money_Result_Type::Boolean;
				result_comp = money_a != money_b;
				break;
			case ML::Money_Operator_ID::Greater_than_or_equal_to:
				result_t = Money_Result_Type::Boolean;
				result_comp = money_a >= money_b;
				break;
			case ML::Money_Operator_ID::Greater_than:
				result_t = Money_Result_Type::Boolean;
				result_comp = money_a > money_b;
				break;
			case ML::Money_Operator_ID::Multiplication:
				error = "Cannot multiply Money by Money";
				return; // exit
				break;
			default:
				error = "Unknown operation";
				return;
			}
		} else {
			switch (op.id) {
			case ML::Money_Operator_ID::Multiplication:
				result_t = Money_Result_Type::Money;
				update_result(money_a * val);
				break;
			case ML::Money_Operator_ID::Division:
				if (reverse_terms) {
					error = "Cannot divide a decimal value by Money";
					return;
				}
				result_t = Money_Result_Type::Money;
				update_result(money_a / val);
				break;
			case ML::Money_Operator_ID::Addition:
			case ML::Money_Operator_ID::Subtraction:
				error = "Cannot add / subtract decimal values "
						"to / from Money";
				return;
				break;
			case ML::Money_Operator_ID::Less_than:
			case ML::Money_Operator_ID::Less_than_or_equal_to:
			case ML::Money_Operator_ID::Equal_to:
			case ML::Money_Operator_ID::Not_equal_to:
			case ML::Money_Operator_ID::Greater_than_or_equal_to:
			case ML::Money_Operator_ID::Greater_than:
				error = "Cannot compare decimal values to Money";
				break;
			default:
				error = "Unknown operation";
				return;
			}
		}
	}
	catch (const std::exception& e) {
		error = e.what();
		return;
	}
	catch (...) {
		error = "Unknown errror";
		return;
	}

	eval_success = true;
}

void Money_Expression::update_result(const Money_lib::Money& m)
{
	// A bit hacky, but the book hasn't covered copy constructors so far
	result_money_amt = m.amount();
	result_money_cur = m.currency();
}

//------------------------------------------------------------------------------
Parser_Action get_action(const std::string& input) {
	Parser_Action a{};
	try {
		if (input == Key_help + "\n") {
			a.type = PA_Type::Print_instructions;
		} else if (input == Key_quit + "\n") {
			a.type = PA_Type::Quit;
		} else if (input == Key_currencies + "\n") {
			a.type = PA_Type::List_currencies;
		} else if (input == Key_operators + "\n") {
			a.type = PA_Type::List_operators;
		} else {
			a.buffer = input;
		}
	} catch (...) {
        throw std::runtime_error("Invalid input");
	}
	return a;
}

void test_interactive()
{
	ML::Monetary_math_session s{};
	setup_session(s);
	print_intro();

	std::istream& istr{ std::cin };

	Money_Expression expr{ s, istr };

	bool stop{};
	while (!stop) {
		s.reset();
		expr.reset();

		std::cout << Symbol_prompt;

		// Line based input is desired, but the book has not covered getline()
		std::string input{ string_until_newline(istr) };

		// 'Words' are counted, to perform either:
		// a. Parsing and evaluation of expressions consisting of 5 or 4 terms
		// b. A single keyword action
		int words{ word_count(input, 5) };

		if (words == 5 || words == 4) {
			// The line read earlier has to be put back and std::cin used for
			// input to use the >> operator. (The book has not covered
			// stringstreams yet).
			putback_string(input, istr);

			if (words == 5) {
				expr.parse_money_money();
			} else {
				expr.parse_money_value();
				if (!expr.is_parsed()) {
					istr.clear();
					clear_buffer(istr);
					putback_string(input, istr);
					s.reset();
					expr.reset();
					expr.parse_money_value(true); // Try reversing
				}
			}

			if (!expr.is_parsed()) {
				istr.clear();
				clear_buffer(istr);
				std::cout << "Could not parse expression:" << '\n' <<
					expr.error_message() << '\n';
				continue;
			}

			expr.evaluate();
			if (!expr.is_evaluated()) {
				std::cout << "The expression failed to evaluate:" << '\n' <<
					expr.error_message() << '\n';
				continue;
			}

			std::cout << " = ";
			switch (expr.result_type()) {
			case Money_Result_Type::Money:
				std::cout << expr.result_as_money() << '\n';
				break;
			case Money_Result_Type::Decimal_Number:
				std::cout << expr.result_as_decimal_number() << '\n';
				break;
			case Money_Result_Type::Boolean:
				std::cout << expr.result_as_true_or_false() << '\n';
				break;
			}
		} else if (words == 1) {
			Parser_Action a { get_action(input) };
			switch (a.type) {
			case PA_Type::Quit:
				std::cout << "Bye!" << '\n';
				stop = true;
				break;
			case PA_Type::Print_instructions:
				print_more_info();
				break;
			case PA_Type::List_currencies:
				print_currencies(s);
				break;
			case PA_Type::List_operators:
				print_operators();
				break;
			case PA_Type::Unknown:
			default:
				std::cout << "Unknown action..." << '\n';
				break;
			}
		} else {
			std::cout << "Invalid input" << '\n';
		}
	}
}
