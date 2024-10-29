#ifndef MY_WINDOW_H
#define MY_WINDOW_H
#include "../../lib/GUI.h"
#include "../../lib/Graph.h"
#include "../share/outlined_text.h"
#include "../share/win/anim_win.h"
#include "pickup.h"
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
	const int top_m;
	double speed_px;     // Move truck by this distance
	double target_thold; // Target is reached if truck is within this distance
	double target_min_dist;
	double target_max_dist;
	const Graph_lib::Point default_target;
	Graph_lib::Point target;

	Outlined_text txt_pause;
	Progress_bar bar;

	Pickup pkup;

	Graph_lib::Button btn_start;
	Graph_lib::Button btn_pause;

	// Get corner coordinates
	Graph_lib::Point crn(int idx, int w, int h, int top_m) const
	{
		idx = idx % 4;
		return {(idx == 1 || idx == 2) * w, (idx > 1) * h + (idx < 2) * top_m};
	};

	void new_random_target();

	virtual void polling_action() override;
};

#endif // MY_WINDOW_H
