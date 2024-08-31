#include "em_templates.h"

emot::Smiling_party_animal::Smiling_party_animal(Graph_lib::Point pos,
                                                 int radius,
                                                 const std::string& pattern_path,
                                                 Graph_lib::Color color,
                                                 Graph_lib::Color bg_color)
    : Smiley(pos, radius, color, bg_color)
    , hat(*this, pattern_path)
{
	attach_attire(hat);
}

//------------------------------------------------------------------------------

emot::Frowning_dunce::Frowning_dunce(Graph_lib::Point pos,
                                     int radius,
                                     Graph_lib::Color color,
                                     Graph_lib::Color bg_color)
    : Frowney(pos, radius, color, bg_color)
    , hat(*this)
{
	attach_attire(hat);
}
