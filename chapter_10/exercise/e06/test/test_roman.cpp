#include "test_roman.h"

std::istream& trom::operator>>(std::istream& is, Test_case& t)
{
	int a;
	std::string eq;
	romi::Roman_int b;
	is >> a >> eq >> b;
	if (is && eq == "==") {
		t = {a, b};
	}
	return is;
}

std::ostream& trom::operator<<(std::ostream& os, const Test_case& t)
{
	return os << "( " << t.a << ", " << t.a.as_int() << " ) "
	          << ((t.a == t.b) ? "==" : "!=") << " ( " << t.b << ", "
	          << t.b.as_int() << " )";
}

void trom::run_tests()
{
	std::ifstream is{file_path()};
	while (is.good()) {
		Test_case t;
		is >> t;
		if (t.a != t.b) {
			throw t;
		}
		std::cout << t << '\n';
	}
}
