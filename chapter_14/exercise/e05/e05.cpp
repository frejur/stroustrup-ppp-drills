#include "../../lib/Debug_window.h"
#include "../../lib/Graph.h"
#include "../share/geo/strpe_circ.h"
#include "../share/geo/strpe_rec.h"
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

		strpe_geo::Striped_rectangle r{{mid_x - 200, mid_y - 100},
		                               {mid_x + 40, mid_y + 50},
		                               5,
		                               10};
		r.set_color(Graph_lib::Color::invisible);
		r.set_fill_color(Graph_lib::Color::dark_green);
		win.attach(r);

		strpe_geo::Striped_rectangle r2{{mid_x - 50, mid_y - 50},
		                                {mid_x + 200, mid_y + 200},
		                                1,
		                                1};
		r2.set_color(Graph_lib::Color::black);
		r2.set_fill_color(Graph_lib::Color::red);
		r2.set_style(Graph_lib::Line_style(Graph_lib::Line_style::solid, 5));
		win.attach(r2);

		strpe_geo::Striped_circle c{{mid_x - 150, mid_y - 17}, 125, 10, 5};
		c.set_color(Graph_lib::Color::invisible);
		c.set_fill_color(Graph_lib::Color::yellow);
		win.attach(c);

		strpe_geo::Striped_circle c2{{mid_x + 160, mid_y - 130}, 64, 2, 4};
		c2.set_color(Graph_lib::Color::invisible);
		c2.set_fill_color(Graph_lib::Color::white);
		win.attach(c2);

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
