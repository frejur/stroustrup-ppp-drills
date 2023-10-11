#ifndef BOX_H
#define BOX_H

#include <exception>
#include "../../lib/Graph.h"
#include <map>

namespace E02 { //------------------------------------------

// Draws a rectangle with rounded corners.

// The profile of the corner curvature is defined by either:
// A. 0 < Curvedness ratio < 1 (In relation to box size)
// B. Curvedness radius (Radius of the corner arc)

enum class CrvMethod {	Ratio, Radius };
enum class Corner { NW, NE, SE, SW }; // North West, etc...

class Box : public Graph_lib::Shape
{
public:
    // Define by corner points
    Box(
        Graph_lib::Point o, Graph_lib::Point e,
        double crv_ratio
    );
    Box(
        Graph_lib::Point o, int w, int h, double crv_ratio
    );

    // Define by top left corner point and size
    Box(
        Graph_lib::Point o, Graph_lib::Point e,
        int crv_radius
    );
    Box(
        Graph_lib::Point o, int w, int h, int crv_radius
    );
private:
    CrvMethod crv_method;
    double crv_ratio{ 0 };  // Used to set crv_radius
    int crv_radius{ 0 };    // Controls corner curvature
    int w{ 0 }, h{ 0 };		// Size

    const std::map<Corner, std::pair<int, int>>
        dir_to_next_pt // Clockwise
    {
        { Corner::NW, {1, 0} },
        { Corner::NE, {0, 1} },
        { Corner::SE, {-1, 0} },
        { Corner::SW, {0, -1} }
    };

    void setSize(
        const Graph_lib::Point& o, const Graph_lib::Point& e
    );
    void setSize(int hh, int ww);

    void updateCornerPoints(
        const Graph_lib::Point& o, const Graph_lib::Point& e
    );

    int getIterDistToNW_Corner(
        const Graph_lib::Point& o, const Graph_lib::Point& e
    ) const;

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
    void draw_lines() const; // override Shape::draw_lines()
};

} // namespace E02 -----------------------------------------

#endif // BOX_H
