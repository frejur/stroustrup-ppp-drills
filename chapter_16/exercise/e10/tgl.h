#ifndef TGL_H
#define TGL_H
#include "../share/shape_button.h"

// -----------------------------------------------------------------------------
// A Shape_button that can be toggled on/off, with visuals that reflect
// its current state.
//
// Uses the pre-existing 'activate()' and 'normalize()' methods to switch
// between different visual modes.
//
// Stores its internal On / Off state in a simple boolean variable.
// -----------------------------------------------------------------------------

class Toggle : public shp_btn::Shape_button
{
public:
	Toggle(Graph_lib::Point top_left,
	       int width,
	       int height,
	       Graph_lib::Callback callback_fn,
	       Graph_lib::Color active_bg_color);

	// Control State
	void toggle();
	void turn_on();
	void turn_off();
	bool is_on() const { return is_on_; }

protected:
	// Update visuals depending on State
	virtual void activate() override;
	virtual void normalize() override;

public:
	// General widget overrides
	virtual void move(int offs_x, int offs_y) override;
	virtual void hide() override;
	virtual void show() override;
	virtual void attach(Graph_lib::Window&) override;

	// Visuals
	virtual void set_fill_color(Graph_lib::Color col) override;
	void set_inactive_fill_color(Graph_lib::Color col);
	void set_square_color(Graph_lib::Color col);
	Graph_lib::Color inactive_fill_color() const { return off_fill; }
	Graph_lib::Color square_color() const { return tgl_square.fill_color(); }

private:
	bool is_on_;

protected:
	Graph_lib::Color on_fill;
	Graph_lib::Color off_fill;
	Graph_lib::Rectangle tgl_square;
};

#endif // TGL_H
