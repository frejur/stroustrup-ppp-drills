#ifndef E06_H
#define E06_H
#include "dstr/dstr.h"
#include <string>
#include <vector>

namespace e06{

// -----------------------------------------------------------------------------

inline const std::string& quit_word()
{
	static const std::string q{"quit;"};
	return q;
}

// -----------------------------------------------------------------------------

inline const std::string& file_path_test_punct() {
    static const std::string f{"data_e06/test_punct.txt"};
    return f;
};
inline const std::string& file_path_contractions() {
    static const std::string f{"data_e06/contractions.txt"};
    return f;
};
inline const std::string& file_path_test_contr() {
    static const std::string f{"data_e06/test_contr.txt"};
    return f;
};
inline const std::string& file_path_multi_page()
{
	static const std::string f{"data_e06/multi_page.txt"};
    return f;
};

// -----------------------------------------------------------------------------

constexpr int word_padding{8};
constexpr int max_width{80};

// -----------------------------------------------------------------------------

enum class Command_ID {
	Unknown = -1,
	Manual_input,
	Test_punctuation,
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
	    c{{Command_ID::Manual_input, 'a', "Manually enter words"},
	      {Command_ID::Test_punctuation, 'b', "Test strip punctuation"},
	      {Command_ID::Test_contractions,
	       'c',
	       "Test convert contractions (Don't = Do not, etc.)"},
	      {Command_ID::Generate_dictionary,
	       'd',
	       "Generate dictionary from a multi-page file"},
	      {Command_ID::Quit, 'q', "Quit"}};
	return c;
}

// -----------------------------------------------------------------------------

void print_hello();
void print_options();
void print_input_help();

// -----------------------------------------------------------------------------

Command_ID get_command(std::istream& is);

// -----------------------------------------------------------------------------

void run_manual_input();
void run_tests(const std::string& test_cases_file_path);
void run_test_dictionary();

// -----------------------------------------------------------------------------

void add_contractions_from_file(dstr::Dict_stream& ds,
                                const std::string& file_path);

// -----------------------------------------------------------------------------
struct Test_case
{
	std::string input;
	std::string expected;
};

std::vector<Test_case> test_cases_from_file(const std::string& file_path);

// -----------------------------------------------------------------------------

} // namespace e06

#endif // E06_H
