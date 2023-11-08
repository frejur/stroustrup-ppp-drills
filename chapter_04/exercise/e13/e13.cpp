#include "../../lib/std_lib_facilities.h"
// Note that because of the implementation of vector in the above header file
// you can't use the [] operator with vector<bool>, you have to use at() instead

// Exercise 13 (and 14), Prime numbers using the Sieve of Eratosthenes
// Rewrite exercise 12 using "the Sieve of Eratosthenes"
// Exercise 14 is the same as 13 only the user gets to decide the upper limit.

// The Sieve of Eratosthenes:
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
// 	1. Create a list of consequitive integers from 1 to prime_max.
// 	2. Variable p = 2 initially (The smallest prime number).
//	3. Mark every multiple of p within the given range as a composite number,
// 		ergo not a prime number.
// 	4. Find the smallest number still not marked as composite and greater than
//		the current value of p, update p to contain the new value.
// 	5. Stop if no new value of p can be found, otherwise keep repeating from
//		step 3.


// Forward declare
vector<bool> assume_all_primes(int length);
vector<int> get_multiples_of_prime(int prime, int max);

// -----------------------------------------------------------------------------
int main()
{
	constexpr int RANGE_MAX{ 1000 };
	std::cout << "Prime number generator" << '\n'
		<< "Please enter a number within the range of 2 to " << RANGE_MAX
		<< ", up until which you want to generate prime numbers:" << '\n';
	int prime_max{ 0 };
	int ask_count{ 0 };
	while (prime_max < 2 || prime_max > RANGE_MAX ) {
		if (ask_count > 0) {
			std::cout << "Invalid number, please try again!" << '\n';
		}
		if (ask_count > 10) {
			std::cout << "Goodbye!" << '\n';
			keep_window_open();
			return 1;
		}
		if (!(std::cin >> prime_max)) {
			std::cin.clear();
			std::cin.ignore();
		}
		++ask_count;
	}

	vector<bool> is_prime_v{ assume_all_primes(prime_max) };
	is_prime_v.at(0) = false;
	is_prime_v.at(1) = false;

	int old_p { 0 };
	int p{ 2 };
	while (p > old_p) {
		for (int m : get_multiples_of_prime(p, prime_max)) {
			is_prime_v.at(m) = false;
		}
		old_p = p;
		for (int i = p + 1; i < is_prime_v.size(); ++i) {
			if (is_prime_v.at(i)) {
				p = i;
				break;
			}
		}
	}

	for (int j = 0; j < prime_max; ++j) {
		if (!is_prime_v.at(j)) {
			continue;
		}
		std::cout << j << " is a prime number." << '\n';
	}

	keep_window_open();

    return 0;
}
// -----------------------------------------------------------------------------

vector<bool> assume_all_primes(int length) {
	// Returns a vector of given length, with all 'true' values.
	// Signifies: index == number == is a prime num
	return vector<bool>(length + 1, true);
}

vector<int> get_multiples_of_prime(int prime, int max) {
	if (prime < 2) {
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

