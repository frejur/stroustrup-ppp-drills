#ifndef PNP_H
#define PNP_H
#include "../share/geo/pac.h"

namespace ch14_e10 {

class Pac_and_pills : public Graph_lib::Shape
{
public:
	using GLP = Graph_lib::Point;
	using GLC = Graph_lib::Color;
	Pac_and_pills(GLP start_pos,
	              int radius,
	              int jaw_state,
	              pac::Pacman_dir direction,
	              GLC pacman_color,
	              GLC color);
	;
	void move(int offset_x, int offset_y) override;
	int number_of_pills() const { return pills.number_of_elements(); };
	void move_pacman(int offs_x, int offs_y) { pac.move(offs_x, offs_y); };
	void set_pacman_direction(pac::Pacman_dir ndir) { pac.set_direction(ndir); }
	void set_jaw_state(float jaw_state) { pac.set_jaw_state(jaw_state); };
	float jaw_state() const { return pac.jaw_state(); }

	GLP pacman_position() const { return pac.center(); };
	GLP pill_position(int idx) const { return pills.center(idx); };

	void hide_pill(int idx) { pills.set_fill_color(GLC::invisible, idx); };
	void reset();
	void reset_colors();

	void draw_lines() const override;
	void add_pill(Graph_lib::Point pos);
	GLP direction_vector() const;
	void attach_pacman() { pac_attached = true; };
	void detach_pacman() { pac_attached = false; };
	bool pacman_is_attached() { return pac_attached; };

private:
	Graph_lib::Point start_p;
	float start_jaw;
	pac::Pacman_dir start_dir;
	bool pac_attached;
	pac::Pacman pac;
	pac::Pills pills;
};
} // namespace ch14_e10

#endif // PNP_H
