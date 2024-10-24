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

int calc_lb_w(const std::string& txt, Graph_lib::Font f, int f_sz);

} // namespace ch16_hlp

#endif // CH16_HELPERS_H
