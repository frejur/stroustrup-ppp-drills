#ifndef MONEY_H
#define MONEY_H
#include <string>
#include <vector>
#include <iostream>

namespace Money_lib { // -------------------------------------------------------

enum class Currency_ID{ Not_a_currency=-1, USD, EUR, JPY };

struct Currency_pair{
	Currency_ID base;
	Currency_ID counter;
	double xrate;
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
	Conversion_table() : tbl{ {} } {};;
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
	Monetary_math();

	Currency get_currency(Currency_ID id) const;
	double get_exchange_rate(Currency_ID id_a, Currency_ID id_b) const;

	Money new_money(Monetary_math& self, long amt_in_c=0,
	                Currency_ID id=DEFAULT_CURRENCY().id);
	Money new_combined_money(Monetary_math& self, double combined_amt=0,
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
	double as_floating_point() const { return static_cast<float>(c / 100.0); }

	Currency currency() const { return cur; };
	const Monetary_math& session() const { return mm; }; // can of worms
	void deactivate_session() { mm.deactivate(); };\
	Money new_amount(long new_amt) { return {mm, new_amt, cur.id }; };
private:
	Monetary_math& mm; // can of worms
	const Currency cur;
	long c;
};

// Arithmetic operators
Money operator+(Money& a, const Money& b);
Money operator-(Money& a, const Money& b);

double operator/(Money& a, const Money& b);
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

std::istream& operator>>(std::istream& is, Money m);
std::ostream& operator<<(std::ostream& is, Money m);

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
	Money new_combined_money(double combined_amt=0,
	                         Currency_ID id=DEFAULT_CURRENCY().id)
	{
		return mm.new_combined_money(mm, combined_amt, id);
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
