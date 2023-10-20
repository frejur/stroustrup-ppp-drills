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
	enum BG_shape { BG_NONE, BG_BOX, BG_ELLIPSE };
	Text_box(GL::Point xy, const string& text, BG_shape bg = BG_NONE);
    void draw_lines() const;
private:
	static constexpr int default_font_size{ 18 };
	static constexpr int default_font_face{ FL_SCREEN };
	std::unique_ptr<GL::Lines> c_mark;
	std::unique_ptr<GL::Shape> bg_shape;
	std::pair<int, int> get_bbox_size() const;
	std::unique_ptr<GL::Shape> init_bg_shape(BG_shape bg, int w, int h);
};

} // end namespace TBX ---------------------------------------------------------
#endif // TEXT_BOX_H
