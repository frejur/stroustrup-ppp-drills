#ifndef MY_WINDOW_H
#define MY_WINDOW_H
#include "../../lib/GUI.h"
#include "../../lib/Graph.h"
#include "../share/geo/arrow.h"
#include "../share/outlined_text.h"
#include "../share/win/anim_win.h"
#include "clock_face.h"

struct Hms
{
	int hours;
	int minutes;
	int seconds;
};

class My_window : public anm_win::Animated_window
{
public:
	My_window(Graph_lib::Point top_left,
	          int width,
	          int height,
	          const std::string& title,
	          int refresh_rate_ms = Animated_window::default_rate_ms);

	void start_ticking();
	void stop_ticking();

private:
	int angle_sec;
	int angle_min;
	int angle_hour;

	Arrow hand_sec;
	Arrow hand_min;
	Arrow hand_hour;

	Graph_lib::Circle frame;
	Graph_lib::Circle bg;
	Clock_face face;

	Outlined_text txt_pause;

	Graph_lib::Button btn_start;
	Graph_lib::Button btn_pause;

	virtual void polling_action() override;
};

// Get current local time as Hours, minutes and seconds (copypasta)
Hms current_time_as_hms();

#endif // ANIMATED_WINDOW_H
