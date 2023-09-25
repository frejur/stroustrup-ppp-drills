#include "graph_box.h"

GraphBox::GraphBox(int x, int y, int w, int h, int g, int m, const char* file, const char* label, bool casc)
    : HelpView(Point{x, y}, w, h, label, 0), grd { g }, margin { m }, html_file { file }, cascade { casc }
{
    loc.x = margin + x * grd;
    loc.y = margin + y * grd;
    width = w * grd;
    height = h * grd;
}

void GraphBox::attach(Graph_lib::Window& win)
{
    for (int i = cascade ? 3 : 1; i > 0; --i) {
        float casc_offset = std::round(grd * 0.25) * (i-1);
        unique_ptr<Fl_Help_View> v =
            make_unique<Fl_Help_View>(
                loc.x - casc_offset, loc.y - casc_offset,
                width, height, label.c_str()
            );

        v->box(FL_BORDER_BOX);
        v->color(FL_BLACK);
        v->scrollbar_size(-1);
        v->load(html_file);

        if (i>1) {
            v->label(0);
            v->textsize(-1);
            casc_boxes.push_back(std::move(v));
            continue;
        }

        v->align(FL_ALIGN_TOP_LEFT);
        v->labelsize(round(grd * 0.7));
        v->labelfont(FL_HELVETICA_BOLD);
        v->textsize(round(grd * 0.65));
        v->textfont(FL_HELVETICA);
        pw = std::move(v);
    }
    own = &win;
}

Graph_lib::Point GraphBox::getBoundsPosition(float pos) {
    /* Retrieves position along the bounds of GraphBox:
     * - Input arg. pos is a ratio from 0.0 to 4.0
     * - Each side of the box is represented by a range:
     * 		- 0.0 to 1.0 Top
     * 		- 1.0 to 2.0 Right
     * 		- 2.0 to 3.0 Bottom
     * 		- 3.0 to 4.0 Left
     * The 'direction' or the ratios is clockwise.
     * Returns a Point with the resulting position */

    float w_r {0}, h_r {0};				  // Width/height
    int o_x { pw->x() }, o_y { pw->y() }; // Origin
    float diff = pos - std::floor(pos);   // Used to calc.
                                          //        ratio

    if (pos >= 2.0) diff = 1.0 - diff;
    if ((0.0 <= pos && pos < 1.0) ||
        (2.0 <= pos && pos < 3.0))
    {
        w_r = diff;
        h_r = (pos < 1.0) ? 0.0 : 1.0;
    } else {
        h_r = diff;
        w_r = (pos >= 3.0) ? 0.0 : 1.0;
    }

    if (cascade && (pos < 1.0 || pos >= 3.0)) {
        o_x = casc_boxes[0]->x();
        o_y = casc_boxes[0]->y();
    }

    return Graph_lib::Point{
        (int)std::round(o_x + w_r * pw->w()),
        (int)std::round(o_y + h_r * pw->h()) };
}
