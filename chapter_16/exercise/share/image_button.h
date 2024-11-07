#ifndef IMAGE_BUTTON_H
#define IMAGE_BUTTON_H

#include "shape_button.h"

namespace shp_btn {

class Filled_image : public Graph_lib::Image
{
public:
	Filled_image(Graph_lib::Point xy,
	             const Shape_button& parent_button,
	             std::string file_name,
	             Graph_lib::Suffix e = Graph_lib::Suffix::none)
	    : Graph_lib::Image(xy, file_name, e)
	    , parent_btn(parent_button){};
	virtual void draw_lines() const
	{
		if (fill_color().visibility()) {
			Graph_lib::Color ocol = fl_color();
			fl_color(fill_color().as_int());
			fl_rectf(parent_btn.position().x,
			         parent_btn.position().y,
			         parent_btn.width(),
			         parent_btn.height());
			fl_color(ocol.as_int());
		}
		Graph_lib::Image::draw_lines();
	};

private:
	const Shape_button& parent_btn;
};

class Image_button : public Shape_button
{
public:
	Image_button(Graph_lib::Point top_left,
	             int width,
	             int height,
	             const string& label,
	             Graph_lib::Callback callback_fn,
	             const std::string& image_path);
	Image_button(Graph_lib::Point top_left,
	             int normal_width,
	             int normal_height,
	             int active_width,
	             int active_height,
	             const string& label,
	             Graph_lib::Callback callback_fn,
	             const std::string& image_path);

	// Override Widget methods
	virtual void show() override;
	virtual void hide() override;
	virtual void move(int offs_x, int offs_y) override;
	virtual void attach(Graph_lib::Window&) override;

	virtual void put_on_top() override;

	virtual Graph_lib::Color fill_color() const override
	{
		return img.fill_color();
	};
	virtual void set_fill_color(Graph_lib::Color col) override
	{
		img.set_fill_color(col);
	};

	// Adjust image mask
	Graph_lib::Point mask_position() const { return {mask_x, mask_y}; }
	void set_mask(int x, int y, int width, int height);
	void offset_image(int offs_x, int offs_y);

private:
	int mask_x;
	int mask_y;
	int mask_w;
	int mask_h;
	Filled_image img; // Background image
};
} // namespace shp_btn

#endif // IMAGE_BUTTON_H
