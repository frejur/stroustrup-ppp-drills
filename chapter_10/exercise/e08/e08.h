#ifndef E08_H
#define E08_H

#include <string>

namespace e08 {

// -----------------------------------------------------------------------------

inline const std::string& file_path_start()
{
	static std::string s{"data/start.txt"};
	return s;
}

inline const std::string& file_path_end()
{
	static std::string s{"data/end.txt"};
	return s;
}

inline const std::string& file_path_final()
{
	static std::string s{"data/final.txt"};
	return s;
}

// -----------------------------------------------------------------------------

void concat_files(const std::string& file_a,
                  const std::string& file_b,
                  const std::string& file_merged);

} // namespace e08

#endif
