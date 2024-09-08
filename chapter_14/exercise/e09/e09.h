#ifndef E09_H
#define E09_H
#include "../../lib/Graph.h"
#include "../share/anim/anim_shp.h"
#include <string>

namespace ch14_e09 {

void e09();

//------------------------------------------------------------------------------

static const std::string& info_start()
{
	static const std::string s{"Click to start the animation."};
	return s;
}

static const std::string& info_stop()
{
	static const std::string s{"Click to STOP."};
	return s;
}
static const std::vector<Graph_lib::Color>& colors()
{
	static const std::vector<Graph_lib::Color>& c{Graph_lib::Color::dark_magenta,
	                                              Graph_lib::Color::yellow,
	                                              Graph_lib::Color::dark_green,
	                                              Graph_lib::Color::white};
	return c;
}

static const std::vector<Graph_lib::Line_style>& styles()
{
	static const std::vector<Graph_lib::Line_style>
	    s{Graph_lib::Line_style(Graph_lib::Line_style::dash, 5),
	      Graph_lib::Line_style(Graph_lib::Line_style::solid, 10),
	      Graph_lib::Line_style(Graph_lib::Line_style::dot, 3)};
	return s;
}

//------------------------------------------------------------------------------

class Board_animator : public anim::Shape_animator
{
public:
	using anim::Shape_animator::Shape_animator;

private:
	void animate() override;
	void finish() override;
};

} // namespace ch14_e09

#endif // E09_H
