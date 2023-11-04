#include "../../lib/std_lib_facilities.h"

int square(int n) {
	int result = 0;
	for (int i = 0; i < n; ++i) {
		result += n;
	}
	return result;
}
int main()
{
	for (int i = 0; i < 100; ++i) {
		std::cout << i << '\t' << square(i) << '\n';
	}
	keep_window_open();
	return 0;
}
