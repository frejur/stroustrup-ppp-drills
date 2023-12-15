#ifndef TEST_H
#define TEST_H
#include "../rational.h"

void test_gcd_multiple();
void test_gcd(const long p, const long q, const long expected);

void test_r_opmult(const RAT::Rational& r1, const RAT::Rational& r2,
                   const RAT::Rational& expected);
void test_r_opmult_multiple();

void test_r_opdiv(const RAT::Rational& r1, const RAT::Rational& r2,
                   const RAT::Rational& expected);
void test_r_opdiv_multiple();

void test_r_opadd(const RAT::Rational& r1, const RAT::Rational& r2,
                   const RAT::Rational& expected);
void test_r_opadd_multiple();

void test_r_opsub(const RAT::Rational& r1, const RAT::Rational& r2,
                   const RAT::Rational& expected);
void test_r_opsub_multiple();

void test_to_double(const RAT::Rational& r1, const double expected);
void test_to_double_multiple();

#endif // TEST_H
