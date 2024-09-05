#define _USE_MATH_DEFINES
#include "../../lib/Debug_window.h"
#include "../../lib/Graph.h"
#include "../share/anim/anim_shp.h"
#include "../share/geo/regularpoly.h"
#include <cmath>

// Exercise 8. Create a (Regular) 'Octagon' Shape class and test its functions.

// Notes:
// - Reused Regular_polygon code from the previous chapters as the base class.
// - Changed Regular_polygon class, implemented the following methods:
//   + move(int offset_x, int offset_y)
//   + scale(double scale_factor)
//   + rotate(double offset_degrees)
// - Changes to some of Regular_poly's interface and implementation logic,
//   (e.g. Initial placement is now based on the center point)
// - Test the above methods by creating an Octagon object and animating it.

const std::string& info_start()
{
	static const std::string s{"Click to start the animation."};
	return s;
}

const std::string& info_stop()
{
	static const std::string s{"Click to STOP."};
	return s;
}
const std::vector<Graph_lib::Color>& colors()
{
	static const std::vector<Graph_lib::Color>& c{Graph_lib::Color::dark_magenta,
	                                              Graph_lib::Color::yellow,
	                                              Graph_lib::Color::dark_green,
	                                              Graph_lib::Color::white};
	return c;
}

const std::vector<Graph_lib::Line_style>& styles()
{
	static const std::vector<Graph_lib::Line_style>
	    s{Graph_lib::Line_style(Graph_lib::Line_style::dash, 5),
	      Graph_lib::Line_style(Graph_lib::Line_style::solid, 10),
	      Graph_lib::Line_style(Graph_lib::Line_style::dot, 3)};
	return s;
}

//------------------------------------------------------------------------------

class Octagon_animator : public anim::Shape_animator
{
public:
	using anim::Shape_animator::Shape_animator;

private:
	void animate() override
	{
		RPOL::RegularPolygon& p = dynamic_cast<RPOL::RegularPolygon&>(ws.shape);

		p.rotate(10); // Spin

		// Move in circular pattern
		double time_f = time() / time_out();
		double move_angle = M_PI * 2 * time_f - M_PI;
		double move_dist = 4 * p.radius() / (time_out() / refresh_rate());
		double move_x = cos(move_angle) * move_dist;
		move_x += (move_x > 0) ? 0.5 : -0.5;
		double move_y = sin(move_angle) * move_dist;
		move_y += (move_y > 0) ? 0.5 : -0.5;
		p.move(static_cast<int>(move_x), static_cast<int>(move_y));

		// Grow / shrink
		double cycles = 4;
		double adj_time_f = (sin(cycles * 2 * M_PI * time_f - 0.5 * M_PI) + 1)
		                    / 2;
		double cycle_div = (1.0 / cycles) * 0.5;
		int current_cycle = static_cast<int>(time_f / cycle_div);
		double adj_time_f2 = adj_time_f;
		if (current_cycle % 2 == 1) {
			adj_time_f2 = (adj_time_f - 1) * 0.55;
			adj_time_f2 *= -adj_time_f2;
		} else {
			adj_time_f2 *= adj_time_f2;
		}
		p.scale(1 + adj_time_f2 * 0.05);
	};
};

//------------------------------------------------------------------------------

void e08()
{
	constexpr bool ENABLE_DEBUG{false};
	constexpr bool ENABLE_CLICK{true};

	constexpr int win_w{ 640 };
	constexpr int win_h{ 480 };
	GL::Point c{ static_cast<int>(win_w*0.5), static_cast<int>(win_h*0.5) };
	Debug_window win{{10, 10},
	                 win_w,
	                 win_h,
	                 "Playpen",
	                 ENABLE_DEBUG,
	                 ENABLE_CLICK};

	fl_color(0);

	Graph_lib::Text info{{64, 32}, info_start()};
	win.attach(info);

	RPOL::RegularPolygon rp{c, 64, 8};
	rp.set_fill_color(Graph_lib::Color::invisible);

	win.attach(rp);

	Octagon_animator anim{win, rp};

	int count_clicks = 0;
	int is_animating = false;
	while (win.shown()) {
		if (win.click_has_been_registered()) {
			if (!is_animating) {
				// Start
				rp.set_fill_color(colors()[count_clicks++ % colors().size()]);
				rp.set_color(colors()[count_clicks % colors().size()]);
				rp.set_style(styles()[(count_clicks + 1) % styles().size()]);
				info.set_label(info_stop());
				is_animating = true;
				anim.start();
			} else {
				// Stop
				info.set_label(info_start());
				is_animating = false;
				anim.stop();
			}
		}
		win.wait_for_click();
	}
}

int main() {
	try {
		e08();
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
