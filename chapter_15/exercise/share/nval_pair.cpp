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
