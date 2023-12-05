#ifndef PATRON_H
#define PATRON_H

#include <string>
#include <vector>
#include "../date/date.h"

struct Fee
{
	int id;
	double amount;
	Date registered;
	std::string comment;
	bool is_paid{ false };
};

class Patron
{
public:
	Patron(const std::string& user_name, const std::string& card_number);
	std::string user_name() const { return user; };
	std::string card_number() const { return card; };
	bool has_unpaid_fees() const;
	double debt() const;

	void add_fee(double amount);
	void add_fee(double amount, Date date_registered);
	void mark_fee_as_paid(int fee_id);
	void mark_fee_as_paid(int fee_id, const std::string& comment);
	void update_fee_comment(int fee_id,const std::string& comment);
	const std::vector<Fee>& all_fees() const { return fees; };
	Fee single_fee(int fee_id) { return fee_by_id(fee_id); };
private:
	std::string user;
	std::string card;
	std::vector<Fee> fees;

	Fee& fee_by_id(int fee_id);
	int new_fee_id() const;
};
//------------------------------------------------------------------------------

std::string validate_user_name(const std::string& user_name);
std::string validate_card_number(const std::string& card_number);

//------------------------------------------------------------------------------


#endif // PATRON_H
