#ifndef INITIALS_H
#define INITIALS_H

#include "../../lib/Graph.h"
#include <vector>

struct ArcParms
{
    ArcParms(int x, int y, int r, double sa, double ea);
    int x, y;
    int radius {};
    double start_angle {};
    double end_angle {};
};

class InitialByShape : public Graph_lib::Shape
{
private:
    void draw_F(Graph_lib::Point origin, int height);
    void draw_J(Graph_lib::Point origin, int height);
    std::vector<ArcParms> arcs{};
public:
    InitialByShape(char i, Graph_lib::Point origin, int height);
    void addArc(ArcParms a);
    void draw_lines() const;
};

#endif // INITIALS_H
