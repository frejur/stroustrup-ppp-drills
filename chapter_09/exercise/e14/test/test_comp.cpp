#include "test.h"

using namespace Money_lib;
namespace MLH = Money_lib_helpers;

void test_op_comp()
{
	Monetary_math_session s{ test_mmath_init_session() };
	Money m_min{ s.new_money(100) };
	Money m{ s.new_money(500) };
	Money m_max{ s.new_money(1000) };
	Money m_zero{ s.new_money() };
	Money m_neg{ s.new_money( -100 ) };

	// Same currency -----------------------------------------------------------
	// Equality
	test_op_comp_eq(s, m_min, m_min);
	test_op_comp_eq(s, m, m);
	test_op_comp_eq(s, m_max, m_max);
	test_op_comp_eq(s, m_zero, m_zero);
	test_op_comp_eq(s, m_neg, m_neg);

	// Test inverted equality
	test_op_comp_not_eq(s, m_min, m);
	test_op_comp_not_eq(s, m_min, m_zero);
	test_op_comp_not_eq(s, m_min, m_neg);

	// Test less than
	test_op_comp_less(s, m_min, m);
	test_op_comp_less(s, m, m_max);
	test_op_comp_less(s, m_neg, m_zero);

	// Test equal to or less than
	test_op_comp_less_or_eq(s, m_min, m);
	test_op_comp_less_or_eq(s, m_min, m_min);
	test_op_comp_less_or_eq(s, m_neg, m_zero);
	test_op_comp_less_or_eq(s, m_zero, m_zero);

	// Test greater than
	test_op_comp_gr(s, m, m_min);
	test_op_comp_gr(s, m_max, m);
	test_op_comp_gr(s, m_zero, m_neg);

	// Test greater than or equal to
	test_op_comp_gr_or_eq(s, m, m_min);
	test_op_comp_gr_or_eq(s, m_min, m_min);
	test_op_comp_gr_or_eq(s, m_zero, m_neg);
	test_op_comp_gr_or_eq(s, m_zero, m_zero);

	// Mixed currencies --------------------------------------------------------
	const Currency cur_eur{ Currency_ID::EUR, "Euros", "EUR" };
	const Currency cur_yen{ Currency_ID::JPY, "Japanese Yen", "JPY" };
	const double xrate_eur{ 0.915724 };
	const double xrate_yen{ 142.496 };
	s.add_currency(cur_eur);
	s.add_currency(cur_yen);
	s.add_exchange_rate(DEFAULT_CURRENCY().id, cur_eur.id, xrate_eur);
	s.add_exchange_rate(DEFAULT_CURRENCY().id, cur_yen.id, xrate_yen);

	// EUR <-> JPY
	long long xrate_yen_ll{ static_cast<long long>(
		MLH::XRATE_FACTOR() * xrate_yen) };
	double xrate_eur_yen{ static_cast<double>(
		xrate_yen_ll / xrate_eur / MLH::XRATE_FACTOR()) };
	s.add_exchange_rate(cur_eur.id, cur_yen.id, xrate_eur_yen);

	Money m_min_eur{ new_conv_money(s, m_min, xrate_eur, Currency_ID::EUR) };
	Money m_min_yen{ new_conv_money(s, m_min, xrate_yen, Currency_ID::JPY) };
	Money m_eur{ new_conv_money(s, m, xrate_eur, Currency_ID::EUR) };
	Money m_yen{ new_conv_money(s, m, xrate_yen, Currency_ID::JPY) };
	Money m_max_eur{ new_conv_money(s, m_max, xrate_eur, Currency_ID::EUR) };
	Money m_max_yen{ new_conv_money(s, m_max, xrate_yen, Currency_ID::JPY) };
	Money m_zero_eur{ s.new_money( 0, Currency_ID::EUR) };
	Money m_zero_yen{ s.new_money( 0, Currency_ID::JPY) };

	// m_neg objects
	// These objects will be used to test the conversion of Yen to Euros:
	// Assuming the initial value of 'm_neg' = 100, multiply by 10000 to achieve
	// the necessary precision.
	Money m_neg_eur{
		new_conv_money(s, m_neg * 10000, xrate_eur, Currency_ID::EUR) };
	Money m_neg_yen{
		new_conv_money(s, m_neg * 10000, xrate_yen, Currency_ID::JPY) };

	// Equality
	test_op_comp_eq(s, m_min, m_min_eur);
	test_op_comp_eq(s, m, m_yen);
	test_op_comp_eq(s, m_max_eur, m_max);
	test_op_comp_eq(s, m_zero_yen, m_zero);

	test_op_comp_eq(s, m_neg_eur, m_neg_yen); // Needs to be accurate to the
	test_op_comp_eq(s, m_neg_yen, m_neg_eur); // very last cent

	// Test inverted equality
	test_op_comp_not_eq(s, m_min, m_eur);
	test_op_comp_not_eq(s, m_min, m_zero_yen);
	test_op_comp_not_eq(s, m_min, m_neg);

	// Test less than
	test_op_comp_less(s, m_min, m_yen);
	test_op_comp_less(s, m_yen, m_max_yen);
	test_op_comp_less(s, m_neg_eur, m_zero_yen);

	// Test equal to or less than
	test_op_comp_less_or_eq(s, m_min_eur, m);
	test_op_comp_less_or_eq(s, m_neg, m_zero_yen);
	test_op_comp_less_or_eq(s, m_zero_eur, m_zero);

	test_op_comp_less_or_eq(s, m_neg_eur, m_neg_yen); // Also needs to be
	test_op_comp_less_or_eq(s, m_neg_yen, m_neg_eur); // accurate to the very
	                                                  // last cent
	// Test greater than
	test_op_comp_gr(s, m_eur, m_min);
	test_op_comp_gr(s, m_max_yen, m_eur);
	test_op_comp_gr(s, m_zero_eur, m_neg_yen);

	// Test greater than or equal to
	test_op_comp_gr_or_eq(s, m_eur, m_min);
	test_op_comp_gr_or_eq(s, m_min_yen, m_min);

	test_op_comp_gr_or_eq(s, m_neg_eur, m_neg_yen); // Also needs to be
	test_op_comp_gr_or_eq(s, m_neg_yen, m_neg_eur); // accurate to the very
	                                                // last cent
}

void test_op_comp_eq(Money_lib::Monetary_math_session& s,
                     Money_lib::Money m_a, Money_lib::Money m_b)
{
	test_op_comp_use_enum(s, m_a, m_b, Comp_op::Equals);
}

void test_op_comp_not_eq(Money_lib::Monetary_math_session& s,
                         Money_lib::Money m_a, Money_lib::Money m_b)
{
	test_op_comp_use_enum(s, m_a, m_b, Comp_op::Does_not_equal);
}

void test_op_comp_less(Money_lib::Monetary_math_session& s,
                       Money_lib::Money m_a, Money_lib::Money m_b)
{
	test_op_comp_use_enum(s, m_a, m_b, Comp_op::Less_than);
}

void test_op_comp_less_or_eq(Money_lib::Monetary_math_session& s,
                             Money_lib::Money m_a, Money_lib::Money m_b)
{
	test_op_comp_use_enum(s, m_a, m_b, Comp_op::Less_than_or_equals);
}

void test_op_comp_gr(Money_lib::Monetary_math_session& s,
                     Money_lib::Money m_a, Money_lib::Money m_b)
{
	test_op_comp_use_enum(s, m_a, m_b, Comp_op::Greater_than);
}

void test_op_comp_gr_or_eq(Money_lib::Monetary_math_session& s,
                           Money_lib::Money m_a, Money_lib::Money m_b)
{
	test_op_comp_use_enum(s, m_a, m_b, Comp_op::Greater_than_or_equals);
}


void test_op_comp_use_enum(Monetary_math_session& s, Money m_a, Money m_b,
                           const Comp_op op_enum)
{
	try {
		std::string op_str;
		bool result{};
		switch (op_enum) {
		case Comp_op::Equals:
			op_str = "==";
			result = (m_a == m_b);
			break;
		case Comp_op::Does_not_equal:
			op_str = "!=";
			result = (m_a != m_b);
			break;
		case Comp_op::Less_than:
			op_str = "<";
			result = (m_a < m_b);
			break;
		case Comp_op::Less_than_or_equals:
			op_str = "<=";
			result = (m_a <= m_b);
			break;
		case Comp_op::Greater_than:
			op_str = ">";
			result = (m_a > m_b);
			break;
		case Comp_op::Greater_than_or_equals:
			op_str = ">=";
			result = (m_a >= m_b);
			break;
		}
		std::cout
			<< "Evaluating " << m_a << ' ' << op_str << ' ' << m_b << "... ";
		if (!result) {
			std::string s_amt_a{ std::to_string(m_a.as_floating_point()) };
			std::string s_amt_b{ std::to_string(m_b.as_floating_point()) };
			std::string s_amt_b_conv{ "No conversion" };
			validate_session(m_a, m_b);
			if (m_b.amount() != 0 && (m_a.currency().id != m_b.currency().id)) {
				long conv_amt{ convert_currency_amt(m_b.amount(),
				               m_b.currency().id, m_a.currency().id,
				               m_a.session()) };
				s_amt_b_conv = "Amount B was converted to:" +
				               std::to_string(conv_amt) + " centesimal units";
			}
			throw std::runtime_error(
				"Expected (" + s_amt_a + ' ' + m_a.currency().symbol + ' ' +
				op_str + ' ' + s_amt_b + ' ' + m_b.currency().symbol +
				") to return true, but got false" + '\n' +
				//"Error: "
				  "       (" + s_amt_b_conv + ')'
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
