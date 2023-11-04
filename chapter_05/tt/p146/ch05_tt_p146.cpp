#include "../../lib/std_lib_facilities.h"

// calculate area of a rectangle;
int area(int length, int width)
{
	if (length <= 0 || width <= 0) {
		std::cerr << "non-positive argument called by area()\n";
	}
	return length * width;
}

int framed_area(int x, int y)      // calculate area within frame
{
	constexpr int frame_width = 2;
	if (x - frame_width <= 0 || y - frame_width <= 0) {
		std::cerr << "non-positive area() argument called by framed_area()\n";
	}
	return area(x - frame_width, y - frame_width);
}

float get_ratio(int area1, int area2) {
	if (area1 <= 0 || area2 <= 0) {
		std::cerr << "non-positive argument called by get_ratio()\n";
	}
	return float(area1) / area2;
}

int main()
{
	int x, y, z;

	while (std::cin >> x >> y >> z) {
		int area1 = area(x, y);
		int area2 = framed_area(x, z);
		double ratio = get_ratio(area1, area2);
		std::cout << "Area 1: " << area1 << '\t'
			 << "Area 2: " << area2 << '\t'
			 << "Ratio: "  << ratio << '\n';
	}

	keep_window_open();

	return 0;
}
