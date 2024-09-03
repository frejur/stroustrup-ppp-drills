#include "../../lib/Debug_window.h"
#include "../../lib/Graph.h"
#include "../share/geo/strpe_pline.h"
#include "dynpline.h"
#include <cmath>

// Exercise 7. Striped_closed_polyline

// Renamed it to just 'Striped_polyline'.
// Allowed for the user to draw their own shapes.

const std::string& info_click()
{
	static const std::string s{
	    "Click anywhere to start drawing a polyline"};
	return s;
}

const std::string& info_transform()
{
	static const std::string s{
	    "Keep clicking to add segments, finish by clicking the starting point."};
	return s;
}

//------------------------------------------------------------------------------

namespace e07draw {

class Draw_polyline : public Shape
{
public:
	Draw_polyline(){};
	void add_pline(const std::vector<GL::Point>& pts)
	{
		pline_v.push_back(std::make_unique<strpe_geo::Striped_polyline>());
		for (Graph_lib::Point pt : pts) {
			pline_v.back()->add(pt);
		}
		pline_v.back()->set_color(Graph_lib::Color::dark_magenta);
		pline_v.back()->set_style(
		    Graph_lib::Line_style(Graph_lib::Line_style::solid, 4));
		pline_v.back()->set_fill_color(Graph_lib::Color::green);
	};
	void draw_lines() const
	{
		for (int i = 0; i < pline_v.size(); ++i) {
			pline_v[i]->draw();
		}
	};

private:
	std::vector<std::unique_ptr<strpe_geo::Striped_polyline>> pline_v;
};
} // namespace e07draw

//------------------------------------------------------------------------------

void e07()
{
	constexpr bool ENABLE_DEBUG{false};
	constexpr bool ENABLE_CLICK{true};

	constexpr int win_w{ 640 };
	constexpr int win_h{ 480 };
	GL::Point c{ static_cast<int>(win_w*0.5), static_cast<int>(win_h*0.5) };
	Debug_window win{{10, 10},
	                 win_w,
	                 win_h,
	                 "Raster Master",
	                 ENABLE_DEBUG,
	                 ENABLE_CLICK};

	fl_color(0);
	const GL::Point o{32, 64};
	const int t_w{win_w - 64};
	const int t_h{win_h - 96};

	dynpline::Dynamic_pline dyn_p{o, {o.x + 1, o.y + 1}};
	win.attach(dyn_p);

	dynpline::Window_and_pline pass_to_callback{win, dyn_p};

	Graph_lib::Text info{{64, 32}, info_click()};
	win.attach(info);

	// Store and draw polylines
	e07draw::Draw_polyline dp{};
	win.attach(dp);

	int count_logged = 0;
	while (win.shown()) {
		if (win.click_has_been_registered()) {
			if (!dyn_p.is_transforming()) {
				dyn_p.enable_transform();
				hacky_redraw_pline(pass_to_callback); // transform by moving mouse
				info.set_label(info_transform());
			} else {
				dyn_p.apply_transform();
				++count_logged;
				if (count_logged > 10) {
					win.clear_logs();
					count_logged = 0;
				}
				if (!dyn_p.is_transforming()) {
					dp.add_pline(dyn_p.points());
					info.set_label(info_click());
				}
			}
		}
		win.wait_for_click();
	}
}


int main() {
	try {
		e07();
		return 0;
	} catch (exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	} catch (...) {
		std::cerr << "Unknown error\n";
		return 2;
	}
	return 0;
}
