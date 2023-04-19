#include "initials.h"
#include <iostream>

ArcParms::ArcParms(int xx, int yy, int r, double sa, double es) :
    x { xx }, y { yy }, radius { r }, start_angle { sa }, end_angle{ es } {}

InitialByShape::InitialByShape(char i, Graph_lib::Point origin, int height)
{
    switch (toupper(i)) {
        case 'F':
            draw_F(origin, height);
            break;
        case 'J':
            draw_J(origin, height);
            break;
    }
}

void InitialByShape::draw_F(Graph_lib::Point origin, int height)
{
    int width = static_cast<int>(height * 0.5);
    add({ origin.x, origin.y + height });
    add(origin);
    add({ origin.x + width, origin.y });
    add(origin);
    add({ origin.x, origin.y + width });
    add({ origin.x + width, origin.y + width });
}


void InitialByShape::draw_J(Graph_lib::Point origin, int height)
{
    int width = { static_cast<int>(height * 0.5) };
    int r { static_cast<int>(width * 0.5) };
    add({ origin.x + width, origin.y });
    add({ origin.x + width, origin.y + height - r});
    addArc({ origin.x + width - 2 * r, origin.y + height - 2 * r, r, 180, 360 });
}

void InitialByShape::addArc(ArcParms a)
{
    arcs.push_back(a);
}


void InitialByShape::draw_lines() const
{
    Graph_lib::Shape::draw_lines();
    for (unsigned int i=0; i < arcs.size(); ++i) {
        fl_arc(
            arcs[i].x,
            arcs[i].y,
            arcs[i].radius * 2,
            arcs[i].radius * 2,
            arcs[i].start_angle,
            arcs[i].end_angle
        );
    }
}
