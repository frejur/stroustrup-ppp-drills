#include "std_lib_facilities.h"

namespace ch04_tt_p113
{
	int main()
	{
		for (int i = 0; i <=25; ++i) {
			cout << char('a' + i) << '\t' << 'a' + i
				 << "\t | " << char('A' + i) << '\t' << 'A' + i << '\n';
		}
		keep_window_open();
		return 0;
	}
}