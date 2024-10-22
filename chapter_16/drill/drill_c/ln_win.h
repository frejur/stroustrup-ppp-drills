#ifndef LN_WIN_H
#define LN_WIN_H

#include "../../lib/GUI.h"
#include "../../lib/Graph.h"
#include "../../lib/Window.h"

struct Lines_window : Graph_lib::Window
{
	Lines_window(Graph_lib::Point xy, int w, int h, const string& title);

private:
	static constexpr int stroke_width{2};
	Graph_lib::Open_polyline lines;
	Graph_lib::Menu clr_menu;
	Graph_lib::Menu sty_menu;
	Graph_lib::Button next_button; // Adds Point(next_x, next_y) to 'lines'
	Graph_lib::Button quit_button;
	Graph_lib::Button clr_menu_button;
	Graph_lib::Button sty_menu_button;
	Graph_lib::In_box next_x;
	Graph_lib::In_box next_y;
	Graph_lib::Out_box xy_out;

	void next();
	void quit();

	// Callbacks
	static void cb_next(Graph_lib::Address, Graph_lib::Address pw)
	{
		Graph_lib::reference_to<Lines_window>(pw).next();
	};
	static void cb_quit(Graph_lib::Address, Graph_lib::Address pw)
	{
		Graph_lib::reference_to<Lines_window>(pw).quit_pressed();
	};

	// Color callbacks
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

	// Line style callbacks
	static void cb_solid(Graph_lib::Address, Graph_lib::Address pw)
	{
		Graph_lib::reference_to<Lines_window>(pw).solid_pressed();
	};

	static void cb_dotted(Graph_lib::Address, Graph_lib::Address pw)
	{
		Graph_lib::reference_to<Lines_window>(pw).dotted_pressed();
	};

	static void cb_dashed(Graph_lib::Address, Graph_lib::Address pw)
	{
		Graph_lib::reference_to<Lines_window>(pw).dashed_pressed();
	};

	// Menu callbacks
	static void cb_clr_menu(Graph_lib::Address, Graph_lib::Address pw)
	{
		Graph_lib::reference_to<Lines_window>(pw).clr_menu_pressed();
	};
	static void cb_sty_menu(Graph_lib::Address, Graph_lib::Address pw)
	{
		Graph_lib::reference_to<Lines_window>(pw).sty_menu_pressed();
	};

	// Actions
	void hide_clr_menu()
	{
		clr_menu.hide();
		clr_menu_button.show();
	}
	void clr_menu_pressed()
	{
		clr_menu_button.hide();
		hide_sty_menu();
		clr_menu.show();
	};

	void hide_sty_menu()
	{
		sty_menu.hide();
		sty_menu_button.show();
	}
	void sty_menu_pressed()
	{
		sty_menu_button.hide();
		hide_clr_menu();
		sty_menu.show();
	};

	void quit_pressed() { hide(); };

	// Color actions
	void red_pressed()
	{
		change_color(Graph_lib::Color::red);
		hide_clr_menu();
	};
	void blue_pressed()
	{
		change_color(Graph_lib::Color::blue);
		hide_clr_menu();
	};
	void black_pressed()
	{
		change_color(Graph_lib::Color::black);
		hide_clr_menu();
	};

	// Line style actions
	void solid_pressed()
	{
		change_style(
		    Graph_lib::Line_style(Graph_lib::Line_style::solid, stroke_width));
		hide_sty_menu();
	}
	void dotted_pressed()
	{
		change_style(
		    Graph_lib::Line_style(Graph_lib::Line_style::dot, stroke_width));
		hide_sty_menu();
	}
	void dashed_pressed()
	{
		change_style(
		    Graph_lib::Line_style(Graph_lib::Line_style::dash, stroke_width));
		hide_sty_menu();
	}

	void change_color(Graph_lib::Color c) { lines.set_color(c); };
	void change_style(Graph_lib::Line_style s) { lines.set_style(s); };
};

#endif // LN_WIN_H
