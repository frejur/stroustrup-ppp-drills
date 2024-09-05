#ifndef ANIM_H
#define ANIM_H
#include "../../../lib/Debug_window.h"
#include "../../../lib/Graph.h"
#include <memory>

namespace anim {

constexpr float refresh_rate{0.05};
constexpr float refresh_time_out{10};

// Animate shapes, hacky, but useful for demonstration purposes.

struct Window_and_shape
/* The callback needs to access and modify:
 * - The window: The cursor / mouse
 * - The shape: Transformation
 */
{
	Debug_window& win;
	Graph_lib::Shape& shape;
};

class Shape_animator
{
public:
	Shape_animator(Debug_window& win,
	               Graph_lib::Shape& shape,
	               double ref_rate = anim::refresh_rate,
	               double ref_time_out = anim::refresh_time_out)
	    : ws{Window_and_shape{win, shape}}
	{
		rate = ref_rate;
		tm_out = ref_time_out;
		tm = 0;
	};
	void start()
	{
		stp = false;
		Fl::add_timeout(rate, transform_shape_cb, (void*) this);
	};
	void stop()
	{
		stp = true;
		Fl::add_timeout(rate, transform_shape_cb, (void*) this);
	};

private:
	bool stp{};
	double tm;
	double rate;
	double tm_out;
	static void transform_shape_cb(void* data);

protected:
	Window_and_shape ws;
	virtual void animate() = 0;
	virtual void finish(){};
	double time() const { return tm; };
	double time_out() const { return tm_out; };
	double refresh_rate() const { return rate; };
};

} // namespace anim

#endif // ANIM_H
