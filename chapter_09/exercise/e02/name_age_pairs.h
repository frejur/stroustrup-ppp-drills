#ifndef NAME_AGE_PAIRS_H
#define NAME_AGE_PAIRS_H

#include <iostream>
#include <vector>


class Name_age_pairs
{
public:
	Name_age_pairs() : is(std::cin), os(std::cout), es(std::cerr) {};
	void read_names();
	void read_ages();
	void print(const std::string& label) const;
	void sort();
	friend std::ostream& operator<<(std::ostream& os, const Name_age_pairs& na);
	friend bool operator==(const Name_age_pairs& a, const Name_age_pairs& b);
	friend bool operator!=(const Name_age_pairs& a, const Name_age_pairs& b);
private:
	std::istream& is;
	std::ostream& os;
	std::ostream& es;
	std::vector<std::string> names;
	std::vector<int> ages;
};

#endif // NAME_AGE_PAIRS_H
