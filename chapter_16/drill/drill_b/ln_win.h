#ifndef LN_WIN_H
#define LN_WIN_H

#include "../../lib/GUI.h"
#include "../../lib/Graph.h"
#include "../../lib/Window.h"

struct Lines_window : Graph_lib::Window
{
	Lines_window(Graph_lib::Point xy, int w, int h, const string& title);

private:
	Graph_lib::Open_polyline lines;
	Graph_lib::Menu clr_menu;
	Graph_lib::Button next_button; // Adds Point(next_x, next_y) to 'lines'
	Graph_lib::Button quit_button;
	Graph_lib::Button menu_button;
	Graph_lib::In_box next_x;
	Graph_lib::In_box next_y;
	Graph_lib::Out_box xy_out;

	void next();
	void quit();

	void hide_menu()
	{
		clr_menu.hide();
		menu_button.show();
	}

	// Callbacks
	static void cb_red(Graph_lib::Address, Graph_lib::Address pw)
	{
		Graph_lib::reference_to<Lines_window>(pw).red_pressed();
	};
	static void cb_blue(Graph_lib::Address, Graph_lib::Address pw)
	{
		Graph_lib::reference_to<Lines_window>(pw).blue_pressed();
	};
	static void cb_black(Graph_lib::Address, Graph_lib::Address pw)
	{
		Graph_lib::reference_to<Lines_window>(pw).black_pressed();
	};
	static void cb_menu(Graph_lib::Address, Graph_lib::Address pw)
	{
		Graph_lib::reference_to<Lines_window>(pw).menu_pressed();
	};
	static void cb_next(Graph_lib::Address, Graph_lib::Address pw)
	{
		Graph_lib::reference_to<Lines_window>(pw).next();
	};
	static void cb_quit(Graph_lib::Address, Graph_lib::Address pw)
	{
		Graph_lib::reference_to<Lines_window>(pw).quit_pressed();
	};

	// Actions
	void red_pressed()
	{
		change(Graph_lib::Color::red);
		hide_menu();
	};
	void blue_pressed()
	{
		change(Graph_lib::Color::blue);
		hide_menu();
	};
	void black_pressed()
	{
		change(Graph_lib::Color::black);
		hide_menu();
	};
	void menu_pressed()
	{
		menu_button.hide();
		clr_menu.show();
	};
	void quit_pressed() { hide(); };

	void change(Graph_lib::Color c) { lines.set_color(c); };
};

#endif // LN_WIN_H
