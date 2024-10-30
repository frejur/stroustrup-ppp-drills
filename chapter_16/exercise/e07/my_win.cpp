#define _USE_MATH_DEFINES
#include "my_win.h"
#include "../share/ch16_helpers.h"
#include <chrono>
#include <random>

namespace {
constexpr int top_margin{36};
constexpr int button_vertical_padding{static_cast<int>(top_margin * 0.125)};
constexpr int bar_height{static_cast<int>(top_margin * 0.125)};
constexpr int side_margin{4};
constexpr int button_width{48};
constexpr int button_height{static_cast<int>(top_margin * 0.45)};
constexpr int pause_text_font_size = 36;
constexpr double speed_in_pixels{8};
constexpr double target_min_distance_factor{3.0};
constexpr double target_max_distance_factor{20.0};
constexpr double target_threshold_factor{0.125};

const Graph_lib::Color& transparent_color()
{
	static const Graph_lib::Color& c{
	    Graph_lib::Color(Graph_lib::Color::black, Graph_lib::Color::invisible)};
	return c;
}

inline int rand_int(int min, int max)
{
	static default_random_engine ran{static_cast<unsigned>(
	    std::chrono::system_clock::now().time_since_epoch().count())};
	return uniform_int_distribution<>{min, max}(ran);
}

Pickup::Direction direction_from_angle(double angle_radians)
{
	double a = ch16_hlp::wrap_angle(angle_radians) + M_PI * 0.125;
	if (a > M_PI * 2) {
		a -= M_PI * 2;
	}
	using Pdir = Pickup::Direction;
	Pdir d = Pdir::N;
	int dir_num_val = static_cast<int>(a / (M_PI * 0.25));
	switch (dir_num_val) {
	case 0:
		d = Pdir::E;
		break;
	case 1:
		d = Pdir::SE;
		break;
	case 2:
		d = Pdir::S;
		break;
	case 3:
		d = Pdir::SW;
		break;
	case 4:
		d = Pdir::W;
		break;
	case 5:
		d = Pdir::NW;
		break;
	case 6:
		d = Pdir::N;
		break;
	case 7:
		d = Pdir::NE;
		break;
	}
	return d;
}

} // namespace

//------------------------------------------------------------------------------

My_window::My_window(Graph_lib::Point top_left,
                     int width,
                     int height,
                     const string& title,
                     int refresh_rate_ms)
    : anm_win::Animated_window(top_left, width, height, title, refresh_rate_ms)
    , top_m(top_margin)
    , speed_px(speed_in_pixels)
    , target_thold(speed_px * target_threshold_factor)
    , target_min_dist(speed_px * target_min_distance_factor)
    , target_max_dist(speed_px * target_max_distance_factor)
    , default_target({x_max() / 2, y_max() / 2})
    , target(default_target)
    , txt_pause({x_max() / 2, y_max() / 2}, "Animation Paused")
    , bar({side_margin, button_vertical_padding},
          x_max() - side_margin * 2,
          bar_height)
    , pkup(default_target, 64)
    , btn_start({x_max() / 2 - button_width / 2,
                 button_vertical_padding * 2 + bar_height},
                button_width,
                button_height,
                "Start",
                [](void*, void* pw) {
	                (*static_cast<My_window*>(pw)).start_moving();
                })
    , btn_pause(btn_start.loc,
                btn_start.width,
                btn_start.height,
                "Pause",
                [](void*, void* pw) {
	                (*static_cast<My_window*>(pw)).stop_moving();
                })
{
	size_range(width, height, width, height); // Lock window size

	// Pickup
	attach(pkup);
	pkup.set_bounding_box_size(50);

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

//------------------------------------------------------------------------------

void My_window::start_moving()
{
	if (is_polling()) {
		return;
	}

	txt_pause.set_color(transparent_color());
	btn_start.hide();
	btn_pause.show();

	new_random_target();
	double target_angle = ch16_hlp::angle_between(target, pkup.center());
	pkup.set_direction(direction_from_angle(target_angle));

	start_polling(20);

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

void My_window::new_random_target()
{
	const int obj_sz = pkup.bounding_box_size();
	int new_x = rand_int(obj_sz / 2, x_max() - obj_sz / 2);
	int new_y = rand_int(top_m + obj_sz / 2, y_max() - obj_sz / 2);

	const double dist_to_rand = ch16_hlp::distance_between(target,
	                                                       {new_x, new_y});
	if (dist_to_rand >= target_min_dist && dist_to_rand <= target_max_dist) {
		target = {new_x, new_y};
		return;
	}

	// Fallback target
	// Determine furthest point from current target: Center or random Corner
	const Graph_lib::Point center = {x_max() / 2, y_max() / 2};
	const Graph_lib::Point corner = crn(rand_int(0, 3),
	                                    x_max(),
	                                    y_max(),
	                                    top_margin);
	const double dist_to_c = ch16_hlp::distance_between(target, center);
	const double dist_to_tr = ch16_hlp::distance_between(target, corner);
	Graph_lib::Point furthest = (dist_to_c > dist_to_tr) ? center : corner;
	const double furthest_dist = (std::max)(dist_to_c, dist_to_tr);

	// Set target to random point along vector towards furthest point
	const double angle = ch16_hlp::angle_between(furthest, target)
	                         * (180 / M_PI)
	                     + 90;
	const double rand_dist_f = (rand_int(0, 100) * 0.01);
	const double rand_dist_max = (std::min)(target_max_dist, furthest_dist);
	const double rand_dist = speed_px
	                         + (rand_dist_max - target_min_dist) * rand_dist_f;

	target = ch16_hlp::point_at_angle(target, angle, rand_dist);
}

//------------------------------------------------------------------------------

void My_window::polling_action()
{
	// Update progress bar
	double progress_raw = 100
	                      * (milliseconds_passed()
	                         / (polling_duration_in_seconds() * 1'000.0));
	bar.set_value((std::max)(0.0, (std::min)(100.0, progress_raw))); // Clamp

	// Move truck
	double dist_to_target = ch16_hlp::distance_between(pkup.center(), target);
	if ((dist_to_target - speed_px) <= target_thold) {
		pkup.move(target.x - pkup.center().x, target.y - pkup.center().y);
		new_random_target();
		double target_angle = ch16_hlp::angle_between(target, pkup.center());
		pkup.set_direction(direction_from_angle(target_angle));
	} else {
		double target_angle = ch16_hlp::angle_between(target, pkup.center())
		                          * (180 / M_PI)
		                      + 90;
		Graph_lib::Point xy{
		    ch16_hlp::point_at_angle(pkup.center(), target_angle, speed_px)};
		pkup.move(xy.x - pkup.center().x, xy.y - pkup.center().y);
	}
}
