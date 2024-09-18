#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "../../lib/Graph.h"
#include "ctrl_obj.h"
#include "maze_anim.h"

namespace ch14_e16 {

class Toggle
{
public:
	Toggle()
	    : is_on_(false){};
	virtual void on() { is_on_ = true; };
	virtual void off() { is_on_ = false; };
	bool is_on() const { return is_on_; };

protected:
	bool is_on_;
};

//------------------------------------------------------------------------------

class Controller : public Toggle
{
public:
	Controller()
	    : lv(0){};
	virtual void set_level(int l) { lv = l; };
	virtual void show() = 0;
	int level() const { return lv; }

private:
	int lv;
};

//------------------------------------------------------------------------------

class Test_controller : public Controller
{
public:
	Test_controller(Graph_lib::Text& text)
	    : Controller()
	    , txt(text){};
	virtual void show();

private:
	Graph_lib::Text& txt;
};

//------------------------------------------------------------------------------

class Action_controller : public Controller
{
public:
	Action_controller(Action_button& button)
	    : Controller()
	    , btn(button){};
	virtual void on() override;
	;
	virtual void off() override;
	;

private:
	virtual void show() override{};

private:
	Action_button& btn;
};

//------------------------------------------------------------------------------

class Level_controller : public Controller
{
public:
	Level_controller(Level_indicator& button)
	    : Controller()
	    , btn(button){};
	virtual void show() override
	{
		btn.set_label(std::to_string(level() + 1));
	};
	virtual void on() override
	{
		Controller::on();
		btn.set_color(Graph_lib::Color::dark_green);
		btn.set_fill_color(Graph_lib::Color::green);
	};
	virtual void off() override
	{
		Controller::off();
		btn.set_color(Graph_lib::Color::black);
		btn.set_fill_color(Graph_lib::Color::invisible);
	};

private:
	Level_indicator& btn;
};

//------------------------------------------------------------------------------

class Anim_controller : public ch14_e16::Controller
{
public:
	using ch14_e16::Controller::Controller;
	void add(ch14_e16::Maze_animator& animator);
	virtual void on() override;
	virtual void off() override;
	virtual void set_level(int l) override;
	;
	void reset() { anim[valid_level()].reset(); }
	bool has_reached_end() const;
	;
	int number_of_animators() const { return anim.size(); };

private:
	int valid_level() const;
	virtual void show() override{}; // Hide
	Graph_lib::Vector_ref<ch14_e16::Maze_animator> anim;
};

} // namespace ch14_e16

#endif // CONTROLLER_H
