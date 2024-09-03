#define _USE_MATH_DEFINES
#include "dynpline.h"
#include <math.h>

dynpline::Dynamic_pline::Dynamic_pline(Graph_lib::Point origin,
                                       Graph_lib::Point end,
                                       int min_side_len,
                                       int max_side_len)
    : init_pos(false)
    , has_pts(false)
    , is_xform(false)
    , draw_new(true)
    , min_s(min_side_len)
    , max_s(max_side_len)
    , o(origin)
    , end(end)
    , c(default_color())
    , bg(default_bg_color())
    , preview_c(default_preview_color())
    , preview_bg(default_preview_bg_color())
{
	cap_seg_len(end);
	seg = new_seg(origin, end);
	if (!valid_min_max(min_side_len, max_side_len)) {
		throw std::runtime_error("Invalid parameters");
	}
	init_pos = true;
}

//------------------------------------------------------------------------------

std::unique_ptr<Graph_lib::Open_polyline> dynpline::Dynamic_pline::new_pline()
{
	std::initializer_list<Graph_lib::Point> pts{o};
	return std::make_unique<Graph_lib::Open_polyline>(pts);
};
std::unique_ptr<Graph_lib::Line> dynpline::Dynamic_pline::new_seg(
    Graph_lib::Point pt0, Graph_lib::Point pt1)
{
	return std::make_unique<Graph_lib::Line>(pt0, pt1);
}

//------------------------------------------------------------------------------
// Transformation

void dynpline::Dynamic_pline::cue_transform(Graph_lib::Point new_point)
// Register new transform values
{
	if (!is_transforming() || !init_pos) {
		return;
	}

	if (draw_new) {
		o = new_point;
		end = new_point;
	} else {
		cap_seg_len(new_point);
		end = new_point;
	}
}

void dynpline::Dynamic_pline::apply_transform(bool preview)
{
	if (draw_new) {
		new_seg(o, end);
		pline = new_pline();
		has_pts = true;
		draw_new = false;
		return; // First segment: abort ----------------------------------------
	}

	if (preview) {
		seg = new_seg(pline->point(pline->number_of_points() - 1), end);
		seg->set_color(preview_c);
		pline->set_color(preview_c);
		pline->set_fill_color(preview_bg);
	} else {
		pline->add(end);
		seg->set_color(c);
		pline->set_color(c);
		pline->set_fill_color(bg);
		if (start_eq_end()) {
			disable_transform();
			seg->set_color(Graph_lib::Color::invisible);
			pline->set_color(Graph_lib::Color::Transparency::invisible);
			pline->set_fill_color(Graph_lib::Color::Transparency::invisible);
			draw_new = true;
		}
	}
}

bool dynpline::Dynamic_pline::start_eq_end() const
{
	if (!init_pos || !has_pts || draw_new || pline->number_of_points() < 2) {
		return false;
	}
	int x_dist = o.x - end.x;
	int y_dist = o.y - end.y;
	return (sqrt(x_dist * x_dist + y_dist * y_dist) <= start_end_snap_distance);
}

//------------------------------------------------------------------------------

void dynpline::Dynamic_pline::cap_seg_len(Graph_lib::Point& pt)
{
	Graph_lib::Point start = (has_pts)
	                             ? pline->point(pline->number_of_points() - 1)
	                             : o;

	int x_dist = start.x - pt.x;
	int y_dist = start.y - pt.y;
	seg_len = static_cast<int>(sqrt(x_dist * x_dist + y_dist * y_dist));
	if (seg_len < min_s) {
		seg_len = min_s;
	} else if (seg_len > max_s) {
		seg_len = max_s;
	} else {
		return; // No adjustment needed
	}

	float angle = atan2(static_cast<float>(y_dist), static_cast<float>(x_dist))
	              - (M_PI * 1);
	pt.x = start.x + static_cast<int>(cos(angle) * seg_len);
	pt.y = start.y + static_cast<int>(sin(angle) * seg_len);
}

//------------------------------------------------------------------------------

static void dynpline::transform_pline_cb(void* data)
{
	static float time = 0;
	Window_and_pline* tw = static_cast<Window_and_pline*>(data);
	if (!tw->win.shown()) {
		Fl::remove_timeout(transform_pline_cb, data);
		return;
	}
	time += refresh_rate;
	if (!tw->pline.is_transforming() || time >= refresh_time_out) {
		if (time >= refresh_time_out) {
			tw->pline.reset_transform();
			tw->win.force_click();
		}
		time = 0;
		Fl::remove_timeout(transform_pline_cb, data);
	} else {
		bool preview = true;
		GL::Point clk{tw->win.click_position()};
		GL::Point m{tw->win.mouse_position()};

		tw->pline.cue_transform(m);
		tw->pline.apply_transform(preview);
		Fl::repeat_timeout(refresh_rate, transform_pline_cb, data);
	}
	tw->win.redraw();
}

void dynpline::hacky_redraw_pline(Window_and_pline& tw)
{
	Fl::add_timeout(refresh_rate, transform_pline_cb, (void*) &tw);
}
