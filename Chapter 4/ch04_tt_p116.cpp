#include "std_lib_facilities.h"

namespace ch04_tt_p116
{
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
			cout << i << '\t' << square(i) << '\n';
		}
		keep_window_open();
		return 0;
	}
}