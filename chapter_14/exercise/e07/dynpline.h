#ifndef DYNPLINE_H
#define DYNPLINE_H
#include "../../lib/Debug_window.h"
#include "../../lib/Graph.h"
#include <memory>
#include <vector>

namespace dynpline {

constexpr int start_end_snap_distance{5};
constexpr int default_min_segment_len{5};
constexpr int default_max_segment_len{600};
constexpr int default_max_number_of_points{10};
inline const Graph_lib::Color& default_preview_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::black};
	return c;
}
inline const Graph_lib::Color& default_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::black};
	return c;
}
inline const Graph_lib::Color& default_preview_bg_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::white};
	return c;
}
inline const Graph_lib::Color& default_bg_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::Transparency::invisible};
	return c;
}

constexpr float refresh_rate{0.1};
constexpr float refresh_time_out{60};

class Dynamic_pline : public Graph_lib::Shape
{
public:
	Dynamic_pline(Graph_lib::Point origin,
	             Graph_lib::Point end,
	             int min_side_len = default_min_segment_len,
	             int max_side_len = default_max_segment_len);

	void draw_lines() const
	{
		if (has_pts) {
			pline->draw();
		}
		seg->draw();
	};
	bool is_transforming() const { return is_xform; };
	void cue_transform(Graph_lib::Point new_point);
	void reset_transform() { cue_transform(o); };
	void apply_transform(bool preview = false);
	void enable_transform() { is_xform = true; };
	void disable_transform() { is_xform = false; };
	Graph_lib::Point origin() const { return o; };
	int segment_length() const { return seg_len; };
	int min_side_len() const { return min_s; };
	int max_side_len() const { return max_s; };
	std::vector<Graph_lib::Point> points() const
	{
		if (!has_pts) {
			throw std::runtime_error(
			    "Cannot return points when nothing has been drawn yet");
		}
		std::vector<Graph_lib::Point> pts;
		for (int i = 0; i < pline->number_of_points() - 1; ++i) {
			pts.push_back(pline->point(i));
		}
		return pts;
	}

private:
	bool init_pos;
	bool has_pts;
	bool is_xform;
	bool draw_new;
	const int min_s;
	const int max_s;

	int seg_len;
	Graph_lib::Point o;
	Graph_lib::Point end;

	Graph_lib::Color c;
	Graph_lib::Color bg;
	Graph_lib::Color preview_c;
	Graph_lib::Color preview_bg;

	bool start_eq_end() const;

	bool valid_min_max(int min_seg_len, int max_seg_len) const
	{
		return !(min_seg_len >= max_seg_len || seg_len < min_seg_len);
	}
	void cap_seg_len(Graph_lib::Point& pt);
	std::unique_ptr<Graph_lib::Line> seg;
	std::unique_ptr<Graph_lib::Line> new_seg(Graph_lib::Point pt0,
	                                         Graph_lib::Point pt1);
	std::unique_ptr<Graph_lib::Open_polyline> pline;
	std::unique_ptr<Graph_lib::Open_polyline> new_pline();
};

//------------------------------------------------------------------------------
// Interactively draw the current Open_polyline, hacky, but improves debugging.

struct Window_and_pline
/* The callback needs to access and modify:
 * - The window: The cursor / mouse
 * - The polyline: Transformation
 */
{
	Debug_window& win;
	dynpline::Dynamic_pline& pline;
};

static void transform_pline_cb(void* data);
void hacky_redraw_pline(Window_and_pline& tw);

} // namespace dynpline

#endif // DYNPLINE_H
