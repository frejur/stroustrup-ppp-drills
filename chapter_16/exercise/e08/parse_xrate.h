#ifndef PARSE_XRATE_H
#define PARSE_XRATE_H

#include "../share/money/money.h"
#include <iostream>

//------------------------------------------------------------------------------

struct Currency_ID_and_symbol
{
	Money_lib::Currency_ID id;
	std::string symbol;
};

struct String_surrounded_by_quotes
{
	std::string value;
};

//------------------------------------------------------------------------------

std::istream& operator>>(std::istream& is, String_surrounded_by_quotes& s);

std::istream& operator>>(std::istream& is, Money_lib::Currency_ID& id);

std::istream& operator>>(std::istream& is, Money_lib::Currency& cur);

std::istream& operator>>(std::istream& is, Money_lib::Currency_pair& cur);

std::vector<Money_lib::Currency> read_currencies_from_file(
    const std::string& filename);

std::vector<Money_lib::Currency_pair> read_exchange_rates_from_file(
    const std::string& filename);

#endif // PARSE_XRATE_H
