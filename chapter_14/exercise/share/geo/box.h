#ifndef BOX_H
#define BOX_H

#include "../../../lib/Graph.h"

namespace BOX { //------------------------------------------

// Draws a rectangle with rounded corners.

// The profile of the corner curvature is defined by either:
// A. 0 < Curvedness ratio < 1 (In relation to box size)
// B. Curvedness radius (Radius of the corner arc)

enum class CrvMethod {	Ratio, Radius };
enum class Corner { NW, NE, SE, SW }; // North West, etc...
enum class Flatten_side { None, Top, Right, Bottom, Left };

class Box : public Graph_lib::Shape
{
public:
    // Define by corner points
	Box(Graph_lib::Point o,
	    Graph_lib::Point e,
	    double crv_ratio,
	    CrvMethod m = CrvMethod::Ratio,
	    Flatten_side fl = Flatten_side::None);
	Box(Graph_lib::Point o,
	    Graph_lib::Point e,
	    int crv_radius,
	    CrvMethod m,
	    Flatten_side fl = Flatten_side::None)
	    : Box(o, e, static_cast<double>(crv_radius), m, fl){};

	// Define by top left corner point and size
	Box(Graph_lib::Point o,
	    int w,
	    int h,
	    double crv_ratio,
	    CrvMethod m = CrvMethod::Ratio,
	    Flatten_side fl = Flatten_side::None);
	Box(Graph_lib::Point o,
	    int w,
	    int h,
	    int crv_radius,
	    CrvMethod m,
	    Flatten_side fl = Flatten_side::None)
	    : Box(o, w, h, static_cast<double>(crv_radius), m, fl){};
	void draw_lines() const; // override Shape::draw_lines()
	enum Drawing_mode { DRAW_STROKE, DRAW_FILL };
	int width() const { return w; };
	int height() const { return h; };
	double corner_radius() const { return crv_radius; };
	Graph_lib::Point bbox_origin() const;
	void updateSize(int hh, int ww);
	void updateSize(const Graph_lib::Point& o, const Graph_lib::Point& e);

	int dir_idx(const Graph_lib::Point& o, const Graph_lib::Point& e) const;

private:
	void draw_box(Drawing_mode mode = DRAW_STROKE) const;
    CrvMethod crv_method;
    double crv_ratio{ 0 };  // Used to set crv_radius
	double crv_radius{0};   // Controls corner curvature
	int w{0}, h{0};         // Size
	Flatten_side flat_s;

	const std::vector<std::pair<Corner, std::pair<int, int>>>
	    dir_to_next_pt // Clockwise, order must remain
	    {{Corner::NW, {1, 0}},
	     {Corner::NE, {0, 1}},
	     {Corner::SE, {-1, 0}},
	     {Corner::SW, {0, -1}}};

	void initRadius(CrvMethod m, double ratio_or_radius, double radius_max);

	void setSize(int hh, int ww);
	void setSize(const Graph_lib::Point& o, const Graph_lib::Point& e);

	void updateCornerPoints(const Graph_lib::Point& o,
	                        const Graph_lib::Point& e);

	int getIterDistToNW_Corner(const Graph_lib::Point& o,
	                           const Graph_lib::Point& e) const;

	// Given a rectangle: get the name of corner point p1,
	// with p2 being the opposite corner point.
	inline Corner getCorner(
        const Graph_lib::Point& p1,
        const Graph_lib::Point& p2
    ) const;

    inline int getMaxRadius() const;
    void setRadius(int r, int max);
    int getRadiusFromRatio(double r, int max) const;

    void errorIfZeroArea(int ww, int hh) const;
    void errorIfZeroArea(
        Graph_lib::Point o, Graph_lib::Point e
    ) const;
    bool areaIsZero() const;

	bool corner_is_flat(Corner c) const;
};

} // namespace BOX -----------------------------------------

#endif // BOX_H
