#include "test_roman.h"

std::istream& trom::operator>>(std::istream& is, Test_case& t)
{
	std::string l, mid, r;
	is >> l >> mid >> r;

	if (!is) {
		return is;
	}

	bool invert = false;
	if (!(mid == "==" || mid == "!=")) {
		throw std::runtime_error("Faulty test case input, expected "
		                         "'==' or '!='");
	} else {
		if (mid == "!=") {
			invert = true;
		}
	}

	int ia, ib;
	romi::Roman_int ra, rb;

	Bool_pair expect_exception{(r == error_keyword()), l == error_keyword()};
	if (expect_exception.a && expect_exception.b) {
		throw std::runtime_error("Invalid syntax");
	}

	bool a_is_int = false;
	bool b_is_int = false;

	try {
		if (!expect_exception.b) {
			try {
				ia = help::string_to_int(l);
				a_is_int = true;
				ra = romi::Roman_int{ia};
			} catch (...) {
				if (a_is_int) {
					throw;
				}
				ra = romi::Roman_int{l};
			}
		}
		if (!expect_exception.a) {
			try {
				ib = help::string_to_int(r);
				b_is_int = true;
				rb = romi::Roman_int{ib};
			} catch (...) {
				if (b_is_int) {
					throw;
				}
				rb = romi::Roman_int{r};
			}
		}
	} catch (const std::exception& e) {
		if (expect_exception.a == true || expect_exception.b == true) {
			std::string msg{"( " + ((expect_exception.a) ? l : r)
			                + " ) Error: " + e.what()};
			t = {ra, rb, expect_exception, invert, msg};
			throw t;
		} else {
			throw e;
		}
	}
	t = {ra, rb, expect_exception, invert};
	return is;
}

std::ostream& trom::operator<<(std::ostream& os, const Test_case& t)
{
	if (t.expect_e.a) {
		os << t.error_msg;
	} else if (t.expect_e.b) {
		os << error_keyword();
	} else {
		os << "( " << t.a << ", " << t.a.as_int() << " )";
	}

	if (t.expect_e.a || t.expect_e.b) {
		os << " == ";
	} else {
		os << ((t.a == t.b) ? " == " : " !=");
	}

	if (t.expect_e.b) {
		os << t.error_msg;
	} else if (t.expect_e.a) {
		os << error_keyword();
	} else {
		os << "( " << t.b << ", " << t.b.as_int() << " )";
	}

	return os;
}

void trom::run_tests()
{
	std::ifstream is{file_path()};

	if (!is) {
		throw std::runtime_error("Could not load file: '" + file_path());
	}

	while (is.good()) {
		Test_case t;
		Bool_pair expect_exception = {false, false};
		try {
			is >> t;
		} catch (const Test_case& e_t) {
			if (e_t.expect_e.a == true || e_t.expect_e.b == true) {
				t = e_t;
				expect_exception = e_t.expect_e;
			} else {
				throw std::runtime_error("Unexpected error: " + e_t.error_msg);
			}
		}
		if (!expect_exception.a && !expect_exception.b) {
			if (t.inv == false && t.a != t.b) {
				throw t;
			} else if (t.inv == true && t.a == t.b) {
				throw t;
			}
		}
		std::cout << t << '\n';
	}
	help::keep_window_open("return to the main program");
}
