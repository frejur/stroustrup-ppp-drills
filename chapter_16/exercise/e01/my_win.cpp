#include "my_win.h"

namespace {
constexpr int window_top_padding{8};
constexpr int window_right_padding{8};
constexpr int button_width{64};
constexpr int button_height{32};
constexpr int button_horizontal_padding{4};

const std::string& button_label_next()
{
	static const std::string s{"Next"};
	return s;
}

const std::string& button_label_quit()
{
	static const std::string s{"Exit"};
	return s;
}
} // namespace

//------------------------------------------------------------------------------

My_window::My_window(Graph_lib::Point xy, int w, int h, const string& title)
    : Window(xy, w, h, title)
    , waiting(false)
    , btn_next(Graph_lib::Point{x_max()
                                    - (window_right_padding + button_width * 2
                                       + button_horizontal_padding),
                                window_top_padding},
               button_width,
               button_height,
               button_label_next(),
               cb_next)
    , btn_quit(Graph_lib::Point{x_max() - (window_right_padding + button_width),
                                window_top_padding},
               button_width,
               button_height,
               button_label_quit(),
               cb_quit)
    , which_button(Button_pushed::None)
{
	attach(btn_next);
	attach(btn_quit);
}

//------------------------------------------------------------------------------

void My_window::cb_quit(void*, void* pw)
{
	(*static_cast<My_window*>(pw)).trigger_quit();
}

void My_window::cb_next(void*, void* pw)
{
	(*static_cast<My_window*>(pw)).trigger_next();
}

//------------------------------------------------------------------------------

void My_window::trigger_quit()
{
	if (!waiting) {
		reset_which_button();
		perform_quit();
		return;
	}
	which_button = Button_pushed::Quit;
}

void My_window::trigger_next()
{
	if (!waiting) {
		perform_next();
		return;
	}
	which_button = Button_pushed::Next;
}

//------------------------------------------------------------------------------

void My_window::perform_next() {}

void My_window::perform_quit()
{
	hide();
}

//------------------------------------------------------------------------------

void My_window::wait_for_button()
{
	waiting = true;
	while (shown() && button_is_none()) {
		Fl::wait();
	}
	switch (which_button) {
	case Button_pushed::Next:
		perform_next();
		break;
	case Button_pushed::Quit:
		perform_quit();
	case Button_pushed::None:
	default:
		break;
	}

	reset_which_button();
	waiting = false;
	Fl::redraw();
}
