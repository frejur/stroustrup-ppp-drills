#define _USE_MATH_DEFINES
#include "anim_shp.h"
#include "../geo/regularpoly.h"
#include <cmath>

static void anim::transform_shape_cb(void* data)
{
	static float time = 0;
	Window_and_shape* ws = static_cast<Window_and_shape*>(data);
	if (!ws->win.shown()) {
		Fl::remove_timeout(transform_shape_cb, data);
		return;
	}
	time += refresh_rate;
	if (ws->stop || time >= refresh_time_out) {
		if (time >= refresh_time_out) {
			ws->win.force_click();
		}
		time = 0;
		Fl::remove_timeout(transform_shape_cb, data);
	} else {
		RPOL::RegularPolygon& p = dynamic_cast<RPOL::RegularPolygon&>(ws->shape);

		p.rotate(10); // Spin

		// Move in circular pattern
		double time_f = time / refresh_time_out;
		double move_angle = M_PI * 2 * time_f - M_PI;
		double move_dist = 4 * p.radius() / (refresh_time_out / refresh_rate);
		double move_x = cos(move_angle) * move_dist;
		move_x += (move_x > 0) ? 0.5 : -0.5;
		double move_y = sin(move_angle) * move_dist;
		move_y += (move_y > 0) ? 0.5 : -0.5;
		p.move(static_cast<int>(move_x), static_cast<int>(move_y));
		Fl::repeat_timeout(refresh_rate, transform_shape_cb, data);
	}
	ws->win.redraw();
}

void anim::hacky_redraw_shape(Window_and_shape& ts, bool stop)
{
	ts.stop = stop;
	Fl::add_timeout(refresh_rate, transform_shape_cb, (void*) &ts);
}
