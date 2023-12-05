#include "patron.h"
#include "../lib/lib_helpers.h"
#include <stdexcept>

Patron::Patron(const std::string& user_name, const std::string& card_number)
: user(validate_user_name(user_name)), card(validate_card_number(card_number))
{}

//------------------------------------------------------------------------------

int Patron::new_fee_id() const {
	return fees.size();
}

void Patron::add_fee(double amount, Date date_registered)
{
	if (amount <= 0) {
		throw std::runtime_error("Invalid fee, amount must be greater than 0");
	}
	fees.push_back({ new_fee_id(), amount, date_registered, "", false });
}

void Patron::add_fee(double amount) {
	add_fee(amount, {});
}

Fee& Patron::fee_by_id(int fee_id) {
	for (Fee& f: fees) {
		if (f.id == fee_id) {
			return f;
		}
	}
	throw std::runtime_error("Could not find a fee with that ID");
}

void Patron::mark_fee_as_paid(int fee_id, const std::string& comment) {
	Fee& f{ fee_by_id(fee_id) };
	if (f.is_paid) {
		throw std::runtime_error("Fee is already marked as paid");
	}
	f.is_paid = true;
	f.comment = comment;
}

void Patron::mark_fee_as_paid(int fee_id) {
	Fee& f{ fee_by_id(fee_id) };
	if (f.is_paid) {
		throw std::runtime_error("Fee is already marked as paid");
	}
	f.is_paid = true;
}

void Patron::update_fee_comment(int fee_id, const std::string& comment) {
	Fee& f{ fee_by_id(fee_id) };
	f.comment = comment;
}

//------------------------------------------------------------------------------

bool Patron::has_unpaid_fees() const {
	for (const Fee& f : fees) {
		if (!f.is_paid) {
			return true;
		}
	}
	return false;
}

double Patron::debt() const {
	double d{ 0 };
	for (const Fee& f : fees) {
		if (!f.is_paid) {
			d += f.amount;
		}
	}
	return d;
}

//------------------------------------------------------------------------------

std::string validate_user_name(const std::string& user) {
	using CODE = HLP::User_name_code;
	CODE c{ HLP::is_valid_user_name(user) };

	switch (c){
	case CODE::Success:
		break;
	case CODE::Empty:
		throw std::runtime_error("Invalid user name, empty string");
		break;
	case CODE::Invalid_character:
		throw std::runtime_error("Invalid user name, only letters are allowed");
		break;
	case CODE::Expected_letter:
		throw std::runtime_error("Invalid user name, user name must begin and "
		                         "end with a character");
		break;
	case CODE::Invalid_hyphen:
		throw std::runtime_error("Invalid user name, hyphens may only be used "
								 "to separate words");
		break;
	case CODE::Invalid_space:
		throw std::runtime_error("Invalid user name, spaces may only be used "
								 "to separate words");
		break;
	}

	return user;
}
//------------------------------------------------------------------------------

std::string validate_card_number(const std::string& card) {
	using CODE = HLP::Card_number_code;
	CODE c{ HLP::is_valid_card_number(card) };

	switch (c){
	case CODE::Success:
		break;
	case CODE::Invalid_string_length:
		throw std::runtime_error("Invalid card number, must be a 6-digit "
		                         "number");
		break;
	case CODE::Non_digit:
		throw std::runtime_error("Invalid card number, only digits are "
		                         "allowed");
		break;
	case CODE::Invalid_first_digit:
		throw std::runtime_error("Invalid card number, the first digit may not "
		                         "be '0'");
		break;
	}

	return card;
}
