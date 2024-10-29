#ifndef CLOCK_FACE_H
#define CLOCK_FACE_H
#include "../../lib/Graph.h"

class Clock_face : public Graph_lib::Shape
{
public:
	Clock_face(Graph_lib::Point center, int radius);
	void draw_lines() const override;

	Graph_lib::Point center() const { return point(0); };
	int radius() const { return r; };

	void set_font(Graph_lib::Font f) { fnt = f; }
	Graph_lib::Font font() const { return fnt; }

	void set_font_size(int s) { fsz = s; }
	int font_size() const { return fsz; }

private:
	int r;
	int fsz;
	Graph_lib::Font fnt{0};

	static int notch_min_len;
	static int notch_hour_len;

	int valid_r(int r) const;
};

#endif // CLOCK_FACE_H
