#include "dyntile.h"
#include "../geo/regularhexagon.h"
#include "../geo/righttriangle.h"

dyntile::Dynamic_tile::Dynamic_tile(dyntile::Tile_type type,
                                    Graph_lib::Point origin,
                                    int side_len,
                                    float angle,
                                    int min_side_len,
                                    int max_side_len)
    : init_pos(false)
    , is_xform(false)
    , min_s(min_side_len)
    , max_s(max_side_len)
    , s(side_len)
    , a(angle)
    , o(origin)
    , preview_s(side_len)
    , preview_a(angle)
    , preview_o(origin)
    , c(default_color())
    , bg(default_bg_color())
    , preview_c(default_preview_color())
    , preview_bg(default_preview_bg_color())
    , t(type)
{
	if (!valid_min_max(min_side_len, max_side_len)) {
		throw std::runtime_error("Invalid parameters");
	}
	init_pos = true;
	cap_parms(side_len, angle);
	tile = new_tile(type);
	tile->set_color(Graph_lib::Color::black);
}

//------------------------------------------------------------------------------

std::unique_ptr<Graph_lib::Closed_polyline> dyntile::Dynamic_tile::new_tile(
    Tile_type type)
{
	if (type == Tile_type::Right_triangle) {
		Graph_lib::Point in_end{static_cast<int>(std::round(
		                            preview_o.x + cos(preview_a) * preview_s)),
		                        static_cast<int>(std::round(
		                            preview_o.y + sin(preview_a) * preview_s))};
		return std::make_unique<RTRI::RightTriangle>(preview_o, in_end);
	} else {
		return std::make_unique<RHEX::RegularHexagon>(preview_o,
		                                              preview_s,
		                                              preview_a);
	}
};

//------------------------------------------------------------------------------
// Transformation

void dyntile::Dynamic_tile::cue_transform(Graph_lib::Point new_origin,
                                          int new_side_len,
                                          float new_angle)
// Register new transform values
{
	if (!is_transforming() || !init_pos) {
		return;
	}
	if (t == Tile_type::Regular_hexagon) {
		preview_o = {new_origin.x + new_side_len, new_origin.y};
	} else {
		preview_o = new_origin;
	}
	cap_parms(new_side_len, new_angle);
	preview_s = new_side_len;
	preview_a = new_angle;
}

void dyntile::Dynamic_tile::apply_transform(bool preview)
// Replace current tile with a newly transformed tile
{
	if (preview && s == preview_s && a == preview_a && o == preview_o) {
		return;
	}
	tile = new_tile(t);
	if (preview) {
		tile->set_color(preview_c);
		tile->set_fill_color(preview_bg);
	} else {
		tile->set_color(c);
		tile->set_fill_color(bg);
		o = preview_o;
		s = preview_s;
		a = preview_a;
	}
}

//------------------------------------------------------------------------------

void dyntile::Dynamic_tile::cap_parms(int& side_len, float& angle)
{
	if (side_len < min_s) {
		side_len = min_s;
	} else if (side_len > max_s) {
		side_len = max_s;
	}
}

//------------------------------------------------------------------------------

static void dyntile::transform_tile_cb(void* data)
{
    static float time = 0;
    Window_and_tile* tw = static_cast<Window_and_tile*>(data);
    if (!tw->win.shown()) {
        Fl::remove_timeout(transform_tile_cb, data);
        return;
    }
    time += refresh_rate;
    if (!tw->tile.is_transforming() || time >= refresh_time_out) {
        if (time >= refresh_time_out) {
            tw->tile.reset_transform();
            tw->win.force_click();
        }
        time = 0;
        Fl::remove_timeout(transform_tile_cb, data);
    } else {
		bool preview = true;
		GL::Point clk{tw->win.click_position()};
        GL::Point m{tw->win.mouse_position()};
        int x_dist = m.x - clk.x;
        int y_dist = m.y - clk.y;

		int dist = sqrt(x_dist * x_dist + y_dist * y_dist);
		float angle = atan2(static_cast<float>(y_dist),
		                    static_cast<float>(x_dist))
		              - (M_PI * 0.25);

		Graph_lib::Point o{tw->win.click_position()};
		int side = dist;
		if (tw->tile.type() == Tile_type::Regular_hexagon) {
			side *= 0.5;
			angle -= (45 * 3 * M_PI / 180);
			o.x -= side;
		}

		if (angle < 0) {
			angle += M_PI * 2;
		}

		tw->tile.cue_transform(o, side, angle);
		tw->tile.apply_transform(preview);
		Fl::repeat_timeout(refresh_rate, transform_tile_cb, data);
	}
	tw->win.redraw();
}

void dyntile::hacky_redraw_tile(Window_and_tile& tw)
{
    Fl::add_timeout(refresh_rate, transform_tile_cb, (void*) &tw);
}

