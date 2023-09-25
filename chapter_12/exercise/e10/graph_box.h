#ifndef GRAPH_BOX_H
#define GRAPH_BOX_H
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Help_View.H>
#include "../../lib/Simple_window.h"
#include <memory>
#include <vector>

class HelpView {
public:
    HelpView(Point xy, int w, int h, const string& s, Callback cb)
        : loc(xy), width(w), height(h), label(s), do_it(cb)
    {}

    virtual ~HelpView() { }

    virtual void move(int dx,int dy) { hide(); pw->position(loc.x+=dx, loc.y+=dy); show(); }
    virtual void hide() { pw->hide(); }
    virtual void show() { pw->show(); }
    virtual void attach(Graph_lib::Window&) = 0;

    Point loc;
    int width;
    int height;
    string label;
    Callback do_it;

protected:
    Graph_lib::Window* own;    // every Widget belongs to a Window
    unique_ptr<Fl_Help_View> pw;  // connection to the FLTK Widget

};

class GraphBox : public HelpView {
public:
    GraphBox(int x, int y, int w, int h, int grd, int margin, const char* html_file, const char* label, bool cascade = false);
    void attach(Graph_lib::Window& win);
    Graph_lib::Point getBoundsPosition(float pos);
private:
    vector<unique_ptr<Fl_Help_View>> casc_boxes {};
    int grd;
    int margin;
    const char* html_file;
    bool cascade;
};

#endif // GRAPH_BOX_H
