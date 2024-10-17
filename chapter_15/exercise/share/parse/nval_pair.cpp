#include "nval_pair.h"

std::istream& operator>>(std::istream& is, Name_value_pair& p)
{
	char l_par{}, r_par{}; // parentheses
	char l_quo{}, r_quo{}; // quotes
	char comma;
	double val;

	is >> l_par >> l_quo;
	if (l_par != '(' || l_quo != '"') {
		is.clear(std::ios_base::badbit);
		return is;
	}

	bool found_r_quo = false;
	std::string name;
	while (is) {
		is.get(r_quo);
		if (r_quo == '"') {
			found_r_quo = true;
			break;
		}
		name += r_quo;
	}

	if (!found_r_quo) {
		is.clear(std::ios_base::badbit);
		return is;
	}

	is >> comma >> val >> r_par;

	if (!is || comma != ',' || r_par != ')') {
		is.clear(std::ios_base::badbit);
		return is;
	}

	p = {name, val};
	return is;
}

std::istream& operator>>(std::istream& is, Name_value_value_triplet& t)
{
	char l_par{}, r_par{}; // parentheses
	char l_quo{}, r_quo{}; // quotes
	char cm_0{}, cm_1{};
	double val_a{}, val_b{};

	is >> l_par >> l_quo;
	if (l_par != '(' || l_quo != '"') {
		is.clear(std::ios_base::badbit);
		return is;
	}

	bool found_r_quo = false;
	std::string name;
	while (is) {
		is.get(r_quo);
		if (r_quo == '"') {
			found_r_quo = true;
			break;
		}
		name += r_quo;
	}

	if (!found_r_quo) {
		is.clear(std::ios_base::badbit);
		return is;
	}

	is >> cm_0 >> val_a >> cm_1 >> val_b >> r_par;

	if (!is || cm_0 != ',' || cm_1 != ',' || r_par != ')') {
		is.clear(std::ios_base::badbit);
		return is;
	}

	t = {name, val_a, val_b};
	return is;
}
