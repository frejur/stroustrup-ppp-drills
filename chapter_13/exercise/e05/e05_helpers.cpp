#include "e05_helpers.h"
#include <map>
#include <utility>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

using HLP = E05::ConnectionPointHelper;

enum class HLP::PtID {
	NW, N, NE,
	W, C, E,
	SW, S, SE
};

const std::map<HLP::PtID, double> HLP::dir_angle {
	{HLP::PtID::NW, -135.0},
	{HLP::PtID::N,  -90.0},
	{HLP::PtID::NE, -45.0},
	{HLP::PtID::E,  0.0},
	{HLP::PtID::SE,  45.0},
	{HLP::PtID::S, 90.0},
	{HLP::PtID::SW,  135.0},
	{HLP::PtID::W, 180.0},
	{HLP::PtID::C,  0.0}
};

Graph_lib::Point HLP::get(const Graph_lib::Ellipse& e, HLP::PtID id)
{
	if (id == HLP::PtID::C)
	{
		return e.center();
	}
	double angle{ dir_angle.find(id)->second };
	double len{ 0 };

	if (e.major()==e.minor())
	{
		len = e.major();
		angle *= M_PI / 180;
	}
	else if (static_cast<int>(angle)%90 == 0)
	{
		len = (static_cast<int>(angle)%180 == 0) ? e.major() : e.minor();
		angle *= M_PI / 180;
	}
	else
	{
		double angle_add{ std::atan((e.minor()*0.5) / (e.major()*0.5)) };
		angle -= 45;
		if (static_cast<int>(angle)%180 == 0) {
			angle = angle * M_PI / 180 + angle_add;
		} else {
			angle = angle * M_PI / 180 + (M_PI / 2 - angle_add);
		}
		len = (
			(e.major() * e.minor()) /
			sqrt(
				e.major()*e.major() * std::sin(angle)*std::sin(angle) +
				e.minor()*e.minor() * std::cos(angle)*std::cos(angle)
			)
		);
	}
	return(
		GL::Point{
			static_cast<int>(round(e.center().x + len * std::cos(angle))),
			static_cast<int>(round(e.center().y + len * std::sin(angle)))
		}
	);
}

Graph_lib::Point HLP::get(const Graph_lib::Circle& c, HLP::PtID id)
{
	if (id == HLP::PtID::C)
	{
		return c.center();
	}
	double angle = dir_angle.find(id)->second * (M_PI / 180);
	return(
		GL::Point{
			static_cast<int>(
				round(c.center().x + c.radius() * std::cos(angle))),
			static_cast<int>(
				round(c.center().y + c.radius() * std::sin(angle)))
		}
	);
}

HLP::ConnectionPointHelper() {}; // No initialization

Graph_lib::Point E05::nw(const Graph_lib::Ellipse& r)
{
	return HLP::get(r, HLP::PtID::NW);
}
Graph_lib::Point E05::n(const Graph_lib::Ellipse& r)
{
	return HLP::get(r, HLP::PtID::N);
}
Graph_lib::Point E05::ne(const Graph_lib::Ellipse& r)
{
	return HLP::get(r, HLP::PtID::NE);
}
Graph_lib::Point E05::w(const Graph_lib::Ellipse& r) {
	return HLP::get(r, HLP::PtID::W);
}
Graph_lib::Point E05::center(const Graph_lib::Ellipse& r)
{
	return HLP::get(r, HLP::PtID::C);
}
Graph_lib::Point E05::e(const Graph_lib::Ellipse& r)
{
	return HLP::get(r, HLP::PtID::E);
}
Graph_lib::Point E05::sw(const Graph_lib::Ellipse& r)
{
	return HLP::get(r, HLP::PtID::SW);
}
Graph_lib::Point E05::s(const Graph_lib::Ellipse& r)
{
	return HLP::get(r, HLP::PtID::S);
}
Graph_lib::Point E05::se(const Graph_lib::Ellipse& r)
{
	return HLP::get(r, HLP::PtID::SE);
}

Graph_lib::Point E05::nw(const Graph_lib::Circle& r)
{
	return HLP::get(r, HLP::PtID::NW);
}
Graph_lib::Point E05::n(const Graph_lib::Circle& r)
{
	return HLP::get(r, HLP::PtID::N);
}
Graph_lib::Point E05::ne(const Graph_lib::Circle& r)
{
	return HLP::get(r, HLP::PtID::NE);
}
Graph_lib::Point E05::w(const Graph_lib::Circle& r) {
	return HLP::get(r, HLP::PtID::W);
}
Graph_lib::Point E05::center(const Graph_lib::Circle& r)
{
	return HLP::get(r, HLP::PtID::C);
}
Graph_lib::Point E05::e(const Graph_lib::Circle& r)
{
	return HLP::get(r, HLP::PtID::E);
}
Graph_lib::Point E05::sw(const Graph_lib::Circle& r)
{
	return HLP::get(r, HLP::PtID::SW);
}
Graph_lib::Point E05::s(const Graph_lib::Circle& r)
{
	return HLP::get(r, HLP::PtID::S);
}
Graph_lib::Point E05::se(const Graph_lib::Circle& r)
{
	return HLP::get(r, HLP::PtID::SE);
}
