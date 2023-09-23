#ifndef ARROW_H
#define ARROW_H

#include "../../lib/Graph.h"

using namespace Graph_lib;

class Arrow : public Shape
{
private:
    void draw_arrow(Point origin, Point end);
    void draw_line(Point origin, Point end);
    void draw_arrow_head(Point end, float angle);
public:
    Arrow(Graph_lib::Point origin, Graph_lib::Point end);
};

#endif // ARROW_H
