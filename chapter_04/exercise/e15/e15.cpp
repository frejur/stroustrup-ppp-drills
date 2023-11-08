#include "../../lib/std_lib_facilities.h"
#include <cmath>
// Note that because of the implementation of vector in the above header file
// you can't use the [] operator with vector<bool>, you have to use at() instead

// Exercise 15, Prime numbers again
// Rewrite exercise 13 / 14 but let the user decide how many numbers to generate

// The problem here, assuming that we want to keep using the sieve, is how
// to estimate the size of the vector:
// " Sometimes instead of the primes less than n you need the
//   first x primes. The simplest method is to estimate the value
//   of n using the Prime Number Theorem, first conjectured by
//   Carl Friedrich Gauss in 1792 or 1793 (at the age of fifteen)
//   and proved independently by Jacques Hadamard and Charles
//   Jean de la Vall´ee-Poussin in 1896, which states that there are
//   approximately x/logex primes less than x. A corollary to the
//   Prime Number Theorem states that, for n > 5, the nth prime
//   number Pn is on the range n log n < Pn < n(log n+log log n)
//   so to compute the first x primes, sieve to n(log n + log log n)
//   and discard the excess. "
// Source: https://programmingpraxis.files.wordpress.com/2012/09/primenumbers.pdf

// Forward declare
int estimate_sieve_size(int n);
vector<bool> assume_all_primes(int length);
vector<int> get_multiples_of_prime(int prime, int max);

// -----------------------------------------------------------------------------
int main()
{
	constexpr int RANGE_MAX{ 200 };
	std::cout << "Prime number generator" << '\n'
		<< "Please enter how many prime numbers N you want to generate "
		<< "(1 < N <= " << RANGE_MAX << ")." << '\n';
	int prime_max{ 0 };
	int ask_count{ 0 };
	while (prime_max < 1 || prime_max > RANGE_MAX ) {
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

	int sieve_sz{ estimate_sieve_size(prime_max) };
	std::cout << "Estimated sieve size: " << sieve_sz << '\n';

	vector<bool> is_prime_v{ assume_all_primes(sieve_sz) };
	is_prime_v.at(0) = false;
	is_prime_v.at(1) = false;

	int p{ 2 };
	int prime_count{ 1 };
	while (prime_count <= prime_max) {
		for (int m : get_multiples_of_prime(p, sieve_sz)) {
			is_prime_v.at(m) = false;
		}
		for (int i = p + 1; i < is_prime_v.size(); ++i) {
			if (is_prime_v.at(i)) {
				p = i;
				++prime_count;
				break;
			}
		}
	}

	prime_count = 1;
	for (int j = 0; j < p; ++j) {
		if (!is_prime_v.at(j)) {
			continue;
		}
		std::cout << prime_count << ":" << '\t'
			<< j << " is a prime number." << '\n';
		++prime_count;
	}

	keep_window_open();

    return 0;
}
// -----------------------------------------------------------------------------
int estimate_sieve_size(int n) {
	return static_cast<int>(
		std::ceil(
			n * (std::log(n) + std::log(std::log(n)))
		)
	);
}

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
