#include "money.h"
#include <stdexcept>

namespace ML = Money_lib;

ML::Currency_pair ML::Conversion_table::get(const Currency_ID id_a,
                                            const Currency_ID id_b) const
{
	for (int i = 0; i < tbl.size(); ++i) {
		if ((tbl[i].base == id_a && tbl[i].counter == id_b) ||
		    (tbl[i].base == id_b && tbl[i].counter == id_a)) {
			return tbl[i];
		}
	}
	return {Currency_ID::Not_a_currency, Currency_ID::Not_a_currency, 0};
}

bool ML::Conversion_table::already_exists(const ML::Currency_ID a,
                                          const ML::Currency_ID b) const
{
	for (int i = 0; i < tbl.size(); ++i) {
		if ((tbl[i].base == a && tbl[i].counter == b) ||
		    (tbl[i].counter == a && tbl[i].base == b)) {
			return true;
		}
	}
	return false;
}

void ML::Conversion_table::add(const ML::Currency_pair cur)
{
	if (cur.base == Currency_ID::Not_a_currency ||
	    cur.counter == Currency_ID::Not_a_currency)
	{
		throw std::runtime_error("Invalid Currency ID");
	}
	if (cur.base == cur.counter) {
		throw std::runtime_error("Invalid Currency pair, base and counter are "
                                 "identical");
	}
	if (already_exists(cur.base, cur.counter)) {
		throw std::runtime_error("Cannot add entry, there is already a value "
		                         "recorded for the given Currency pair");
	}
	if (cur.xrate.value() <= 0) {
		throw std::runtime_error("Cannot add entry, the exchange rate must "
		                         "be greater than 0 (zero)");
	}
	tbl.push_back(cur);
}

std::vector<Money_lib::Currency_ID>
Money_lib::Conversion_table::filter_currencies_convertible_with_id(
    const Currency_ID id) const
{
	std::vector<Money_lib::Currency_ID> id_v;
	Money_lib::Currency_ID this_id;
	for (int i = 0; i < tbl.size(); ++i) {
		if (tbl[i].base == id) {
			this_id = tbl[i].counter;
		} else if (tbl[i].counter == id) {
			this_id = tbl[i].base;
		} else {
			continue;
		}
		id_v.push_back(this_id);
	}
	return id_v;
}
