#define NOMINMAX
#ifndef PACMAN_H
#define PACMAN_H
#include "e10.h"
#include <algorithm>

constexpr float pacman_open_jaw_angle{75};

namespace ch14_e10 {

enum class Pacman_dir { Up = -1, Right, Down, Left };

class Pacman : public Graph_lib::Circle
{
public:
	Pacman(Graph_lib::Point center,
	       int radius,
	       float jaw_state = 1,
	       Pacman_dir start_dir = Pacman_dir::Right)
	    : Circle(center, radius)
	    , jaw(valid_jaw(jaw_state))
	    , dir(start_dir){};

protected:
	void draw_lines() const override;

private:
	float jaw; // 0 = closed, 1 = open
	Pacman_dir dir;
	float valid_jaw(float j) const
	{
		return std::min(1.0f, std::max(j, 0.0f));
	};
};

} // namespace ch14_e10

#endif // PACMAN_H
