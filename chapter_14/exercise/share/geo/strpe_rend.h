#ifndef STRIPED_RENDERER_H
#define STRIPED_RENDERER_H

#include "../../../lib/Graph.h"

namespace strpe_geo {

//------------------------------------------------------------------------------

constexpr int default_stripe_height{4};
constexpr int default_gap_height{2};
constexpr int default_stripe_color{static_cast<int>(Graph_lib::Color::cyan)};

//------------------------------------------------------------------------------

class Striped_shape_renderer
{
public:
	Striped_shape_renderer(int stripe_height,
	                       int gap_height,
	                       Graph_lib::Shape& shape,
	                       Graph_lib::Color color = default_stripe_color);

	void draw_stripes() const;
	void set_stripe_height(int height);
	void set_gap_height(int height);

	void set_color(Graph_lib::Color color) { col = color; };
	Graph_lib::Color color() const { return col; };

private:
	int strpe_h;
	int gap_h;
	Graph_lib::Color col;
	static int valid_strpe_h(int height, const std::string& name);

	virtual void draw_single_stripe(int row) const = 0;
	virtual int width() const = 0;
	virtual int height() const = 0;

protected:
	Graph_lib::Shape& shp;
};

//------------------------------------------------------------------------------

class Striped_rectangle_renderer : public Striped_shape_renderer
{
public:
	Striped_rectangle_renderer(int stripe_height,
	                           int gap_height,
	                           Graph_lib::Shape& rect,
	                           Graph_lib::Color color = default_stripe_color)
	    : Striped_shape_renderer(stripe_height, gap_height, rect, color){};

private:
	void draw_single_stripe(int row) const override;
	int width() const override;
	int height() const override;
};

} // namespace strpe_geo

#endif // STRIPED_RENDERER_H
