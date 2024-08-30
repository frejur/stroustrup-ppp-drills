#ifndef ATTIRE_H
#define ATTIRE_H
#include "../../lib/Graph.h"
#include "emoticons.h"

namespace emot {

//------------------------------------------------------------------------------

class Attire : public Graph_lib::Shape
{
protected:
	virtual void draw_lines() const = 0;
};

class Hat : public Attire
{};

//------------------------------------------------------------------------------

class Dunce_hat : public Hat
{
public:
	Dunce_hat(Graph_lib::Point position, int width, double rotation = 0);
	Dunce_hat(const emot::Emoticon& head);

private:
	char txt{'D'};
	int txt_sz;
	int w;
	double rot;
	Graph_lib::Closed_polyline cone;

protected:
	void draw_lines() const;
};

} // namespace emot
#endif // ATTIRE_H
