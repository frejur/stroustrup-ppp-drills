#include "image_cutout.h"
#include <stdexcept>

imgcut::Image_cutout::Image_cutout(Graph_lib::Point xy,
                                   std::string s,
                                   Graph_lib::Suffix e)
    : Graph_lib::Image(xy, s, e)
    , p_masked(nullptr)
    , offs_x(0)
    , offs_y(0)
{
	if (e == Graph_lib::Suffix::none) {
		e = Graph_lib::get_encoding(s);
	}

	if (e == Graph_lib::Suffix::gif) {
		fn.set_label("unsupported file type \"" + s + '"');
		p = new Graph_lib::Bad_image(30, 20); // the "error image"
	}
}
void imgcut::Image_cutout::set_poly_mask(const Graph_lib::Closed_polyline& pm,
                                         int offset_x,
                                         int offset_y)
{
	if (p->fail()) {
		return;
	}
	int npts = pm.number_of_points();
	if (npts < 2) {
		throw std::runtime_error(
		    "Invalid mask, expected a polyline with at least 3 points");
	}

	offs_x = offset_x;
	offs_y = offset_y;

	mask.clear();

	// Add mask points and record min. xy
	Graph_lib::Point min_xy{pm.point(0)};
	for (int i = 0; i < pm.number_of_points(); ++i) {
		Graph_lib::Point i_pt{pm.point(i)};
		mask.push_back(i_pt);
		if (i > 0) {
			if (i_pt.x < min_xy.x) {
				min_xy.x = i_pt.x;
			}
			if (i_pt.y < min_xy.y) {
				min_xy.y = i_pt.y;
			}
		}
	}

	// Offset mask points to align with image top left corner,
	//     (And add additional offset if any)
	for (Graph_lib::Point& pt : mask) {
		pt.x -= min_xy.x - offset_x;
		pt.y -= min_xy.y - offset_y;
	}

	int img_w = p->w();
	int img_h = p->h();

	unsigned char* rgba_data = new unsigned char[img_w * img_h * 4];
	const unsigned char* raw_data = reinterpret_cast<const unsigned char*>(
	    p->data()[0]);

	for (int y = 0; y < img_h; ++y) {
		for (int x = 0; x < img_w; ++x) {
			int index_rgb = (y * img_w + x) * 3;
			int index_rgba = (y * img_w + x) * 4;

			rgba_data[index_rgba] = raw_data[index_rgb];
			rgba_data[index_rgba + 1] = raw_data[index_rgb + 1];
			rgba_data[index_rgba + 2] = raw_data[index_rgb + 2];

			if (!is_inside_polygon(x, y, mask)) {
				rgba_data[index_rgba + 3] = 0;
			} else {
				rgba_data[index_rgba + 3] = 255;
			}
		}
	}

	if (p_masked) {
		delete p_masked;
	}

	p_masked = new Fl_RGB_Image(rgba_data, img_w, img_h, 4);
}

void imgcut::Image_cutout::draw_lines() const
{
	if (fn.label() != "") {
		fn.draw_lines();
	}

	if (mask.empty()) {
		p->draw(point(0).x, point(0).y);
	} else {
		p_masked->draw(point(0).x - offs_x, point(0).y - offs_y);
	}
}

//------------------------------------------------------------------------------

bool imgcut::is_inside_polygon(int x,
                               int y,
                               const std::vector<Graph_lib::Point>& polygon)
{
	int n = polygon.size();
	bool inside = false;
	for (int i = 0, j = n - 1; i < n; j = i++) {
		int xi = polygon[i].x, yi = polygon[i].y;
		int xj = polygon[j].x, yj = polygon[j].y;

		bool intersect = ((yi > y) != (yj > y))
		                 && (x < (xj - xi) * (y - yi) / (yj - yi) + xi);
		if (intersect) {
			inside = !inside;
		}
	}
	return inside;
}
