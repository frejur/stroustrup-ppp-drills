#include "test.h"
#include <iostream>
#include <stdexcept>
#include <string>

void test_gcd_multiple() {
	std::cout << "Running tests for greatest_common_divisor()..."  << '\n';
	test_gcd(   36,    63,   9);
	test_gcd(   10,    25,   5);
	test_gcd(  120,   120, 120);
	test_gcd(    2,    12,   2);
	test_gcd(   23,    37,   1);
	test_gcd(   45,   330,  15);
	test_gcd(24528, 65934,   6);
	test_gcd(  120,  -120, 120);
	test_gcd(   -2,    12,   2);
	test_gcd(   37,    23,   1);
}

void test_r_opmult_multiple() {
	std::cout << "Running multiplication tests..."  << '\n';
	test_r_opmult({ -133, 64 }, { 202, 229 }, { -13433, 7328 });
	test_r_opmult({ 200, 15 }, { 208, 109 }, { 8320, 327 });
	test_r_opmult({ 64, -153 }, { 113, 64 }, { -113, 153 });
	test_r_opmult({ -194, 105 }, { 150, -83 }, { 1940, 581 });
	test_r_opmult({ 245, 214 }, { -177, 139 }, { -43365, 29746 });
	test_r_opmult({ 128, 202 }, { -203, 256 }, { -203, 404 });
	test_r_opmult({ -168, 199 }, { 140, 222 }, { -3920, 7363 });
	test_r_opmult({ 24, 165 }, { 249, 113 }, { 1992, 6215 });
	test_r_opmult({ 104, 203 }, { 124, -43 }, { -12896, 8729 });
	test_r_opmult({ 212, 241 }, { -105, 218 }, { -11130, 26269 });
}

void test_r_opdiv_multiple() {
	std::cout << "Running division tests..."  << '\n';
	test_r_opdiv({ 225, 34 }, { 21, 198 }, { 7425, 119 });
	test_r_opdiv({ 154, 176 }, { 112, -159 }, { -159, 128 });
	test_r_opdiv({ -61, -98 }, { 103, 118 }, { 3599, 5047 });
	test_r_opdiv({ 35, 74 }, { 253, 253 }, { 35, 74 });
	test_r_opdiv({ 136, 17 }, { 22, 32 }, { 128, 11 });
	test_r_opdiv({ -253, 109 }, { 2, 184 }, { -23276, 109 });
	test_r_opdiv({ 240, 198 }, { 111, 69 }, { 920, 1221 });
	test_r_opdiv({ -162, 191 }, { -168, -86 }, { -1161, 2674 });
	test_r_opdiv({ 9, 10 }, { 7, 182 }, { 117, 5 });
	test_r_opdiv({ 148, -104 }, { 254, -252 }, { 2331, 1651 });
}

void test_r_opadd_multiple() {
	std::cout << "Running addition tests..."  << '\n';
	test_r_opadd({ -29, 30 }, { 171, -27 }, { -73, 10 });
	test_r_opadd({ 88, 209 }, { 85, 128 }, { 2639, 2432 });
	test_r_opadd({ 104, 77 }, { 89, -17 }, { -5085, 1309 });
	test_r_opadd({ 100, 50 }, { 15, 253 }, { 521, 253 });
	test_r_opadd({ 173, 76 }, { -91, 8 }, { -1383, 152 });
	test_r_opadd({ 162, 146 }, { 108, -14 }, { -3375, 511 });
	test_r_opadd({ -187, -157 }, { -224, -170 }, { 33479, 13345 });
	test_r_opadd({ 95, 2 }, { 218, 30 }, { 1643, 30 });
	test_r_opadd({ 59, 249 }, { -43, -91 }, { 16076, 22659 });
	test_r_opadd({ -38, 159 }, { 166, 9 }, { 8684, 477 });
}

void test_r_opsub_multiple() {
	std::cout << "Running subtraction tests..."  << '\n';
	test_r_opsub({ 74, 203 }, { 116, 101 }, { -16074, 20503 });
	test_r_opsub({ -207, 152 }, { 67, -55 }, { -1201, 8360 });
	test_r_opsub({ 32, 17 }, { 242, 16 }, { -1801, 136 });
	test_r_opsub({ 47, -52 }, { 241, -37 }, { 10793, 1924 });
	test_r_opsub({ -203, 237 }, { 230, 17 }, { -57961, 4029 });
	test_r_opsub({ -74, 70 }, { 216, 39 }, { -3001, 455 });
	test_r_opsub({ 154, -167 }, { 43, 121 }, { -25815, 20207 });
	test_r_opsub({ -58, 71 }, { -65, 90 }, { -121, 1278 });
	test_r_opsub({ 73, 252 }, { -226, 38 }, { 29863, 4788 });
	test_r_opsub({ 16, 177 }, { 58, 169 }, { -7562, 29913 });
}

void test_to_double_multiple() {
	std::cout << "Running tests for to_double() (Rounding to 3 decimals)..."  << '\n';
	test_to_double({ 1, 3 }, 0.333);
	test_to_double({ 5, 7 }, 0.714);
	test_to_double({ 9, 3 }, 3);
	test_to_double({ 12, -245 }, -0.048);
	test_to_double({ 146, 219 }, 0.667);
	test_to_double({ -177, 223 }, -0.793);
	test_to_double({ 178, 61 }, 2.918);
	test_to_double({ 119, 246 }, 0.484);
	test_to_double({ 67, 97 }, 0.691);
	test_to_double({ 163, 175 }, 0.931);
	test_to_double({ 213, 251 }, 0.849);
}

// -----------------------------------------------------------------------------

void test_gcd(long p, long q, long expected) {
	std::cout << "Calculating the greatest common divisor for: "
	          << p << " / " << q << " ... ";
	long result{ RAT::greatest_common_divisor(p, q) };
	if (result != expected) {
		throw std::runtime_error("Expected " + std::to_string(expected) +
		                         " but got: " + std::to_string(result));
	}
	std::cout << "SUCCESS! The result is " << result << " as expected" << '\n';
}
void test_r_opmult(const RAT::Rational& r1, const RAT::Rational& r2,
                   const RAT::Rational& expected)
{
	std::cout << "Calculating "
	          << r1.get_p() << " / " << r1.get_q() << " * "
	          << r2.get_p() << " / " << r2.get_q() << " ... ";
	RAT::Rational result{ r1 * r2 };
	if (result != expected) {
		throw std::runtime_error("Expected " +
		                         std::to_string(expected.get_p()) + " / " +
		                         std::to_string(expected.get_q()) +
		                         " but got: " +
		                         std::to_string(result.get_p()) + " / " +
		                         std::to_string(result.get_q())
		);
	}
	std::cout
		<< "SUCCESS! The result is " << result.get_p() << " / "
		<< result.get_q() << " as expected" << '\n';
}

void test_r_opdiv(const RAT::Rational& r1, const RAT::Rational& r2,
                   const RAT::Rational& expected)
{
	std::cout << "Calculating "
	          << r1.get_p() << " / " << r1.get_q() << " div. by "
	          << r2.get_p() << " / " << r2.get_q() << " ... ";
	RAT::Rational result{ r1 / r2 };
	if (result != expected) {
		throw std::runtime_error("Expected " +
		                         std::to_string(expected.get_p()) + " / " +
		                         std::to_string(expected.get_q()) +
		                         " but got: " +
		                         std::to_string(result.get_p()) + " / " +
		                         std::to_string(result.get_q())
		);
	}
	std::cout
		<< "SUCCESS! The result is " << result.get_p() << " / "
		<< result.get_q() << " as expected" << '\n';
}

void test_r_opadd(const RAT::Rational& r1, const RAT::Rational& r2,
                   const RAT::Rational& expected)
{
	std::cout << "Calculating "
	          << r1.get_p() << " / " << r1.get_q() << " + "
	          << r2.get_p() << " / " << r2.get_q() << " ... ";
	RAT::Rational result{ r1 + r2 };
	if (result != expected) {
		throw std::runtime_error("Expected " +
		                         std::to_string(expected.get_p()) + " / " +
		                         std::to_string(expected.get_q()) +
		                         " but got: " +
		                         std::to_string(result.get_p()) + " / " +
		                         std::to_string(result.get_q())
		);
	}
	std::cout
		<< "SUCCESS! The result is " << result.get_p() << " / "
		<< result.get_q() << " as expected" << '\n';
}

void test_r_opsub(const RAT::Rational& r1, const RAT::Rational& r2,
                   const RAT::Rational& expected)
{
	std::cout << "Calculating "
	          << r1.get_p() << " / " << r1.get_q() << " - "
	          << r2.get_p() << " / " << r2.get_q() << " ... ";
	RAT::Rational result{ r1 - r2 };
	if (result != expected) {
		throw std::runtime_error("Expected " +
		                         std::to_string(expected.get_p()) + " / " +
		                         std::to_string(expected.get_q()) +
		                         " but got: " +
		                         std::to_string(result.get_p()) + " / " +
		                         std::to_string(result.get_q())
		);
	}
	std::cout
		<< "SUCCESS! The result is " << result.get_p() << " / "
		<< result.get_q() << " as expected" << '\n';
}

void test_to_double(const RAT::Rational& r, const double expected)
{
	std::cout << "Converting " << r.get_p() << " / " << r.get_q() << " "
	             "into type <double>... ";
	double result = static_cast<int>(r.to_double() * 1000 + 0.5) / 1000.0;
	if (result != expected) {
		throw std::runtime_error("Expected " + std::to_string(expected) +
		                         " but got " + std::to_string(result)
		);
	}
	std::cout
		<< "SUCCESS! The result is " << result << " as expected" << '\n';
}
