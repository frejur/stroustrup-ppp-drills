#ifndef IMAGE_BUTTON_H
#define IMAGE_BUTTON_H

#include "shape_button.h"

namespace shp_btn {

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

	// Adjust image mask
	void set_mask(int x, int y, int width, int height);
	void offset_image(int offs_x, int offs_y);

private:
	int mask_x;
	int mask_y;
	int mask_w;
	int mask_h;
	Graph_lib::Image img; // Background image
};
} // namespace shp_btn

#endif // IMAGE_BUTTON_H
