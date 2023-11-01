#include "swatchgrid.h"
#include "../../lib/Graph.h"
#include <cmath>
#include <memory>
#define _USE_MATH_DEFINES
#include <math.h>
#include <FL/fl_draw.H>

using namespace SWGR;

SwatchGrid::SwatchGrid(
	Graph_lib::Point xxy, int ww, int hh, int num_x, int num_y, int pad
) : xy(xxy), w(ww), h(hh), sw_num_x(num_x), sw_num_y(num_y), pad_sz(pad)
{
	int pad_sz_total_x{ (sw_num_x + 1) * pad_sz };
	int pad_sz_total_y{ (sw_num_y + 1) * pad_sz };
	sw_sz_x = static_cast<int>((std::floor)((w - pad_sz_total_x) / num_x));
	sw_sz_y = static_cast<int>((std::floor)((h - pad_sz_total_y) / num_y));
	for (int col = 0; col < sw_num_x; ++col) {
		for (int row = 0; row < sw_num_y; ++row) {
			Graph_lib::Point p{
				xy.x + pad_sz * (col + 1) + col * sw_sz_x,
				xy.y + pad_sz * (row + 1) + row * sw_sz_y
			};
			swatches.push_back(
				std::make_unique<Graph_lib::Rectangle>(p, sw_sz_x, sw_sz_y)
			);
			swatches.back()->set_color(
				Graph_lib::Color::Transparency::invisible);
			swatches.back()->set_fill_color(Graph_lib::Color{ col * 16 + row });
		}
	}
}

void SwatchGrid::draw_lines() const
{
	for(const auto& sw : swatches) {
		sw->draw();
	}
}

RGB SwatchGrid::RGB_from_HSV(HSV hsv)
{
	int sextant;
	double fract, p, q, t;

	if (hsv.s <= 0) {
		return { hsv.v };
	}
	hsv.h =	(hsv.h == 360) ? 0 : hsv.h / 60;
	sextant = std::floor(hsv.h);
	fract = hsv.h - sextant;
	p = hsv.v * (1 - hsv.s);
	q = hsv.v * (1 - (hsv.s * fract));
	t = hsv.v * (1 - (hsv.s * (1 - fract)));
	if (sextant == 0) {
		return { hsv.v, t, p };
	}
	if (sextant == 1) {
		return { q, hsv.v, p };
	}
	if (sextant == 2) {
		return { p, hsv.v, t };
	}
	if (sextant == 3) {
		return { p, q, hsv.v };
	}
	if (sextant == 4) {
		return { t, p, hsv.v };
	}
	return { hsv.v, p, q };
}
