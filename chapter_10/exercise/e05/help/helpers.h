#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <random>

namespace help {

int scale_factor(int decimal_count);
char digit_to_char(int i);
std::string double_to_string(double d, int decimal_count = 2);
inline std::string int_to_string(int i)
{
	return double_to_string(i, 0);
}
std::string int_to_ordinal(int i);
void clear_buffer(std::istream& is);
void wait_for_enter();

char chtoupper(char c);

inline void swap(int& a, int& b)
{
	int temp{a};
	a = b;
	b = temp;
}

// Random number generators (From stdlibfacilities.h) --------------------------

inline std::default_random_engine& get_rand()
{
	static std::default_random_engine ran; // note: not thread_local
	return ran;
};

inline void seed_randint(int s)
{
	get_rand().seed(s);
}

inline int randint(int min, int max)
{
	return std::uniform_int_distribution<>{min, max}(get_rand());
}

inline int randint(int max)
{
	return randint(0, max);
}

// More random numbers ---------------------------------------------------------

inline void seed_randint()
{
	seed_randint(time(NULL));
}

std::vector<int> sequence(int min, int max, int n);

void shuffle(std::vector<int>& v, int iterations);

} // namespace help

#endif // HELPERS_H
