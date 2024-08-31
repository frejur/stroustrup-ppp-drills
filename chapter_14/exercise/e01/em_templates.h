#ifndef EM_TEMPLATES_H
#define EM_TEMPLATES_H
#include "attire.h"
#include "emoticons.h"

namespace emot {

class Smiling_party_animal : public Smiley
{
public:
	Smiling_party_animal(Graph_lib::Point pos,
	                     int radius,
	                     const std::string& pattern_path,
	                     Graph_lib::Color color = smiley_default_color(),
	                     Graph_lib::Color bg_color = smiley_default_bg_color());

private:
	emot::Party_hat hat;
};

//------------------------------------------------------------------------------

class Frowning_dunce : public Frowney
{
public:
	Frowning_dunce(Graph_lib::Point pos,
	               int radius,
	               Graph_lib::Color color = smiley_default_color(),
	               Graph_lib::Color bg_color = smiley_default_bg_color());

private:
	emot::Dunce_hat hat;
};

} // namespace emot

#endif // EM_TEMPLATES_H
