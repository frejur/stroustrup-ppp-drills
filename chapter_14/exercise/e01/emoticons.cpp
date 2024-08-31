#include "emoticons.h"

//------------------------------------------------------------------------------

emot::Eye_attr emot::eye_attributes(Graph_lib::Point pos, int radius)
{
	return {{pos.x - static_cast<int>(radius * 0.4),
	         pos.y - static_cast<int>(radius * 0.25)},
	        static_cast<int>(radius * 0.1),
	        static_cast<int>(radius * 0.3),
	        static_cast<int>(radius * 0.8)};
}

//------------------------------------------------------------------------------

emot::Smiley::Smiley(Graph_lib::Point pos,
                     int radius,
                     Graph_lib::Color color,
                     Graph_lib::Color bg_color)
    : Emoticon(pos, radius)
    , mouth({pos.x, pos.y + static_cast<int>(radius * 0.3)},
            static_cast<int>(radius * 1.25),
            static_cast<int>(radius * 0.4))
{
	set_color(color);
	set_fill_color(bg_color);
	set_eye_color(color);
	mouth.set_color(color);
}

void emot::Smiley::draw_lines() const
{
	Circle::draw_lines();
	mouth.draw();
	draw_eyes();
	draw_attire();
}

//------------------------------------------------------------------------------

emot::Frowney::Frowney(Graph_lib::Point pos,
                       int radius,
                       Graph_lib::Color color,
                       Graph_lib::Color bg_color)
    : Emoticon(pos, radius)
    , mouth({pos.x, pos.y + static_cast<int>(radius * 0.6)},
            static_cast<int>(radius * 1),
            static_cast<int>(radius * 0.5),
            Arc_geo::S_arc_dir::Down)
{
	set_color(color);
	set_fill_color(bg_color);
	set_eye_color(color);
	mouth.set_color(color);
}

void emot::Frowney::draw_lines() const
{
	Circle::draw_lines();
	mouth.draw();
	draw_eyes();
	draw_attire();
}
