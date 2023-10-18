#ifndef DEBUG_WINDOW_H
#define DEBUG_WINDOW_H

#include "Simple_window.h"
#include "./GUI.h"
#include <memory>
#include <cmath>
#include <Fl/Fl_Multiline_Output.H>
#include <string>
#include <iostream>

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
		pw->color(38);
		Fl_Multiline_Output& con{ reference_to<Fl_Multiline_Output>(pw) };
		con.textcolor(52);
		con.textfont(FL_SCREEN);
		con.textsize(18);
		own = &w;
	}

	void put(const std::string& s) {
		Fl_Multiline_Output& con{ reference_to<Fl_Multiline_Output>(pw) };
		con.value((con.value() + s).c_str());
	}
private:
	bool const m_console_is_empty() {
		return reference_to<Fl_Multiline_Output>(pw).size() == 0;
	}
};

class Debug_window;

class FLTK_buffer : public std::streambuf{
public:
	FLTK_buffer(Debug_window& win);
	virtual int_type overflow(int_type c);
	virtual int sync();
	~FLTK_buffer();
private:
	Debug_window& m_win;
	std::string m_buf;
	std::streambuf* m_sb;
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
		m_fltk_buf = std::make_unique<FLTK_buffer>(
			FLTK_buffer(*this)
		);
		attach(*m_console);
	}
	using GL::Window::attach;
	void const log(const std::string& s) {
		if (!m_debug_is_enabled) {
			return;
		}
		m_console->put(s);
	}
private:
	const bool m_debug_is_enabled;
	std::unique_ptr<Debug_console> m_console;
	std::unique_ptr<FLTK_buffer> m_fltk_buf;
};


FLTK_buffer::FLTK_buffer(Debug_window& win)
: m_win(win) {
	setp(0, 0);
	m_sb = std::cout.rdbuf(this);
}

FLTK_buffer::~FLTK_buffer() {
	std::cout.rdbuf(m_sb);
}

FLTK_buffer::int_type FLTK_buffer::overflow(int_type c) {
	if (c != traits_type::eof()) {
		this->m_buf.push_back(c);
	}
	return traits_type::not_eof(c);
}
int FLTK_buffer::sync() {
	m_win.log(m_buf);
	m_buf.clear();
	return 0;
}


#endif // DEBUG_WINDOW_H
