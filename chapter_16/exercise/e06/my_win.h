#ifndef MY_WINDOW_H
#define MY_WINDOW_H
#include "../../lib/Graph.h"
#include "../share/geo/arrow.h"
#include "../share/win/anim_win.h"

class My_window : public anm_win::Animated_window
{
public:
	My_window(Graph_lib::Point top_left,
	          int width,
	          int height,
	          const std::string& title,
	          int refresh_rate_ms = Animated_window::default_rate_ms);

private:
	virtual void polling_action() override;

	Graph_lib::Text txt;
	Arrow hand_sec;
};

#endif // ANIMATED_WINDOW_H
