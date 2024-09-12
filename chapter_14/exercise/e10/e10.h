#ifndef E10_H
#define E10_H
#include "../../lib/Graph.h"
#include "e10_anim.h"
#include "e10_pac.h"
#include "e10_pnp.h"
#include "e10_pswin.h"
#include <string>

namespace ch14_e10 {

void e10();

//------------------------------------------------------------------------------

inline const std::string& info_start()
{
	static const std::string s{"Click to play animation."};
	return s;
}

inline const std::string& info_stop()
{
	static const std::string s{"Click to STOP."};
	return s;
}

inline const Graph_lib::Color& inactive_color()
{
	static const Graph_lib::Color c{static_cast<int>(fl_rgb_color(90, 90, 90))};
	return c;
}

//------------------------------------------------------------------------------

enum class Pacman_dir;

} // namespace ch14_e10
#endif // E10_H
