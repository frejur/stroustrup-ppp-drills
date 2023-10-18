#ifndef DEBUG_WINDOW_H
#define DEBUG_WINDOW_H

#include "Simple_window.h"
#include "./GUI.h"
#include <memory>
#include <cmath>
#include <Fl/Fl_Multiline_Output.H>
#include <string>

namespace GL = Graph_lib;

class Debug_console : public GL::Widget
{
public:
	Debug_console(GL::Point xy, int w, int h)
	: GL::Widget(xy, w, h, "", 0)
	{}

	void attach(GL::Window &w) {
		pw = new Fl_Multiline_Output(loc.x, loc.y + 25, width,
			(std::max)(25, height-25), 0);
		pw->align(FL_ALIGN_TOP_LEFT);
		pw->color(FL_BLACK);
		reference_to<Fl_Multiline_Output>(pw).textcolor(FL_WHITE);
		own = &w;
	}

	void put(const std::string& s) {
		Fl_Multiline_Output& con{ reference_to<Fl_Multiline_Output>(pw) };
		std::string nl{ (!m_console_is_empty()) ? "\n" : "" };
		con.value((con.value() + nl + s).c_str());
	}
private:
	bool const m_console_is_empty() {
		return reference_to<Fl_Multiline_Output>(pw).size() == 0;
	}
};

class Debug_window : public Simple_window
{
public:
	Debug_window(GL::Point xy, int w, int h, const string& title,
		bool enable_debug=false)
	:	Simple_window(xy, static_cast<int>(w + w*enable_debug), h, title),
		m_debug_is_enabled( enable_debug )
	{
		if (!enable_debug) {
			return;
		}
		m_console = std::make_unique<Debug_console>(
			Debug_console({w, 0}, w, h)
		);
		attach(*m_console);
	}
	using GL::Window::attach;
	void log(const std::string& s) {
		if (!m_debug_is_enabled) {
			return;
		}
		m_console->put(s);
	}
private:
	const bool m_debug_is_enabled;
	std::unique_ptr<Debug_console> m_console;
};



#endif // DEBUG_WINDOW_H
