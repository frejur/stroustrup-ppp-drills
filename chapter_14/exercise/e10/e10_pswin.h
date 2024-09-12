#ifndef PSWIN_H
#define PSWIN_H
#include "../share/geo/box.h"
#include "../share/grp/grp_shp.h"
#include "e10_pac.h"

namespace ch14_e10 {

constexpr int default_button_corner_radius{4};

inline const Graph_lib::Color& default_button_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::white};
	return c;
}

inline const Graph_lib::Color& default_button_fill_color()
{
	static const Graph_lib::Color c{
	    static_cast<int>(fl_rgb_color(40, 110, 240))};
	return c;
}

inline const Graph_lib::Color& default_close_button_fill_color()
{
	static const Graph_lib::Color c{
	    static_cast<int>(fl_rgb_color(230, 100, 75))};
	return c;
}

inline const Graph_lib::Color& default_window_fill_color()
{
	static const Graph_lib::Color c{static_cast<int>(fl_rgb_color(0, 85, 230))};
	return c;
}

inline const Graph_lib::Color& default_window_stroke_color()
{
	static const Graph_lib::Color c{static_cast<int>(fl_rgb_color(0, 30, 255))};
	return c;
}

inline const Graph_lib::Color& default_canvas_color()
{
	static const Graph_lib::Color c{
	    static_cast<int>(fl_rgb_color(115, 115, 115))};
	return c;
}

//------------------------------------------------------------------------------

struct Button_padding
{
	Graph_lib::Point top_left;
	Graph_lib::Point top_right;
	Graph_lib::Point btm_right;
	Graph_lib::Point btm_left;
};

class Control_button : public grp_shp::Shape_group
{
public:
	Control_button(Graph_lib::Point origin,
	               int width,
	               int height,
	               Graph_lib::Color color = default_button_color(),
	               Graph_lib::Color fill_color = default_button_fill_color(),
	               int corner_radius = default_button_corner_radius);
	void move(int offset_x, int offset_y) override
	{
		grp_shp::Shape_group::move(offset_x, offset_y);
		btn.move(offset_x, offset_y);
	};

protected:
	int w;
	int h;
	int pad;
	Graph_lib::Color sym_color;
	virtual Button_padding padded_corners() const;

private:
	BOX::Box btn;
	void draw_lines() const override;
	int calc_padding(int width, int height) const;
};

//------------------------------------------------------------------------------

class Close_button : public Control_button
{
public:
	Close_button(Graph_lib::Point origin,
	             int width,
	             int height,
	             Graph_lib::Color color = default_button_color(),
	             Graph_lib::Color fill_color = default_close_button_fill_color(),
	             int corner_radius = default_button_corner_radius);

private:
	void init_symbol();
	Button_padding padded_corners() const override;
};

//------------------------------------------------------------------------------

class Maximize_button : public Control_button
{
public:
	Maximize_button(Graph_lib::Point origin,
	                int width,
	                int height,
	                Graph_lib::Color color = default_button_color(),
	                Graph_lib::Color fill_color = default_button_fill_color(),
	                int corner_radius = default_button_corner_radius);

private:
	void init_symbol();
};

//------------------------------------------------------------------------------

class Minimize_button : public Control_button
{
public:
	Minimize_button(Graph_lib::Point origin,
	                int width,
	                int height,
	                Graph_lib::Color color = default_button_color(),
	                Graph_lib::Color fill_color = default_button_fill_color(),
	                int corner_radius = default_button_corner_radius);

private:
	void init_symbol();
};

//------------------------------------------------------------------------------

class Pseudo_window : public Graph_lib::Shape
{
public:
	Pseudo_window(Graph_lib::Point origin, int width, int height);
	void attach(Graph_lib::Shape& s) { content.add(s); };
	void move(int offset_x, int offset_y) override;
	Graph_lib::Point origin() const { return point(0); };

private:
	BOX::Box frame;
	Pacman icon;
	Graph_lib::Text title;
	Minimize_button btn_min;
	Maximize_button btn_max;
	Close_button btn_close;
	Graph_lib::Rectangle canvas;
	grp_shp::Shape_group content;

	void draw_lines() const override;
};

//------------------------------------------------------------------------------

} // namespace ch14_e10

#endif // PSWIN_H
