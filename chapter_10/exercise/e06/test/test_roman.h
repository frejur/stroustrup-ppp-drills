#ifndef TEST_ROMAN_H
#define TEST_ROMAN_H

#include "../roman/roman.h"
#include <fstream>
#include <iostream>
#include <string>

namespace trom {

inline const std::string& file_path()
{
	static std::string p{"data_e06/roman/int_to_roman_test_data.txt"};
	return p;
}

inline const std::string& error_keyword()
{
	static std::string p{"EXPECT_ERROR"};
	return p;
}

struct Bool_pair
{
	bool a = false;
	bool b = false;
};

struct Test_case
{
	romi::Roman_int a;
	romi::Roman_int b;
	Bool_pair expect_e;
	bool inv = false;
	std::string error_msg;
};

std::istream& operator>>(std::istream& is, Test_case& t);
std::ostream& operator<<(std::ostream& os, const Test_case& t);

void run_tests();

} // namespace trom

#endif
