#ifndef DYNTILE_H
#define DYNTILE_H
#include "../../../lib/Debug_window.h"
#include "../../../lib/Graph.h"
#include <memory>

namespace dyntile {

constexpr int default_min_side_len{10};
constexpr int default_max_side_len{200};
inline const Graph_lib::Color& default_preview_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::red};
	return c;
}
inline const Graph_lib::Color& default_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::black};
	return c;
}
inline const Graph_lib::Color& default_preview_bg_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::red};
	return c;
}
inline const Graph_lib::Color& default_bg_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::Transparency::invisible};
	return c;
}

constexpr float refresh_rate{0.1};
constexpr float refresh_time_out{10};

enum class Tile_type { Right_triangle, Regular_hexagon };

class Dynamic_tile : public Graph_lib::Shape
{
public:
	Dynamic_tile(Tile_type type,
	             Graph_lib::Point origin,
	             int side_len,
	             float angle,
	             int min_side_len = default_min_side_len,
	             int max_side_len = default_max_side_len);

	void draw_lines() const { tile->draw(); };
	bool is_transforming() const { return is_xform; };
	void cue_transform(Graph_lib::Point new_origin,
	                   int new_side_len,
	                   float new_angle);
	void reset_transform() { cue_transform(o, s, a); };
	void apply_transform(bool preview = false);
	void enable_transform() { is_xform = true; };
	void disable_transform() { is_xform = false; };
	Graph_lib::Point origin() const { return o; };
	int side_length() const { return s; };
	float angle() const { return a; };
	int min_side_len() const { return min_s; };
	int max_side_len() const { return max_s; };

private:
	bool init_pos;
	bool is_xform;
	const int min_s;
	const int max_s;

	// Transform values
	int s;
	float a;
	Graph_lib::Point o;
	int preview_s;
	float preview_a;
	Graph_lib::Point preview_o;

	Graph_lib::Color c;
	Graph_lib::Color bg;
	Graph_lib::Color preview_c;
	Graph_lib::Color preview_bg;

	Tile_type t;
	bool valid_min_max(int min_side_len, int max_side_len) const
	{
		return !(min_side_len >= max_side_len || s < min_side_len);
	}
	void cap_parms(int& side_len, float& angle);
	std::unique_ptr<Graph_lib::Closed_polyline> tile;
	std::unique_ptr<Graph_lib::Closed_polyline> new_tile(Tile_type type);
};

//------------------------------------------------------------------------------
// Interactively transforming the initial tile, hacky, but improves debugging.

struct Window_and_tile
/* The callback needs to access and modify:
 * - The window: The cursor / mouse
 * - The tile: Transformation
 */
{
    Debug_window& win;
    dyntile::Dynamic_tile& tile;
};

static void transform_tile_cb(void* data);
void hacky_redraw_tile(Window_and_tile& tw);

} // namespace dyntile

#endif // DYNTILE_H
