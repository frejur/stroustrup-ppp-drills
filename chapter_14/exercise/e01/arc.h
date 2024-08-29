#ifndef ARC_H
#define ARC_H

#include "../../lib/Graph.h"

namespace Arc_geo {

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

enum class ArcDir
{
    NE, // North East
    SE, // etc...
    SW, NW
};

class Arc : public Graph_lib::Shape
{
public:
    Arc(
        Graph_lib::Point o, Graph_lib::Point e,
        bool flip = false);
private:
    int w, h; 	   // Width, height of bounding box
    int ox, oy;    // Origin coordinates
    int ex, ey;    // End point
    int offs_x,	   // We draw a partial ellipse and need
        offs_y;	   //     to realign the origin
    double a1, a2; // Start, end angles of a full ellipse

    bool areaIsZero();

    ArcDir getDirection(
        const Graph_lib::Point& o, const Graph_lib::Point& e
    );
    void setSize(
        const Graph_lib::Point& o, const Graph_lib::Point& e
    );
    void setOrigin(
        const Graph_lib::Point& o, const Graph_lib::Point& e
    );
    void setEnd(
        const Graph_lib::Point& o, const Graph_lib::Point& e
    );
    void setOffset(ArcDir, bool flip);
    void setAngles(ArcDir, bool flip);
    void draw_lines() const; // override Shape::draw_lines()
};

}


#endif // ARC_H
