#ifndef REGULARHEXAGON_H
#define REGULARHEXAGON_H
#include "regularpoly.h"
#include <vector>

namespace RHEX {

class RegularHexagon : public RPOL::RegularPolygon
{
public:
	RegularHexagon(Graph_lib::Point xy, int radius, float angle = 0);
	void close_side(int n);
	void close_sides_before(int n);
	bool side_is_open(int n) const;
	void draw_lines() const;
	std::pair<int, int> get_bbox_size(const string &s) const;
	void set_font(Graph_lib::Font f) { fnt = f; }
	Graph_lib::Font font() const { return fnt; }
    void set_font_size(int s) { fnt_sz = s; }
    int font_size() const { return fnt_sz; }
    Graph_lib::Point point(int i) const {
    	return Shape::point((((6-i)%6) + 2)%6);
	}
private:
	Graph_lib::Font fnt{fl_font()};
    int fnt_sz{fl_size()<14?14:fl_size()};
	static constexpr int num_sides{ 6 };
	std::vector<bool> side_states;
};
} // namespace RHEX

#endif // REGULARHEXAGON_H
