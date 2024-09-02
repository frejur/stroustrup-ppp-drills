#ifndef HELPERS_H
#define HELPERS_H
#include "../../../lib/Graph.h"

namespace ch14_hlp {

Graph_lib::Point point_at_angle(Graph_lib::Point center,
                                double rotation,
                                double distance);

int val_from_f(int min_val, int max_val, double f);

void draw_mark(Graph_lib::Point xy,
               char c,
               Graph_lib::Font fnt = fl_font(),
               int fnt_sz = fl_size(),
               Graph_lib::Color color = Graph_lib::Color::black);

Graph_lib::Point shape_min_xy(const Graph_lib::Shape& s);
Graph_lib::Point shape_max_xy(const Graph_lib::Shape& s);

} // namespace ch14_hlp

#endif // HELPERS_H
