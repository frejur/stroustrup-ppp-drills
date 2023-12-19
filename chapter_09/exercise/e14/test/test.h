#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <string>
#include "../money/money.h"

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
void test_new_combined_money_single(Money_lib::Monetary_math_session& s,
                                    const double value, const long expected);

void test_table();
void test_table_add_exp_failure(Money_lib::Monetary_math_session& s,
                                Money_lib::Currency_pair p,
                                const std::string& description);
void test_table_add_exp_success(Money_lib::Monetary_math_session& s,
                                Money_lib::Currency_pair p,
                                const std::string& description);

void test_money();
void test_money_exp_failure(Money_lib::Monetary_math_session& s);
Money_lib::Money test_money_exp_success(Money_lib::Monetary_math_session& s);
void test_money_validate_session_exp_failure(Money_lib::Money a,
                                             Money_lib::Money b,
                                             const std::string& description);
void test_money_validate_session_exp_success(Money_lib::Money a,
                                             Money_lib::Money b,
                                             const std::string& description);

void test_op_arithm();
void test_op_arithm_add(Money_lib::Monetary_math_session& s, Money_lib::Money a,
                        Money_lib::Money b, Money_lib::Money expected);
void test_op_comp();
void test_op_iostr();

void test_interactive();

#endif // TEST_H
