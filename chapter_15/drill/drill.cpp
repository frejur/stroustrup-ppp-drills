#include "../lib/Graph.h"
#include "../lib/Window.h"

double slope(double x)
{
	return x / 2;
};

using Fct = std::function<double(double)>;

struct Funky : Graph_lib::Shape
{
	// the function parameters are not stored
	Funky(Fct f,
	      double r1,
	      double r2,
	      Graph_lib::Point xy,
	      int count = 100,
	      double xscale = 25,
	      double yscale = 25)

	{
		if (r2 - r1 <= 0)
			error("bad graphing range");
		if (count <= 0)
			error("non-positive graphing count");
		double dist = (r2 - r1) / count;
		double r = r1;

		double prev_x = r1 * xscale + xy.x;
		int last_u = static_cast<int>(prev_x / xscale);
		for (int i = 0; i < count; ++i) {
			double curr_x = r * xscale + xy.x;
			int curr_u = static_cast<int>(curr_x / xscale);
			if (i == 0 || i == count - 1 || curr_u > last_u) {
				int offsy = 300;
				add(Graph_lib::Point{
				    xy.x + static_cast<int>(std::round(r * xscale)),
				    xy.y - static_cast<int>(std::round(f(r) * yscale))});
				add(Graph_lib::Point{
				    xy.x + static_cast<int>(std::round(r * xscale)),
				    xy.y - static_cast<int>(std::round(f(r) * yscale) + offsy)});
				add(Graph_lib::Point{
				    xy.x + static_cast<int>(std::round(r * xscale)),
				    xy.y - static_cast<int>(std::round(f(r) * yscale) - offsy)});
				last_u = curr_u;
			}
			add(Graph_lib::Point{xy.x + int(std::round(r * xscale)),
			                     xy.y - int(std::round(f(r) * yscale))});
			r += dist;
		}
	};
	Funky(double (*f)(double),
	      double r1,
	      double r2,
	      Graph_lib::Point xy,
	      int count = 100,
	      double xscale = 25,
	      double yscale = 25)
	    : Funky{static_cast<Fct>(f), r1, r2, xy, count, xscale, yscale} {};
};

void drill()
{
	constexpr int xmax = 600;
	constexpr int ymax = 400; // Bounds
	constexpr int x_orig = xmax / 2;
	constexpr int y_orig = ymax / 2; // Graph origin
	constexpr int r_min = -10;
	constexpr int r_max = 11; // # of units
	constexpr int x_scale = 30;
	constexpr int y_scale = 30; // Unit size
	constexpr int n_points = 400;
	Graph_lib::Window win{{0, 0}, xmax, ymax, "Drill"};

	fl_color(0);
	// Initialize graph
	Funky slope_f{slope,
	              r_min,
	              r_max,
	              {x_orig, y_orig},
	              n_points,
	              x_scale,
	              y_scale};

	win.attach(slope_f);

	constexpr int xlength = xmax - 40;
	// make the axis a bit smaller than the window

	constexpr int ylength = ymax - 40;
	Graph_lib::Axis x{Graph_lib::Axis::x,
	                  Graph_lib::Point{20, y_orig},
	                  xlength,
	                  xlength / x_scale,
	                  "one notch == 1"};
	x.set_color(Graph_lib::Color::red);
	Graph_lib::Axis y{Graph_lib::Axis::y,
	                  Graph_lib::Point{x_orig, ylength + 20},
	                  ylength,
	                  ylength / y_scale,
	                  "one notch == 1"};
	win.attach(x);
	win.attach(y);

	Graph_lib::Rectangle r{{x_orig, y_orig}, x_scale, y_scale};
	win.attach(r);

	Graph_lib::gui_main();
}

int main()
try {
	drill();
} catch (const std::exception& e) {
	std::cerr << "Error: " << e.what() << '\n';
	std::cin.get();
} catch (...) {
	std::cerr << "Unknown error" << '\n';
	std::cin.get();
}
