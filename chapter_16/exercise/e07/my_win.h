#ifndef MY_WINDOW_H
#define MY_WINDOW_H
#include "../../lib/GUI.h"
#include "../../lib/Graph.h"
#include "../share/outlined_text.h"
#include "../share/win/anim_win.h"
#include "prg_bar.h"

class My_window : public anm_win::Animated_window
{
public:
	My_window(Graph_lib::Point top_left,
	          int width,
	          int height,
	          const std::string& title,
	          int refresh_rate_ms = Animated_window::default_rate_ms);

	void start_moving();
	void stop_moving();

private:
	Outlined_text txt_pause;
	Progress_bar bar;

	Graph_lib::Button btn_start;
	Graph_lib::Button btn_pause;

	virtual void polling_action() override;
};

#endif // MY_WINDOW_H
