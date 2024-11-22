#ifndef E04_H
#define E04_H

#include "../../lib/help.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace e04 {

//------------------------------------------------------------------------------

inline const std::string& file_path_input()
{
	static std::string p{"data_e04/input.txt"};
	return p;
}

struct Command
{
	std::string symbol;
	std::string name;
};

inline bool operator==(const Command& cmd_a, const Command& cmd_b)
{
	return cmd_a.symbol == cmd_b.symbol;
}
inline bool operator!=(const Command& cmd_a, const Command& cmd_b)
{
	return !(cmd_a == cmd_b);
}

inline const Command& cmd_manual_input()
{
	static Command c{"a", "Manual input"};
	return c;
}

inline const Command& cmd_load_from_file()
{
	static Command c{"b", "Load input from file"};
	return c;
}

inline const Command& cmd_quit()
{
	static Command c{"q", "Exit"};
	return c;
}

inline const std::vector<Command>& commands()
{
	static std::vector<Command> cmds{cmd_manual_input(),
	                                 cmd_load_from_file(),
	                                 cmd_quit()};
	return cmds;
}

//------------------------------------------------------------------------------

inline int names_max_size(const std::vector<std::string>& names)
{
	int max_sz = 0;
	for (int i = 0; i < names.size(); ++i) {
		max_sz = (max_sz < names[i].size() ? names[i].size() : max_sz);
	}
	return max_sz;
}

inline std::vector<std::string> make_eq_len(
    const std::vector<std::string> strings, int max_len)
{
	std::vector<std::string> new_strings;
	for (const std::string& s : strings) {
		new_strings.push_back(s);
		for (int i = max_len - s.size(); i > 0; --i) {
			new_strings.back().push_back(' ');
		}
	}
	return new_strings;
}

enum class Input_type { Unknown = -1, Decimal, Hexadecimal, Octal };
inline const std::string& input_type_name(Input_type t,
                                          bool append_spaces = false)
{
	static std::vector<std::string> names{"Unknown",
	                                      "Decimal",
	                                      "Hexadecimal",
	                                      "Octal"};
	static int max_sz = names_max_size(names);
	static std::vector<std::string> names_eq_len{make_eq_len(names, max_sz)};

	if (append_spaces) {
		return names_eq_len.at(static_cast<int>(t) + 1);
	}
	return names.at(static_cast<int>(t) + 1);
}

Input_type input_type(const std::string& s, int v);
std::ostream& operator<<(std::ostream& os, Input_type t);

struct Multi_input
{
	int value;
	Input_type type;
	std::string input;
};

std::ostream& operator<<(std::ostream& os, Multi_input mi);

class Multi_stream
{
public:
	Multi_stream(std::istream& is)
	    : src(is)
	{
		buf.unsetf(std::ios_base::dec);
	};
	Multi_stream& operator>>(Multi_input& mi);
	operator bool()
	{
		return !(src.fail() || src.bad()) && (buf.good() || buf.eof());
	};
	void clear()
	{
		src.clear();
		buf.clear();
	}

private:
	std::istream& src;
	std::stringstream buf;
};

//------------------------------------------------------------------------------

void consume_leftover_endl();
Command get_command(bool restore_buffer = false);
void run_manual_input_mode();
void load_input_from_file(const std::string& file_path);
void print_commands();

//------------------------------------------------------------------------------
} // namespace e04

#endif
