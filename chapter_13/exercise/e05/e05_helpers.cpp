#include "e05_helpers.h"
#include <map>
#include <utility>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

using HLP = E05::ConnectionPointHelper;
namespace GL = Graph_lib;

enum class HLP::PtID {
	NW, N, NE,
	W, C, E,
	SW, S, SE
};

const std::map<HLP::PtID, double> HLP::dir_angle {
	{HLP::PtID::NW, -135.0},
	{HLP::PtID::N,  -90.0},
	{HLP::PtID::NE, -45.0},
	{HLP::PtID::E, 0.0},
	{HLP::PtID::SE, 45.0},
	{HLP::PtID::S, 90.0},
	{HLP::PtID::SW, 135.0},
	{HLP::PtID::W, 180.0},
	{HLP::PtID::C,  0.0}
};

const GL::Point getPerimeterPoint(const GL::Ellipse& e, double rad_x,
	double rad_y, double ang
) {
	return(
		GL::Point{
			static_cast<int>(round(e.center().x + rad_x * std::cos(ang))),
			static_cast<int>(round(e.center().y + rad_y * std::sin(ang)))
		}
	);
}

GL::Point HLP::get(const GL::Ellipse& e, HLP::PtID id)
{
	if (id == HLP::PtID::C)
	{
		return e.center();
	}
	double angle{ dir_angle.find(id)->second };
	int angle_i { static_cast<int>(angle) };
	double angle_radians{ angle * (M_PI / 180) };
	double len_x{ static_cast<double>(e.major()) };
	double len_y{ static_cast<double>(e.minor()) };

	if (len_x != len_y && (angle_i%90) != 0.0) {
		double parametric_angle{
			std::atan(len_x / len_y * std::tan(angle_radians))
		};
		if (angle_i%135) {
			parametric_angle += M_PI;
		}
		double average_angle{ (angle_radians + parametric_angle) * 0.5 };
		return getPerimeterPoint(e, len_x, len_y, parametric_angle);
	}
	return getPerimeterPoint(e, len_x, len_y, angle_radians);
}

GL::Point HLP::get(const GL::Circle& c, HLP::PtID id)
{
	if (id == HLP::PtID::C)
	{
		return c.center();
	}
	double angle_radians = dir_angle.find(id)->second * (M_PI / 180);
	return(
		GL::Point{
			static_cast<int>(
				round(c.center().x + c.radius() * std::cos(angle_radians))),
			static_cast<int>(
				round(c.center().y + c.radius() * std::sin(angle_radians)))
		}
	);
}

HLP::ConnectionPointHelper() {}; // No initialization

GL::Point E05::nw(const GL::Ellipse& r)
{
	return HLP::get(r, HLP::PtID::NW);
}
GL::Point E05::n(const GL::Ellipse& r)
{
	return HLP::get(r, HLP::PtID::N);
}
GL::Point E05::ne(const GL::Ellipse& r)
{
	return HLP::get(r, HLP::PtID::NE);
}
GL::Point E05::w(const GL::Ellipse& r) {
	return HLP::get(r, HLP::PtID::W);
}
GL::Point E05::center(const GL::Ellipse& r)
{
	return HLP::get(r, HLP::PtID::C);
}
GL::Point E05::e(const GL::Ellipse& r)
{
	return HLP::get(r, HLP::PtID::E);
}
GL::Point E05::sw(const GL::Ellipse& r)
{
	return HLP::get(r, HLP::PtID::SW);
}
GL::Point E05::s(const GL::Ellipse& r)
{
	return HLP::get(r, HLP::PtID::S);
}
GL::Point E05::se(const GL::Ellipse& r)
{
	return HLP::get(r, HLP::PtID::SE);
}

GL::Point E05::nw(const GL::Circle& r)
{
	return HLP::get(r, HLP::PtID::NW);
}
GL::Point E05::n(const GL::Circle& r)
{
	return HLP::get(r, HLP::PtID::N);
}
GL::Point E05::ne(const GL::Circle& r)
{
	return HLP::get(r, HLP::PtID::NE);
}
GL::Point E05::w(const GL::Circle& r) {
	return HLP::get(r, HLP::PtID::W);
}
GL::Point E05::center(const GL::Circle& r)
{
	return HLP::get(r, HLP::PtID::C);
}
GL::Point E05::e(const GL::Circle& r)
{
	return HLP::get(r, HLP::PtID::E);
}
GL::Point E05::sw(const GL::Circle& r)
{
	return HLP::get(r, HLP::PtID::SW);
}
GL::Point E05::s(const GL::Circle& r)
{
	return HLP::get(r, HLP::PtID::S);
}
GL::Point E05::se(const GL::Circle& r)
{
	return HLP::get(r, HLP::PtID::SE);
}
