#ifndef NVAL_PAIR_H
#define NVAL_PAIR_H
#include <iostream>
#include <string>

struct Name_value_pair
{
	std::string name;
	double value;
};

struct Name_value_value_triplet
{
	std::string name;
	double value_a;
	double value_b;
};

std::istream& operator>>(std::istream& is, Name_value_pair& p);
std::istream& operator>>(std::istream& is, Name_value_value_triplet& t);

#endif // NVAL_PAIR_H
