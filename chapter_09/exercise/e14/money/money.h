#ifndef MONEY_H
#define MONEY_H
#include <string>
#include <vector>
#include <iostream>
#include "moneyhelpers.h"
#include "exchangerate.h"

namespace Money_lib { // -------------------------------------------------------

namespace XRT = Exchange_rate_lib;

enum class Currency_ID{ Not_a_currency=-1, USD, EUR, JPY };

struct Currency_pair{
	Currency_ID base;
	Currency_ID counter;
	XRT::Exchange_rate xrate; // store whole number part + fractional part as
	                          // XRATE_SIGNIFICANT_DIGITS no. of of digits
};

struct Currency{
	Currency_ID id;
	std::string name;
	std::string symbol;
};

const Currency& DEFAULT_CURRENCY();

class Money; // Forward-declaration

//------------------------------------------------------------------------------
// Exchange rates

class Conversion_table
{
public:
	Currency_pair get(const Currency_ID id_a, const Currency_ID id_b) const;
	void add(const Currency_pair cur);
private:
	bool already_exists(const Currency_ID a,  const Currency_ID b) const;
	std::vector<Currency_pair> tbl;
};

/* -----------------------------------------------------------------------------
 * Monetary Math
 *
 * All instances of 'Money' are created by this class in order to keep track of
 * currencies and their exchange rates
 */

class Monetary_math {
public:
	Monetary_math(std::istream& istr = std::cin);

	Currency get_currency(Currency_ID id) const;
	Currency get_currency_by_symbol(const std::string& symbol) const;
	XRT::Exchange_rate get_exchange_rate(Currency_ID id_a, Currency_ID id_b)
		const;
	std::vector<std::string> get_currency_list() const;

	Money new_money(Monetary_math& self, long amt_in_c=0,
	                Currency_ID id=DEFAULT_CURRENCY().id);
	Money new_decimal_money(Monetary_math& self, double combined_amt=0,
	                        Currency_ID id=DEFAULT_CURRENCY().id);
	void add_currency(Currency cur);
	void add_currency(Currency_ID id, const std::string& name,
	                  const std::string& symbol);
	void add_exchange_rate(Currency_ID id_a, Currency_ID id_b, double xrate);

	bool status() const { return is_active; };
	void deactivate() { is_active = false; }; // Indicate failure
	void reset() { is_active = true; };       // Recover after failure
private:
	bool is_active;
	std::vector<Currency> cur_v{};
	Conversion_table tbl{};
	bool has_currency() const { return cur_v.size() > 0; }
	std::istream& is;
};

// Operators -------------------------------------------------------------------

enum class Money_Operator_ID{
	Not_an_operator=-1, Addition, Subtraction, Division, Multiplication,
	Equal_to, Not_equal_to, Less_than, Less_than_or_equal_to,
	Greater_than_or_equal_to, Greater_than
};

struct Money_Operator{
public:
	Money_Operator_ID id;
	std::string symbol;
	std::string name;
};

static const std::vector<Money_Operator> Money_Operators{
	{ Money_Operator_ID::Addition, "+", "Addition" },
	{ Money_Operator_ID::Subtraction, "-", "Subtraction" },
	{ Money_Operator_ID::Division, "/", "Division" },
	{ Money_Operator_ID::Multiplication, "*", "Multiplication" },
	{ Money_Operator_ID::Equal_to, "==", "Equal to" },
	{ Money_Operator_ID::Not_equal_to, "!=", "Not equal to" },
	{ Money_Operator_ID::Less_than, "<", "Less than" },
	{ Money_Operator_ID::Less_than_or_equal_to,
	  "<=",
	 "Less than or equal to" },
	{ Money_Operator_ID::Greater_than_or_equal_to,
	  ">=",
	 "Greater than or equal to" },
	{ Money_Operator_ID::Greater_than, ">", "Greater than" }
};

//------------------------------------------------------------------------------

long convert_currency_amt(long amt, Currency_ID in, Currency_ID out,
                          const Monetary_math& mm);

//------------------------------------------------------------------------------

void validate_session(const Money&a);
void validate_session(const Money&a, const Money& b);

class Money
{
public:
	Money(Monetary_math& mmm, long cc=0, Currency_ID id=DEFAULT_CURRENCY().id);

	long amount() const { return c; }
	double as_floating_point() const { return static_cast<double>(c / 100.0); }

	Currency currency() const { return cur; };
	const Monetary_math& session() const { return mm; }; // can of worms
	void deactivate_session() { mm.deactivate(); };
	Money new_amount(long new_amt, Currency_ID new_cur) {
		return mm.new_money(mm, new_amt, new_cur);
	}
	Money new_amount(long new_amt) { return new_amount(new_amt, cur.id); };
	Money new_decimal_amount(double new_decimal_amt, Currency_ID new_cur) {
		return mm.new_decimal_money(mm, new_decimal_amt, new_cur);
	}
	Money new_decimal_amount(double new_decimal_amt) {
		return new_decimal_amount(new_decimal_amt, cur.id);
	};
	void update_amount(long new_amt, Currency_ID new_id);
	void update_amount(long new_amt) { update_amount(new_amt, cur.id); };
	void update_decimal_amount(double new_amt, Currency_ID new_id);
	void update_decimal_amount(double new_amt) {
		update_decimal_amount(new_amt, cur.id);
	};
private:
	Monetary_math& mm; // can of worms
	Currency cur = DEFAULT_CURRENCY();
	long c;
};

// Arithmetic operators
Money operator+(Money& a, const Money& b);
Money operator-(Money& a, const Money& b);

long double operator/(Money& a, const Money& b);
Money operator/(Money& a, const double b);

Money operator*(Money& a, const double b);
Money operator*(const double a, Money& b);

// Comparison operators
bool operator==(Money& a, const Money& b);
bool operator!=(Money& a, const Money& b);
bool operator<(Money& a, const Money& b);
bool operator<=(Money& a, const Money& b);
bool operator>=(Money& a, const Money& b);
bool operator>(Money& a, const Money& b);

//------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& is, Money m);
std::istream& operator>>(std::istream& is, Money& m);

//------------------------------------------------------------------------------
// Monetary_math_session - Wrapper with a simplified Monetary_math interface

struct Monetary_math_session
{
	Monetary_math_session(Monetary_math mmm={}) : mm{ mmm } {};
	const Monetary_math& session() { return mm; };
	Money new_money(long amt_in_c=0, Currency_ID id=DEFAULT_CURRENCY().id)
	{
		return mm.new_money(mm, amt_in_c, id);
	};
	Money new_decimal_money(double combined_amt=0,
	                         Currency_ID id=DEFAULT_CURRENCY().id)
	{
		return mm.new_decimal_money(mm, combined_amt, id);
	};
	void add_currency(Currency cur) { mm.add_currency(cur); };
	void add_currency(Currency_ID id, const std::string& name,
	                  const std::string& symbol)
	{
		mm.add_currency(id, name, symbol);
	}
	void add_exchange_rate(Currency_ID id_a, Currency_ID id_b, double xrate) {
		mm.add_exchange_rate(id_a, id_b, xrate);
	};
	std::vector<std::string> get_currency_list() const {
		return mm.get_currency_list();
	};
	bool status() const { return mm.status(); };
	void deactivate() { mm.deactivate(); };
	void reset() { mm.reset(); };
private:
	Monetary_math mm;
};

// Enable session == true when active
bool operator==(const Monetary_math_session& mm, const bool b);
bool operator!=(const Monetary_math_session& mm, const bool b);

} // namespace Money_lib ------------------------------------------------------

#endif // MONEY_H
