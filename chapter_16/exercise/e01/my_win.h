#ifndef MY_WIN_H
#define MY_WIN_H

#include "../../lib/GUI.h"
#include "../../lib/Graph.h"
#include "../../lib/Window.h"

class My_window : public Graph_lib::Window
{
public:
	My_window(Graph_lib::Point xy, int w, int h, const string& title);
	void wait_for_button(); // Performs the action contained in which_button

	// Toggle button visibility
	void show_next_button() { btn_next.show(); };
	void hide_next_button() { btn_next.hide(); };
	void show_quit_button() { btn_quit.show(); };
	void hide_quit_button() { btn_quit.hide(); };

private:
	bool waiting;
	enum class Button_pushed { None, Next, Quit };
	Graph_lib::Button btn_next;
	Graph_lib::Button btn_quit;

	Button_pushed which_button;
	void reset_which_button() { which_button = Button_pushed::None; };
	bool button_is_none() const { return which_button == Button_pushed::None; };

	// Callbacks
	static void cb_next(void*, void*);
	static void cb_quit(void*, void*);

	// Sets the which_button flag if waiting == true, or performs the action.
	void trigger_next();

	void trigger_quit();

	void perform_next();
	void perform_quit();

};

#endif // MY_WIN_H
