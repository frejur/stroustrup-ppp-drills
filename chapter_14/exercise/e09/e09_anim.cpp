#define _USE_MATH_DEFINES
#include "../share/grp/grp_rpoly.h"
#include "e09.h"
#include "e09_board.h"
#include <cmath>

void ch14_e09::Board_animator::animate()
{
	ch14_e09::Board& p = dynamic_cast<Board&>(ws.shape);
	static bool grow_uniform = true;
	static bool grow_piece = true;
	if (std::fmod(time(), 0.5) <= refresh_rate()) {
		grow_uniform = !grow_uniform;
	}
	if (grow_uniform) {
		p.scale(1.01);
	} else {
		p.scale(0.99);
	}
	if (std::fmod(time(), 1.0) <= refresh_rate()) {
		grow_piece = !grow_piece;
	}
	if (grow_piece) {
		// p.scale(1.05, p.number_of_elements() - 1);
	} else {
		// p.scale(0.95, p.number_of_elements() - 1);
	}
	p.rotate(1);
};

void ch14_e09::Board_animator::finish()
{
	ch14_e09::Board& p = dynamic_cast<Board&>(ws.shape);
	p.reset();
}
