#include "std_lib_facilities.h"

namespace ch04_tt_p111
{
	int main()
	{
		int i = 0;
		while (i <= 25) {
			cout << char('a' + i) << '\t' << 'a' + i << '\n';
			++i;
		}
		keep_window_open();
		return 0;
	}
}