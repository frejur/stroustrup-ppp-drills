#ifndef ATTIRE_H
#define ATTIRE_H
#include "../../lib/Graph.h"
#include "../share/geo/isoscelestriangle.h"
#include "../share/geo/star.h"
#include "../share/img/image_cutout.h"
// #include "emoticons.h"
#include <string>

namespace emot {

class Emoticon;

//------------------------------------------------------------------------------

class Attire : public Graph_lib::Shape
{
public:
	virtual void draw_lines() const = 0;
};

class Hat : public Attire
{};

//------------------------------------------------------------------------------

Graph_lib::Point point_at_angle(Graph_lib::Point center,
                                double rotation,
                                double distance);

int val_from_f(int min_val, int max_val, double f);

void draw_mark(Graph_lib::Point xy,
               char c,
               Graph_lib::Font fnt = fl_font(),
               int fnt_sz = fl_size(),
               Graph_lib::Color color = Graph_lib::Color::black);

Graph_lib::Point shape_min_xy(const Graph_lib::Shape& s);

//------------------------------------------------------------------------------

class Conical_hat : public Hat
{
public:
	Conical_hat(Graph_lib::Point position,
	            int width,
	            int height,
	            double rotation = 0);
	Conical_hat(const emot::Emoticon& head,
	            double width_f,  // Ratio 0 - 1, from narrow to wide
	            double height_f, // Ratio 0 - 1, from flat to pointy
	            double rotation);
	void draw_lines() const;

protected:
	int w;
	int h;
	double rot;
	Graph_lib::Point base_pt;
	itri::IsoscelesTriangle cone;
};

//------------------------------------------------------------------------------

class Dunce_hat : public Conical_hat
{
public:
	Dunce_hat(Graph_lib::Point position, int width, double rotation = 0);
	Dunce_hat(const emot::Emoticon& head);
	void draw_lines() const;

private:
	char txt{'D'};
	int txt_sz;
};

//------------------------------------------------------------------------------

class Party_hat : public Conical_hat
{
public:
	Party_hat(Graph_lib::Point position,
	          int width,
	          const std::string& pattern_path,
	          double rotation = 0);
	Party_hat(const emot::Emoticon& head, const std::string& pattern_path);
	void draw_lines() const;

private:
	imgcut::Image_cutout pattern;
	stella::Star st;
};

} // namespace emot
#endif // ATTIRE_H
