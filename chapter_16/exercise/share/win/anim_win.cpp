#include "anim_win.h"
#include <ctime>

namespace {
constexpr int min_refresh_rate_ms{100};
constexpr int max_refresh_rate_ms{10000};
constexpr int max_duration_sec{60 * 2};
} // namespace

const int anm_win::Animated_window::default_rate_ms = 500;

//------------------------------------------------------------------------------

anm_win::Animated_window::Animated_window(Graph_lib::Point top_left,
                                          int width,
                                          int height,
                                          const string& title,
                                          int refresh_rate_ms)
    : Graph_lib::Window(top_left, width, height, title)
    , trigger_stop(false)
    , is_poll(false)
    , rate_ms(valid_rate(refresh_rate_ms))
    , passed_ms(0)
    , dur_sec(max_duration_sec)
{}

//------------------------------------------------------------------------------

static double wait_for_x_sec(double x_sec, double wait_interval_sec)
{
	time_t start_t = clock();
	int num_clocks = static_cast<int>(x_sec * CLOCKS_PER_SEC);
	int delta = 0;
	while (delta < num_clocks) {
		Fl::wait(wait_interval_sec);
		delta = static_cast<int>(clock() - start_t);
	}

	return static_cast<double>(delta) / CLOCKS_PER_SEC;
}

void anm_win::Animated_window::start_polling(int duration_sec)
{
	// Manage state
	if (is_poll) {
		throw std::runtime_error("Polling already active");
	}
	is_poll = true;
	dur_sec = valid_duration(duration_sec, rate_ms);
	const int dur_ms = dur_sec * 1000.0;
	passed_ms = 0;

	// Rate and wait interval in seconds
	const double rs = rate_ms / 1000.0;

	// Try to adapt the refresh rate to the system's clock resolution
	double precision = 0;
	if (CLOCKS_PER_SEC < 1000) {
		precision = 0.0000025;
	} else if (CLOCKS_PER_SEC <= 1000000) {
		precision = 0.000005;
	} else {
		precision = 0.005;
	}
	const double wait_sec = rs * precision;

	// Est. and track # of polling actions to perform
	const int num_act = static_cast<int>(dur_sec / rs) + 1;
	int act_count = 0;

	// At minimum, perform action once
	polling_action();
	++act_count;
	Fl::redraw();

	// Execute polling action for every x number of ms
	while (shown() && is_polling() && act_count < num_act) {
		// Wait
		double t_diff = wait_for_x_sec(rs, wait_sec);
		passed_ms = (std::min)(dur_ms,
		                       passed_ms + static_cast<int>(t_diff * 1000));

		// Polling action, repeat if time passed indicates it
		int expected_act_count = (passed_ms / rate_ms) + 1;
		int do_act = static_cast<int>(expected_act_count - act_count);
		for (int i = 0; i < do_act; ++i) {
			polling_action();
		}
		act_count += do_act;
		Fl::redraw();

		if (trigger_stop) {
			trigger_stop = false;
			break;
		}
	}

	// Reset state
	is_poll = false;
	dur_sec = 0;
	passed_ms = 0;
}

void anm_win::Animated_window::stop_polling()
{
	trigger_stop = true;
}

//------------------------------------------------------------------------------

int anm_win::Animated_window::valid_rate(int r_ms) const
{
	if (r_ms < min_refresh_rate_ms || r_ms > max_refresh_rate_ms) {
		throw std::runtime_error(
		    "Invalid refresh rate, expected a value between "
		    + std::to_string(min_refresh_rate_ms) + " and "
		    + std::to_string(max_refresh_rate_ms) + ", but got "
		    + std::to_string(r_ms));
	}
	return r_ms;
}

int anm_win::Animated_window::valid_duration(int d_sec, int r_ms) const
{
	const int min_d_sec{static_cast<int>((r_ms / 1000.0) + 0.5)};
	if (d_sec < min_d_sec || d_sec > max_duration_sec) {
		throw std::runtime_error("Invalid duration, expected a value between "
		                         + std::to_string(min_d_sec) + " and "
		                         + std::to_string(max_duration_sec)
		                         + ", but got " + std::to_string(d_sec));
	}
	return d_sec;
}
