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
    void set_bg_shape_color(GL::Color);
    void set_fill_color(GL::Color);
    void set_color(GL::Color);
    void set_style(GL::Line_style);
    BG_shape shape_type() const { return bg_type; };
    GL::Point center() const { return { c.x, c.y - h_nudge}; };
    GL::Point bbox_origin() const;
    int width() const;
    int height() const;
    int corner_radius() const;
    GL::Point bbox_point(int p) const;
private:
	int text_w;
	int text_h;
	int h_nudge;
	GL::Point c;
	BG_shape bg_type;
	static constexpr int default_font_size{ 16 };
	static constexpr int default_font_face{ FL_HELVETICA_BOLD };
	static constexpr int default_font_color{ FL_BLACK };
	std::unique_ptr<GL::Lines> c_mark;
	std::unique_ptr<GL::Shape> bg_shape;
	std::pair<int, int> get_bbox_size(const string& s="") const;
	std::unique_ptr<GL::Shape> init_bg_shape(BG_shape bg, int w, int h);
};

} // end namespace TBX ---------------------------------------------------------
#endif // TEXT_BOX_H
