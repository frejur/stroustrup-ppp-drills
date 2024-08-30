#ifndef ARC_H
#define ARC_H

#include "../../../lib/Graph.h"

namespace Arc_geo {

// Quarter Arc
// This definition of an "Arc" assumes that the user wants
// to draw a quarter of a full ellipse.

// The first argument is the origin expressed as a Point,
// the second argument the end Point.

// The position of those points in relation to eachother
// defines the direction and shape of the resulting curve.

// By default the curvature of the arc travels along the Y-
// axis towards the end point, before easing off along the
// X-axis to reach its target. Pass along a value of true
// to the third argument to flip the curve.

//------------------------------------------------------------------------------

bool areaIsZero(int w, int h);

//------------------------------------------------------------------------------

enum class Q_arc_dir {
	NE, // North East
	SE, // etc...
	SW,
	NW
};

class Quarter_arc : public Graph_lib::Shape
{
public:
	Quarter_arc(Graph_lib::Point o, Graph_lib::Point e, bool flip = false);

private:
    int w, h; 	   // Width, height of bounding box
    int ox, oy;    // Origin coordinates
    int ex, ey;    // End point
    int offs_x,	   // We draw a partial ellipse and need
        offs_y;	   //     to realign the origin
    double a1, a2; // Start, end angles of a full ellipse

	Q_arc_dir getDirection(const Graph_lib::Point& o, const Graph_lib::Point& e);
	void setSize(const Graph_lib::Point& o, const Graph_lib::Point& e);
	void setOrigin(const Graph_lib::Point& o, const Graph_lib::Point& e);
	void setEnd(const Graph_lib::Point& o, const Graph_lib::Point& e);
	void setOffset(Q_arc_dir, bool flip);
	void setAngles(Q_arc_dir, bool flip);
	void draw_lines() const; // override Shape::draw_lines()
};

//------------------------------------------------------------------------------

// Semi Arc

// Assumes an 180 degree arc.

// This class may be extended with additional constructors later,
// this is how you initiate it for now:

// The first argument is the base point.
// The second argument is the width (chord) of the Arc.
// The third argument is the height (sagitta) of the Arc.
// The fourth argument is the direction (Defaults to 'Up')
//      __           ^
//  .''   ''.        |height
// :    .    :       v
//      ^Base point
// <--- w --->

enum class S_arc_dir { Up, Right, Down, Left };

class Semi_arc : public Graph_lib::Shape
{
public:
	Semi_arc(Graph_lib::Point base,
	         int width,
	         int height,
	         S_arc_dir direction = S_arc_dir::Up);

private:
	Graph_lib::Point b;
	int w, h; // Width, height arc
	S_arc_dir dir;
	Graph_lib::Point min_pt, max_pt;
	double a1, a2;

	double start_angle(S_arc_dir d) const
	{
		return 180 + static_cast<int>(d) * 90;
	}
	Graph_lib::Point bbox_min(Graph_lib::Point base,
	                          int width,
	                          int height,
	                          S_arc_dir direction) const;
	Graph_lib::Point bbox_max(Graph_lib::Point base,
	                          int width,
	                          int height,
	                          S_arc_dir direction) const
	{
		return bbox_min(base, -width, -height, direction);
	};
	void draw_lines() const; // override Shape::draw_lines()
};

} // namespace Arc_geo

#endif // ARC_H
