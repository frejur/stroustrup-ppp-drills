#ifndef CTRL_OBJ_H
#define CTRL_OBJ_H
#include "../../lib/Graph.h"
#include "../share/geo/box.h"

namespace ch14_e16 {

class Level_indicator : public Graph_lib::Circle
{
public:
	using Graph_lib::Circle::Circle;
	void set_label(const std::string& s) { label = s; }
	void draw_lines() const override;
	;

private:
	std::string label;
};

//------------------------------------------------------------------------------

class Action_button : public BOX::Box
{
public:
	using BOX::Box::Box;
	void set_label(const std::string& s);
	;
	void draw_lines() const override;
	;
	Graph_lib::Color active_color() const { return active_c; };
	Graph_lib::Color inactive_color() const { return inactive_c; };
	void set_active_color(Graph_lib::Color color) { active_c = color; };
	void set_inactive_color(Graph_lib::Color color) { inactive_c = color; };
	bool point_is_on_button(Graph_lib::Point pt) const;

private:
	std::string label;
	Graph_lib::Font fnt{Graph_lib::Font::courier};
	int txt_pad() const
	{
		return static_cast<int>(std::round(0.3 * height()));
	};
	Graph_lib::Color active_c{Graph_lib::Color::green};
	Graph_lib::Color inactive_c{Graph_lib::Color::invisible};
};

} // namespace ch14_e16

#endif // CTRL_OBJ_H
