#ifndef E10_H
#define E10_H
#include "../../lib/Graph.h"
#include "../share/anim/anim_shp.h"
#include <string>

namespace ch14_e10 {

void e10();

//------------------------------------------------------------------------------

static const std::string& info_start()
{
	static const std::string s{"Click to play animation inside the window."};
	return s;
}

static const std::string& info_stop()
{
	static const std::string s{"Click to STOP."};
	return s;
}

//------------------------------------------------------------------------------

class Window_animator : public anim::Shape_animator
{
public:
	using anim::Shape_animator::Shape_animator;

private:
	void animate() override;
	void finish() override;
};

} // namespace ch14_e10
#endif // E10_H
