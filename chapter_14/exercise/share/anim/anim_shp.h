#ifndef ANIM_H
#define ANIM_H
#include "../../../lib/Debug_window.h"
#include "../../../lib/Graph.h"
#include <memory>

constexpr float refresh_rate{0.05};
constexpr float refresh_time_out{10};

namespace anim {
// Animate shapes, hacky, but useful for demonstration purposes.

struct Window_and_shape
/* The callback needs to access and modify:
 * - The window: The cursor / mouse
 * - The shape: Transformation
 */
{
	Debug_window& win;
	Graph_lib::Shape& shape;
	bool stop{false};
};

static void transform_shape_cb(void* data);
void hacky_redraw_shape(Window_and_shape& ts, bool stop = false);

} // namespace anim

#endif // ANIM_H
