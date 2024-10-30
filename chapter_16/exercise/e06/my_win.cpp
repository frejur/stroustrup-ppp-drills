#include "my_win.h"
#include "../share/ch16_helpers.h"
#include <chrono>

namespace {
constexpr int clock_radius = 136;
constexpr int clock_face_radius = 128;
constexpr int clock_font_size = 32;
constexpr int hand_sec_len = 128;
constexpr int hand_min_len = 128;
constexpr int hand_hour_len = 88;
constexpr int hand_sec_thk = 2;
constexpr int hand_min_thk = 3;
constexpr int hand_hour_thk = 4;
constexpr int clock_frame_thk = 12;
constexpr int pause_text_font_size = 36;

const Graph_lib::Color& transparent_color()
{
	static const Graph_lib::Color& c{
	    Graph_lib::Color(Graph_lib::Color::black, Graph_lib::Color::invisible)};
	return c;
}
const Graph_lib::Color& clock_primary_color()
{
	static const Graph_lib::Color& c{
	    Graph_lib::Color(fl_rgb_color(177, 46, 33))};
	return c;
}
const Graph_lib::Color& clock_secondary_color()
{
	static const Graph_lib::Color& c{
	    Graph_lib::Color(fl_rgb_color(245, 245, 245))};
	return c;
}

} // namespace

//------------------------------------------------------------------------------

My_window::My_window(Graph_lib::Point top_left,
                     int width,
                     int height,
                     const string& title,
                     int refresh_rate_ms)
    : anm_win::Animated_window(top_left, width, height, title, refresh_rate_ms)
    , angle_sec(0)
    , angle_min(0)
    , angle_hour(0)
    , hand_sec({x_max() / 2, y_max() / 2}, {x_max() / 2, hand_sec_len})
    , hand_min({x_max() / 2, y_max() / 2}, {x_max() / 2, hand_min_len})
    , hand_hour({x_max() / 2, y_max() / 2}, {x_max() / 2, hand_hour_len})
    , frame({x_max() / 2, y_max() / 2}, clock_radius + clock_frame_thk)
    , bg({x_max() / 2, y_max() / 2}, clock_radius)
    , face({x_max() / 2, y_max() / 2}, clock_face_radius)
    , txt_pause({x_max() / 2, y_max() / 2}, "Animation Paused")
    , btn_start({x_max() / 2 - 24, 16},
                48,
                16,
                "Start",
                [](void*, void* pw) {
	                (*static_cast<My_window*>(pw)).start_ticking();
                })
    , btn_pause({x_max() / 2 - 24, 16}, 48, 16, "Pause", [](void*, void* pw) {
	    (*static_cast<My_window*>(pw)).stop_ticking();
    })
{
	size_range(width, height, width, height); // Lock window size

	// Frame / outer border
	attach(frame);
	frame.set_color(transparent_color());
	frame.set_fill_color(clock_primary_color());

	// Background
	attach(bg);
	bg.set_fill_color(clock_secondary_color());
	bg.set_color(transparent_color());
	bg.set_style(
	    Graph_lib::Line_style(Graph_lib::Line_style::solid, clock_frame_thk));

	// Face (Digits, notches)
	attach(face);
	face.set_font_size(clock_font_size);

	// Hands
	attach(hand_min);
	hand_min.set_style(
	    Graph_lib::Line_style(Graph_lib::Line_style::solid, hand_min_thk));
	attach(hand_hour);
	hand_hour.set_style(
	    Graph_lib::Line_style(Graph_lib::Line_style::solid, hand_hour_thk));
	attach(hand_sec);
	hand_sec.set_color(clock_primary_color());
	hand_min.set_style(
	    Graph_lib::Line_style(Graph_lib::Line_style::solid, hand_sec_thk));

	// Pause text (Shown when paused)
	attach(txt_pause);
	txt_pause.set_font_size(pause_text_font_size);
	txt_pause.set_color(Graph_lib::Color::white);
	int txt_w = ch16_hlp::calc_lb_w(txt_pause.label(),
	                                txt_pause.font(),
	                                txt_pause.font_size());
	txt_pause.move(-txt_w / 2, pause_text_font_size / 2 - fl_descent());

	// Start and pause buttons
	attach(btn_start);
	attach(btn_pause);
	btn_pause.hide();

	start_ticking();
}

void My_window::start_ticking()
{
	if (is_polling()) {
		return;
	}

	txt_pause.set_color(transparent_color());
	btn_start.hide();
	btn_pause.show();

	start_polling(60);

	txt_pause.set_color(Graph_lib::Color::white);
	btn_pause.hide();
	btn_start.show();
}

void My_window::stop_ticking()
{
	if (!is_polling()) {
		return;
	}
	stop_polling();
}

//------------------------------------------------------------------------------

void My_window::polling_action()
{
	// Angles from current time
	Hms t = current_time_as_hms();
	angle_sec = t.seconds * 6;
	angle_min = t.minutes * 6;
	angle_hour = ((t.hours % 12) + t.minutes / 60.0) * 30;

	// Update clock hands
	Graph_lib::Point c{hand_sec.point(0)};
	hand_hour.new_start_and_end_points(c,
	                                   ch16_hlp::point_at_angle(c,
	                                                            angle_hour,
	                                                            hand_hour_len));

	hand_min.new_start_and_end_points(c,
	                                  ch16_hlp::point_at_angle(c,
	                                                           angle_min,
	                                                           hand_min_len));

	hand_sec.new_start_and_end_points(c,
	                                  ch16_hlp::point_at_angle(c,
	                                                           angle_sec,
	                                                           hand_sec_len));
}

//------------------------------------------------------------------------------

Hms current_time_as_hms()
{
	auto now{std::chrono::system_clock::now()};
	std::time_t t{std::chrono::system_clock::to_time_t(now)};
	std::tm local_t;

// Thread-safe conversion to local time
#if defined(_WIN32) || defined(_WIN64)
	localtime_s(&local_t, &t); // Windows
#else
	localtime_r(&local_t, &t); // POSIX
#endif

	return {local_t.tm_hour, local_t.tm_min, local_t.tm_sec};
}
