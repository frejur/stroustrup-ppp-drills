#include "calc.h"

void Calculator_button::attach(Graph_lib::Window& win, My_calculator& calc)
{
	shp_btn::Image_button::attach(win);
	pw->callback(reinterpret_cast<Fl_Callback*>(do_it),
	             &calc); // pass the Calculator
}

void Modal_button::attach(Graph_lib::Window& win, My_calculator& calc)
{
	shp_btn::Shape_button::attach(win);
	pw->callback(reinterpret_cast<Fl_Callback*>(do_it),
	             &calc); // pass the Calculator
}

//------------------------------------------------------------------------------

void Calculator_button::normalize()
{
	using c_ = My_calculator::constants;
	if (!is_normal()) {
		Graph_lib::Point m_xy{mask_position()};
		set_mask(m_xy.x - c_::disabled_sprite_sheet_offset_x,
		         m_xy.y - c_::disabled_sprite_sheet_offset_y,
		         My_calculator::constants::sprite_size,
		         My_calculator::constants::sprite_size);
	}
	shp_btn::Image_button::normalize();
}
void Calculator_button::disable()
{
	using c_ = My_calculator::constants;
	if (!is_disabled()) {
		Graph_lib::Point m_xy{mask_position()};
		set_mask(m_xy.x + c_::disabled_sprite_sheet_offset_x,
		         m_xy.y + c_::disabled_sprite_sheet_offset_y,
		         My_calculator::constants::sprite_size,
		         My_calculator::constants::sprite_size);
	}
	shp_btn::Image_button::disable();
}
