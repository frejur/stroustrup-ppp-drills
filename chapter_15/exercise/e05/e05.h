#ifndef E05_H
#define E05_H
#include "../../lib/Graph.h"
#include <string>

namespace ch15_e05 {

void e05();

//------------------------------------------------------------------------------

class Graph_canvas
{
public:
	Graph_canvas(Graph_lib::Point canvas_origin,
	             int width,
	             int height,
	             Graph_lib::Point graph_origin,
	             int notch_size_x,
	             int notch_size_y);
	Graph_lib::Point graph_origin() const { return o_graph; };
	int number_of_neg_x_notches() const { return count_x_neg; };
	int number_of_pos_x_notches() const { return count_x_pos; };
	int number_of_x_notches() const { return count_x_neg + count_x_pos; };
	int number_of_y_notches() const { return count_y_neg + count_y_pos; };
	int x_notch_size() const { return sz_x; };
	int y_notch_size() const { return sz_y; };
	Graph_lib::Point x_axis_start() const;
	Graph_lib::Point y_axis_start() const;
	int x_axis_length() const { return number_of_x_notches() * x_notch_size(); }
	int y_axis_length() const { return number_of_y_notches() * y_notch_size(); }

private:
	int w;
	int h;
	int sz_x;
	int sz_y;
	int count_x_neg;
	int count_x_pos;
	int count_y_neg;
	int count_y_pos;
	Graph_lib::Point o_canvas;
	Graph_lib::Point o_graph;
};

//------------------------------------------------------------------------------

enum class Text_alignment {
	Top_left,
	Top_center,
	Top_right,
	Mid_left,
	Mid_center,
	Mid_right,
	Btm_left,
	Btm_center,
	Btm_right
};

struct Label_style
{
	Label_style(Graph_lib::Font f,
	            int sz,
	            Graph_lib::Color c,
	            Text_alignment a = Text_alignment::Top_center)
	    : font(f)
	    , font_size(sz)
	    , color(c)
	    , text_alignment(a)
	    , vertical_padding{static_cast<int>(sz * 0.5 + 0.5)}
	    , horizontal_padding{static_cast<int>(sz * 0.5 + 0.5)} {};
	const Graph_lib::Font font;
	const int font_size;
	const Graph_lib::Color color;
	const Text_alignment text_alignment;
	const int vertical_padding;
	const int horizontal_padding;
	void apply_to(Graph_lib::Text& t);
};

//------------------------------------------------------------------------------

int calc_lb_w(const std::string& txt, Graph_lib::Font f, int f_sz);

} // namespace ch15_e05

#endif // E05_H
