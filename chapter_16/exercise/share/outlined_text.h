#ifndef OUTLINED_TEXT_H
#define OUTLINED_TEXT_H
#include "../../lib/Graph.h"

class Outlined_text : public Graph_lib::Text
{
public:
	Outlined_text(Graph_lib::Point btm_left, const std::string& label)
	    : Graph_lib::Text(btm_left, label)
	{
		set_color(Graph_lib::Color::white);
		set_outline_color(Graph_lib::Color::black);
	};
	void set_outline_color(Graph_lib::Color c) { oln_c = c; };
	Graph_lib::Color outline_color() const { return oln_c; };

	virtual void draw_lines() const
	{
		if (!color().visibility() || !outline_color().visibility()) {
			return;
		}

		fl_font(font().as_int(), font_size());
		Graph_lib::Color ocol = fl_color();
		fl_color(outline_color().as_int());
		// clang-format off
		std::vector<Graph_lib::Point> offs{{-1, -1}, {0, -1}, {1, -1},
		                                   {-1, 0},  {0, 0},  {1, 0},
		                                   {-1, 1},  {0, 1} , {1, 1}}; // clang-format on

		for (Graph_lib::Point o : offs) {
			fl_draw(label().c_str(), point(0).x + o.x, point(0).y + o.y);
		}
		fl_color(ocol.as_int());

		Graph_lib::Text::draw_lines();
	}

private:
	Graph_lib::Color oln_c{0};
};

#endif // OUTLINED_TEXT_H
