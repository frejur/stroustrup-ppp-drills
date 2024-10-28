#ifndef ANIMATED_WINDOW_H
#define ANIMATED_WINDOW_H
#include "../../../lib/Graph.h"
#include "../../../lib/Window.h"

namespace anm_win {

class Animated_window : public Graph_lib::Window
{
public:
	Animated_window(Graph_lib::Point top_left,
	                int width,
	                int height,
	                const std::string& title,
	                int refresh_rate_ms = default_rate_ms);
	void start_polling(int duration_sec);
	void stop_polling();

	bool is_polling() const { return is_poll; };
	int milliseconds_passed() const { return passed_ms; };
	int polling_duration_in_seconds() const { return dur_sec; };

protected:
	static const int default_rate_ms;

	virtual void polling_action() = 0;

private:
	bool trigger_stop;
	bool is_poll;
	int rate_ms;

	int passed_ms;
	int dur_sec;

	void poll();

	int valid_rate(int r_ms) const;
	int valid_duration(int d_sec, int r_ms) const;
};

} // namespace anm_win

#endif // ANIMATED_WINDOW_H
