#include "../../lib/std_lib_facilities.h"
using std::cin;
using std::cout;

// Exercise 2. Fix the Celsius to Kelvin program

static constexpr char DEG{ '\370' };

double ctok(double c)
{
	double k = c + 273.15;
	return k;
}

int main()
{
	cout
		<< "Enter a temperature value in degrees Celsius "
		<< "to convert it into Kelvin\n";
	double c = 0;
	cin >> c;
	double k = ctok(c);
	cout << c << DEG << "C = " << k << 'K' << '\n';

	keep_window_open();
	return 0;
}


// Original code:
//double ctok(double c)
//{
//	int k = c + 273.15;
//	return int;
//}

//int main()
//{
//	double c = 0;
//	cin >> d;
//	double k = ctok("c");
//	Cout << k << '\n';
//}
