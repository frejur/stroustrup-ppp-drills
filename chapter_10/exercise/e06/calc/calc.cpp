#include "calc.h"
#include "../help/help.h"
#include "../roman/roman.h"

namespace {
using std::string;
using std::vector;
using RM = calc::Read_mode;
using WM = calc::Write_mode;
using EC = calc::Error_code;
} // namespace

//------------------------------------------------------------------------------
// CH07E09
int calc::hextodec(std::string hex)
{
	double dec{0};
	bool error = false;
	for (int i = 0; i < hex.size(); ++i) {
		if (!help::isvalidch(hex.at(i))) {
			error = true;
			break;
		}

		int char_int{hex.at(i) - '0'};
		if (0 <= char_int && char_int <= 9) {
			dec += (char_int * pow(16, (hex.size() - i - 1)));
		} else if (('a' - '0') <= char_int && char_int <= ('f' - '0')) {
			char_int = char_int - ('a' - '0') + 10;
			dec += (char_int * pow(16, (hex.size() - i - 1)));
		} else if (('A' - '0') <= char_int && char_int <= ('F' - '0')) {
			char_int = char_int - ('A' - '0') + 10;
			dec += (char_int * pow(16, (hex.size() - i - 1)));
		} else {
			error = true;
			break;
		}
	}
	if (error) {
		calc_error(EC::Hex_invalid, "Invalid hex character");
	}
	return help::narrow_cast<int>(dec);
}
//------------------------------------------------------------------------------

std::ostream& calc::operator<<(std::ostream& os, const Result& r)
{
	if (r.type == Result_type::Floating_point_value) {
		os << r.val_dec;
	} else if (r.type == Result_type::Integer_value) {
		os << r.val_int;
	} else if (r.type == Result_type::Roman_numeral) {
		os << r.val_rom.as_roman();
	}
	return os;
}

bool calc::operator==(const Result& a, const Result& b)
{
	return a.as_floating_point() == b.as_floating_point();
}
bool calc::operator!=(const Result& a, const Result& b)
{
	return !(a == b);
}
bool calc::operator==(const Result& a, double b)
{
	return a.as_floating_point() == b;
}
bool calc::operator!=(const Result& a, double b)
{
	return !(a == b);
}

bool calc::operator<(const Result& a, double b)
{
	return a.as_floating_point() < b;
}

bool calc::operator<=(const Result& a, double b)
{
	return (a < b) && (a == b);
}

bool calc::operator>=(const Result& a, double b)
{
	return (a > b) && (a == b);
}

bool calc::operator>(const Result& a, double b)
{
	return a.as_floating_point() > b;
}
calc::Result calc::operator*(const Result& a, const Result& b)
{
	if (a.type == Result_type::Roman_numeral
	    || b.type == Result_type::Roman_numeral) {
		return {Result_type::Roman_numeral,
		        help::narrow_cast<int>(
		            help::narrow_cast<int>(a.as_floating_point())
		            * help::narrow_cast<int>(b.as_floating_point()))};
	}
	return {Result_type::Floating_point_value,
	        a.as_floating_point() * b.as_floating_point()};
}
calc::Result calc::operator/(const Result& a, const Result& b)
{
	if (a.type == Result_type::Roman_numeral
	    || b.type == Result_type::Roman_numeral) {
		return {Result_type::Roman_numeral,
		        help::narrow_cast<int>(
		            help::narrow_cast<int>(a.as_floating_point())
		            / help::narrow_cast<int>(b.as_floating_point()))};
	}
	return {Result_type::Floating_point_value,
	        a.as_floating_point() / b.as_floating_point()};
}
calc::Result calc::operator%(const Result& a, const Result& b)
{
	if (a.type == Result_type::Roman_numeral
	    || b.type == Result_type::Roman_numeral) {
		return {Result_type::Roman_numeral,
		        help::narrow_cast<int>(
		            help::narrow_cast<int>(a.as_floating_point())
		            % help::narrow_cast<int>(b.as_floating_point()))};
	}
	calc_error(EC::Modulus_on_floating_point,
	           "Cannot perform modulus on floating-point values");
	return {};
}
calc::Result calc::operator*(const Result& a, int b)
{
	if (a.type != Result_type::Floating_point_value) {
		return {a.type, help::narrow_cast<int>(a.as_floating_point() * b)};
	}
	return {a.type, a.as_floating_point() * b};
}

calc::Result calc::operator*(int a, const Result& b)
{
	return b * a;
}
calc::Result calc::operator+(const Result& a, const Result& b)
{
	if (a.type == Result_type::Roman_numeral
	    || b.type == Result_type::Roman_numeral) {
		return {Result_type::Roman_numeral,
		        help::narrow_cast<int>(
		            help::narrow_cast<int>(a.as_floating_point())
		            + help::narrow_cast<int>(b.as_floating_point()))};
	}
	return {Result_type::Floating_point_value,
	        a.as_floating_point() + b.as_floating_point()};
}

calc::Result calc::operator-(const Result& a, const Result& b)
{
	if (a.type == Result_type::Roman_numeral
	    || b.type == Result_type::Roman_numeral) {
		return {Result_type::Roman_numeral,
		        help::narrow_cast<int>(
		            help::narrow_cast<int>(a.as_floating_point())
		            - help::narrow_cast<int>(b.as_floating_point()))};
	}
	return {Result_type::Floating_point_value,
	        a.as_floating_point() - b.as_floating_point()};
}

//------------------------------------------------------------------------------
// CH07E03, Symbol_table

romi::Roman_int calc::Symbol_table_roman::get(string name)
{
	// attempts to find Variable s and return its value
	for (const Variable_roman& v : var_table)
		if (v.name == name)
			return v.value;
	calc_error(EC::Get_undefined, "Unable to get undefined variable: " + name);
	return 0;
}

double calc::Symbol_table_decimal::get(string name)
{
	// attempts to find Variable s and return its value
	for (const Variable_decimal& v : var_table)
		if (v.name == name)
			return v.value;
	calc_error(EC::Get_undefined, "Unable to get undefined variable: " + name);
	return 0;
}

void calc::Symbol_table_roman::set(string name, romi::Roman_int val)
{
	// attempts to find variable s and set its value to d
	for (Variable_roman& v : var_table)
		if (v.name == name) {
			if (v.is_const) {
				calc_error(EC::Reassign_constant, "Cannot reassign a constant");
			}
			v.value = val;
			return;
		}
	calc_error(EC::Assign_to_undefined,
	           "Unable to assign value to undefined variable ");
}

void calc::Symbol_table_decimal::set(string name, double val)
{
	// attempts to find variable s and set its value to d
	for (Variable_decimal& v : var_table)
		if (v.name == name) {
			if (v.is_const) {
				calc_error(EC::Reassign_constant, "Cannot reassign a constant");
			}
			v.value = val;
			return;
		}
	calc_error(EC::Assign_to_undefined,
	           "Unable to assign value to undefined variable ");
}

bool calc::Symbol_table_roman::is_declared(string name)
{
	for (const Variable_roman& v : var_table) {
		if (v.name == name) {
			return true;
		}
	}
	return false;
}

bool calc::Symbol_table_decimal::is_declared(string name)
{
	for (const Variable_decimal& v : var_table) {
		if (v.name == name) {
			return true;
		}
	}
	return false;
}

romi::Roman_int calc::Symbol_table_roman::declare(string name,
                                                  romi::Roman_int val,
                                                  bool is_const)
{
	if (is_declared(name))
		calc_error(EC::Redeclaration, "'" + name + "' declared twice");
	if (output_trace)
		std::cout << "DEF: adding " << name << " = " << val << '\n';
	var_table.push_back(Variable_roman{name, val, is_const});
	return val;
}

double calc::Symbol_table_decimal::declare(string name,
                                           double val,
                                           bool is_const)
{
	if (is_declared(name))
		calc_error(EC::Redeclaration, "'" + name + "' declared twice");
	if (output_trace)
		std::cout << "DEF: adding " << name << " = " << val << '\n';
	var_table.push_back(Variable_decimal{name, val, is_const});
	return val;
}
//------------------------------------------------------------------------------

calc::Token_stream::Token_stream(Calculator_version v)
    : full(false)
    , buffer(0)
    , ver(v)
{}

void calc::Token_stream::putback(Token t)
{
	if (full)
		calc_error(EC::Buffer_full, "buffer is full");
	if (output_trace) std::cout << "TOK: putting back token into buffer\n";
	buffer = t; full = true;
}

calc::Token calc::Token_stream::getBuffer()
{
	full = false;
	return buffer;
}
//------------------------------------------------------------------------------

void calc::Token_stream::ignore(std::istream& istr)
{
	// check buffer for char
	if (full && getBuffer().kind == '\n') {
		return;
	}
	char ch = 0;
	while (ch != '\n') {
		istr.get(ch);
	}
}

void calc::clean_up_mess(Token_stream& ts, std::istream& istr)
{
	ts.ignore(istr);
}

char calc::Token_stream::skipto_break_nonws(std::istream& istr)
{
	char ch{ ' ' };
	while (istr && (help::isspace(ch) && ch != '\n')) {
		istr.get(ch);
	}
	return ch;
}
//------------------------------------------------------------------------------

calc::Token calc::Token_stream::peek(std::istream& istr)
{
	return get(istr, true);
}

calc::Token calc::Token_stream::get(std::istream& istr, bool peek)
{
	if (full) {
		if (output_trace) std::cout << "TOK: getting token from buffer\n";
		Token t = getBuffer();
		if (peek) {
			putback(t);
		}
		return t;
	}
	char ch{};
	ch = skipto_break_nonws(istr);

	// check for hexadecimal prefix CH07E09
	if (ch == hex_prefix.at(0)) {
		char ch2{};
		istr.get(ch2);
		if (ch2 == hex_prefix.at(1)) {
			std::string s{ "" };
			char ch3{ };
			while (istr.get(ch3) && help::isalnum(ch3)) {
				s += ch3;
			}
			istr.putback(ch3);
			if (s.size() == 0) {
				calc_error(EC::Hex_incomplete, "Incomplete Hexadecimal number");
			}
			if (ver == Calculator_version::Roman) {
				return Token(hex_token,
				             {Result_type::Roman_numeral, hextodec(s)});
			}
			return Token(hex_token, {Result_type::Integer_value, hextodec(s)});
		}
		istr.putback(ch2);
		istr.putback(ch);
	}

	// check for roman numeral
	if (ver == Calculator_version::Roman
	    && (ch == 'N' || romi::ch_is_valid(ch))) {
		std::string r{ch};
		char ch2{};
		while (istr.get(ch2) && help::isalnum(ch2)) {
			r += ch2;
		}
		istr.putback(ch2);
		return Token(roman, {Result_type::Roman_numeral, r});
	}

	switch (ch) {
	case '\n':
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case ',':
	case assign:
		if (output_trace)
			std::cout << "TOK: operator '" << ch << "'" << '\n';
		if (peek) {
			istr.putback(ch);
		}
		return Token(ch); // characters represent themselves
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9': {
		if (ver == Calculator_version::Decimal) {
			istr.putback(ch);     // put digit back into input stream
			double val_dbl;       // CH07E10
			istr >> val_dbl;
			if (output_trace)
				std::cout << "TOK: number " << val_dbl << '\n';
			if (peek) {
				for (char c : std::to_string(val_dbl)) {
					istr.putback(c);
				}
			}
			return Token(number, {Result_type::Floating_point_value, val_dbl});
		}
		break;
	}
	default:
		if (help::isalpha(ch) || ch == declkey.front()
		    || ch == quit_key.front()) {
			if (output_trace)
				std::cout << "TOK: alphanumeric character found: " << ch
				          << '\n';
			string s;
			s += ch;

			// read through istr, feed alphanumeric chars into string
			// CH07E01: add underscore to list of valid characters
			while (istr.get(ch)
			       && (help::isalpha(ch) || help::isdigit(ch) || ch == '_')) {
				s += ch;
			}

			if (peek) {
				for (char c : s) {
					istr.putback(c);
				}
			}

			istr.putback(ch); // put non-alphanumeric back into std::cin

			if (s == read_key()) {
				if (output_trace)
					std::cout << "TOK: read keyword found: " << s << '\n';
				return Token(read_token);
			}

			if (s == write_key()) {
				if (output_trace)
					std::cout << "TOK: write keyword found: " << s << '\n';
				return Token(write_token);
			}

			if (s == quit_key) {
				if (output_trace)
					std::cout << "TOK: quit keyword found: " << s << '\n';
				return Token(quit_token);
			}

			if (s == help_key) {
				if (output_trace)
					std::cout << "TOK: help keyword found: " << s << '\n';
				return Token(help_token);
			}

			if (s == declkey) {
				if (output_trace)
					std::cout << "TOK: declaration keyword found: " << s
					          << '\n';
				return Token(let);
			}

			if (s == constkey) { // CH07E03
				if (output_trace)
					std::cout << "TOK: const keyword found: " << s << '\n';
				return Token(const_token);
			}

			if (s == sqrt_word) {
				if (output_trace)
					std::cout << "TOK: squareroot keyword found: " << s << '\n';
				return Token(sqrt_token);
			}

			if (s == pow_word) {
				if (output_trace)
					std::cout << "TOK: power of keyword found: " << s << '\n';
				return Token(pow_token);
			}
			if (islower(s.front())) {
				if (output_trace)
					std::cout << "TOK: string found: " << s << '\n';
				return Token{name, s};
			}
		}
		calc_error(EC::Token_bad, "Bad token");
		break;
	}
	return 0;
}

//------------------------------------------------------------------------------

std::vector<string> calc::line_to_expressions(std::istream& is)
{
	std::vector<std::string> expressions;

	char c{};
	int count_chars = 0;
	bool prev_char_is_print = false;
	bool prev_char_is_wspace = false;
	bool exp_too_long = false;
	std::string e;
	while (is.get(c)) {
		++count_chars;
		if (count_chars > expression_char_limit
		    || expressions.size() > expression_count_limit) {
			exp_too_long = true;
			break;
		}

		if (c == print || c == '\n') {
			if (!prev_char_is_print) {
				if (e.size() > 0) {
					expressions.push_back(e);
				}
				e = "";
				prev_char_is_print = true;
				prev_char_is_wspace = false;
			}
			if (c == '\n') {
				break;
			}
			continue;
		}

		if (help::isspace(c)) {
			if (prev_char_is_wspace || e.size() == 0) {
				continue;
			}
			prev_char_is_wspace = true;
		} else {
			prev_char_is_wspace = false;
		}

		e += c;
		prev_char_is_print = false;
	}
	if (exp_too_long) {
		calc_error(
		    EC::Expression_too_long,
		    "Expression too long or too many chained expressions, please "
		    "split up into multiple lines");
	}
	return expressions;
}

//------------------------------------------------------------------------------

void calc::run(Calculator_version v)
{
	Token_stream ts(v);
	if (v == Calculator_version::Decimal) {
		print_greeting(std::cout);
		ts.declare("pi",
		           {Result_type::Floating_point_value, 3.14159265358979323846},
		           true);
	} else {
		print_greeting_latin(std::cout);
		ts.declare("rmin", {Result_type::Roman_numeral, romi::min_int}, true);
		ts.declare("rmax", {Result_type::Roman_numeral, romi::max_int}, true);
	}

	Stream_pair streams;
	session(ts);
	help::keep_window_open("return to the main program");
}

//------------------------------------------------------------------------------

void calc::session(Token_stream& ts,
                   RM rmode,
                   WM wmode,
                   const std::string& inpath,
                   const std::string& outpath)
{
	if (rmode == RM::Read_from_console && wmode == WM::Write_to_console) {
		Stream_pair streams{};
		calculate(ts, streams);
	} else if (rmode == RM::Read_from_console && wmode == WM::Write_to_file) {
		std::ofstream ofs{outpath};
		Stream_pair streams{std::cin, ofs};
		calculate(ts, streams);
	} else if (rmode == RM::Read_from_file && wmode == WM::Write_to_console) {
		std::ifstream ifs{inpath};
		Stream_pair streams{ifs, std::cout};
		calculate(ts, streams);
	} else if (rmode == RM::Read_from_file && wmode == WM::Write_to_file) {
		std::ofstream ofs{outpath};
		std::ifstream ifs{inpath};
		Stream_pair streams{ifs, ofs};
		calculate(ts, streams);
	} else {
		calc_error(EC::Session_parameters_invalid, "Invalid session parameters");
	}
}

calc::Write_quota calc::nested_session(Token_stream& ts,
                                       const std::string& inpath,
                                       std::ostream& ostr,
                                       Write_quota quota)
{
	std::ifstream ifs{inpath};
	Stream_pair streams{ifs, ostr};
	return calculate(ts, streams, quota);
}

//------------------------------------------------------------------------------

calc::Write_quota calc::calculate(Token_stream& ts,
                                  Stream_pair& streams,
                                  Write_quota quota)
{
	if (streams.read_mode() == RM::Read_from_file) {
		if (!streams.in()) {
			calc_error(EC::Open_read_file_failure, "Failed to open in file");
		}
		streams.in().exceptions(streams.in().exceptions()
		                        | std::ios_base::badbit);
	}

	if (streams.write_mode() == WM::Write_to_file) {
		if (!streams.out()) {
			calc_error(EC::Open_write_file_failure, "Failed to open out file");
		}
		streams.out().exceptions(streams.out().exceptions()
		                         | std::ios_base::badbit);
	}

	// limit in and output
	bool read_limit_exceeded = false;
	bool write_limit_exceeded = false;
	int num_ch_read = 0;
	int num_ch_written = 0;
	int num_statem_written = 0;

	while (streams.in())
		try {
			if (streams.read_mode() == RM::Read_from_console) {
				if (streams.write_mode() == WM::Write_to_file) {
					// std::cout << "Written Ch: " << num_ch_written << " / "
					//           << quota.characters << ",    "
					//           << "St: " << num_statem_written << " / "
					//           << quota.statements << '\n';
					std::cout << "(FILE) ";
				}
				std::cout << prompt << ' ';
			}
			std::vector<std::string> e{line_to_expressions(streams.in())};

			for (int i = 0; i < e.size(); ++i) {
				if (streams.read_mode() == RM::Read_from_file) {
					num_ch_read += e[i].size() + 1;
					if (num_ch_read > read_from_file_char_limit) {
						read_limit_exceeded = true;
						throw 0;
					}
				}
				help::putback_str(streams.in(), {e[i] + "\n"});

				// Check for high priority commands
				Token t{ts.get(streams.in())};
				if (t.kind == quit_token) {
					throw_if_not_end(ts);
					if (streams.read_mode() == RM::Read_from_console) {
						ts.get();               // consume newline token
						std::cin.putback('\n'); // put back newline char
						help::clear_buffer(std::cin);
					} else {
						calc_error(
						    EC::Quit_while_reading,
						    "The 'quit' command is disabled while reading from "
						    "a file");
					}
					return {quota.characters - num_ch_written,
					        quota.statements - num_statem_written};
				}
				if (t.kind == help_token) {
					throw_if_not_end(ts);
					ts.get(streams.in()); // consume newline
					if (ts.version() == Calculator_version::Decimal) {
						print_instructions(streams.out());
					} else {
						print_instructions_latin(streams.out());
					}
					continue;
				}
				if (t.kind == read_token || t.kind == write_token) {
					throw_if_mid_of_chain(e, i);
					Token t_fpath{ts.get(streams.in())};
					if (t_fpath.kind != name) {
						ts.putback(t_fpath);
						calc_error(EC::File_path_expected, "Expected file path");
					}

					throw_if_not_end(ts);
					ts.get(streams.in()); // consume newline

					if (streams.read_mode() != RM::Read_from_console) {
						calc_error(
						    EC::To_or_from_in_ifstream,
						    "The 'to' and 'from' commands are disabled while "
						    "reading from a file");
					}

					// Note that all filepaths have been hard-coded.
					if (t.kind == read_token) {
						std::string path_in;
						if (ts.version() == Calculator_version::Decimal) {
							path_in = file_path_in_decimal();
						} else {
							path_in = file_path_in_roman();
						}
						streams.out() << "Reading from file '" << path_in
						              << "'..." << '\n';
						Write_quota nested_quota{quota.characters
						                             - num_ch_written,
						                         quota.statements
						                             - num_statem_written};
						quota = nested_session(ts,
						                       path_in,
						                       streams.out(),
						                       nested_quota);

						streams.out()
						    << "Finished reading from file..." << '\n';

						// Also close file being written to if quota is depleted
						if (streams.write_mode() == WM::Write_to_file
						    && (quota.characters <= 0
						        || quota.statements <= 0)) {
							return {0, 0};
						}
					} else {
						std::string path_out;
						if (ts.version() == Calculator_version::Decimal) {
							path_out = file_path_out_decimal();
						} else {
							path_out = file_path_out_roman();
						}
						streams.out() << "Writing to file '" << path_out
						              << "'..." << '\n';
						session(ts,
						        RM::Read_from_console,
						        WM::Write_to_file,
						        "",
						        path_out);
						streams.out() << "Finished writing to file..." << '\n';
					}
					continue;
				}

				// Proceed with statement
				ts.putback(t);
				Result st{statement(ts, streams.in())};
				throw_if_not_end(ts);
				ts.get(streams.in()); // consume newline

				if (streams.write_mode() == WM::Write_to_file) {
					++num_statem_written;
					num_ch_written += st.as_string().size();
					if (num_statem_written > quota.statements
					    || num_ch_written > quota.characters) {
						write_limit_exceeded = true;
						throw 0;
					}
				}

				streams.out() << result_sign << ' ' << st << '\n';
			}
		} catch (...) {
			try {
				if (streams.write_mode() == WM::Write_to_file) {
					++num_statem_written;
					if (num_statem_written > quota.statements) {
						write_limit_exceeded = true;
					}
				}
				if (read_limit_exceeded) {
					calc_error(EC::Read_overflow,
					           "The file being read from exceeded the "
					           "character limit, ",
					           true);
				}
				if (write_limit_exceeded) {
					calc_error(EC::Write_overflow,
					           "The maximum number of character allowed to "
					           "be written to disk has been exceeded, ",
					           true);
				}
				bool its_bad = false;
				if (streams.read_mode() == RM::Read_from_file
				    && streams.in().bad()) {
					calc_error(EC::Read_file_bad,
					           "In file in a bad state, ",
					           true);
					its_bad = true;
				}
				if (streams.write_mode() == WM::Write_to_file
				    && streams.out().bad()) {
					calc_error(EC::Write_file_bad,
					           "Out file in a bad state, ",
					           true);
					its_bad = true;
				}
				if (read_limit_exceeded || write_limit_exceeded || its_bad) {
					std::cerr << "aborting..." << '\n';
					break; // exit while loop ---------------
				}

				// Recover from errors
				clean_up_mess(ts, streams.in());
				throw;
			} catch (std::exception& e) {
				if (streams.write_mode() == WM::Write_to_file) {
					streams.out() << e.what() << '\n';
				} else {
					std::cerr << e.what() << '\n';
				}
			} catch (...) {
				std::string msg{"Unexpected error"};
				if (streams.write_mode() == WM::Write_to_file) {
					streams.out() << msg << '\n';
				} else {
					std::cerr << msg << '\n';
				}
			}
		}
	return {quota.characters - num_ch_written,
	        quota.statements - num_statem_written};
}

//------------------------------------------------------------------------------

calc::Result calc::statement(Token_stream& ts, std::istream& istr)
{
	Token t = ts.get(istr);
	switch (t.kind) {
	case let:
	case const_token:
		if (output_trace)
			std::cout << "STA: declaration keyword found, get declaration()"
			          << '\n';
		ts.putback(t); // CH07E03
		return declaration(ts, istr);
		break;
	case name: {
		// CH07E02 Redefine if 'name' is followed by 'assignment' token
		if (output_trace)
			std::cout << "STA: name found, try to get assigment" << '\n';
		Token t_peek = ts.peek(istr); // peek ahead
		if (t_peek.kind == assign) {
			if (output_trace)
				std::cout << "STA: name followed by assignment keyword "
				             "found, put back token: "
				          << t.kind << '\n';
			ts.putback(t);
			return redefinition(ts, istr);
		} else {
			if (output_trace)
				std::cout << "STA: no assigment operator found" << '\n';
		}
	}
	default:
		if (output_trace)
			std::cout << "STA: get expression()" << '\n';
		ts.putback(t);
		return expression(ts, istr);
		break;
	}
	return {};
}

//------------------------------------------------------------------------------

calc::Result calc::redefinition(Token_stream& ts, std::istream& istr)
{
	// after detecting statement w. a name followed by the assignment operator
	if (output_trace)
		std::cout << "RED: get token, fetching name." << '\n';
	Token t{ts.get(istr)};
	if (t.kind != name) {
		ts.putback(t);
		calc_error(EC::Name_expected_in_redefinition,
		           "Expected name in redefinition");
	}
	if (output_trace)
		std::cout << "RED: get token, expecting assignment." << '\n';
	Token t2{ts.get(istr)};
	if (t2.kind != assign) {
		ts.putback(t2);
		calc_error(EC::Assignment_operator_expected_in_redefinition,
		           "Expected assigment operator in redefinition");
	}
	if (output_trace)
		std::cout << "RED: get expression()" << '\n';
	Result d = expression(ts, istr);
	if (output_trace)
		std::cout << "RED: set_value(" << t.name << ", " << d << ')' << '\n';
	ts.set(t.name, d);
	return d;
}

// CH0703, modififed declaration() to handle both constants and regular vars
calc::Result calc::declaration(Token_stream& ts, std::istream& istr)
{
	// after detecting statement w. the declaration or constant keyword
	Token t = ts.get(istr);
	if (t.kind != let && t.kind != const_token) {
		ts.putback(t);
		calc_error(EC::Declaration_or_constant_token_expected,
		           "Expected a declaration or constant token");
	}
	bool is_const{(t.kind == const_token)};
	Token t2 = ts.get(istr);
	if (t2.kind != name) {
		ts.putback(t2);
		calc_error(EC::Name_expected_in_declaration,
		           "name expected in declaration");
	}
	Token t3 = ts.get(istr);
	if (t3.kind != '=') {
		ts.putback(t3);
		calc_error(EC::Assignment_operator_expected_in_declaration,
		           "= missing in declaration of '" + t.name + "'");
	}
	if (output_trace)
		std::cout << "DEC: get expression()" << '\n';
	Result d = expression(ts, istr);
	if (output_trace)
		std::cout << "DEC: define_name(" << t2.name << ", " << d << ")" << '\n';
	ts.declare(t2.name, d, is_const);
	return d;
}

//------------------------------------------------------------------------------

calc::Result calc::expression(Token_stream& ts, std::istream& istr)
{
	if (output_trace)
		std::cout << "EXP: get term" << '\n';
	Result left = term(ts, istr);

	if (output_trace)
		std::cout << "EXP: get next token" << '\n';
	Token t = ts.get(istr); // get next token
	while (true) {
		switch (t.kind) {
		case '+': // addition
			if (output_trace)
				std::cout << "EXP: add, getting term" << '\n';
			left = left + term(ts, istr);
			if (output_trace)
				std::cout << "EXP: result of addition " << left << '\n';
			if (output_trace)
				std::cout << "EXP: get next token" << '\n';
			t = ts.get(istr);
			break;
		case '-': // subtraction
			if (output_trace)
				std::cout << "EXP: subtract, getting term" << '\n';
			left = left - term(ts, istr);
			if (output_trace)
				std::cout << "EXP: result of subtraction " << left << '\n';
			if (output_trace)
				std::cout << "EXP: get next token" << '\n';
			t = ts.get(istr);
			break;
		default:
			if (output_trace)
				std::cout << "EXP: put back " << t.kind << " into buffer"
				          << '\n';
			ts.putback(t);
			if (output_trace)
				std::cout << "EXP: return result " << left << '\n';
			return left;
		}
	}
	return {};
}

//------------------------------------------------------------------------------

calc::Result calc::term(Token_stream& ts, std::istream& istr)
{
	if (output_trace)
		std::cout << "TER: get primary" << '\n';
	Result left{primary(ts, istr)};

	if (output_trace)
		std::cout << "TER: get next token" << '\n';
	Token t = ts.get(istr); // get next token

	while (true) {
		switch (t.kind) {
		case '*': // multiply
			if (output_trace)
				std::cout << "TER: multiply, getting primary" << '\n';
			left = left * primary(ts, istr);
			if (output_trace)
				std::cout << "TER: result of multiplication: " << left << '\n';
			if (output_trace)
				std::cout << "TER: get next token" << '\n';
			t = ts.get(istr);
			break;
		case '/': // division
		{
			if (output_trace)
				std::cout << "TER: divide, getting primary" << '\n';
			Result prim = primary(ts, istr);
			if (prim == 0)
				calc_error(EC::Divide_by_zero, "Divide by zero");
			left = left / prim;
			if (output_trace)
				std::cout << "TER: result of division: " << left << '\n';
			if (output_trace)
				std::cout << "TER: get next token" << '\n';
			t = ts.get(istr);
			break;
		}
		case '%': // modulo
		{
			if (ts.version() == Calculator_version::Roman) {
				Result i1 = primary(ts, istr);
				if (i1 == 0)
					calc_error(EC::Modulo_divide_by_zero, "% Divide by zero");
				left = left % i1;
				t = ts.get(istr);
			} else {
				calc_error(
				    EC::Modulus_on_floating_point,
				    "Modulus is not supported for floating-point values");
			}
			break;
		}
		case assign: // CH07E02, assignment not allowed as part of an expression
			calc_error(
			    EC::Assignment_operator_invalid_context,
			    "The assignment operator cannot be used in this context. "
			    "Variables may only be redefined as separate statements.");
			break;
		default:
			if (output_trace)
				std::cout << "TER: put back" << t.kind << " into buffer"
				          << '\n';
			ts.putback(t);
			if (output_trace)
				std::cout << "TER: return result: " << left << '\n';
			return left;
		}
	}
	return {};
}

//------------------------------------------------------------------------------

calc::Result calc::primary(Token_stream& ts, std::istream& istr)
{
	if (output_trace)
		std::cout << "PRI: get token" << '\n';
	Token t = ts.get(istr);
	switch (t.kind) {
	case '(': // expression
	{
		if (output_trace)
			std::cout << "PRI: found '(', get expression" << '\n';
		Result exp = expression(ts, istr);
		if (output_trace)
			std::cout << "PRI: eof expression, expecting ')'" << '\n';
		t = ts.get(istr);
		if (t.kind != ')') {
			ts.putback(t);
			calc_error(EC::Parentheses_expected_at_expression_end,
			           "expected ')'");
		}
		return exp;
	}
	case sqrt_token: // square root
	{
		t = ts.get(istr);
		if (t.kind != '(') {
			ts.putback(t);
			calc_error(EC::Parentheses_expected_at_square_root_start,
			           "expected '(' after square root keyword");
		}
		if (output_trace)
			std::cout << "PRI: found '(' after square root keyword, "
			          << "get expression() of which we want to get "
			          << "the square root" << '\n';
		Result exp = expression(ts, istr);
		if (exp < 0)
			calc_error(EC::Square_root_of_negative_value,
			           "cannot calculate square root of a negative number");
		t = ts.get(istr);
		if (t.kind != ')') {
			ts.putback(t);
			calc_error(EC::Parentheses_expected_at_square_root_end,
			           "expected ')' after square root expression");
		}
		if (output_trace)
			std::cout << "PRI: getting squareroot." << '\n';
		double sqrt_val{sqrt(exp.as_floating_point())};
		Result_type type{exp.type};
		if (type == Result_type::Floating_point_value) {
			return {type, sqrt_val};
		} else {
			return {type, help::narrow_cast<int>(sqrt_val)};
		}
	}
	case pow_token: // power of
	{
		t = ts.get(istr);
		if (t.kind != '(') {
			ts.putback(t);
			calc_error(EC::Parentheses_expected_at_power_of_start,
			           "expected '(' after power of keyword");
		}
		if (output_trace)
			std::cout << "PRI: found '(' after power of keyword, "
			          << "get the expression() of which we want to raise "
			             "by a number"
			          << '\n';
		Result expr = expression(ts, istr);
		t = ts.get(istr);
		if (t.kind != ',') {
			ts.putback(t);
			calc_error(EC::Comma_expected_after_power_of_base,
			           "expected ',' after expression");
		}
		if (output_trace)
			std::cout << "PRI: getting exponent expression()" << '\n';
		Result expo = expression(ts, istr);
		t = ts.get(istr);
		if (t.kind != ')') {
			ts.putback(t);
			calc_error(EC::Parentheses_expected_at_power_of_end,
			           "expected ')' after exponent");
		}
		double pow_val = 0;
		double expr_val = expr.as_floating_point();
		double expo_val = expo.as_floating_point();
		Result_type type_expr{expr.type};
		Result_type type_expo{expo.type};
		Result_type type_return{Result_type::Floating_point_value};
		if (type_expr != Result_type::Floating_point_value
		    || type_expo != Result_type::Floating_point_value) {
			expr_val = help::narrow_cast<int>(expr_val);
			expo_val = help::narrow_cast<int>(expo_val);
			pow_val = help::narrow_cast<int>(pow(expr_val, expo_val));
			type_return = Result_type::Roman_numeral;
		} else {
			pow_val = pow(expr_val, expo_val);
		}
		return {type_return, pow_val};
	}
	case number: // number
		if (output_trace)
			std::cout << "PRI: found number: " << t.result << '\n';
		return t.result;
	case hex_token: // CH07E09
		return t.result;
	case roman: // CH07E09
		return t.result;
	case '-':
		return -1 * primary(ts, istr);
	case '+':
		return primary(ts, istr);
	case name:
		return ts.get(t.name);
	default:
		ts.putback(t);
		calc_error(EC::Primary_expected, "expected Primary");
	}
	return {};
}

//------------------------------------------------------------------------------

void calc::print_instructions(std::ostream& os)
{
	os << "The following arithmetic operators are available: " << '\n'
	   << "    "
	   << "'-', '+', '/', '*' ,'%'" << '\n'
	   << "Use parentheses for grouping.\n"
	   << "Declare / define variables using:" << '\n'
	   << "    '" << declkey << " name " << assign << " value'" << '\n'
	   << "    '" << constkey << " name " << assign << " value'"
	   << " (immutable variable)" << '\n'
	   << "    'name " << assign << " value'"
	   << " (reassign value to existing)" << '\n'
	   << "Available functions:" << '\n';
	for (const string& fn : available_fn()) {
		os << "    " << fn << '\n';
	}
}

void calc::print_instructions_latin(std::ostream& os)
{
	os << "Sequentes operatores arithmetici sunt disponibiles: " << '\n'
	   << "    "
	   << "'-', '+', '/', '*' ,'%'" << '\n'
	   << "Utere parenthesibus ad grouping.\n"
	   << "Variabiles declara/define usando:" << '\n'
	   << "    '" << declkey << " nomen " << assign << " valor'" << '\n'
	   << "    '" << constkey << " nomen " << assign << " valor'"
	   << " (variabilis immutabilis)" << '\n'
	   << "    'nomen " << assign << " valor'"
	   << " (reassigna valorem ad existentem)" << '\n'
	   << "Functiones disponibiles:" << '\n';
	for (const string& fn : available_fn()) {
		os << "    " << fn << '\n';
	}
}

void calc::print_greeting(std::ostream& os)
{
	os << "Calculator\n"
	   << "Please enter expressions using floating-point numbers, " << '\n'
	   << "finish with <Enter>.\n"
	   << "(!) Use the '" << hex_prefix << "' prefix to define numbers using "
	   << '\n'
	   << "    hexadecimal notation. e.g. '0xFF' equals '255'" << '\n'
	   << "(!) Write '" << quit_key << "' to exit"
	   << " or '" << help_key << "' for more info." << '\n';
	print_instr_to_from(os);
}

void calc::print_greeting_latin(std::ostream& os)
{
	os << "Computus\n"
	   << "Quaeso inscribe expressiones usurpando numeros fluminis "
	      "mobilis, "
	   << '\n'
	   << "conclude cum <Enter>.\n"
	   << "(!) Utere praefixo '" << hex_prefix
	   << "' ad definiendum numeros usurpando " << '\n'
	   << "    notationem hexadecimalem. e.g. '0xFF' aequabitur '255'" << '\n'
	   << "(!) Scribe '" << quit_key << "' ad exeundum"
	   << " vel '" << help_key << "' ad petendum plus informationis." << '\n'
	   << "(!) Haec versio calculatoris operatur in <int> solummodo " << '\n'
	   << "    itaque amissio praecisionis posset accidere, e.g. quicquid "
	   << '\n'
	   << "    supra 0x7FFFFFFF efficiet inundationem in plerisque "
	      "systematibus."
	   << '\n';
	print_instr_to_from_latin(os);
}

void calc::print_instr_to_from(std::ostream& os)
{
	os << "(!) Use '" << read_key() << " x' to read and parse expressions"
	   << '\n'
	   << "    from a text file" << '\n'
	   << "(!) Use '" << write_key()
	   << " y' to direct all output to a text file," << '\n'
	   << "    type '" << quit_key << "' to exit from this context." << '\n';
}

void calc::print_instr_to_from_latin(std::ostream& os)
{
	os << "(!) Utitur '" << read_key()
	   << " x' ad legere et parsere expressiones" << '\n'
	   << "    ex scheda textuali" << '\n'
	   << "(!) Utitur '" << write_key()
	   << " y' ad omne productum dirigere ad schedam textualis," << '\n'
	   << "    type '" << quit_key << "' ex hac contextu excedere." << '\n';
}
