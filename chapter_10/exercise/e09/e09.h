#ifndef E09_H
#define E09_H

#include <string>
#include <vector>

namespace e09 {

// -----------------------------------------------------------------------------

inline const std::string& file_path_words_01()
{
	static std::string s{"data_e09/words_01.txt"};
	return s;
}

inline const std::string& file_path_words_02()
{
	static std::string s{"data_e09/words_02.txt"};
	return s;
}

inline const std::string& file_path_final()
{
	static std::string s{"data_e09/final.txt"};
	return s;
}

// -----------------------------------------------------------------------------

void append_words_from_file(std::vector<std::string>& words,
                            const std::string& file_path);
std::vector<std::string> words_from_files(
    const std::vector<std::string>& file_paths);
void words_to_file(const std::vector<std::string>& words,
                   const std::string& file_path);

} // namespace e09

#endif
