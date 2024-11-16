#ifndef CH16_HELPERS_H
#define CH16_HELPERS_H
#include "../../lib/Graph.h"

namespace ch16_hlp {

enum class Text_alignment { Top, Right, Bottom, Left, Center };

void draw_text(Graph_lib::Point xy,
               const std::string& text,
               Graph_lib::Font font,
               int font_size,
               Graph_lib::Color text_color,
               Text_alignment alignment,
               int px_offset = 0);

struct Text_extents
{
	int width;
	int height;
};

Text_extents calc_lb_ext(const std::string& txt, Graph_lib::Font f, int f_sz);
int calc_lb_w(const std::string& txt, Graph_lib::Font f, int f_sz);
int calc_lb_h(const std::string& txt, Graph_lib::Font f, int f_sz);

//------------------------------------------------------------------------------

double wrap_angle(double angle);

int val_from_f(int min_val, int max_val, double f);

//------------------------------------------------------------------------------

Graph_lib::Point point_at_angle(Graph_lib::Point center,
                                double rotation,
                                double distance);

double distance_between(Graph_lib::Point a, Graph_lib::Point b);
double angle_between(Graph_lib::Point a, Graph_lib::Point b);

} // namespace ch16_hlp

#endif // CH16_HELPERS_H
