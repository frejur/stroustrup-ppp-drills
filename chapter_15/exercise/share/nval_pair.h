#ifndef NVAL_PAIR_H
#define NVAL_PAIR_H
#include <iostream>
#include <string>

struct Name_value_pair
{
	std::string name;
	double value;
};

std::istream& operator>>(std::istream& is, Name_value_pair& p);

#endif // NVAL_PAIR_H
