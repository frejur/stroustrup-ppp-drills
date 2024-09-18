#include "controller.h"
#include <sstream>

void ch14_e16::Test_controller::show()
{
	std::ostringstream os;
	os << "Status: " << (is_on() ? "On" : "Off")
	   << ", Level: " << (level() + 1);
	txt.set_label(os.str());
}

//------------------------------------------------------------------------------

void ch14_e16::Action_controller::on()
{
	Controller::on();
	btn.set_fill_color(btn.active_color());
}

void ch14_e16::Action_controller::off()
{
	Controller::off();
	btn.set_fill_color(btn.inactive_color());
}

//------------------------------------------------------------------------------

void ch14_e16::Anim_controller::add(Maze_animator& animator)
{
	anim.push_back(animator);
	if (anim.size() > 1) {
		anim[anim.size() - 1].hide();
	}
}

void ch14_e16::Anim_controller::on()
{
	if (is_on()) {
		return;
	}
	ch14_e16::Controller::on();
	anim[valid_level()].start();
}

void ch14_e16::Anim_controller::off()
{
	if (!is_on()) {
		return;
	}
	ch14_e16::Controller::off();
	anim[valid_level()].stop();
}

void ch14_e16::Anim_controller::set_level(int l)
{
	if (is_on()) {
		throw runtime_error("Cannot change level while animation is playing");
	}
	anim[valid_level()].hide();
	ch14_e16::Controller::set_level(l);
	anim[valid_level()].show();
}

bool ch14_e16::Anim_controller::has_reached_end() const
{
	return anim[valid_level()].has_reached_end();
}

int ch14_e16::Anim_controller::valid_level() const
{
	if (level() < 0 || level() > anim.size() - 1) {
		throw std::runtime_error("There is no level with that index");
	}
	return level();
}
