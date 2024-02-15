#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <string>
#include "../money/money.h"

// Run all tests
void test_all();

// Conversion helper
Money_lib::Money  new_conv_money(Money_lib::Monetary_math_session& s,
                                 Money_lib::Money m_in,
                                 const double xrate,
                                 const Money_lib::Currency_ID id_out);
double significant_d(double amt, int num_d);

// Monetary math ---------------------------------------------------------------
void test_mmath();
Money_lib::Monetary_math_session test_mmath_init_session();
void test_mmath_get_currency_exp_failure(Money_lib::Monetary_math_session& s);
Money_lib::Currency test_mmath_get_currency_exp_success(
	Money_lib::Monetary_math_session& s, Money_lib::Currency_ID
);
void test_mmath_add_currency(Money_lib::Monetary_math_session& s);
void test_new_money(Money_lib::Monetary_math_session& s);
void test_new_money_single(Money_lib::Monetary_math_session& s,
                           const long value, const long expected);
void test_new_money_single(Money_lib::Monetary_math_session& s,
                           const long value);
void test_new_decimal_money_single(Money_lib::Monetary_math_session& s,
                                    const double value, const long expected);

// Conversion table ------------------------------------------------------------
void test_table();
void test_table_add_exp_failure(Money_lib::Monetary_math_session& s,
                                Money_lib::Currency_ID id_a,
                                Money_lib::Currency_ID id_b, double xrate,
                                const std::string& description);
void test_table_add_exp_success(Money_lib::Monetary_math_session& s,
                                Money_lib::Currency_ID id_a,
                                Money_lib::Currency_ID id_b, double xrate,
                                const std::string& description);

// Money -----------------------------------------------------------------------
void test_money();
void test_money_exp_failure(Money_lib::Monetary_math_session& s);
Money_lib::Money test_money_exp_success(Money_lib::Monetary_math_session& s);
void test_money_validate_session_exp_failure(Money_lib::Money a,
                                             Money_lib::Money b,
                                             const std::string& description);
void test_money_validate_session_exp_success(Money_lib::Money a,
                                             Money_lib::Money b,
                                             const std::string& description);

// Arithmetic operators---------------------------------------------------------
void test_op_arithm();

// Addition
void test_op_arithm_add(Money_lib::Monetary_math_session& s, Money_lib::Money a,
                        Money_lib::Money b, Money_lib::Money expected);
void test_op_arithm_add(Money_lib::Monetary_math_session& s, long a, long b,
                        long expected);
void test_op_arithm_add(Money_lib::Monetary_math_session& s,
                        long a, Money_lib::Currency_ID id_a,
                        long b, Money_lib::Currency_ID id_b,
                        long expected, Money_lib::Currency expected_currency);

// Subtraction
void test_op_arithm_sub(Money_lib::Monetary_math_session& s, Money_lib::Money a,
                        Money_lib::Money b, Money_lib::Money expected);
void test_op_arithm_sub(Money_lib::Monetary_math_session& s, long a, long b,
                        long expected);
void test_op_arithm_sub(Money_lib::Monetary_math_session& s,
                        long a, Money_lib::Currency_ID id_a,
                        long b, Money_lib::Currency_ID id_b,
                        long expected, Money_lib::Currency expected_currency);

// Division
void test_op_arithm_div(Money_lib::Monetary_math_session& s,
                        long a, Money_lib::Currency_ID id_a,
                        long b, Money_lib::Currency_ID id_b,
                        long double expected);
void test_op_arithm_div(Money_lib::Monetary_math_session& s, Money_lib::Money a,
                        Money_lib::Money b, long double expected);
void test_op_arithm_div(Money_lib::Monetary_math_session& s, long amount,
                        Money_lib::Currency_ID id, long double denominator,
                        long expected_amount);
void test_op_arithm_div_by_zero(Money_lib::Monetary_math_session& s);
void test_op_arithm_div_by_zero(Money_lib::Monetary_math_session& s,
                                Money_lib::Money m_a, Money_lib::Money m_b);

// Multiplication
void test_op_arithm_mult(Money_lib::Monetary_math_session& s, long amount,
                         Money_lib::Currency_ID id, long double factor,
                         long expected_amount);

// Comparison operators --------------------------------------------------------
void test_op_comp();

enum class Comp_op{
	Equals, Does_not_equal, Less_than, Less_than_or_equals, Greater_than,
	Greater_than_or_equals
};

void test_op_comp_eq(Money_lib::Monetary_math_session& s,
                     Money_lib::Money m_a, Money_lib::Money m_b);
void test_op_comp_not_eq(Money_lib::Monetary_math_session& s,
                         Money_lib::Money m_a, Money_lib::Money m_b);
void test_op_comp_less(Money_lib::Monetary_math_session& s,
                       Money_lib::Money m_a, Money_lib::Money m_b);
void test_op_comp_less_or_eq(Money_lib::Monetary_math_session& s,
                             Money_lib::Money m_a, Money_lib::Money m_b);
void test_op_comp_gr(Money_lib::Monetary_math_session& s,
                     Money_lib::Money m_a, Money_lib::Money m_b);
void test_op_comp_gr_or_eq(Money_lib::Monetary_math_session& s,
                           Money_lib::Money m_a, Money_lib::Money m_b);
void test_op_comp_use_enum(Money_lib::Monetary_math_session& s,
                           Money_lib::Money m_a, Money_lib::Money m_b,
                           const Comp_op op_enum);

// Input / output operators ----------------------------------------------------
void test_op_iostr();

#endif // TEST_H
