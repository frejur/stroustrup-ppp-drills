#include "my_win.h"
#include "../share/ch16_helpers.h"

namespace {
constexpr int pause_text_font_size = 36;

const Graph_lib::Color& transparent_color()
{
	static const Graph_lib::Color& c{
	    Graph_lib::Color(Graph_lib::Color::black, Graph_lib::Color::invisible)};
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
    , txt_pause({x_max() / 2, y_max() / 2}, "Animation Paused")
    , bar({4, 4}, x_max() - 4 * 2, 8)
    , btn_start({x_max() / 2 - 24, 16},
                48,
                16,
                "Start",
                [](void*, void* pw) {
	                (*static_cast<My_window*>(pw)).start_moving();
                })
    , btn_pause({x_max() / 2 - 24, 16}, 48, 16, "Pause", [](void*, void* pw) {
	    (*static_cast<My_window*>(pw)).stop_moving();
    })
{
	// Progress bar
	attach(bar);

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
}

void My_window::start_moving()
{
	if (is_polling()) {
		return;
	}

	txt_pause.set_color(transparent_color());
	btn_start.hide();
	btn_pause.show();

	start_polling(5);

	bar.set_value(0);
	txt_pause.set_color(Graph_lib::Color::white);
	btn_pause.hide();
	btn_start.show();
}

void My_window::stop_moving()
{
	if (!is_polling()) {
		return;
	}
	stop_polling();
}

//------------------------------------------------------------------------------

void My_window::polling_action()
{
	double progress_raw = 100
	                      * (milliseconds_passed()
	                         / (polling_duration_in_seconds() * 1'000.0));
	// Clamp
	bar.set_value((std::max)(0.0, (std::min)(100.0, progress_raw)));
}
