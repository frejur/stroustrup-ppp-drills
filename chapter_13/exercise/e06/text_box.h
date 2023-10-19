#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include "../../lib/Graph.h"
#include <memory>
#include <utility>
#include <string>

namespace TBX { //--------------------------------------------------------------

namespace GL = Graph_lib;

class Text_box : public GL::Text
{
public:
	enum BG_shape { None, Box, Ellipse };
	Text_box(GL::Point xy, const string& text);
	Text_box(GL::Point xy, const string& text, BG_shape bg = BG_shape::None);
    void draw_lines() const;
private:
	static constexpr int default_font_size{ 18 };
	std::unique_ptr<GL::Lines> c_mark;
	std::unique_ptr<GL::Shape> bg_shape;
	std::pair<int, int> get_bbox_size() const;
	GL::Shape init_bg_shape(BG_shape bg);
};

} // end namespace TBX ---------------------------------------------------------
#endif // TEXT_BOX_H
