#ifndef EMOTICONS_H
#define EMOTICONS_H
#include "../../lib/Graph.h"
#include "../share/geo/arc.h"
#include "attire.h"

namespace emot {

// Default values --------------------------------------------------------------

inline const Graph_lib::Color& smiley_default_color()
{
	static Graph_lib::Color c{Graph_lib::Color::black};
	return c;
}

inline const Graph_lib::Color& smiley_default_bg_color()
{
	static Graph_lib::Color c{Graph_lib::Color::yellow};
	return c;
}

//------------------------------------------------------------------------------

struct Eye_attr
{
	Eye_attr(Graph_lib::Point p_origin,
	         int p_width,
	         int p_height,
	         int p_offset_x)
	    : origin(p_origin)
	    , width(p_width)
	    , height(p_height)
	    , offset_x(p_offset_x){};
	int width{0};
	int height{0};
	int offset_x{0};
	Graph_lib::Point origin;
};

Eye_attr eye_attributes(Graph_lib::Point pos, int radius);

//------------------------------------------------------------------------------

class Emoticon : public Graph_lib::Circle
{
public:
	void attach_attire(Attire& att) { att_v.push_back(att); };

protected:
	Emoticon(Graph_lib::Point pos, int radius)
	    : Graph_lib::Circle(pos, radius)
	    , eye_a(eye_attributes(pos, radius))
	    , l_eye(eye_a.origin, eye_a.width, eye_a.height)
	    , r_eye({eye_a.origin.x + eye_a.offset_x, eye_a.origin.y},
	            eye_a.width,
	            eye_a.height)
	{
		l_eye.set_color(Graph_lib::Color::Transparency::invisible);
		r_eye.set_color(Graph_lib::Color::Transparency::invisible);
		set_eye_color(Graph_lib::Color::black);
	}
	Eye_attr eye_a;
	Graph_lib::Ellipse l_eye;
	Graph_lib::Ellipse r_eye;
	Graph_lib::Vector_ref<Attire> att_v;
	void draw_eyes() const
	{
		l_eye.draw();
		r_eye.draw();
	};
	void set_eye_color(Graph_lib::Color color)
	{
		l_eye.set_fill_color(color);
		r_eye.set_fill_color(color);
	}
	void draw_attire() const
	{
		for (int i = 0; i < att_v.size(); ++i) {
			att_v[i].draw_lines();
		}
	}
};

//------------------------------------------------------------------------------

class Smiley : public Emoticon
{
public:
	Smiley(Graph_lib::Point pos,
	       int radius,
	       Graph_lib::Color color = smiley_default_color(),
	       Graph_lib::Color bg_color = smiley_default_bg_color());
	void draw_lines() const;

private:
	Arc_geo::Semi_arc mouth;
};

//------------------------------------------------------------------------------

class Frowney : public Emoticon
{
public:
	Frowney(Graph_lib::Point pos,
	        int radius,
	        Graph_lib::Color color = smiley_default_color(),
	        Graph_lib::Color bg_color = smiley_default_bg_color());
	void draw_lines() const;

private:
	Arc_geo::Semi_arc mouth;
};

//------------------------------------------------------------------------------

} // namespace emot
#endif // EMOTICONS_H
