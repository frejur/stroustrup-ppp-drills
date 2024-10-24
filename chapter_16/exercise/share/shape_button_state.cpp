#include "shape_button.h"

bool shp_btn::Shape_button::is_normal() const
{
	return st == Shape_button_state::Normal;
}

bool shp_btn::Shape_button::is_active() const
{
	return st == Shape_button_state::Active;
}

bool shp_btn::Shape_button::is_disabled() const
{
	return st == Shape_button_state::Disabled;
}

bool shp_btn::Shape_button::is_visible() const
{
	return !is_hidden;
}

void shp_btn::Shape_button::normalize()
{
	Graph_lib::Button::show();
	btn_act.hide();
	st = Shape_button_state::Normal;
	box.transform(normal_xy, {normal_xy.x + normal_w, normal_xy.y + normal_h});
}

void shp_btn::Shape_button::activate()
{
	btn_act.show();
	Graph_lib::Button::hide();
	st = Shape_button_state::Active;
	box.transform(active_xy, {active_xy.x + active_w, active_xy.y + active_h});
}

void shp_btn::Shape_button::disable()
{
	st = Shape_button_state::Disabled;
}
