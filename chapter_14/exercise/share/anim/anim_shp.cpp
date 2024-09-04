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
		dynamic_cast<RPOL::RegularPolygon&>(ws->shape).rotate(10);
		Fl::repeat_timeout(refresh_rate, transform_shape_cb, data);
	}
	ws->win.redraw();
}

void anim::hacky_redraw_shape(Window_and_shape& ts, bool stop)
{
	ts.stop = stop;
	Fl::add_timeout(refresh_rate, transform_shape_cb, (void*) &ts);
}
