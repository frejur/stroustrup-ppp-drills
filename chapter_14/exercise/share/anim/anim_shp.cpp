#define _USE_MATH_DEFINES
#include "anim_shp.h"
#include "../geo/regularpoly.h"
#include <cmath>

void anim::Shape_animator::transform_shape_cb(void* data)
{
	anim::Shape_animator* a = static_cast<anim::Shape_animator*>(data);
	Window_and_shape* ws = &a->ws;
	if (!ws->win.shown()) {
		Fl::remove_timeout(transform_shape_cb, data);
		return;
	}
	a->tm += a->rate;
	if (a->stp || a->tm >= a->tm_out) {
		if (a->tm >= a->tm_out) {
			ws->win.force_click();
		}
		a->tm = 0;
		a->finish();
		Fl::remove_timeout(transform_shape_cb, data);
	} else {
		a->animate();
		Fl::repeat_timeout(a->rate, transform_shape_cb, data);
	}
	ws->win.redraw();
}
