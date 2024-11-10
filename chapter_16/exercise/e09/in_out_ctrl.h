#ifndef IN_OUT_CTRL_H
#define IN_OUT_CTRL_H
#include "../../lib/GUI.h"

class My_calculator; // Forward declare

// Some custom widgets that are attached to a calculator object rather than a
// window object

// An In_box that triggers its callback function when edited
class In_box_control : public Graph_lib::Widget
{
public:
	In_box_control(Graph_lib::Point xy,
	               int w,
	               int h,
	               const string& s,
	               Graph_lib::Callback callback_fn)
	    : Graph_lib::Widget(xy, w, h, s, callback_fn)
	    , is_hidden(false)
	{}

	int get_int();
	string get_string();
	void clear();
	void put(const std::string& s);
	virtual void attach(Graph_lib::Window& win) override{}; // disable
	void attach(Graph_lib::Window& win, My_calculator& calc);
	virtual void move(int dx, int dy) override;
	virtual void hide() override;
	virtual void show() override;
	bool is_visible() const { return !is_hidden; };

private:
	bool ignore_next;
	bool is_hidden;
};

//------------------------------------------------------------------------------
// An Out_box, with an added method for retrieving the label width
class Out_box_control : public Graph_lib::Out_box
{
public:
	using Graph_lib::Out_box::Out_box;
	int label_width() const;
	virtual void attach(Graph_lib::Window& win) override{}; // disable
	void attach(Graph_lib::Window& win, My_calculator& calc);
	virtual void move(int dx, int dy) override;
	virtual void hide() override;
	virtual void show() override;
	bool is_visible() const { return !is_hidden; };

private:
	bool is_hidden{false};
};

#endif // IN_OUT_CTRL_H
