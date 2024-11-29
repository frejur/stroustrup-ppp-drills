#include "pickup.h"

namespace {
constexpr int minimum_size{16};
constexpr int maximum_size{256};
const Pickup::Direction default_direction{Pickup::Direction::N};
const std::string& image_file_path()
{
	static const std::string p{"img_e07/pkup_sprt.png"};
	return p;
}
} // namespace

//------------------------------------------------------------------------------

Pickup::Pickup(Graph_lib::Point center, int size)
    : Graph_lib::Image(center, image_file_path())
    , spr_sz(valid_sz(size))
    , bbox_sz(spr_sz)
    , dir(default_direction)
{
	Graph_lib::Image::move(-spr_sz / 2, -spr_sz / 2); // Move to center
	upd_spr_sheet(dir);
}

//------------------------------------------------------------------------------

void Pickup::set_direction(Direction d)
{
	if (d == dir) {
		return;
	}

	dir = d;
	upd_spr_sheet(d);
}

void Pickup::upd_spr_sheet(Direction d)
{
	Graph_lib::Point xy{};
	switch (d) {
	case Direction::NW:
		xy = {0, 0};
		break;
	case Direction::N:
		xy = {size(), 0};
		break;
	case Direction::NE:
		xy = {size() * 2, 0};
		break;
	case Direction::E:
		xy = {size() * 2, size()};
		break;
	case Direction::SE:
		xy = {size() * 2, size() * 2};
		break;
	case Direction::S:
		xy = {size(), size() * 2};
		break;
	case Direction::SW:
		xy = {0, size() * 2};
		break;
	case Direction::W:
		xy = {0, size()};
		break;
	}
	Graph_lib::Image::set_mask(xy, size(), size());
}

//------------------------------------------------------------------------------

int Pickup::valid_sz(int sz) const
{
	if (sz < minimum_size || sz > maximum_size) {
		throw std::runtime_error("Invalid sprite size, expected a value "
		                         "between: "
		                         + std::to_string(minimum_size) + " and "
		                         + std::to_string(maximum_size) + " , but got "
		                         + std::to_string(sz));
	}
	return sz;
}

int Pickup::valid_bbox_sz(int sz) const
{
	if (sz < minimum_size || sz > maximum_size) {
		throw std::runtime_error("Invalid bbox size, expected a value "
		                         "between: "
		                         + std::to_string(minimum_size) + " and "
		                         + std::to_string(maximum_size) + " , but got "
		                         + std::to_string(sz));
	}
	return sz;
}
