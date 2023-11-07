#include "../../lib/std_lib_facilities.h"
// Note that because of the implementation of vector in the above header file
// you can't use the [] operator with vector<bool>, you have to use at() instead

// Exercise 11, Prime numbers
// Find all the prime numbers between 1 and 100:
// 	A whole number.
// 	> 0
// 	Cannot be exactly divided by any other whole number other than itself and 1.

// Forward declare
vector<bool> assume_all_primes(int length);
bool divisible_only_by_itself_and_1(int num);
vector<int> get_multiples_of_prime(int prime, int max);

// -----------------------------------------------------------------------------
int main()
{
	constexpr int PRIME_MAX{ 100 };
	vector<bool> is_prime_v{ assume_all_primes(PRIME_MAX) };
	for (int i = 0; i < PRIME_MAX; ++i) {
		if (is_prime_v.at(i)) {
			// assumed true, check
			int num = i + 1;
			if (!divisible_only_by_itself_and_1(num)) {
				is_prime_v.at(i) = false;
				continue;
			}
			// rule out future multiples
			for (int m : get_multiples_of_prime(num, PRIME_MAX)) {
				is_prime_v.at(m - 1) = false;
			}
		}
	}

	for (int j = 0; j < PRIME_MAX; ++j) {
		if (!is_prime_v.at(j)) {
			continue;
		}
		int num{ j + 1};
		std::cout << num << " is a prime number." << '\n';
	}

	keep_window_open();

    return 0;
}
// -----------------------------------------------------------------------------

vector<bool> assume_all_primes(int length) {
	// Returns a vector of given length, with all 'true' values.
	// Signifies: index == number == is a prime num
	// 0-based, so the number at index 0 is actually 1
	return vector<bool>(100, true);
}

bool divisible_only_by_itself_and_1(int num) {
	if (num <=3) {
		return true;
	}
	int divisor_max{ static_cast<int>(std::floor(num * 0.5)) };
	int divisor { 3 };
	while (divisor <= divisor_max) {
		if (num % divisor == 0) {
			return false;
		}
		divisor += 2;
	}
	return true;
}

vector<int> get_multiples_of_prime(int prime, int max) {
	if (prime == 1) {
		return {};
	}

	vector<int> multiples{};
	int new_multiple{ prime * 2 };
	while (new_multiple <= max) {
		multiples.push_back(new_multiple);
		new_multiple += prime;
	}
	return multiples;
}

