#ifndef E06_H
#define E06_H
#include <vector>
#include <string>

namespace e06{
// -----------------------------------------------------------------------------

inline const std::string& file_path_test_punct() {
    static const std::string f{"data/test_punct.txt"};
    return f;
};
inline const std::string& file_path_contractions() {
    static const std::string f{"data/contractions.txt"};
    return f;
};
inline const std::string& file_path_test_contr() {
    static const std::string f{"data/test_contr.txt"};
    return f;
};
inline const std::string& file_path_multi_page()
{
	static const std::string f{"data/multi_page.txt"};
    return f;
};

// -----------------------------------------------------------------------------

enum class Command_ID {
	Unknown = -1,
	Test_punctuation = 0,
	Test_contractions,
	Generate_dictionary,
	Quit
};

struct Command
{
	Command_ID id;
	char symbol;
	std::string name;
};

inline const std::vector<Command>& options()
{
	static const std::vector<Command>
	    c{{Command_ID::Test_punctuation, 'a', "Test strip punctuation"},
	      {Command_ID::Test_contractions,
	       'b',
	       "Test convert contractions (Don't = Do not, etc.)"},
	      {Command_ID::Generate_dictionary,
	       'c',
	       "Generate dictionary from a multi-page file"},
	      {Command_ID::Quit, 'q', "Quit"}};
	return c;
}

// -----------------------------------------------------------------------------

void print_hello();
void print_options();

// -----------------------------------------------------------------------------

Command_ID get_command(std::istream& is);

// -----------------------------------------------------------------------------

void run_test_punctuation();
void run_test_contractions();
void run_test_dictionary();

// -----------------------------------------------------------------------------

} // namespace e06

#endif // E06_H
