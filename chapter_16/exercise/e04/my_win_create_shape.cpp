#include "../share/geo/regularpoly.h"
#include "my_win.h"

//------------------------------------------------------------------------------

const Graph_lib::Color& circle_color()
{
	static const Graph_lib::Color c{
	    Graph_lib::Color(fl_rgb_color(255, 240, 115))};
	return c;
}
const Graph_lib::Color& square_color()
{
	static const Graph_lib::Color c{
	    Graph_lib::Color(fl_rgb_color(220, 110, 165))};
	return c;
}
const Graph_lib::Color& hexagon_color()
{
	static const Graph_lib::Color c{
	    Graph_lib::Color(fl_rgb_color(135, 240, 255))};
	return c;
}
const Graph_lib::Color& triangle_color()
{
	static const Graph_lib::Color c{
	    Graph_lib::Color(fl_rgb_color(75, 210, 145))};
	return c;
}
const Graph_lib::Line_style& shape_style()
{
	static const Graph_lib::Line_style s{
	    Graph_lib::Line_style(Graph_lib::Line_style::solid, 5)};
	return s;
}

//------------------------------------------------------------------------------

void My_window::create_shape(Shape_type type)

{
	if (number_of_shapes() > max_num_shp) {
		clear_shapes();
		num_shp = 0;
	}

	switch (type) {
	case Shape_type::Circle:
		shp_v.push_back(new Graph_lib::Circle{new_shp_c, shp_r});
		shp_v[shp_v.size() - 1].set_color(circle_color());
		break;
	case Shape_type::Square: {
		int half_sz = static_cast<int>(
		    std::round(sqrt(((double) shp_r * shp_r) * 2) * 0.5));
		shp_v.push_back(new Graph_lib::Rectangle{{new_shp_c.x - half_sz,
		                                          new_shp_c.y - half_sz},
		                                         half_sz * 2,
		                                         half_sz * 2});
		shp_v[shp_v.size() - 1].set_color(square_color());
		break;
	}
	case Shape_type::Hexagon:
		shp_v.push_back(new RPOL::Regular_polygon{new_shp_c, shp_r, 6, 30});
		shp_v[shp_v.size() - 1].set_color(hexagon_color());
		break;
	case Shape_type::Triangle:
		shp_v.push_back(new RPOL::Regular_polygon{new_shp_c, shp_r, 3, 0});
		shp_v[shp_v.size() - 1].set_color(triangle_color());
		break;
	default:
		throw std::runtime_error("Shape not implemented");
		break;
	}
	shp_v[shp_v.size() - 1].set_style(shape_style());

	attach(shp_v[shp_v.size() - 1]);

	menu.hide();
	arrow.hide();

	++num_shp;
}
