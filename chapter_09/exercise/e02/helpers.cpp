#include "helpers.h"

//------------------------------------------------------------------------------
// Helper functions

void swap(int& a, int& b) {
	int temp{ a };
	a = b;
	b = temp;
}

void swap(std::string& a, std::string& b) {
	std::string temp{ a };
	a = b;
	b = temp;
}

int find_element(const std::string& s,
                 const std::vector<std::string>& unsorted,
                 const std::vector<std::string>& sorted) {
	int idx{ -1 }; // no match
	for (int i = 0; i < sorted.size(); ++i) {
		if (unsorted.at(i) != sorted.at(i) && s == unsorted.at(i)) {
			idx = i;
			break;
		}
	}
	return idx;
}

void clear_buffer(std::istream& is) {
	char c{};
	while(is.get(c) && c != '\n') {}
}

void keep_window_open() {
	#if defined _WIN32 || defined _WIN64
    system("pause");
	#endif
}

//------------------------------------------------------------------------------
