#include "my_win.h"
#include "../share/ch16_helpers.h"

//------------------------------------------------------------------------------

My_window::My_window(Graph_lib::Point top_left,
                     int width,
                     int height,
                     const string& title,
                     int refresh_rate_ms)
    : anm_win::Animated_window(top_left, width, height, title, refresh_rate_ms)
    , txt({x_max() / 2, y_max() / 2}, "0")
    , hand_sec({x_max() / 2, y_max() / 2}, {x_max() / 2, 0})
{
	attach(txt);
	attach(hand_sec);
}

//------------------------------------------------------------------------------

void My_window::polling_action()
{
	Graph_lib::Point c{hand_sec.point(0)};
	int a = milliseconds_passed() / 1000 * 360 / 60;
	int r = static_cast<int>(x_max() * 0.4);
	hand_sec.new_start_and_end_points(c, ch16_hlp::point_at_angle(c, a, r));
	txt.set_label(std::to_string(milliseconds_passed() / 1'000.0) + "ms,    "
	              + std::to_string(a) + " degrees");
}
