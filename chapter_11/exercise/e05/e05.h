#ifndef E03_H
#define E03_H

#include "../../lib/help.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace e05 {

//------------------------------------------------------------------------------

inline const std::string& file_path_text()
{
	static std::string p{"data/otwist.txt"};
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

//------------------------------------------------------------------------------

void consume_leftover_endl();
Command get_command(bool restore_buffer = false);
void run_manual_input_mode();
void load_input_from_file(const std::string& file_path);
void print_commands();

//------------------------------------------------------------------------------
} // namespace e05

#endif
