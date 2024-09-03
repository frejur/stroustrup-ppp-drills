#ifndef HELPERS_H
#define HELPERS_H
#include "../../../lib/Graph.h"
#include <algorithm>
#include <vector>

namespace ch14_hlp {

double apothem(int radius, int chord);
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

//------------------------------------------------------------------------------

struct Line_points
{
	Graph_lib::Point start;
	Graph_lib::Point end;
};

//------------------------------------------------------------------------------

enum class Polyline_v_dir { Flat = -1, Up, Down };
enum class Polyline_h_dir { Flat = -1, Left, Right };
Polyline_v_dir Polyline_vertical_direction(const Graph_lib::Point& start,
                                           const Graph_lib::Point& mid,
                                           const Graph_lib::Point& end);
Polyline_h_dir Polyline_horizontal_direction(const Graph_lib::Point& start,
                                             const Graph_lib::Point& mid,
                                             const Graph_lib::Point& end);

//------------------------------------------------------------------------------

bool scanline_has_intersection(int scan_y, Line_points line);
Graph_lib::Point scanline_intersection_point(int scan_y, Line_points line);
std::vector<int> scanline_sorted_intersection_x_coords(
    int scan_y, const std::vector<Graph_lib::Point>& points);
std::vector<int> scanline_sorted_intersection_x_coords(
    int scan_y, const Graph_lib::Closed_polyline& polyline);

} // namespace ch14_hlp
#endif // HELPERS_H
