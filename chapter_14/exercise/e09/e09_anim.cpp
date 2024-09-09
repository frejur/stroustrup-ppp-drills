#define _USE_MATH_DEFINES
#include "../share/grp/grp_rpoly.h"
#include "e09.h"
#include "e09_board.h"
#include <cmath>

struct Move
{
	int start;
	int end;
};

static const std::vector<Move> moves()
{
	static const std::vector<Move>& m{{32, 28}, {18, 22}, {34, 29}, {16, 21},
	                                  {29, 23}, {12, 18}, {23, 12}, {7, 18},
	                                  {33, 29}, {22, 33}, {33, 24}, {31, 27},
	                                  {21, 32}, {38, 27}, {24, 30}, {35, 24},
	                                  {20, 29}, {39, 34}, {29, 33}, {42, 38},
	                                  {33, 42}, {42, 31}, {31, 22}};
	return m;
}

void ch14_e09::Board_animator::animate()
{
	ch14_e09::Board& p = dynamic_cast<Board&>(ws.shape);
	if (std::fmod(time(), 0.5) <= refresh_rate()) {
		int move_count = static_cast<int>(time() / 0.5);
		if (move_count < moves().size()) {
			p.move_piece(moves()[move_count].start, moves()[move_count].end);
		}
	}
	p.scale(1.0015);
	p.rotate(0.5);
};

void ch14_e09::Board_animator::finish()
{
	ch14_e09::Board& p = dynamic_cast<Board&>(ws.shape);
	p.reset();
}
