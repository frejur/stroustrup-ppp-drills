#include "../../lib/Debug_window.h"
#include "../../lib/Graph.h"
#include <cmath>

// Exercise 5 & 6
// Define subclasses of Rectangle and Circle that draw their respective shapes
// filled with a scanline pattern instead of just a single color.

int main() {
	try {
		constexpr int w{640};
		constexpr int h{480};
		const int mid_x{static_cast<int>(std::round(w * 0.5))};
		const int mid_y{static_cast<int>(std::round(h * 0.5))};

		Debug_window win{{100, 100}, w, h, "Filling in the gaps"};

		Graph_lib::Rectangle r{{mid_x, mid_y}, {mid_x + 100, mid_y + 200}};
		win.attach(r);

		win.wait_for_button();
	} catch (exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	} catch (...) {
		std::cerr << "Unknown error\n";
		return 2;
	}
	return 0;
}
