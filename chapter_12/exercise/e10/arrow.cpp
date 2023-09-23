#include "arrow.h"
#include <math.h>

using namespace Graph_lib;

Arrow::Arrow(Point origin, Point end)
{
    draw_arrow(origin, end);
}

void Arrow::draw_arrow(Point origin, Point end)
{
    float angle = atan2(end.y - origin.y, end.x - origin.x);
    draw_line(origin, end);
    draw_arrow_head(end, angle);
}

void Arrow::draw_line(Point origin, Point end)
{
    add(origin);
    add(end);
}

void Arrow::draw_arrow_head(Point end, float angle)
{
    const float hd_ang = 0.5; // Arrow head angle (Roughly 30 deg)
    add(end);
    add
    (
        { static_cast<int>(end.x - 10 * cos(angle + hd_ang)),
          static_cast<int>(end.y - 10 * sin(angle + hd_ang)) }
    );
    add
    (
        { static_cast<int>(end.x - 10 * cos(angle - hd_ang)),
          static_cast<int>(end.y - 10 * sin(angle - hd_ang)) }
    );
    add(end);
}
