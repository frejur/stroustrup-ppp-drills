#include "../../lib/std_lib_facilities.h"

int main()
{
	int i = 0;
	while (i <= 25) {
		std::cout << char('a' + i) << '\t' << 'a' + i << '\n';
		++i;
	}
	keep_window_open();
	return 0;
}
